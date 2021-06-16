#include "MidiFile.h"


NAMESPACE_MIDI_BEGIN

//////////////////////////////
//
// File::File -- Constuctor.
//

File::File() {
	ticks_per_quarter_note = 120;            // TPQ time base of file
	track_count = 1;                       // # of tracks in file
	the_track_state = TRACK_STATE_SPLIT;    // joined or split
	the_time_state = TIME_STATE_ABSOLUTE;   // absolute or delta
	events.SetCount(1);
	timemap.Clear();
	timemapvalid = 0;
	rwstatus = 1;
}

File::File(String filename) {
	ticks_per_quarter_note = 120;            // TQP time base of file
	track_count = 1;                       // # of tracks in file
	the_track_state = TRACK_STATE_SPLIT;    // joined or split
	the_time_state = TIME_STATE_ABSOLUTE;   // absolute or delta
	events.SetCount(1);
	Read(filename);
	timemap.Clear();
	timemapvalid = 0;
	rwstatus = 1;
}


File::File(Stream& input) {
	ticks_per_quarter_note = 120;            // TQP time base of file
	track_count = 1;                       // # of tracks in file
	the_track_state = TRACK_STATE_SPLIT;    // joined or split
	the_time_state = TIME_STATE_ABSOLUTE;   // absolute or delta
	events.SetCount(1);
	Read(input);
	timemap.Clear();
	timemapvalid = 0;
	rwstatus = 1;
}

bool File::Open(String file) {
	Clear();
	ticks_per_quarter_note = 120;            // TQP time base of file
	track_count = 1;                       // # of tracks in file
	the_track_state = TRACK_STATE_SPLIT;    // joined or split
	the_time_state = TIME_STATE_ABSOLUTE;   // absolute or delta
	events.SetCount(1);
	if (Read(file) <= 0)
		return false;
	timemap.Clear();
	timemapvalid = 0;
	rwstatus = 1;
	return true;
}


//////////////////////////////
//
// File::File(File&) -- Copy constructor.
//

File::File(const File& other) {
	events <<= other.events;
	
	ticks_per_quarter_note = other.ticks_per_quarter_note;
	track_count = other.track_count;
	the_track_state = other.the_track_state;
	the_time_state = other.the_time_state;
	read_file_name = other.read_file_name;
	
	timemapvalid = other.timemapvalid;
	timemap <<= other.timemap;
	rwstatus = other.rwstatus;
}



//////////////////////////////
//
// File::File(File&&) -- Move constructor.
//

File::File(File && other) : events(std::move(other.events)) {
	other.events.Clear();
	other.events.Add();
	
	ticks_per_quarter_note = other.ticks_per_quarter_note;
	track_count = other.track_count;
	the_track_state = other.the_track_state;
	the_time_state = other.the_time_state;
	read_file_name = other.read_file_name;
	
	timemapvalid = other.timemapvalid;
	timemap <<= other.timemap;
	rwstatus = other.rwstatus;
}



//////////////////////////////
//
// File::~File -- Deconstructor.
//

File::~File() {
	events.Clear();
	
	rwstatus = 0;
	timemap.Clear();
	timemapvalid = 0;
}


///////////////////////////////////////////////////////////////////////////
//
// reading/writing functions --
//

//////////////////////////////
//
// File::read -- Parse a Standard MIDI File and store its contents
//      in the object.
//

int File::Read(String filename) {
	timemapvalid = 0;
	SetFilename(filename);
	rwstatus = 1;
	
	FileIn input;
	input.Open(filename);
	
	if (!input.IsOpen()) {
		return 0;
	}
	
	rwstatus = File::Read(input);
	
	return rwstatus;
}


//
// istream version of Read().
//

int File::Read(Stream& input) {
	rwstatus = 1;
	
	if (input.Peek() != 'M') {
		// If the first byte in the input stream is not 'M', then presume that
		// the MIDI file is in the binasc format which is an ASCII representation
		// of the MIDI file.  Convert the binasc content into binary content and
		// then continue reading with this function.
		StringStream binarydata;
		Binasc binasc;
		binasc.WriteToBinary(binarydata, input);
		binarydata.Seek(0);
		
		if (binarydata.Peek() != 'M') {
			last_error = "Bad MIDI data input";
			rwstatus = 0;
			return rwstatus;
		}
		
		else {
			rwstatus = Read(binarydata);
			return rwstatus;
		}
	}
	
	String filename = GetFilename();
	
	int    character;
	
	// uint8  buffer[123456] = {0};
	uint32  longdata;
	
	uint16 shortdata;
	
	
	// Read the MIDI header (4 bytes of ID, 4 byte data size,
	// anticipated 6 bytes of data.
	
	character = input.Get();
	
	if (character == EOF) {
		last_error =	"In file " + filename + ": unexpected end of file. "
						"Expecting 'M' at first byte, but found nothing.";
		rwstatus = 0;
		return rwstatus;
	}
	
	else if (character != 'M') {
		last_error =	"File " + filename + " is not a MIDI file. "
						"Expecting 'M' at first byte but got '"
						+ ChrStr(character) + "'";
		rwstatus = 0;
		return rwstatus;
	}
		
	character = input.Get();
	
	if (character == EOF) {
		last_error =	"In file " + filename + ": unexpected end of file. "
						"Expecting 'T' at first byte, but found nothing.";
		rwstatus = 0;
		return rwstatus;
	}
	
	else if (character != 'T') {
		last_error =	"File " + filename + " is not a MIDI file. "
						"Expecting 'T' at first byte but got '"
						+ ChrStr(character) + "'";
		rwstatus = 0;
		return rwstatus;
	}
		
	character = input.Get();
	
	if (character == EOF) {
		last_error =	"In file " + filename + ": unexpected end of file. "
						"Expecting 'h' at first byte, but found nothing.";
		rwstatus = 0;
		return rwstatus;
	}
	
	else if (character != 'h') {
		last_error =	"File " + filename + " is not a MIDI file. ";
						"Expecting 'h' at first byte but got '"
						+ ChrStr(character) + "'";
		rwstatus = 0;
		return rwstatus;
	}
		
	character = input.Get();
	
	if (character == EOF) {
		last_error =	"In file " + filename + ": unexpected end of file. "
						"Expecting 'd' at first byte, but found nothing.";
		rwstatus = 0;
		return rwstatus;
	}
	
	else if (character != 'd') {
		last_error =	"File " + filename + " is not a MIDI file"
						"Expecting 'd' at first byte but got '"
						+ ChrStr(character) + "'";
		rwstatus = 0;
		return rwstatus;
	}
		
	// read header size (allow larger header size?)
	longdata = File::ReadLittleEndian4Bytes(input);
	
	if (longdata != 6) {
		last_error =	"File " + filename +
						" is not a MIDI 1.0 Standard MIDI file. "
						"The header size is " + IntStr(longdata) + " bytes.";
		rwstatus = 0;
		return rwstatus;
	}
	
	// Header parameter #1: format type
	int type;
	
	shortdata = File::ReadLittleEndian2Bytes(input);
	
	switch (shortdata) {
	
	case 0:
		type = 0;
		break;
		
	case 1:
		type = 1;
		break;
		
	case 2:    // Type-2 MIDI files should probably be allowed as well.
	
	default:
		last_error =	"cannot handle a type-" + HexStr(shortdata) + " MIDI file";
		rwstatus = 0;
		return rwstatus;
	}
	
	// Header parameter #2: track count
	int tracks;
	
	shortdata = File::ReadLittleEndian2Bytes(input);
	
	if (type == 0 && shortdata != 1) {
		last_error =	"Type 0 MIDI file can only contain one track. Instead track count is: " + IntStr(shortdata);
		rwstatus = 0;
		return rwstatus;
	}
	
	else {
		tracks = shortdata;
	}
	
	Clear();
	
	events.SetCount(0);
	events.SetCount(tracks);
	
	for (int i = 0; i < tracks; i++) {
		events[i].Reserve(10000);   // Initialize with 10,000 event storage.
		events[i].Clear();
	}
	
	// Header parameter #3: Ticks per quarter note
	shortdata = File::ReadLittleEndian2Bytes(input);
	
	if (shortdata >= 0x8000) {
		int framespersecond = ((!(shortdata >> 8)) + 1) & 0x00ff;
		int resolution      = shortdata & 0x00ff;
		
		switch (framespersecond) {
		
		case 232:
			framespersecond = 24;
			break;
			
		case 231:
			framespersecond = 25;
			break;
			
		case 227:
			framespersecond = 29;
			break;
			
		case 226:
			framespersecond = 30;
			break;
			
		default:
			LOG("Warning: unknown FPS: " + IntStr(framespersecond));
			framespersecond = 255 - framespersecond + 1;
			LOG("Setting FPS to " << framespersecond);
		}
		
		// actually ticks per second (except for frame=29 (drop frame)):
		ticks_per_quarter_note = shortdata;
		
		LOG("SMPTE ticks: " << ticks_per_quarter_note << " ticks/sec");
		LOG("SMPTE frames per second: " << framespersecond);
		LOG("SMPTE frame resolution per frame: " << resolution);
	}
	
	else {
		ticks_per_quarter_note = shortdata;
	}
	
	
	//////////////////////////////////////////////////
	//
	// now read individual tracks:
	//
	
	uint8 runningCommand;
	
	Event event;
	
	Vector<uint8> bytes;
	
	int absticks;
	
	int xstatus;
	
	// int barline;
	
	for (int i = 0; i < tracks; i++) {
		runningCommand = 0;
		
		// cout << "\nReading Track: " << i + 1 << flush;
		
		// read track header...
		
		character = input.Get();
		
		if (character == EOF) {
			last_error =	"In file " + filename + ": unexpected end of file. "
							"Expecting 'M' at first byte in track, but found nothing.";
			rwstatus = 0;
			return rwstatus;
		}
		
		else if (character != 'M') {
			last_error =	"File " + filename + " is not a MIDI file"
							"Expecting 'M' at first byte in track but got '"
							+ ChrStr(character) + "'";
			rwstatus = 0;
			return rwstatus;
		}
			
		character = input.Get();
		
		if (character == EOF) {
			last_error =	"In file " + filename + ": unexpected end of file. "
							"Expecting 'T' at first byte in track, but found nothing.";
			rwstatus = 0;
			return rwstatus;
		}
		
		else if (character != 'T') {
			last_error =	"File " + filename + " is not a MIDI file"
							"Expecting 'T' at first byte in track but got '"
							+ ChrStr(character) + "'";
			rwstatus = 0;
			return rwstatus;
		}
			
		character = input.Get();
		
		if (character == EOF) {
			last_error =	"In file " + filename + ": unexpected end of file. "
							"Expecting 'r' at first byte in track, but found nothing.";
			rwstatus = 0;
			return rwstatus;
		}
		
		else if (character != 'r') {
			last_error =	"File " + filename + " is not a MIDI file "
							"Expecting 'r' at first byte in track but got '"
							+ ChrStr(character) + "'";
			rwstatus = 0;
			return rwstatus;
		}
			
		character = input.Get();
		
		if (character == EOF) {
			last_error =	"In file " + filename + ": unexpected end of file. "
							"Expecting 'k' at first byte in track, but found nothing.";
			rwstatus = 0;
			return rwstatus;
		}
		
		else if (character != 'k') {
			last_error =	"File " + filename + " is not a MIDI file"
							"Expecting 'k' at first byte in track but got '"
							+ ChrStr(character) + "'";
			rwstatus = 0;
			return rwstatus;
		}
			
		// Now read track chunk size and throw it away because it is
		// not really necessary since the track MUST end with an
		// end of track meta event, and many MIDI files found in the wild
		// do not correctly give the track size.
		longdata = File::ReadLittleEndian4Bytes(input);
		
		// set the size of the track allocation so that it might
		// approximately fit the data.
		events[i].Reserve((int)longdata / 2);
		
		events[i].Clear();
		
		// Process the track
		absticks = 0;
		
		// barline = 1;
		while (!input.IsEof()) {
			longdata = ReadVLValue(input);
			//cout << "ticks = " << longdata);
			absticks += longdata;
			xstatus = ExtractData(input, bytes, runningCommand);
			
			if (xstatus == 0) {
				rwstatus = 0;
				return rwstatus;
			}
			
			event.SetMessage(bytes);
			
			//cout << "command = " << Format("%X", (int)event.data[0] << dec);
			
			if (bytes[0] == 0xff && (bytes[1] == 1 ||
					bytes[1] == 2 || bytes[1] == 3 || bytes[1] == 4)) {
				// mididata.Add('\0');
				// cout << '\t';
				// for (int m=0; m<event.data[2]; m++) {
				//    cout << event.data[m+3];
				// }
				// cout.flush();
			}
			else if (bytes[0] == 0xff && bytes[1] == 0x2f) {
				// end of track message
				// uncomment out the following three lines if you don't want
				// to see the end of track message (which is always required,
				// and added automatically when a MIDI is written.
				event.tick = absticks;
				event.track = i;
				events[i].Add(event);
				
				break;
			}
				
			if (bytes[0] != 0xff && bytes[0] != 0xf0) {
				event.tick = absticks;
				event.track = i;
				events[i].Add(event);
			}
			
			else {
				event.tick = absticks;
				event.track = i;
				events[i].Add(event);
			}
			
		}
		
	}
	
	the_time_state = TIME_STATE_ABSOLUTE;
	
	MarkSequence();
	return 1;
}



