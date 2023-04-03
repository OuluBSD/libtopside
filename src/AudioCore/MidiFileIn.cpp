#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

MidiFileIn::MidiFileIn( String file_name ) {
	file_.Open( file_name.Begin() );

	if ( !file_ ) {
		LOG("MidiFileIn: error opening or finding file (" <<  file_name << ").");
		HandleError( AudioError::FILE_NOT_FOUND );
	}

	char chunkType[4];
	char buffer[4];
	SINT32* size;

	if ( !file_.Get( chunkType, 4 ) ) goto error;

	if ( !file_.Get( buffer, 4 ) ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&buffer);
	#endif
	size = (SINT32*) &buffer;

	if ( strncmp( chunkType, "MThd", 4 ) || ( *size != 6 ) ) {
		LOG("MidiFileIn: file (" <<  file_name << ") does not appear to be a MIDI file!");
		HandleError( AudioError::FILE_UNKNOWN_FORMAT );
	}

	SINT16* data;

	if ( !file_.Get( buffer, 2 ) ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&buffer);
	#endif
	data = (SINT16*) &buffer;

	if ( *data < 0 || *data > 2 ) {
		LOG("MidiFileIn: the file (" <<  file_name << ") format is invalid!");
		HandleError( AudioError::FILE_ERROR );
	}

	format_ = *data;

	if ( !file_.Get( buffer, 2 ) ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&buffer);
	#endif

	if ( format_ == 0 && *data != 1 ) {
		LOG("MidiFileIn: invalid number of tracks (>1) for a file format = 0!");
		HandleError( AudioError::FILE_ERROR );
	}

	nTracks_ = *data;

	if ( !file_.Get( buffer, 2 ) ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&buffer);
	#endif
	division_ = (int) * data;
	float tickrate;
	usingTimeCode_ = false;

	if ( *data & 0x8000 ) {
		tickrate = (float) - (*data & 0x7F00);

		if ( tickrate == 29.0f ) tickrate = 29.97;

		tickrate *= (*data & 0x00FF);
		usingTimeCode_ = true;
	}
	else
		tickrate = (float) (*data & 0x7FFF);

	int i;

	for ( i = 0; i < nTracks_; i++ ) {
		if ( !file_.Get( chunkType, 4 ) ) goto error;

		if ( strncmp( chunkType, "MTrk", 4 ) ) goto error;

		if ( !file_.Get( buffer, 4 ) ) goto error;

		#ifdef __LITTLE_ENDIAN__
		Swap32((unsigned char*)&buffer);
		#endif
		size = (SINT32*) &buffer;
		trackLengths_.Add( *size );
		trackOffsets_.Add( (long) file_. GetSize() );
		trackPointers_.Add( (long) file_.GetSize() );
		trackStatus_.Add( 0 );
		file_.SeekCur( *size );

		if ( usingTimeCode_ ) tickSeconds_.Add( (float) (1.0f / tickrate) );
		else tickSeconds_.Add( (float) (0.5f / tickrate) );
	}

	TempoChange tempoEvent;
	tempoEvent.count = 0;
	tempoEvent.tickSeconds = tickSeconds_[0];
	tempoEvents_.Add( tempoEvent );

	if ( format_ == 1 && !usingTimeCode_ ) {
		Vector<unsigned char> event;
		int value, count;
		usingTimeCode_ = true;
		count = GetNextEvent( &event, 0 );

		while ( event.GetCount() ) {
			if ( ( event.GetCount() == 6 ) && ( event[0] == 0xff ) &&
				 ( event[1] == 0x51 ) && ( event[2] == 0x03 ) ) {
				tempoEvent.count = count;
				value = ( event[3] << 16 ) + ( event[4] << 8 ) + event[5];
				tempoEvent.tickSeconds = (float) (0.000001 * value / tickrate);

				if ( count > tempoEvents_.Top().count )
					tempoEvents_.Add( tempoEvent );
				else
					tempoEvents_.Top() = tempoEvent;
			}

			count += GetNextEvent( &event, 0 );
		}

		RewindTrack( 0 );

		for ( int i = 0; i < nTracks_; i++ ) {
			trackCounters_.Add( 0 );
			trackTempoIndex_.Add( 0 );
		}

		usingTimeCode_ = false;
	}

	return;
error:
	LOG("MidiFileIn: error reading from file (" <<  file_name << ").");
	HandleError( AudioError::FILE_ERROR );
}

MidiFileIn::~MidiFileIn() {
	file_.Close();
}

void MidiFileIn::RewindTrack( int track ) {
	if ( track >= nTracks_ ) {
		LOG("MidiFileIn::GetNextEvent: invalid track argument (" <<  track << ").");
		HandleError( AudioError::WARNING );
		return;
	}

	trackPointers_[track] = trackOffsets_[track];
	trackStatus_[track] = 0;
	tickSeconds_[track] = tempoEvents_[0].tickSeconds;
}

