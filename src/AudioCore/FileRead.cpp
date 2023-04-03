#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FileRead::FileRead()
	: fd_(0), fileSize_(0), channels_(0), data_type_(0), fileRate_(0.0f) {
}

FileRead::FileRead( String file_name, bool type_raw, int channel_count,
					  AudioFormat format, float rate )
	: fd_(0) {
	Open( file_name, type_raw, channel_count, format, rate );
}

FileRead::~FileRead() {
	if ( fd_ )
		fclose( fd_ );
}

void FileRead::Close() {
	if ( fd_ ) fclose( fd_ );

	fd_ = 0;
	wavFile_ = false;
	fileSize_ = 0;
	channels_ = 0;
	data_type_ = 0;
	fileRate_ = 0.0f;
}

bool FileRead::isOpen() {
	if ( fd_ ) return true;
	else return false;
}

void FileRead::Open( String file_name, bool type_raw, int channel_count,
					   AudioFormat format, float rate ) {
	Close();
	#ifdef flagWIN32
	fopen_s(&fd_, file_name.Begin(), "rb" );
	#else
	fd_ = fopen( file_name.Begin(), "rb" );
	#endif
	
	if ( !fd_ ) {
		LOG("FileRead::open: could not open or find file (" << file_name << ")!");
		HandleError( AudioError::FILE_NOT_FOUND );
	}

	bool result = false;

	if ( type_raw )
		result = GetRawInfo( file_name.Begin(), channel_count, format, rate );
	else {
		char header[12];

		if ( fread( &header, 4, 3, fd_ ) != 3 ) goto error;

		if ( !strncmp( header, "RIFF", 4 ) &&
			 !strncmp( &header[8], "WAVE", 4 ) )
			result = GetWavInfo( file_name.Begin() );
		else if ( !strncmp( header, ".snd", 4 ) )
			result = GetSndInfo( file_name.Begin() );
		else if ( !strncmp( header, "FORM", 4 ) &&
				  ( !strncmp( &header[8], "AIFF", 4 ) || !strncmp(&header[8], "AIFC", 4) ) )
			result = GetAifInfo( file_name.Begin() );
		else {
			if ( fseek( fd_, 126, SEEK_SET ) == -1 ) goto error;

			if ( fread( &header, 2, 1, fd_ ) != 1 ) goto error;

			if ( !strncmp( header, "MI", 2 ) ||
				 !strncmp( header, "IM", 2 ) )
				result = GetMatInfo( file_name.Begin() );
			else {
				LOG("FileRead::open: file (" << file_name << ") format unknown.");
				HandleError( AudioError::FILE_UNKNOWN_FORMAT );
			}
		}
	}

	if ( result == false )
		HandleError( AudioError::FILE_ERROR );

	if ( fileSize_ == 0 ) {
		LOG("FileRead::open: file (" << file_name << ") data size is zero!");
		HandleError( AudioError::FILE_ERROR );
	}

	return;
error:
	LOG("FileRead::open: error reading file (" << file_name << ")!");
	HandleError( AudioError::FILE_ERROR );
}

bool FileRead::GetRawInfo( const char* file_name, int channel_count, AudioFormat format, float rate ) {
	struct stat filestat;

	if ( stat(file_name, &filestat) == -1 ) {
		LOG("FileRead: Could not stat RAW file (" << file_name << ").");
		return false;
	}

	if ( channel_count == 0 ) {
		LOG("FileRead: number of channels can't be 0 (" << file_name << ").");
		return false;
	}

	dataOffset_ = 0;
	channels_ = channel_count;
	data_type_ = format;
	fileRate_ = rate;
	int sampleBytes = 0;

	if ( format == AUDIO_SINT8 ) sampleBytes = 1;
	else if ( format == AUDIO_SINT16 ) sampleBytes = 2;
	else if ( format == AUDIO_SINT32 || format == AUDIO_FLOAT32 ) sampleBytes = 4;
	else if ( format == AUDIO_FLOAT64 ) sampleBytes = 8;
	else {
		LOG("FileRead: AudioFormat " << format << " is invalid (" << file_name << ").");
		return false;
	}

	fileSize_ = (long) filestat.st_size / sampleBytes / channels_;
	byte_swap_ = false;
	#ifdef __LITTLE_ENDIAN__
	byte_swap_ = true;
	#endif
	return true;
}