//////////////////////////////
//
// File::write -- write a standard MIDI file to a file or an output
//    stream.
//
int File::Write(String filename) {
	FileOut output(filename);
	
	if (!output.IsOpen()) {
		last_error = "could not write: " + filename;
		return 0;
	}
	
	rwstatus = Write(output);
	
	output.Close();
	return rwstatus;
}


int File::Write(Stream& out) {
	int old_time_state = GetTickState();
	
	if (old_time_state == TIME_STATE_ABSOLUTE) {
		DeltaTicks();
	}
	
	// write the header of the Standard MIDI File
	
	char ch;
	
	// 1. The characters "MThd"
	ch = 'M';
	out << ch;
	ch = 'T';
	out << ch;
	ch = 'h';
	out << ch;
	ch = 'd';
	out << ch;
	
	// 2. write the size of the header (always a "6" stored in unsigned long
	//    (4 bytes).
	uint32 longdata = 6;
	WriteBigEndianULong(out, longdata);
	
	// 3. MIDI file format, type 0, 1, or 2
	uint16 shortdata;
	shortdata = (GetTrackCount() == 1) ? 0 : 1;
	WriteBigEndianUShort(out, shortdata);
	
	// 4. write out the number of tracks.
	shortdata = GetTrackCount();
	WriteBigEndianUShort(out, shortdata);
	
	// 5. write out the number of ticks per quarternote. (avoiding SMTPE for now)
	shortdata = GetTicksPerQuarterNote();
	WriteBigEndianUShort(out, shortdata);
	
	// now write each track.
	Vector<uint8> trackdata;
	uint8 endoftrack[4] = {0, 0xff, 0x2f, 0x00};
	int size;
	for (int i = 0; i < GetTrackCount(); i++) {
		trackdata.Reserve(123456);   // make the track data larger than
		// expected data input
		trackdata.Clear();
		
		for (int j = 0; j < (int)events[i].GetCount(); j++) {
			if (events[i][j].IsEndOfTrack()) {
				// suppress end-of-track meta messages (one will be added
				// automatically after all track data has been written).
				continue;
			}
			
			WriteVLValue(events[i][j].tick, trackdata);
			
			if ((events[i][j].GetCommandByte() == 0xf0) ||
				(events[i][j].GetCommandByte() == 0xf7)) {
				// 0xf0 == Complete sysex message (0xf0 is part of the raw MIDI).
				// 0xf7 == Raw byte message (0xf7 not part of the raw MIDI).
				// Print the first byte of the message (0xf0 or 0xf7), then
				// print a VLV length for the rest of the bytes in the message.
				// In other words, when creating a 0xf0 or 0xf7 MIDI message,
				// do not insert the VLV byte length yourself, as this code will
				// do it for you automatically.
				trackdata.Add(events[i][j][0]); // 0xf0 or 0xf7;
				WriteVLValue(events[i][j].GetCount() - 1, trackdata);
				
				for (int k = 1; k < (int)events[i][j].GetCount(); k++) {
					trackdata.Add(events[i][j][k]);
				}
			}
			
			else {
				// non-sysex type of message, so just output the
				// bytes of the message:
				for (int k = 0; k < (int)events[i][j].GetCount(); k++) {
					trackdata.Add(events[i][j][k]);
				}
			}
		}
		
		size = (int)trackdata.GetCount();
		
		if ((size < 3) || !((trackdata[size-3] == 0xff)
							&& (trackdata[size-2] == 0x2f))) {
			trackdata.Add(endoftrack[0]);
			trackdata.Add(endoftrack[1]);
			trackdata.Add(endoftrack[2]);
			trackdata.Add(endoftrack[3]);
		}
		
		// now ready to write to MIDI file.
		
		// first write the track ID marker "MTrk":
		ch = 'M';
		out << ch;
		ch = 'T';
		out << ch;
		ch = 'r';
		out << ch;
		ch = 'k';
		out << ch;
		
		// A. write the size of the MIDI data to follow:
		longdata = trackdata.GetCount();
		
		WriteBigEndianULong(out, longdata);
		
		// B. write the actual data
		out.Put(trackdata.Begin(), trackdata.GetCount());
	}
	
	if (old_time_state == TIME_STATE_ABSOLUTE) {
		AbsoluteTicks();
	}
	
	return 1;
}