float MidiFileIn::GetTickSeconds( int track ) {
	if ( track >= nTracks_ ) {
		LOG("MidiFileIn::GetTickSeconds: invalid track argument (" <<  track << ").");
		HandleError( AudioError::WARNING );
		return 0.0f;
	}

	return tickSeconds_[track];
}

int MidiFileIn::GetNextEvent( Vector<unsigned char>* event, int track ) {
	event->Clear();

	if ( track >= nTracks_ ) {
		LOG("MidiFileIn::GetNextEvent: invalid track argument (" <<  track << ").");
		HandleError( AudioError::WARNING );
		return 0;
	}

	if ( (trackPointers_[track] - trackOffsets_[track]) >= trackLengths_[track] )
		return 0;

	int ticks = 0, bytes = 0;
	bool isTempoEvent = false;
	file_.Seek( trackPointers_[track] );

	if ( !GetVariableLength( &ticks ) ) goto error;

	unsigned char c;

	if ( !file_.Get( (char*)&c, 1 ) ) goto error;

	switch ( c ) {
	case 0xFF:
		int position;
		trackStatus_[track] = 0;
		event->push_back( c );

		if ( !file_.Get( (char*)&c, 1 ) ) goto error;

		event->push_back( c );

		if ( format_ != 1 && ( c == 0x51 ) ) isTempoEvent = true;

		position = (int)file_.GetSize();

		if ( !GetVariableLength( &bytes ) ) goto error;

		bytes += ( (int)file_.GetSize() - position );
		file_.Seek( position );
		break;

	case 0xF0:
	case 0xF7:
		trackStatus_[track] = 0;
		event->push_back( c );
		position = (int)file_.GetSize();

		if ( !GetVariableLength( &bytes ) ) goto error;

		bytes += ( (int)file_.GetSize() - position );
		file_.Seek( position );
		break;

	default:
		if ( c & 0x80 ) {
			if ( c > 0xF0 ) goto error;

			trackStatus_[track] = c;
			event->push_back( c );
			c &= 0xF0;

			if ( (c == 0xC0) || (c == 0xD0) ) bytes = 1;
			else bytes = 2;
		}
		else if ( trackStatus_[track] & 0x80 ) {
			event->push_back( trackStatus_[track] );
			event->push_back( c );
			c = trackStatus_[track] & 0xF0;

			if ( (c != 0xC0) && (c != 0xD0) ) bytes = 1;
		}
		else goto error;
	}

	int i;

	for ( i = 0; i < bytes; i++ ) {
		if ( !file_.Get( (char*)&c, 1 ) ) goto error;

		event->push_back( c );
	}

	if ( !usingTimeCode_ ) {
		if ( isTempoEvent ) {
			float tickrate = (float) (division_ & 0x7FFF);
			int value = ( event->At(3) << 16 ) + ( event->At(4) << 8 ) + event->At(5);
			tickSeconds_[track] = (float) (0.000001 * value / tickrate);
		}

		if ( format_ == 1 ) {
			trackCounters_[track] += ticks;
			TempoChange tempoEvent = tempoEvents_[ trackTempoIndex_[track] ];

			if ( trackCounters_[track] >= tempoEvent.count && trackTempoIndex_[track] < tempoEvents_.GetCount() - 1 ) {
				trackTempoIndex_[track]++;
				tickSeconds_[track] = tempoEvent.tickSeconds;
			}
		}
	}

	trackPointers_[track] = (long)file_.GetSize();
	return ticks;
error:
	LOG("MidiFileIn::GetNextEvent: file read error!");
	HandleError( AudioError::FILE_ERROR );
	return 0;
}

int MidiFileIn::GetNextMidiEvent( Vector<unsigned char>* midiEvent, int track ) {
	if ( track >= nTracks_ ) {
		LOG("MidiFileIn::GetNextMidiEvent: invalid track argument (" <<  track << ").");
		HandleError( AudioError::WARNING );
		return 0;
	}

	int ticks = GetNextEvent( midiEvent, track );

	while ( midiEvent->GetCount() && ( midiEvent->At(0) >= 0xF0 ) )
		ticks = GetNextEvent( midiEvent, track );

	return ticks;
}

bool MidiFileIn::GetVariableLength( int* value ) {
	*value = 0;
	char c;

	if ( !file_.Get( &c, 1 ) ) return false;

	*value = (int) c;

	if ( *value & 0x80 ) {
		*value &= 0x7f;

		do {
			if ( !file_.Get( &c, 1 ) ) return false;

			*value = ( *value << 7 ) + ( c & 0x7f );
		}
		while ( c & 0x80 );
	}

	return true;
}

NAMESPACE_AUDIO_END