bool FileRead::GetWavInfo( const char* file_name ) {
	char id[4];
	SINT32 chunkSize;

	if ( fread(&id, 4, 1, fd_) != 1 ) goto error;

	while ( strncmp(id, "fmt ", 4) ) {
		if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;

		#ifndef __LITTLE_ENDIAN__
		Swap32((unsigned char*)&chunkSize);
		#endif

		if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;

		if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
	}

	unsigned short format_tag;

	if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;

	if ( fread(&format_tag, 2, 1, fd_) != 1 ) goto error;

	#ifndef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&format_tag);
	Swap32((unsigned char*)&chunkSize);
	#endif

	if ( format_tag == 0xFFFE ) {
		dataOffset_ = ftell(fd_);

		if ( fseek(fd_, 14, SEEK_CUR) == -1 ) goto error;

		unsigned short extSize;

		if ( fread(&extSize, 2, 1, fd_) != 1 ) goto error;

		#ifndef __LITTLE_ENDIAN__
		Swap16((unsigned char*)&extSize);
		#endif

		if ( extSize == 0 ) goto error;

		if ( fseek(fd_, 6, SEEK_CUR) == -1 ) goto error;

		if ( fread(&format_tag, 2, 1, fd_) != 1 ) goto error;

		#ifndef __LITTLE_ENDIAN__
		Swap16((unsigned char*)&format_tag);
		#endif

		if ( fseek(fd_, dataOffset_, SEEK_SET) == -1 ) goto error;
	}

	if ( format_tag != 1 && format_tag != 3 ) {
		LOG("FileRead: " << file_name << " contains an unsupported data format type (" << (int)format_tag << ").");
		return false;
	}

	SINT16 temp;

	if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;

	#ifndef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&temp);
	#endif
	channels_ = (int ) temp;
	SINT32 srate;

	if ( fread(&srate, 4, 1, fd_) != 1 ) goto error;

	#ifndef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&srate);
	#endif
	fileRate_ = (float) srate;
	data_type_ = 0;

	if ( fseek(fd_, 6, SEEK_CUR) == -1 ) goto error;

	if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;

	#ifndef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&temp);
	#endif

	if ( format_tag == 1 ) {
		if ( temp == 8 )
			data_type_ = AUDIO_SINT8;
		else if ( temp == 16 )
			data_type_ = AUDIO_SINT16;
		else if ( temp == 24 )
			data_type_ = AUDIO_SINT24;
		else if ( temp == 32 )
			data_type_ = AUDIO_SINT32;
	}
	else if ( format_tag == 3 ) {
		if ( temp == 32 )
			data_type_ = AUDIO_FLOAT32;
		else if ( temp == 64 )
			data_type_ = AUDIO_FLOAT64;
	}

	if ( data_type_ == 0 ) {
		LOG("FileRead: " << (int)temp << " bits per sample with data format " << (int)format_tag << " are not supported (" << file_name << ").");
		return false;
	}

	if ( fseek(fd_, chunkSize - 16, SEEK_CUR) == -1 ) goto error;

	if ( fread(&id, 4, 1, fd_) != 1 ) goto error;

	while ( strncmp(id, "data", 4) ) {
		if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;

		#ifndef __LITTLE_ENDIAN__
		Swap32((unsigned char*)&chunkSize);
		#endif
		chunkSize += chunkSize % 2;

		if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;

		if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
	}

	SINT32 bytes;

	if ( fread(&bytes, 4, 1, fd_) != 1 ) goto error;

	#ifndef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&bytes);
	#endif
	fileSize_ = bytes / temp / channels_;
	fileSize_ *= 8;
	dataOffset_ = ftell(fd_);
	byte_swap_ = false;
	#ifndef __LITTLE_ENDIAN__
	byte_swap_ = true;
	#endif
	wavFile_ = true;
	return true;
error:
	LOG("FileRead: error reading WAV file (" << file_name << ").");
	return false;
}