//////////////////////////////
//
// File::writeHex -- print the Standard MIDI file as a list of
//    ASCII Hex bytes, formatted 25 to a line by default, and
//    two digits for each hex byte code.  If the input width is 0,
//    then don't wrap lines.
//
//  default value: width=25
//

int File::WriteHex(String file, int width) {
	FileOut output(file);
	
	if (!output.IsOpen()) {
		last_error =	"could not write: " + file;
		return 0;
	}
	
	rwstatus = WriteHex(output, width);
	
	output.Close();
	return rwstatus;
}

//
// ostream version of WriteHex().
//
int File::WriteHex(Stream& out, int width) {
	StringStream tempstream;
	File::Write(tempstream);
	int value = 0;
	int len = (int)tempstream.GetSize();
	int wordcount = 1;
	int linewidth = width >= 0 ? width : 25;
	
	tempstream.Seek(0);
	for (int i = 0; i < len; i++) {
		tempstream.Get(&value, 1);
		
		printf("%02x", value);
		
		if (linewidth) {
			if (i < len - 1) {
				out << (wordcount % linewidth ? ' ' : '\n');
			}
			
			wordcount++;
		}
		
		else {
			// print with no line breaks
			if (i < len - 1) {
				out << ' ';
			}
		}
	}
	
	if (linewidth) {
		out << '\n';
	}
	
	return 1;
}



//////////////////////////////
//
// File::WriteBinasc -- write a standard MIDI file from data into
//    the binasc format (ASCII version of the MIDI file).
//

int File::WriteBinasc(String file) {
	FileOut output(file);
	
	if (!output.IsOpen()) {
		last_error = "could not write: " + file;
		return 0;
	}
	
	rwstatus = WriteBinasc(output);
	
	output.Close();
	return rwstatus;
}


int File::WriteBinascWithComments(String file) {
	FileOut output(file);
	
	if (!output.IsOpen()) {
		last_error = "could not write: " + file;
		return 0;
	}
	
	rwstatus = WriteBinascWithComments(output);
	
	output.Close();
	return rwstatus;
}

int File::WriteBinasc(Stream& output) {
	StringStream binarydata;
	rwstatus = Write(binarydata);
	
	if (rwstatus == 0) {
		return 0;
	}
	
	Binasc binasc;
	
	binasc.SetOn();
	binarydata.Seek(0);
	binasc.ReadFromBinary(output, binarydata);
	return 1;
}


int File::WriteBinascWithComments(Stream& output) {
	StringStream binarydata;
	rwstatus = Write(binarydata);
	
	if (rwstatus == 0) {
		return 0;
	}
	
	Binasc binasc;
	
	binasc.SetOn();
	binasc.SetCommentsOn();
	binarydata.Seek(0);
	binasc.ReadFromBinary(output, binarydata);
	return 1;
}



//////////////////////////////
//
// File::status -- return the success flag from the last read or
//    write (writeHex, WriteBinasc).
//

int File::GetStatus() {
	return rwstatus;
}


///////////////////////////////////////////////////////////////////////////
//
// track-related functions --
//

//////////////////////////////
//
// File::operator[] -- return the event list for the specified track.
//

EventList& File::operator[](int track) {
	return events[track];
}

const EventList& File::operator[](int track) const {
	return events[track];
}


//////////////////////////////
//
// File::GetTrackCount -- return the number of tracks in
//   the  File.
//

int File::GetTrackCount() const {
	return events.GetCount();
}


//////////////////////////////
//
// File::markSequence -- Assign a sequence serial number to
//   every Event in every track in the MIDI file.  This is
//   useful if you want to preseve the order of MIDI messages in
//   a track when they occur at the same tick time.  Particularly
//   for use with JoinTracks() or SortTracks().  markSequence will
//   be done automatically when a MIDI file is read, in case the
//   ordering of events occuring at the same time is important.
//   Use ClearSequence() to use the default sorting behavior of
//   SortTracks().
//

void File::MarkSequence() {
	int sequence = 1;
	
	for (int i = 0; i < GetTrackCount(); i++) {
		for (int j = 0; j < events[i].GetCount(); j++) {
			events[i][j].seq = sequence++;
		}
	}
}



//////////////////////////////
//
// File::clearSequence -- Remove any seqence serial numbers from
//   Events in the File.  This will cause the default ordering by
//   SortTracks() to be used, in which case the ordering of Events
//   occurding at the same tick may switch their ordering.
//

void File::ClearSequence() {
	for (int i = 0; i < GetTrackCount(); i++) {
		for (int j = 0; j < events[i].GetCount(); j++) {
			events[i][j].seq = 0;
		}
	}
}




//////////////////////////////
//
// File::joinTracks -- Interleave the data from all tracks,
//   but keeping the identity of the tracks unique so that
//   the function splitTracks can be called to split the
//   tracks into separate units again.  The style of the
//   File when read from a file is with tracks split.
//   The original track index is stored in the Event::track
//   variable.
//

void File::JoinTracks() {
	if (GetTrackState() == TRACK_STATE_JOINED) {
		return;
	}
	
	if (GetTrackCount() == 1) {
		return;
	}
	
	EventList* joined_track;
	
	joined_track = new EventList;
	
	int messagesum = 0;
	int length = GetTrackCount();
	
	for (int i = 0; i < length; i++) {
		messagesum += events[i].GetCount();
	}
	
	joined_track->Reserve((int)(messagesum + 32 + messagesum * 0.1));
	
	int old_time_state = GetTickState();
	
	if (old_time_state == TIME_STATE_DELTA) {
		AbsoluteTicks();
	}
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < events[i].GetCount(); j++) {
			joined_track->Add(events[i][j]);
		}
	}
	
	ClearNoDeallocate();
	
	joined_track->Link();
	
	events.SetCount(0);
	events.Add(joined_track);
	SortTracks();
	
	if (old_time_state == TIME_STATE_DELTA) {
		DeltaTicks();
	}
	
	the_track_state = TRACK_STATE_JOINED;
}



//////////////////////////////
//
// File::splitTracks -- Take the joined tracks and split them
//   back into their separate track identities.
//

void File::SplitTracks() {
	if (GetTrackState() == TRACK_STATE_SPLIT) {
		return;
	}
	
	int old_time_state = GetTickState();
	
	if (old_time_state == TIME_STATE_DELTA) {
		AbsoluteTicks();
	}
	
	int max_track = 0;
	int length = events[0].GetCount();
	
	for (int i = 0; i < length; i++) {
		if (events[0][i].track > max_track) {
			max_track = events[0][i].track;
		}
	}
	
	int track_count = max_track + 1;
	
	if (track_count <= 1) {
		return;
	}
	
	EventList* olddata = events.Detach(0);
	
	events.SetCount(0);
	events.SetCount(track_count);
	
	int track_value = 0;
	
	for (int i = 0; i < length; i++) {
		track_value = (*olddata)[i].track;
		events[track_value].Add((*olddata)[i]);
	}
	delete olddata;
	
	for(int i = 0; i < events.GetCount(); i++)
		events[i].Link();
	
	if (old_time_state == TIME_STATE_DELTA) {
		DeltaTicks();
	}
	
	the_track_state = TRACK_STATE_SPLIT;
}



//////////////////////////////
//
// File::splitTracksByChannel -- Take the joined tracks and split them
//   back into their separate track identities.
//

void File::SplitTracksByChannel() {
	JoinTracks();
	
	if (GetTrackState() == TRACK_STATE_SPLIT) {
		return;
	}
	
	int old_time_state = GetTickState();
	
	if (old_time_state == TIME_STATE_DELTA) {
		AbsoluteTicks();
	}
	
	int max_track = 0;
	
	
	EventList* eventlist_ = events.Detach(0);
	EventList& eventlist = *eventlist_;
	int length = eventlist.GetCount();
	
	for (int i = 0; i < length; i++) {
		if (eventlist[i].GetCount() == 0) {
			continue;
		}
		
		if ((eventlist[i][0] & 0xf0) == 0xf0) {
			// ignore system and meta messages.
			continue;
		}
		
		if (max_track < (eventlist[i][0] & 0x0f)) {
			max_track = eventlist[i][0] & 0x0f;
		}
	}
	
	int track_count = max_track + 2; // + 1 for expression track
	
	if (track_count <= 1) {
		// only one channel, so don't do anything (leave as Type-0 file).
		return;
	}
	
	events.SetCount(0);
	events.SetCount(track_count);
	
	int track_value = 0;
	
	for (int i = 0; i < length; i++) {
		track_value = 0;
		
		if ((eventlist[i][0] & 0xf0) == 0xf0) {
			track_value = 0;
		}
		
		else
			if (eventlist[i].GetCount() > 0) {
				track_value = (eventlist[i][0] & 0x0f) + 1;
			}
			
		events[track_value].Add(eventlist[i]);
	}
	delete eventlist_;
	
	for(int i = 0; i < events.GetCount(); i++)
		events[i].Link();
	
	if (old_time_state == TIME_STATE_DELTA) {
		DeltaTicks();
	}
	
	the_track_state = TRACK_STATE_SPLIT;
}



//////////////////////////////
//
// File::GetTrackState -- returns what type of track method
//     is being used: either TRACK_STATE_JOINED or TRACK_STATE_SPLIT.
//

int File::GetTrackState() {
	return the_track_state;
}



//////////////////////////////
//
// File::HasJoinedTracks -- Returns true if the File tracks
//    are in a joined state.
//

int File::HasJoinedTracks() {
	return the_track_state == TRACK_STATE_JOINED;
}



//////////////////////////////
//
// File::HasSplitTracks -- Returns true if the File tracks
//     are in a split state.
//

int File::HasSplitTracks() {
	return the_track_state == TRACK_STATE_SPLIT;
}



//////////////////////////////
//
// File::GetSplitTrack --  Return the track index when the File
//   is in the split state.  This function returns the original track
//   when the File is in the joined state.  The Event::track
//   variable is used to store the original track index when the
//   File is converted to the joined-track state.
//

int File::GetSplitTrack(int track, int index) {
	if (HasSplitTracks()) {
		return track;
	}
	
	else {
		return GetEvent(track, index).track;
	}
}

//
// When the parameter is void, assume track 0:
//

int File::GetSplitTrack(int index) {
	if (HasSplitTracks()) {
		return 0;
	}
	
	else {
		return GetEvent(0, index).track;
	}
}



///////////////////////////////////////////////////////////////////////////
//
// tick-related functions --
//

//////////////////////////////
//
// File::DeltaTicks -- convert the time data to
//     delta time, which means that the time field
//     in the Event struct represents the time
//     since the last event was played. When a MIDI file
//     is read from a file, this is the default setting.
//

void File::DeltaTicks() {
	if (GetTickState() == TIME_STATE_DELTA) {
		return;
	}
	
	int temp;
	int length = GetTrackCount();
	int *timedata = new int[length];
	
	for (int i = 0; i < length; i++) {
		timedata[i] = 0;
		
		if (events[i].GetCount() > 0) {
			timedata[i] = events[i][0].tick;
		}
		
		else {
			continue;
		}
		
		for (int j = 1; j < (int)events[i].GetCount(); j++) {
			temp = events[i][j].tick;
			int deltatick = temp - timedata[i];
			
			if (deltatick < 0) {
				last_error =	"negative delta tick value: " + IntStr(deltatick) + ". "
								"Timestamps must be sorted first (use File::SortTracks() before writing).";
			}
			
			events[i][j].tick = deltatick;
			timedata[i] = temp;
		}
	}
	
	the_time_state = TIME_STATE_DELTA;
	
	delete [] timedata;
}



//////////////////////////////
//
// File::AbsoluteTicks -- convert the time data to
//    absolute time, which means that the time field
//    in the Event struct represents the exact tick
//    time to play the event rather than the time since
//    the last event to wait untill playing the current
//    event.
//

void File::AbsoluteTicks() {
	if (GetTickState() == TIME_STATE_ABSOLUTE) {
		return;
	}
	
	int length = GetTrackCount();
	int* timedata = new int[length];
	
	for (int i = 0; i < length; i++) {
		timedata[i] = 0;
		
		if (events[i].GetCount() > 0) {
			timedata[i] = events[i][0].tick;
		}
		
		else {
			continue;
		}
		
		for (int j = 1; j < (int)events[i].GetCount(); j++) {
			timedata[i] += events[i][j].tick;
			events[i][j].tick = timedata[i];
		}
	}
	
	the_time_state = TIME_STATE_ABSOLUTE;
	
	delete [] timedata;
}



//////////////////////////////
//
// File::GetTickState -- returns what type of time method is
//   being used: either TIME_STATE_ABSOLUTE or TIME_STATE_DELTA.
//

int File::GetTickState() {
	return the_time_state;
}



//////////////////////////////
//
// File::IsDeltaTicks -- Returns true if Event .tick
//    variables are in delta time mode.
//

int File::IsDeltaTicks() {
	return the_time_state == TIME_STATE_DELTA ? 1 : 0;
}



//////////////////////////////
//
// File::IsAbsoluteTicks -- Returns true if Event .tick
//    variables are in absolute time mode.
//

int File::IsAbsoluteTicks() {
	return the_time_state == TIME_STATE_ABSOLUTE ? 1 : 0;
}



///////////////////////////////////////////////////////////////////////////
//
// physical-time analysis functions --
//



///////////////////////////////////////////////////////////////////////////
//
// note-analysis functions --
//



///////////////////////////////////////////////////////////////////////////
//
// filename functions --
//

//////////////////////////////
//
// File::SetFilename -- sets the filename of the MIDI file.
//      Currently removed any directory path.
//
void File::SetFilename(String aname) {
	read_file_name = GetFileName(aname);
}



//////////////////////////////
//
// File::GetFilename -- returns the name of the file read into the
//    structure (if the data was read from a file).
//

String File::GetFilename() {
	return read_file_name;
}




















//////////////////////////////
//
// File::AddEvent --
//