bool FileRead::GetSndInfo( const char* file_name ) {
	UINT32 format;

	if ( fseek(fd_, 12, SEEK_SET) == -1 ) goto error;

	if ( fread(&format, 4, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&format);
	#endif

	if (format == 2) data_type_ = AUDIO_SINT8;
	else if (format == 3) data_type_ = AUDIO_SINT16;
	else if (format == 4) data_type_ = AUDIO_SINT24;
	else if (format == 5) data_type_ = AUDIO_SINT32;
	else if (format == 6) data_type_ = AUDIO_FLOAT32;
	else if (format == 7) data_type_ = AUDIO_FLOAT64;
	else {
		LOG("FileRead: data format in file " << file_name << " is not supported.");
		return false;
	}

	UINT32 srate;

	if ( fread(&srate, 4, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&srate);
	#endif
	fileRate_ = (float) srate;
	UINT32 chans;

	if ( fread(&chans, 4, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&chans);
	#endif
	channels_ = chans;
	UINT32 offset;

	if ( fseek(fd_, 4, SEEK_SET) == -1 ) goto error;

	if ( fread(&offset, 4, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&offset);
	#endif
	dataOffset_ = offset;

	if ( fread(&fileSize_, 4, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&fileSize_);
	#endif

	if ( data_type_ == AUDIO_SINT8 )
		fileSize_ /= channels_;

	if ( data_type_ == AUDIO_SINT16 )
		fileSize_ /= 2 * channels_;
	else if ( data_type_ == AUDIO_SINT24 )
		fileSize_ /= 3 * channels_;
	else if ( data_type_ == AUDIO_SINT32 || data_type_ == AUDIO_FLOAT32 )
		fileSize_ /= 4 * channels_;
	else if ( data_type_ == AUDIO_FLOAT64 )
		fileSize_ /= 8 * channels_;

	byte_swap_ = false;
	#ifdef __LITTLE_ENDIAN__
	byte_swap_ = true;
	#endif
	return true;
error:
	LOG("FileRead: Error reading SND file (" << file_name << ").");
	return false;
}

bool FileRead::GetAifInfo( const char* file_name ) {
	bool aifc = false;
	char id[4];

	if ( fseek(fd_, 8, SEEK_SET) == -1 ) goto error;

	if ( fread(&id, 4, 1, fd_) != 1 ) goto error;

	if ( !strncmp(id, "AIFC", 4) ) aifc = true;

	SINT32 chunkSize;

	if ( fread(&id, 4, 1, fd_) != 1) goto error;

	while ( strncmp(id, "COMM", 4) ) {
		if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;

		#ifdef __LITTLE_ENDIAN__
		Swap32((unsigned char*)&chunkSize);
		#endif
		chunkSize += chunkSize % 2;

		if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;

		if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
	}

	SINT16 temp;

	if ( fseek(fd_, 4, SEEK_CUR) == -1 ) goto error;

	if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&temp);
	#endif
	channels_ = temp;
	SINT32 frames;

	if ( fread(&frames, 4, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&frames);
	#endif
	fileSize_ = frames;

	if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;

	#ifdef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&temp);
	#endif
	unsigned char srate[10];
	unsigned char exp;
	int mantissa;
	int last;

	if ( fread(&srate, 10, 1, fd_) != 1 ) goto error;

	mantissa = (int) * (int*)(srate + 2);
	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&mantissa);
	#endif
	exp = 30 - *(srate + 1);
	last = 0;

	while (exp--) {
		last = mantissa;
		mantissa >>= 1;
	}

	if (last & 0x00000001) mantissa++;

	fileRate_ = (float) mantissa;
	byte_swap_ = false;
	#ifdef __LITTLE_ENDIAN__
	byte_swap_ = true;
	#endif
	data_type_ = 0;

	if ( aifc == false ) {
		if ( temp <= 8 ) data_type_ = AUDIO_SINT8;
		else if ( temp <= 16 ) data_type_ = AUDIO_SINT16;
		else if ( temp <= 24 ) data_type_ = AUDIO_SINT24;
		else if ( temp <= 32 ) data_type_ = AUDIO_SINT32;
	}
	else {
		if ( fread(&id, 4, 1, fd_) != 1 ) goto error;

		if ( !strncmp(id, "sowt", 4) ) {
			if ( byte_swap_ == false ) byte_swap_ = true;
			else byte_swap_ = false;
		}

		if ( !strncmp(id, "NONE", 4) || !strncmp(id, "sowt", 4) ) {
			if ( temp <= 8 ) data_type_ = AUDIO_SINT8;
			else if ( temp <= 16 ) data_type_ = AUDIO_SINT16;
			else if ( temp <= 24 ) data_type_ = AUDIO_SINT24;
			else if ( temp <= 32 ) data_type_ = AUDIO_SINT32;
		}
		else if ( (!strncmp(id, "fl32", 4) || !strncmp(id, "FL32", 4)) && temp == 32 ) data_type_ = AUDIO_FLOAT32;
		else if ( (!strncmp(id, "fl64", 4) || !strncmp(id, "FL64", 4)) && temp == 64 ) data_type_ = AUDIO_FLOAT64;
	}

	if ( data_type_ == 0 ) {
		LOG("FileRead: AIFF/AIFC file (" << file_name << ") has unsupported data type (" << id << ").");
		return false;
	}

	if ( fseek(fd_, 12, SEEK_SET) == -1 ) goto error;

	if ( fread(&id, 4, 1, fd_) != 1 ) goto error;

	while ( strncmp(id, "SSND", 4) ) {
		if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;

		#ifdef __LITTLE_ENDIAN__
		Swap32((unsigned char*)&chunkSize);
		#endif
		chunkSize += chunkSize % 2;

		if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;

		if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
	}

	if ( fseek(fd_, 12, SEEK_CUR) == -1 ) goto error;

	dataOffset_ = ftell(fd_);
	return true;
error:
	LOG("FileRead: Error reading AIFF file (" << file_name << ").");
	return false;
}

bool FileRead::FindNextMatArray( SINT32* chunkSize, SINT32* rows, SINT32* columns, SINT32* nametype ) {
	SINT32 datatype;
	*chunkSize = 0;

	do {
		if ( fseek(fd_, *chunkSize, SEEK_CUR) == -1 ) return false;

		if ( fread(&datatype, 4, 1, fd_) != 1 ) return false;

		if ( byte_swap_ ) Swap32((unsigned char*)&datatype);

		if ( fread(chunkSize, 4, 1, fd_) != 1 ) return false;

		if ( byte_swap_ ) Swap32((unsigned char*)chunkSize);
	}
	while ( datatype != 14 );

	if ( fseek(fd_, 20, SEEK_CUR) == -1 ) return false;

	SINT32 size;

	if ( fread(&size, 4, 1, fd_) != 1 ) return false;

	if ( byte_swap_ ) Swap32((unsigned char*)&size);

	if ( size != 8 ) return false;

	if ( fread(rows, 4, 1, fd_) != 1 ) return false;

	if ( byte_swap_ ) Swap32((unsigned char*)rows);

	if ( fread(columns, 4, 1, fd_) != 1 ) return false;

	if ( byte_swap_ ) Swap32((unsigned char*)columns);

	if ( fread(nametype, 4, 1, fd_) != 1 ) return false;

	if ( byte_swap_ ) Swap32((unsigned char*)nametype);

	return true;
}

bool FileRead::GetMatInfo( const char* file_name ) {
	char head[5];

	if ( fseek(fd_, 0, SEEK_SET) == -1 ) goto error;

	if ( fread(&head, 4, 1, fd_) != 1 ) goto error;

	head[4] = '\0';

	if ( strstr(head, "0") ) {
		LOG("FileRead: " << file_name << " appears to be a Version 4 MAT-file, which is not currently supported.");
		return false;
	}

	char mi[2];
	byte_swap_ = false;

	if ( fseek(fd_, 126, SEEK_SET) == -1 ) goto error;

	if ( fread(&mi, 2, 1, fd_) != 1) goto error;

	#ifdef __LITTLE_ENDIAN__

	if ( !strncmp(mi, "MI", 2) )
		byte_swap_ = true;
	else if ( strncmp(mi, "IM", 2) ) goto error;

	#else

	if ( !strncmp(mi, "IM", 2))
		byte_swap_ = true;
	else if ( strncmp(mi, "MI", 2) ) goto error;

	#endif
	bool doneParsing, haveData, haveSampleRate;
	SINT32 chunkSize, rows, columns, nametype;
	long dataoffset;
	doneParsing = false;
	haveData = false;
	haveSampleRate = false;

	while ( !doneParsing ) {
		dataoffset = ftell( fd_ );

		if ( FindNextMatArray( &chunkSize, &rows, &columns, &nametype ) == false ) {
			if ( !haveData ) {
				LOG("FileRead: No audio data found in MAT-file (" << file_name << ").");
				return false;
			}
			else if ( !haveSampleRate ) {
				fileRate_ = 44100.0f;
				LOG("FileRead: No sample rate found ... assuming 44100.0f");
				HandleError( AudioError::WARNING );
				return true;
			}
			else return true;
		}

		if ( !haveSampleRate && rows == 1 && columns == 1 ) {
			SINT32 namesize = 4;

			if ( nametype == 1 ) {
				if ( fread(&namesize, 4, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap32((unsigned char*)&namesize);

				if ( namesize != 2 ) goto tryagain;

				namesize = 8;
			}

			char name[3];
			name[2] = '\0';

			if ( fread(&name, 2, 1, fd_) != 1) goto error;

			if ( strncmp(name, "fs", 2) ) goto tryagain;

			if ( fseek(fd_, namesize - 2, SEEK_CUR) == -1 ) goto error;

			UINT32 type;
			float srate;

			if ( fread(&type, 4, 1, fd_) != 1 ) goto error;

			if ( byte_swap_ ) Swap32((unsigned char*)&type);

			if ( (type & 0xffff0000) != 0 )
				type = (type & 0x0000ffff);
			else if ( fseek(fd_, 4, SEEK_CUR) == -1 ) goto error;

			if ( type == 1 ) {
				signed char rate;

				if ( fread(&rate, 1, 1, fd_) != 1 ) goto error;

				srate = (float) rate;
			}
			else if ( type == 2 ) {
				unsigned char rate;

				if ( fread(&rate, 1, 1, fd_) != 1 ) goto error;

				srate = (float) rate;
			}
			else if ( type == 3 ) {
				SINT16 rate;

				if ( fread(&rate, 2, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap16((unsigned char*)&rate);

				srate = (float) rate;
			}
			else if ( type == 4 ) {
				UINT16 rate;

				if ( fread(&rate, 2, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap16((unsigned char*)&rate);

				srate = (float) rate;
			}
			else if ( type == 5 ) {
				SINT32 rate;

				if ( fread(&rate, 4, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap32((unsigned char*)&rate);

				srate = (float) rate;
			}
			else if ( type == 6 ) {
				UINT32 rate;

				if ( fread(&rate, 4, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap32((unsigned char*)&rate);

				srate = (float) rate;
			}
			else if ( type == 7 ) {
				FLOAT32 rate;

				if ( fread(&rate, 4, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap32((unsigned char*)&rate);

				srate = (float) rate;
			}
			else if ( type == 9 ) {
				FLOAT64 rate;

				if ( fread(&rate, 8, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap64((unsigned char*)&rate);

				srate = (float) rate;
			}
			else
				goto tryagain;

			if ( srate > 0 ) fileRate_ = srate;

			haveSampleRate = true;
		}
		else if ( !haveData ) {
			if ( rows < columns ) {
				channels_ = rows;
				fileSize_ = columns;
			}
			else {
				LOG("FileRead: Transpose the MAT-file array so that audio channels fill matrix rows (not columns).");
				return false;
			}

			SINT32 namesize = 4;

			if ( nametype == 1 ) {
				if ( fread(&namesize, 4, 1, fd_) != 1 ) goto error;

				if ( byte_swap_ ) Swap32((unsigned char*)&namesize);

				namesize = (SINT32) ceil((float)namesize / 8);

				if ( fseek( fd_, namesize * 8, SEEK_CUR) == -1 ) goto error;
			}
			else {
				if ( fseek( fd_, 4, SEEK_CUR ) == -1 ) goto error;
			}

			SINT32 type;

			if ( fread(&type, 4, 1, fd_) != 1 ) goto error;

			if ( byte_swap_ ) Swap32((unsigned char*)&type);

			if ( type == 1 )  data_type_ = AUDIO_SINT8;
			else if ( type == 3 ) data_type_ = AUDIO_SINT16;
			else if ( type == 5 ) data_type_ = AUDIO_SINT32;
			else if ( type == 7 ) data_type_ = AUDIO_FLOAT32;
			else if ( type == 9 ) data_type_ = AUDIO_FLOAT64;
			else {
				LOG("FileRead: The MAT-file array data format (" << type << ") is not supported.");
				return false;
			}

			if ( fseek(fd_, 4, SEEK_CUR) == -1 ) goto error;

			dataOffset_ = ftell(fd_);
			haveData = true;
		}

	tryagain:

		if ( haveData && haveSampleRate ) doneParsing = true;
		else if ( fseek( fd_, dataoffset + chunkSize + 8, SEEK_SET) == -1 ) goto error;
	}

	return true;
error:
	LOG("FileRead: Error reading MAT-file (" << file_name << ") header.");
	return false;
}

void FileRead::Get( AudioFrames& buffer, int StartFrame, bool doNormalize ) {
	if ( fd_ == 0 ) {
		LOG("FileRead::read: a file is not open!");
		Audio::HandleError( AudioError::WARNING );
		return;
	}

	int frame_count = buffer.GetFrameCount();

	if ( frame_count == 0 ) {
		LOG("FileRead::read: AudioFrames buffer size is zero ... no data read!");
		Audio::HandleError( AudioError::WARNING );
		return;
	}

	if ( buffer.GetChannelCount() != channels_ ) {
		LOG("FileRead::read: AudioFrames argument has incompatible number of channels!");
		Audio::HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( StartFrame >= fileSize_ ) {
		LOG("FileRead::read: StartFrame argument is greater than or equal to the file size!");
		Audio::HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( StartFrame + frame_count > fileSize_ )
		frame_count = fileSize_ - StartFrame;

	long i, nSamples = (long) ( frame_count * channels_ );
	int offset = StartFrame * channels_;

	if ( data_type_ == AUDIO_SINT16 ) {
		SINT16* buf = (SINT16*) &buffer[0];

		if ( fseek( fd_, dataOffset_ + (offset * 2), SEEK_SET ) == -1 ) goto error;

		if ( fread( buf, nSamples * 2, 1, fd_ ) != 1 ) goto error;

		if ( byte_swap_ ) {
			SINT16* ptr = buf;

			for ( i = nSamples - 1; i >= 0; i-- )
				Swap16( (unsigned char*) ptr++ );
		}

		if ( doNormalize ) {
			float gain = 1.0f / 32768.0f;

			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = buf[i] * gain;
		}
		else {
			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = buf[i];
		}
	}
	else if ( data_type_ == AUDIO_SINT32 ) {
		SINT32* buf = (SINT32*) &buffer[0];

		if ( fseek( fd_, dataOffset_ + (offset * 4 ), SEEK_SET ) == -1 ) goto error;

		if ( fread( buf, nSamples * 4, 1, fd_ ) != 1 ) goto error;

		if ( byte_swap_ ) {
			SINT32* ptr = buf;

			for ( i = nSamples - 1; i >= 0; i-- )
				Swap32( (unsigned char*) ptr++ );
		}

		if ( doNormalize ) {
			float gain = 1.0f / 2147483648.0f;

			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = buf[i] * gain;
		}
		else {
			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = (float)buf[i];
		}
	}
	else if ( data_type_ == AUDIO_FLOAT32 ) {
		FLOAT32* buf = (FLOAT32*) &buffer[0];

		if ( fseek( fd_, dataOffset_ + (offset * 4), SEEK_SET ) == -1 ) goto error;

		if ( fread( buf, nSamples * 4, 1, fd_ ) != 1 ) goto error;

		if ( byte_swap_ ) {
			FLOAT32* ptr = buf;

			for ( i = nSamples - 1; i >= 0; i-- )
				Swap32( (unsigned char*) ptr++ );
		}

		for ( i = nSamples - 1; i >= 0; i-- )
			buffer[i] = buf[i];
	}
	else if ( data_type_ == AUDIO_FLOAT64 ) {
		FLOAT64* buf = (FLOAT64*) &buffer[0];

		if ( fseek( fd_, dataOffset_ + (offset * 8), SEEK_SET ) == -1 ) goto error;

		if ( fread( buf, nSamples * 8, 1, fd_ ) != 1 ) goto error;

		if ( byte_swap_ ) {
			FLOAT64* ptr = buf;

			for ( i = nSamples - 1; i >= 0; i-- )
				Swap64( (unsigned char*) ptr++ );
		}

		for ( i = nSamples - 1; i >= 0; i-- )
			buffer[i] = buf[i];
	}
	else if ( data_type_ == AUDIO_SINT8 && wavFile_ ) {
		unsigned char* buf = (unsigned char*) &buffer[0];

		if ( fseek( fd_, dataOffset_ + offset, SEEK_SET ) == -1 ) goto error;

		if ( fread( buf, nSamples, 1, fd_) != 1 ) goto error;

		if ( doNormalize ) {
			float gain = 1.0f / 128.0f;

			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = ( buf[i] - 128 ) * gain;
		}
		else {
			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = buf[i] - 128.0f;
		}
	}
	else if ( data_type_ == AUDIO_SINT8 ) {
		char* buf = (char*) &buffer[0];

		if ( fseek( fd_, dataOffset_ + offset, SEEK_SET ) == -1 ) goto error;

		if ( fread( buf, nSamples, 1, fd_ ) != 1 ) goto error;

		if ( doNormalize ) {
			float gain = 1.0f / 128.0f;

			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = buf[i] * gain;
		}
		else {
			for ( i = nSamples - 1; i >= 0; i-- )
				buffer[i] = buf[i];
		}
	}
	else if ( data_type_ == AUDIO_SINT24 ) {
		SINT32 temp;
		unsigned char* ptr = (unsigned char*) &temp;
		float gain = 1.0f / 2147483648.0f;

		if ( fseek(fd_, dataOffset_ + (offset * 3), SEEK_SET ) == -1 ) goto error;

		for ( i = 0; i < nSamples; i++ ) {
			#ifdef __LITTLE_ENDIAN__

			if ( byte_swap_ ) {
				if ( fread( ptr, 3, 1, fd_ ) != 1 ) goto error;

				temp &= 0x00ffffff;
				Swap32( (unsigned char*) ptr );
			}
			else {
				if ( fread( ptr + 1, 3, 1, fd_ ) != 1 ) goto error;

				temp &= 0xffffff00;
			}

			#else

			if ( byte_swap_ ) {
				if ( fread( ptr + 1, 3, 1, fd_ ) != 1 ) goto error;

				temp &= 0xffffff00;
				Swap32( (unsigned char*) ptr );
			}
			else {
				if ( fread( ptr, 3, 1, fd_ ) != 1 ) goto error;

				temp &= 0x00ffffff;
			}

			#endif

			if ( doNormalize )
				buffer[i] = (float) temp * gain;
			else
				buffer[i] = (float) temp / 256;
		}
	}

	buffer.SetDataRate( fileRate_ );
	return;
error:
	LOG("FileRead: Error reading file data.");
	HandleError( AudioError::FILE_ERROR);
}

NAMESPACE_AUDIO_END