int File::AddEvent(int track, int tick, Vector<uint8>& midiData) {
	timemapvalid = 0;
	Event anEvent;
	anEvent.tick = tick;
	anEvent.track = track;
	anEvent.SetMessage(midiData);
	
	events[track].Add(anEvent);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddEvent -- Some bug here when joined_tracks(), but track==1...
//

int File::AddEvent(Event& mfevent) {
	if (GetTrackState() == TRACK_STATE_JOINED) {
		events[0].Add(mfevent);
		return events[0].GetCount() - 1;
	}
	
	else {
		events[mfevent.track].Add(mfevent);
		return events[mfevent.track].GetCount() - 1;
	}
}



///////////////////////////////
//
// File::AddMetaEvent --
//

int File::AddMetaEvent(int track, int tick, int type, Vector<uint8>& meta_data) {
	timemapvalid = 0;
	int length = (int)meta_data.GetCount();
	Vector<uint8> fulldata;
	uint8 size[23] = {0};
	int lengthsize = MakeVLV(size, length);
	
	fulldata.SetCount(2 + lengthsize + length);
	fulldata[0] = 0xff;
	fulldata[1] = type & 0x7F;
	
	for (int i = 0; i < lengthsize; i++) {
		fulldata[2+i] = size[i];
	}
	
	for (int i = 0; i < length; i++) {
		fulldata[2+lengthsize+i] = meta_data[i];
	}
	
	return AddEvent(track, tick, fulldata);
}


int File::AddMetaEvent(int track, int tick, int type, String meta_data) {
	int length = (int)strlen(meta_data);
	Vector<uint8> buffer;
	buffer.SetCount(length);
	
	for (int i = 0; i < length; i++) {
		buffer[i] = (uint8)meta_data[i];
	}
	
	return AddMetaEvent(track, tick, type, buffer);
}



//////////////////////////////
//
// File::AddCopyright --  Add a copyright notice meta-message (#2).
//

int File::AddCopyright(int track, int tick, String text) {
	Event& me = events[track].Add();
	me.MakeCopyright(text);
	me.tick = tick;
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddTrackName --  Add an track name meta-message (#3).
//

int File::AddTrackName(int track, int tick, String name) {
	Event& me = events[track].Add();
	me.MakeTrackName(name);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddInstrumentName --  Add an instrument name meta-message (#4).
//

int File::AddInstrumentName(int track, int tick, String name) {
	Event& me = events[track].Add();
	me.MakeInstrumentName(name);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddLyric -- Add a lyric meta-message (meta #5).
//

int File::AddLyric(int track, int tick, String text) {
	Event& me = events[track].Add();
	me.MakeLyric(text);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddMarker -- Add a marker meta-message (meta #6).
//

int File::AddMarker(int track, int tick, String text) {
	Event& me = events[track].Add();
	me.MakeMarker(text);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddCue -- Add a cue-point meta-message (meta #7).
//

int File::AddCue(int track, int tick, String text) {
	Event& me = events[track].Add();
	me.MakeCue(text);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddTempo -- Add a tempo meta message (meta #0x51).
//

int File::AddTempo(int track, int tick, double aTempo) {
	Event& me = events[track].Add();
	me.MakeTempo(aTempo);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddTimeSignature -- Add a time signature meta message
//      (meta #0x58).  The "bottom" parameter must be a power of two;
//      otherwise, it will be set to the next highest power of two.
//
// Default values:
//     clocks_per_click     == 24 (quarter note)
//     num_32nds_per_quarter ==  8 (8 32nds per quarter note)
//
// Time signature of 4/4 would be:
//    top    = 4
//    bottom = 4 (converted to 2 in the MIDI file for 2nd power of 2).
//    clocks_per_click = 24 (2 eighth notes based on num_32nds_per_quarter)
//    num_32nds_per_quarter = 8
//
// Time signature of 6/8 would be:
//    top    = 6
//    bottom = 8 (converted to 3 in the MIDI file for 3rd power of 2).
//    clocks_per_click = 36 (3 eighth notes based on num_32nds_per_quarter)
//    num_32nds_per_quarter = 8
//

int File::AddTimeSignature(int track, int tick, int top, int bottom,
		int clocks_per_click, int num_32nds_per_quarter) {
	Event& me = events[track].Add();
	me.MakeTimeSignature(top, bottom, clocks_per_click, num_32nds_per_quarter);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddCompoundTimeSignature -- Add a time signature meta message
//      (meta #0x58), where the clocks_per_click parameter is set to three
//      eighth notes for compount meters such as 6/8 which represents
//      two beats per measure.
//
// Default values:
//     clocks_per_click     == 36 (quarter note)
//     num_32nds_per_quarter ==  8 (8 32nds per quarter note)
//

int File::AddCompoundTimeSignature(int track, int tick, int top,
		int bottom, int clocks_per_click, int num_32nds_per_quarter) {
	return AddTimeSignature(track, tick, top, bottom, clocks_per_click,
			num_32nds_per_quarter);
}



//////////////////////////////
//
// File::MakeVLV --  This function is used to create
//   size byte(s) for meta-messages.  If the size of the data
//   in the meta-message is greater than 127, then the size
//   should (?) be specified as a VLV.
//

int File::MakeVLV(uint8 *buffer, int number) {

	unsigned long value = (unsigned long)number;
	
	if (value >= (1 << 28)) {
		last_error =	"Meta-message size too large to handle";
		buffer[0] = 0;
		buffer[1] = 0;
		buffer[2] = 0;
		buffer[3] = 0;
		return 1;
	}
	
	buffer[0] = (value >> 21) & 0x7f;
	
	buffer[1] = (value >> 14) & 0x7f;
	buffer[2] = (value >>  7) & 0x7f;
	buffer[3] = (value >>  0) & 0x7f;
	
	int flag = 0;
	int length = -1;
	
	for (int i = 0; i < 3; i++) {
		if (buffer[i] != 0) {
			flag = 1;
		}
		
		if (flag) {
			buffer[i] |= 0x80;
		}
		
		if (length == -1 && buffer[i] >= 0x80) {
			length = 4 - i;
		}
	}
	
	if (length == -1) {
		length = 1;
	}
	
	if (length < 4) {
		for (int i = 0; i < length; i++) {
			buffer[i] = buffer[4-length+i];
		}
	}
	
	return length;
}



//////////////////////////////
//
// File::AddNoteOn -- Add a note-on message to the given track at the
//    given time in the given channel.
//

int File::AddNoteOn(int track, int tick, int channel, int key, int vel) {
	Event& me = events[track].Add();
	me.MakeNoteOn(channel, key, vel);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddNoteOff -- Add a note-off message (using 0x80 messages).
//

int File::AddNoteOff(int track, int tick, int channel, int key,
		int vel) {
	Event& me = events[track].Add();
	me.MakeNoteOff(channel, key, vel);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddNoteOff -- Add a note-off message (using 0x90 messages with
//   zero attack velocity).
//

int File::AddNoteOff(int track, int tick, int channel, int key) {
	Event& me = events[track].Add();
	me.MakeNoteOff(channel, key);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddController -- Add a controller message in the given
//    track at the given tick time in the given channel.
//

int File::AddController(int track, int tick, int channel,
		int num, int value) {
	Event& me = events[track].Add();
	me.MakeController(channel, num, value);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddPatchChange -- Add a patch-change message in the given
//    track at the given tick time in the given channel.
//

int File::AddPatchChange(int track, int tick, int channel,
		int patchnum) {
	Event& me = events[track].Add();
	me.MakePatchChange(channel, patchnum);
	me.tick = tick;
	events[track].Add(me);
	return events[track].GetCount() - 1;
}



//////////////////////////////
//
// File::AddTimbre -- Add a patch-change message in the given
//    track at the given tick time in the given channel.  Alias for
//    File::AddPatchChange().
//

int File::AddTimbre(int track, int tick, int channel, int patchnum) {
	return AddPatchChange(track, tick, channel, patchnum);
}



//////////////////////////////
//
// File::AddPitchBend -- convert  number in the range from -1 to +1
//     into two 7-bit numbers (smallest piece first)
//
//   -1.0 maps to 0 (0x0000)
//    0.0 maps to 8192 (0x2000 --> 0x40 0x00)
//   +1.0 maps to 16383 (0x3FFF --> 0x7F 0x7F)
//

int File::AddPitchBend(int track, int tick, int channel, double amount) {
	timemapvalid = 0;
	amount += 1.0;
	int value = int(amount * 8192 + 0.5);
	
	// prevent any wrap-around in case of round-off errors
	
	if (value > 0x3fff) {
		value = 0x3fff;
	}
	
	if (value < 0) {
		value = 0;
	}
	
	int lsbint = 0x7f & value;
	
	int msbint = 0x7f & (value  >> 7);
	
	Vector<uint8> mididata;
	mididata.SetCount(3);
	
	if (channel < 0) {
		channel = 0;
	}
	
	else
		if (channel > 15) {
			channel = 15;
		}
		
	mididata[0] = uint8(0xe0 | channel);
	
	mididata[1] = uint8(lsbint);
	mididata[2] = uint8(msbint);
	
	return AddEvent(track, tick, mididata);
}



//////////////////////////////
//
// File::AddTrack -- adds a blank track at end of the
//    track list.  Returns the track number of the added
//    track.
//

int File::AddTrack() {
	int length = GetTrackCount();
	events.SetCount(length + 1);
	events[length].Reserve(10000);
	events[length].Clear();
	return length;
}

int File::AddTrack(int count) {
	int length = GetTrackCount();
	events.SetCount(length + count);
	
	for (int i = 0; i < count; i++) {
		events[length + i].Reserve(10000);
		events[length + i].Clear();
	}
	
	return length + count - 1;
}



//////////////////////////////
//
// File::AllocateEvents --
//

void File::AllocateEvents(int track, int size) {
	int oldsize = events[track].GetCount();
	
	if (oldsize < size) {
		events[track].Reserve(size);
	}
}



//////////////////////////////
//
// File::DeleteTrack -- remove a track from the File.
//   Tracks are numbered starting at track 0.
//

void File::DeleteTrack(int track) {
	int length = GetTrackCount();
	
	if (track < 0 || track >= length) {
		return;
	}
	
	if (length == 1) {
		return;
	}
	
	events.Remove(track);
}



//////////////////////////////
//
// File::clear -- make the MIDI file empty with one
//     track with no data in it.
//

void File::Clear() {
	events.SetCount(0);
	events.SetCount(1);
	
	timemapvalid = 0;
	timemap.Clear();
	the_track_state = TRACK_STATE_SPLIT;
	the_time_state = TIME_STATE_ABSOLUTE;
}



//////////////////////////////
//
// File::getEvent -- return the event at the given index in the
//    specified track.
//

Event& File::GetEvent(int track, int index) {
	return events[track][index];
}



//////////////////////////////
//
// File::GetTicksPerQuarterNote -- returns the number of
//   time units that are supposed to occur during a quarternote.
//

int File::GetTicksPerQuarterNote() {
	if (ticks_per_quarter_note == 0xE728) {
		// this is a special case which is the SMPTE time code
		// setting for 25 frames a second with 40 subframes
		// which means one tick per millisecond.  When SMPTE is
		// being used, there is no real concept of the quarter note,
		// so presume 60 bpm as a simiplification here.
		// return 1000;
	}
	
	return ticks_per_quarter_note;
}

//
// Alias for GetTicksPerQuarterNote:
//

int File::GetTPQ() {
	return GetTicksPerQuarterNote();
}



//////////////////////////////
//
// File::GetEventCount -- returns the number of events
//   in a given track.
//

int File::GetEventCount(int track) {
	return events[track].GetCount();
}



//////////////////////////////
//
// File::MergeTracks -- combine the data from two
//   tracks into one.  Placing the data in the first
//   track location listed, and Moving the other tracks
//   in the file around to fill in the spot where Track2
//   used to be.  The results of this function call cannot
//   be reversed.
//

void File::MergeTracks(int track1, int track2) {
	EventList* mergedTrack;
	mergedTrack = new EventList;
	int old_time_state = GetTickState();
	
	if (old_time_state == TIME_STATE_DELTA) {
		AbsoluteTicks();
	}
	
	int length = GetTrackCount();
	
	for (int i = 0; i < events[track1].GetCount(); i++) {
		mergedTrack->Add(events[track1][i]);
	}
	
	for (int i = 0; i < events[track2].GetCount(); i++) {
		events[track2][i].track = track1;
		mergedTrack->Add(events[track2][i]);
	}
	
	SortTrack(*mergedTrack);
	mergedTrack->Link();
	
	events.Remove(track1);
	events.Insert(track1, *mergedTrack);
	
	for (int i = track2; i < length - 1; i++) {
		events[i] = events[i+1];
	}
	
	events.SetCount(length - 1);
	
	if (old_time_state == TIME_STATE_DELTA) {
		DeltaTicks();
	}
}



//////////////////////////////
//
// File::SetTicksPerQuarterNote --
//

void File::SetTicksPerQuarterNote(int ticks) {
	ticks_per_quarter_note = ticks;
}

//
// Alias for SetTicksPerQuarterNote:
//

void File::SetTPQ(int ticks) {
	SetTicksPerQuarterNote(ticks);
}


//////////////////////////////
//
// File::SetMillisecondTicks -- set the ticks per quarter note
//   value to milliseconds.  The format for this specification is
//   highest 8-bits: SMPTE Frame rate (as a negative 2's compliment value).
//   lowest 8-bits: divisions per frame (as a positive number).
//   for millisecond resolution, the SMPTE value is -25, and the
//   frame rate is 40 frame per division.  In hexadecimal, these
//   values are: -25 = 1110,0111 = 0xE7 and 40 = 0010,1000 = 0x28
//   So setting the ticks per quarter note value to 0xE728 will cause
//   delta times in the MIDI file to represent milliseconds.
//

void File::SetMillisecondTicks() {
	ticks_per_quarter_note = 0xE728;
}



//////////////////////////////
//
// File::SortTrack --
//

void File::SortTrack(EventList& track_data) {
	if (the_time_state == TIME_STATE_ABSOLUTE) {
		Sort(track_data.list, EventCompare());
	}
}



//////////////////////////////
//
// File::SortTracks -- sort all tracks in the File.
//

void File::SortTracks() {
	if (the_time_state == TIME_STATE_ABSOLUTE) {
		for (int i = 0; i < GetTrackCount(); i++) {
			SortTrack(events[i]);
		}
	}
}



//////////////////////////////
//
// File::GetTrackCountAsType1 --  Return the number of tracks in the
//    MIDI file.  Returns the size of the events if not in joined state.
//    If in joined state, reads track 0 to find the maximum track
//    value from the original unjoined tracks.
//

int File::GetTrackCountAsType1() {
	if (GetTrackState() == TRACK_STATE_JOINED) {
		int output = 0;
		
		for (int i = 0; i < (int)events[0].GetCount(); i++) {
			if (GetEvent(0, i).track > output) {
				output = GetEvent(0, i).track;
			}
		}
		
		return output + 1;  // I think the track values are 0 offset...
	}
	
	else {
		return (int)events.GetCount();
	}
}



//////////////////////////////
//
// File::GetTimeInSeconds -- return the time in seconds for
//     the current message.
//

double File::GetTimeInSeconds(int track, int index) {
	return GetTimeInSeconds(GetEvent(track, index).tick);
}


double File::GetTimeInSeconds(int tickvalue) {
	if (timemapvalid == 0) {
		BuildTimeMap();
		
		if (timemapvalid == 0) {
			return -1.0;    // something went wrong
		}
	}
	
	TickTime key;
	
	key.tick    = tickvalue;
	key.seconds = -1;
	
	void* ptr = bsearch(&key, timemap.Begin(), timemap.GetCount(), sizeof(TickTime), TickSearch);
	                    
	if (ptr == NULL) {
		// The specific tick value was not found, so do a linear
		// search for the two tick values which occur before and
		// after the tick value, and do a linear interpolation of
		// the time in seconds values to figure out the final
		// time in seconds.
		// Since the code is not yet written, kill the program at this point:
		return LinearSecondInterpolationAtTick(tickvalue);
	}
	
	else {
		return ((TickTime*)ptr)->seconds;
	}
}



//////////////////////////////
//
// File::GetAbsoluteTickTime -- return the tick value represented
//    by the input time in seconds.  If there is not tick entry at
//    the given time in seconds, then interpolate between two values.
//

int File::GetAbsoluteTickTime(double starttime) {
	if (timemapvalid == 0) {
		BuildTimeMap();
		
		if (timemapvalid == 0) {
			if (timemapvalid == 0) {
				return -1;    // something went wrong
			}
		}
	}
	
	TickTime key;
	
	key.tick    = -1;
	key.seconds = starttime;
	
	void* ptr = bsearch(&key, timemap.Begin(), timemap.GetCount(), sizeof(TickTime), SecondSearch);
	                    
	if (ptr == NULL) {
		// The specific seconds value was not found, so do a linear
		// search for the two time values which occur before and
		// after the given time value, and do a linear interpolation of
		// the time in tick values to figure out the final time in ticks.
		return LinearTickInterpolationAtSecond(starttime);
	}
	
	else {
		return ((TickTime*)ptr)->tick;
	}
	
}



//////////////////////////////
//
// File::GetTotalTimeInSeconds -- Returns the duration of the File
//    event list in seconds.  If DoTimeAnalysis() is not called before this
//    function is called, it will be called automatically.
//

double File::GetTotalTimeInSeconds() {
	if (timemapvalid == 0) {
		BuildTimeMap();
		
		if (timemapvalid == 0) {
			return -1.0;    // something went wrong
		}
	}
	
	double output = 0.0;
	
	for (int i = 0; i < (int)events.GetCount(); i++) {
		if (events[i].Last().seconds > output) {
			output = events[i].Last().seconds;
		}
	}
	
	return output;
}



///////////////////////////////
//
// File::GetTotalTimeInTicks -- Returns the absolute tick value for the
//    latest event in any track.  If the File is in TIME_STATE_DELTA,
//    then temporarily got into TIME_STATE_ABSOLUTE to do the calculations.
//    Note that this is expensive, so you should normally call this function
//    while in aboslute tick mode.
//

int File::GetTotalTimeInTicks() {
	int old_time_state = GetTickState();
	
	if (old_time_state == TIME_STATE_DELTA) {
		AbsoluteTicks();
	}
	
	if (old_time_state == TIME_STATE_DELTA) {
		DeltaTicks();
	}
	
	int output = 0;
	
	for (int i = 0; i < (int)events.GetCount(); i++) {
		if (events[i].Last().tick > output) {
			output = events[i].Last().tick;
		}
	}
	
	return output;
}



///////////////////////////////
//
// File::GetTotalTimeInQuarters -- Returns the Duration of the File
//    in units of quarter notes.  If the File is in TIME_STATE_DELTA,
//    then temporarily got into TIME_STATE_ABSOLUTE to do the calculations.
//    Note that this is expensive, so you should normally call this function
//    while in aboslute tick mode.
//

double File::GetTotalTimeInQuarters() {
	double totalTicks = GetTotalTimeInTicks();
	return totalTicks / GetTicksPerQuarterNote();
}



//////////////////////////////
//
// File::DoTimeAnalysis -- Identify the real-time position of
//    all events by monitoring the tempo in relations to the tick
//    times in the file.
//

void File::DoTimeAnalysis() {
	BuildTimeMap();
}



//////////////////////////////
//
// File::linkNotePairs --  Link note-ons to note-offs separately
//     for each track.  Returns the total number of note message pairs
//     that were linked.
//

int File::LinkNotePairs() {
	int sum = 0;
	
	for (int i = 0; i < GetTrackCount(); i++) {
		sum += events[i].LinkNotePairs();
	}
	
	return sum;
}


int File::LinkEventPairs() {
	return LinkNotePairs();
}


//////////////////////////////
//
// File::clearLinks --
//

void File::ClearLinks() {
	for (int i = 0; i < GetTrackCount(); i++) {
		events[i].ClearLinks();
	}
}



///////////////////////////////////////////////////////////////////////////
//
// private functions
//

//////////////////////////////
//
// File::LinearTickInterpolationAtSecond -- return the tick value at the
//    given input time.
//

int File::LinearTickInterpolationAtSecond(double seconds) {
	if (timemapvalid == 0) {
		BuildTimeMap();
		
		if (timemapvalid == 0) {
			return -1;    // something went wrong
		}
	}
	
	double lasttime = timemap[timemap.GetCount()-1].seconds;
	// give an error value of -1 if time is out of range of data.
	
	if (seconds < 0.0) {
		return -1;
	}
	
	if (seconds > timemap[timemap.GetCount()-1].seconds) {
		return -1;
	}
	
	// Guess which side of the list is closest to target:
	// Could do a more efficient algorithm since time values are sorted,
	// but good enough for now...
	int startindex = -1;
	
	if (seconds < lasttime / 2) {
		for (int i = 0; i < (int)timemap.GetCount(); i++) {
			if (timemap[i].seconds > seconds) {
				startindex = i - 1;
				break;
			}
			
			else
				if (timemap[i].seconds == seconds) {
					startindex = i;
					break;
				}
		}
	}
	
	else {
		for (int i = (int)timemap.GetCount() - 1; i > 0; i--) {
			if (timemap[i].seconds < seconds) {
				startindex = i + 1;
				break;
			}
			
			else
				if (timemap[i].seconds == seconds) {
					startindex = i;
					break;
				}
		}
	}
	
	if (startindex < 0) {
		return -1;
	}
	
	if (startindex >= (int)timemap.GetCount() - 1) {
		return -1;
	}
	
	double x1 = timemap[startindex].seconds;
	
	double x2 = timemap[startindex+1].seconds;
	double y1 = timemap[startindex].tick;
	double y2 = timemap[startindex+1].tick;
	double xi = seconds;
	
	return (int)((xi -x1) * ((y2 - y1) / (x2 - x1)) + y1);
}



//////////////////////////////
//
// File::LinearSecondInterpolationAtTick -- return the time in seconds
//    value at the given input tick time. (Ticks input could be made double).
//

double File::LinearSecondInterpolationAtTick(int ticktime) {
	if (timemapvalid == 0) {
		BuildTimeMap();
		
		if (timemapvalid == 0) {
			return -1.0;    // something went wrong
		}
	}
	
	double lasttick = timemap[timemap.GetCount()-1].tick;
	// give an error value of -1 if time is out of range of data.
	
	if (ticktime < 0.0) {
		return -1;
	}
	
	if (ticktime > timemap.Top().tick) {
		return -1;  // don't try to extrapolate
	}
	
	// Guess which side of the list is closest to target:
	// Could do a more efficient algorithm since time values are sorted,
	// but good enough for now...
	int startindex = -1;
	
	if (ticktime < lasttick / 2) {
		for (int i = 0; i < (int)timemap.GetCount(); i++) {
			if (timemap[i].tick > ticktime) {
				startindex = i - 1;
				break;
			}
			
			else
				if (timemap[i].tick == ticktime) {
					startindex = i;
					break;
				}
		}
	}
	
	else {
		for (int i = (int)timemap.GetCount() - 1; i > 0; i--) {
			if (timemap[i].tick < ticktime) {
				startindex = i;
				break;
			}
			
			else
				if (timemap[i].tick == ticktime) {
					startindex = i;
					break;
				}
		}
	}
	
	if (startindex < 0) {
		return -1;
	}
	
	if (startindex >= (int)timemap.GetCount() - 1) {
		return -1;
	}
	
	if (timemap[startindex].tick == ticktime) {
		return timemap[startindex].seconds;
	}
	
	double x1 = timemap[startindex].tick;
	
	double x2 = timemap[startindex+1].tick;
	double y1 = timemap[startindex].seconds;
	double y2 = timemap[startindex+1].seconds;
	double xi = ticktime;
	
	return (xi -x1) * ((y2 - y1) / (x2 - x1)) + y1;
}



//////////////////////////////
//
// File::BuildTimeMap -- build an index of the absolute tick values
//      found in a MIDI file, and their corresponding time values in
//      seconds, taking into consideration tempo change messages.  If no
//      tempo messages are given (or until they are given, then the
//      tempo is set to 120 beats per minute).  If SMPTE time code is
//      used, then ticks are actually time values.  So don't build
//      a time map for SMPTE ticks, and just calculate the time in
//      seconds from the tick value (1000 ticks per second SMPTE
//      is the only mode tested (25 frames per second and 40 subframes
//      per frame).
//

void File::BuildTimeMap() {

	// convert the MIDI file to absolute time representation
	// in single track mode (and undo if the MIDI file was not
	// in that state when this function was called.
	//
	int trackstate = GetTrackState();
	int timestate  = GetTickState();
	
	AbsoluteTicks();
	JoinTracks();
	
	int allocsize = GetEventCount(0);
	timemap.Reserve(allocsize + 10);
	timemap.Clear();
	
	TickTime value;
	
	int lasttick = 0;
	int curtick;
	int tickinit = 0;
	
	int tpq = GetTicksPerQuarterNote();
	double defaultTempo = 120.0;
	double secondsPerTick = 60.0 / (defaultTempo * tpq);
	
	double lastsec = 0.0;
	double cursec = 0.0;
	
	for (int i = 0; i < GetEventCount(0); i++) {
		curtick = GetEvent(0, i).tick;
		GetEvent(0, i).seconds = cursec;
		
		if ((curtick > lasttick) || !tickinit) {
			tickinit = 1;
			
			// calculate the current time in seconds:
			cursec = lastsec + (curtick - lasttick) * secondsPerTick;
			GetEvent(0, i).seconds = cursec;
			
			// store the new tick to second mapping
			value.tick = curtick;
			value.seconds = cursec;
			timemap.Add(value);
			lasttick   = curtick;
			lastsec    = cursec;
		}
		
		// update the tempo if needed:
		
		if (GetEvent(0, i).IsTempo()) {
			secondsPerTick = GetEvent(0, i).GetTempoSPT(GetTicksPerQuarterNote());
		}
	}
	
	// reset the states of the tracks or time values if necessary here:
	
	if (timestate == TIME_STATE_DELTA) {
		DeltaTicks();
	}
	
	if (trackstate == TRACK_STATE_SPLIT) {
		SplitTracks();
	}
	
	timemapvalid = 1;
	
}



//////////////////////////////
//
// File::ExtractData -- Extract MIDI data from input
//    stream.  Return value is 0 if failure; otherwise, returns 1.
//

int File::ExtractData(Stream& input, Vector<uint8>& array,
		uint8& runningCommand) {
        
	int character;
	uint8 byte;
	array.Clear();
	int runningQ;
	
	character = input.Get();
	
	if (character == EOF) {
		last_error =	"unexpected end of file.";
		return 0;
	}
	
	else {
		byte = (uint8)character;
	}
	
	if (byte < 0x80) {
		runningQ = 1;
		
		if (runningCommand == 0) {
			last_error =	"running command with no previous command";
			return 0;
		}
		
		if (runningCommand >= 0xf0) {
			last_error =	"running status not permitted with meta and sysex event.";
			return 0;
		}
	}
	
	else {
		runningCommand = byte;
		runningQ = 0;
	}
	
	array.Add(runningCommand);
	
	if (runningQ) {
		array.Add(byte);
	}
	
	uint8 metai;
	
	switch (runningCommand & 0xf0) {
	
	case 0x80:        // note off (2 more bytes)
	
	case 0x90:        // note on (2 more bytes)
	
	case 0xA0:        // aftertouch (2 more bytes)
	
	case 0xB0:        // cont. controller (2 more bytes)
	
	case 0xE0:        // pitch wheel (2 more bytes)
		byte = File::ReadByte(input);
		array.Add(byte);
		
		if (!runningQ) {
			byte = File::ReadByte(input);
			array.Add(byte);
		}
		
		break;
		
	case 0xC0:        // patch change (1 more byte)
	
	case 0xD0:        // channel pressure (1 more byte)
	
		if (!runningQ) {
			byte = File::ReadByte(input);
			array.Add(byte);
		}
		
		break;
		
	case 0xF0:
	
		switch (runningCommand) {
		
		case 0xff: {               // meta event
				if (!runningQ) {
					byte = File::ReadByte(input); // meta type
					array.Add(byte);
				}
				
				metai = File::ReadByte(input); // meta type
				
				array.Add(metai);
				
				for (uint8 j = 0; j < metai; j++) {
					byte = File::ReadByte(input); // meta type
					array.Add(byte);
				}
			}
			
			break;
			// The 0xf0 and 0xf7 meta commands deal with system-exclusive
			// messages. 0xf0 is used to either start a message or to store
			// a complete message.  The 0xf0 is part of the outgoing MIDI
			// bytes.  The 0xf7 message is used to send arbitrary bytes,
			// typically the middle or ends of system exclusive messages.  The
			// 0xf7 byte at the start of the message is not part of the
			// outgoing raw MIDI bytes, but is kept in the File message
			// to indicate a raw MIDI byte message (typically a partial
			// system exclusive message).
			
		case 0xf7:                // Raw bytes. 0xf7 is not part of the raw
			// bytes, but are included to indicate
			// that this is a raw byte message.
			
		case 0xf0:                // System Exclusive message
			{                      // (complete, or start of message).
				int length = (int)ReadVLValue(input);
				
				for (int i = 0; i < length; i++) {
					byte = File::ReadByte(input);
					array.Add(byte);
				}
			}
			
			break;
			// other "F" MIDI commands are not expected, but can be
			// handled here if they exist.
		}
		
		break;
		
	default:
		last_error =	"Error reading midifile. Command byte was " + IntStr(runningCommand);
		return 0;
	}
	
	return 1;
}



//////////////////////////////
//
// File::ReadVLValue -- The VLV value is expected to be unpacked into
//   a 4-byte integer no greater than 0x0fffFFFF, so a VLV value up to
//   4-bytes in size (FF FF FF 7F) will only be considered.  Longer
//   VLV values are not allowed in standard MIDI files, so the extract
//   delta time would be truncated and the extra byte(s) will be parsed
//   incorrectly as a MIDI command.
//

uint32 File::ReadVLValue(Stream& input) {
	uint8 b[4] = {0};
	
	for (int i = 0; i < 4; i++) {
		b[i] = File::ReadByte(input);
		
		if (b[i] < 0x80) {
			break;
		}
	}
	
	return UnpackVLV(b[0], b[1], b[2], b[3]);
}



//////////////////////////////
//
// File::UnpackVLV -- converts a VLV value to an unsigned long value.
//     The bytes a, b, c, d are in big-endian order (the order they would
//     be read out of the MIDI file).
// default values: a = b = c = d = 0;
//

uint32 File::UnpackVLV(uint8 a, uint8 b, uint8 c, uint8 d) {
	if (d > 0x7f) {
		last_error =	"VLV value was too long";
		return 0;
	}
	
	uint8 bytes[4] = {a, b, c, d};
	int count = 0;
	
	while (bytes[count] > 0x7f && count < 4) {
		count++;
	}
	
	count++;
	
	uint32 output = 0;
	
	for (int i = 0; i < count; i++) {
		output = output << 7;
		output = output | (bytes[i] & 0x7f);
	}
	
	return output;
}



//////////////////////////////
//
// File::WriteVLValue -- write a number to the midifile
//    as a variable length value which segments a file into 7-bit
//    values and adds a contination bit to each.  Maximum size of input
//    value is 0x0FFFffff.
//

void File::WriteVLValue(long value, Vector<uint8>& outdata) {
	uint8 bytes[4] = {0};
	
	if ((unsigned long)value >= (1 << 28)) {
		last_error =	"number too large to convert to VLV";
		value = 0x0FFFffff;
	}
	
	bytes[0] = (uint8)(((uint32)value >> 21) & 0x7f);  // most significant 7 bits
	
	bytes[1] = (uint8)(((uint32)value >> 14) & 0x7f);
	bytes[2] = (uint8)(((uint32)value >> 7)  & 0x7f);
	bytes[3] = (uint8)(((uint32)value)       & 0x7f);  // least significant 7 bits
	
	int start = 0;
	
	while ((start < 4) && (bytes[start] == 0))
		start++;
		
	for (int i = start; i < 3; i++) {
		bytes[i] = bytes[i] | 0x80;
		outdata.Add(bytes[i]);
	}
	
	outdata.Add(bytes[3]);
}



//////////////////////////////
//
// File::clear_no_deallocate -- Similar to Clear() but does not
//   delete the Events in the lists.  This is primarily used internally
//   to the File class, so don't use unless you really know what you
//   are doing (otherwise you will end up with memory leaks or
//   segmentation faults).
//

void File::ClearNoDeallocate() {
	events.SetCount(0);
	events.SetCount(1);
	
	timemapvalid = 0;
	timemap.Clear();
	// events.SetCount(0);   // causes a memory leak [20150205 Jorden Thatcher]
}



///////////////////////////////////////////////////////////////////////////
//
// external functions
//





//////////////////////////////
//
// operator<< -- for printing an ASCII version of the MIDI file
//

Stream& operator<<(Stream& out, File& aFile) {
	aFile.WriteBinascWithComments(out);
	return out;
}



//////////////////////////////
//
// File::TickSearch -- for finding a tick entry in the time map.
//

int File::TickSearch(const void* A, const void* B) {
	TickTime& a = *((TickTime*)A);
	TickTime& b = *((TickTime*)B);
	
	if (a.tick < b.tick) {
		return -1;
	}
	
	else
		if (a.tick > b.tick) {
			return 1;
		}
		
	return 0;
}



//////////////////////////////
//
// File::SecondSearch -- for finding a second entry in the time map.
//

int File::SecondSearch(const void* A, const void* B) {
	TickTime& a = *((TickTime*)A);
	TickTime& b = *((TickTime*)B);
	
	if (a.seconds < b.seconds) {
		return -1;
	}
	
	else
		if (a.seconds > b.seconds) {
			return 1;
		}
		
	return 0;
}


///////////////////////////////////////////////////////////////////////////
//
// Static functions:
//


//////////////////////////////
//
// File::ReadLittleEndian4Bytes -- Read four bytes which are in
//      little-endian order (smallest byte is first).  Then flip
//      the order of the bytes to create the return value.
//

uint32 File::ReadLittleEndian4Bytes(Stream& input) {
	uint8 buffer[4] = {0};
	input.Get((char*)buffer, 4);
	
	if (input.IsEof()) {
		LOG("error: unexpected end of file");
		return 0;
	}
	
	return buffer[3] | (buffer[2] << 8) | (buffer[1] << 16) | (buffer[0] << 24);
}



//////////////////////////////
//
// File::ReadLittleEndian2Bytes -- Read two bytes which are in
//       little-endian order (smallest byte is first).  Then flip
//       the order of the bytes to create the return value.
//

uint16 File::ReadLittleEndian2Bytes(Stream& input) {
	uint8 buffer[2] = {0};
	input.Get((char*)buffer, 2);
	
	if (input.IsEof()) {
		LOG("error: unexpected end of file");
		return 0;
	}
	
	return buffer[1] | (buffer[0] << 8);
}



//////////////////////////////
//
// File::ReadByte -- Read one byte from input stream.  Exit if there
//     was an error.
//

uint8 File::ReadByte(Stream& input) {
	uint8 buffer[1] = {0};
	input.Get((char*)buffer, 1);
	
	if (input.IsEof()) {
		LOG("error: unexpected end of file");
		return 0;
	}
	
	return buffer[0];
}



//////////////////////////////
//
// File::WriteLittleEndianUShort --
//

Stream& File::WriteLittleEndianUShort(Stream& out, uint16 value) {
	union {
		char bytes[2];
		uint16 us;
	} data;
	data.us = value;
	out << data.bytes[0];
	out << data.bytes[1];
	return out;
}



//////////////////////////////
//
// File::WriteBigEndianUShort --
//

Stream& File::WriteBigEndianUShort(Stream& out, uint16 value) {
	union { char bytes[2];
		uint16 us;
	} data;
	data.us = value;
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// File::WriteLittleEndianShort --
//

Stream& File::WriteLittleEndianShort(Stream& out, short value) {
	union { char bytes[2];
		short s;
	} data;
	data.s = value;
	out << data.bytes[0];
	out << data.bytes[1];
	return out;
}



//////////////////////////////
//
// File::WriteBigEndianShort --
//

Stream& File::WriteBigEndianShort(Stream& out, short value) {
	union { char bytes[2];
		short s;
	} data;
	data.s = value;
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// File::WriteLittleEndianULong --
//

Stream& File::WriteLittleEndianULong(Stream& out, uint32 value) {
	union { char bytes[4];
		uint32 ul;
	} data;
	data.ul = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	return out;
}



//////////////////////////////
//
// File::WriteBigEndianULong --
//

Stream& File::WriteBigEndianULong(Stream& out, uint32 value) {
	union { char bytes[4];
		long ul;
	} data;
	data.ul = value;
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// File::WriteLittleEndianLong --
//

Stream& File::WriteLittleEndianLong(Stream& out, long value) {
	union { char bytes[4];
		long l;
	} data;
	data.l = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	return out;
}



//////////////////////////////
//
// File::WriteBigEndianLong --
//

Stream& File::WriteBigEndianLong(Stream& out, long value) {
	union { char bytes[4];
		long l;
	} data;
	data.l = value;
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
	
}



//////////////////////////////
//
// File::WriteBigEndianFloat --
//

Stream& File::WriteBigEndianFloat(Stream& out, float value) {
	union { char bytes[4];
		float f;
	} data;
	data.f = value;
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// File::WriteLittleEndianFloat --
//

Stream& File::WriteLittleEndianFloat(Stream& out, float value) {
	union { char bytes[4];
		float f;
	} data;
	data.f = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	return out;
}



//////////////////////////////
//
// File::WriteBigEndianDouble --
//

Stream& File::WriteBigEndianDouble(Stream& out, double value) {
	union { char bytes[8];
		double d;
	} data;
	data.d = value;
	out << data.bytes[7];
	out << data.bytes[6];
	out << data.bytes[5];
	out << data.bytes[4];
	out << data.bytes[3];
	out << data.bytes[2];
	out << data.bytes[1];
	out << data.bytes[0];
	return out;
}



//////////////////////////////
//
// File::WriteLittleEndianDouble --
//

Stream& File::WriteLittleEndianDouble(Stream& out, double value) {
	union { char bytes[8];
		double d;
	} data;
	data.d = value;
	out << data.bytes[0];
	out << data.bytes[1];
	out << data.bytes[2];
	out << data.bytes[3];
	out << data.bytes[4];
	out << data.bytes[5];
	out << data.bytes[6];
	out << data.bytes[7];
	return out;
}



//////////////////////////////
//
// File::operator=(File) -- Assignment.
//

File& File::operator=(const File& other) {
	events <<= other.events;
	for(int i = 0; i < events.GetCount(); i++) {
		events[i].Link();
	}
	return *this;
}

NAMESPACE_MIDI_END
