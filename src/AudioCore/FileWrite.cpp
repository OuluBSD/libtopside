#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

const FileWrite::FILE_TYPE FileWrite::FILE_RAW = 1;
const FileWrite::FILE_TYPE FileWrite::FILE_WAV = 2;
const FileWrite::FILE_TYPE FileWrite::FILE_SND = 3;
const FileWrite::FILE_TYPE FileWrite::FILE_AIF = 4;
const FileWrite::FILE_TYPE FileWrite::FILE_MAT = 5;




struct WaveHeader {
	char riff[4];
	SINT32 fileSize;
	char wave[4];
	char fmt[4];
	SINT32 chunkSize;
	SINT16 formatCode;
	SINT16 channel_count;
	SINT32 sampleRate;
	SINT32 bytesPerSecond;
	SINT16 bytesPerSample;
	SINT16 bitsPerSample;
	SINT16 cbSize;
	SINT16 validBits;
	SINT32 channelMask;
	char subformat[16];
	char fact[4];
	SINT32 factSize;
	SINT32 frames;
};


struct SndHeader {
	char pref[4];
	SINT32 headerBytes;
	SINT32 dataBytes;
	SINT32 format;
	SINT32 sampleRate;
	SINT32 channel_count;
	char comment[16];
};



struct AifHeader {
	char form[4];
	SINT32 formSize;
	char aiff[4];
	char comm[4];
	SINT32 commSize;
	SINT16 channel_count;
	int sampleFrames;
	SINT16 sampleSize;
	unsigned char srate[10];
};

struct AifSsnd {
	char ssnd[4];
	SINT32 ssndSize;
	int offset;
	int blockSize;
};


struct MatHeader {
	char heading[124];
	SINT16 hff[2];
	SINT32 fs[16];
	SINT32 adf[11];

};

FileWrite::FileWrite()
	: fd_( 0 ) {
}

FileWrite::FileWrite( String file_name, int channel_count, FILE_TYPE type, Audio::AudioFormat format )
	: fd_( 0 ) {
	this->Open( file_name, channel_count, type, format );
}

FileWrite::~FileWrite() {
	this->Close();
}

void FileWrite::Close() {
	if ( fd_ == 0 ) return;

	if ( file_type_ == FILE_RAW )
		fclose( fd_ );
	else if ( file_type_ == FILE_WAV )
		this->CloseWavFile();
	else if ( file_type_ == FILE_SND )
		this->CloseSndFile();
	else if ( file_type_ == FILE_AIF )
		this->CloseAifFile();
	else if ( file_type_ == FILE_MAT )
		this->CloseMatFile();

	fd_ = 0;
}

bool FileWrite::isOpen() {
	if ( fd_ ) return true;
	else return false;
}

void FileWrite::Open( String file_name, int channel_count, FileWrite::FILE_TYPE type, Audio::AudioFormat format ) {
	this->Close();

	if ( channel_count < 1 ) {
		LOG("FileWrite::open: then channels argument must be greater than zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	channels_ = channel_count;
	file_type_ = type;

	if ( format != AUDIO_SINT8 && format != AUDIO_SINT16 &&
		 format != AUDIO_SINT24 && format != AUDIO_SINT32 &&
		 format != AUDIO_FLOAT32 && format != AUDIO_FLOAT64 ) {
		LOG("FileWrite::open: unknown data type (" << format << ") specified!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	data_type_ = format;
	bool result = false;

	if ( file_type_ == FILE_RAW ) {
		if ( channels_ != 1 ) {
			LOG("FileWrite::open: AUDIO RAW files are, by definition, always monaural (channels = " << channel_count << " not supported)!");
			HandleError( AudioError::FUNCTION_ARGUMENT );
		}

		result = SetRawFile( file_name );
	}
	else if ( file_type_ == FILE_WAV )
		result = SetWavFile( file_name );
	else if ( file_type_ == FILE_SND )
		result = SetSndFile( file_name );
	else if ( file_type_ == FILE_AIF )
		result = SetAifFile( file_name );
	else if ( file_type_ == FILE_MAT )
		result = SetMatFile( file_name );
	else {
		LOG("FileWrite::open: unknown file type (" << file_type_ << ") specified!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( result == false )
		HandleError( AudioError::FILE_ERROR );

	frame_counter_ = 0;
}

bool FileWrite::SetRawFile( String file_name ) {
	if ( file_name.Find( ".raw" ) == -1 ) file_name += ".raw";

	fd_ = fopen( file_name.Begin(), "wb" );

	if ( !fd_ ) {
		LOG("FileWrite: could not create RAW file: " << file_name << '.');
		return false;
	}

	if ( data_type_ != AUDIO_SINT16 ) {
		data_type_ = AUDIO_SINT16;
		LOG("FileWrite: using 16-bit signed integer data format for file " << file_name << '.');
		HandleError( AudioError::WARNING );
	}

	byte_swap_ = false;
	#ifdef __LITTLE_ENDIAN__
	byte_swap_ = true;
	#endif
	LOG("FileWrite: creating RAW file: " << file_name);
	HandleError( AudioError::STATUS );
	return true;
}

bool FileWrite::SetWavFile( String file_name ) {
	if ( file_name.Find( ".wav" ) == -1 ) file_name += ".wav";

	fd_ = fopen( file_name.Begin(), "wb" );

	if ( !fd_ ) {
		LOG("FileWrite: could not create WAV file: " << file_name);
		return false;
	}

	struct WaveHeader hdr = { {'R', 'I', 'F', 'F'}, 44, {'W', 'A', 'V', 'E'}, {'f', 'm', 't', ' '}, 16, 1, 1,
		(SINT32) Audio::GetSampleRate(), 0, 2, 16, 0, 0, 0,
		{'\x01', '\x00', '\x00', '\x00', '\x00', '\x00', '\x10', '\x00', '\x80', '\x00', '\x00', '\xAA', '\x00', '\x38', '\x9B', '\x71'},
		{'f', 'a', 'c', 't'}, 4, 0
	};

	hdr.channel_count = (SINT16) channels_;

	if ( data_type_ == AUDIO_SINT8 )
		hdr.bitsPerSample = 8;
	else if ( data_type_ == AUDIO_SINT16 )
		hdr.bitsPerSample = 16;
	else if ( data_type_ == AUDIO_SINT24 )
		hdr.bitsPerSample = 24;
	else if ( data_type_ == AUDIO_SINT32 )
		hdr.bitsPerSample = 32;
	else if ( data_type_ == AUDIO_FLOAT32 ) {
		hdr.formatCode = 3;
		hdr.bitsPerSample = 32;
	}
	else if ( data_type_ == AUDIO_FLOAT64 ) {
		hdr.formatCode = 3;
		hdr.bitsPerSample = 64;
	}

	hdr.bytesPerSample = (SINT16) (channels_ * hdr.bitsPerSample / 8);
	hdr.bytesPerSecond = (SINT32) (hdr.sampleRate * hdr.bytesPerSample);
	int bytesToWrite = 36;

	if ( channels_ > 2 || hdr.bitsPerSample > 16 ) {
		bytesToWrite = 72;
		hdr.chunkSize += 24;
		hdr.formatCode = 0xFFFE;
		hdr.cbSize = 22;
		hdr.validBits = hdr.bitsPerSample;
		SINT16* subFormat = (SINT16*)&hdr.subformat[0];

		if ( data_type_ == AUDIO_FLOAT32 || data_type_ == AUDIO_FLOAT64 )
			*subFormat = 3;
		else *subFormat = 1;
	}

	byte_swap_ = false;
	#ifndef __LITTLE_ENDIAN__
	byte_swap_ = true;
	Swap32((unsigned char*)&hdr.chunkSize);
	Swap16((unsigned char*)&hdr.formatCode);
	Swap16((unsigned char*)&hdr.channel_count);
	Swap32((unsigned char*)&hdr.sampleRate);
	Swap32((unsigned char*)&hdr.bytesPerSecond);
	Swap16((unsigned char*)&hdr.bytesPerSample);
	Swap16((unsigned char*)&hdr.bitsPerSample);
	Swap16((unsigned char*)&hdr.cbSize);
	Swap16((unsigned char*)&hdr.validBits);
	Swap16((unsigned char*)&hdr.subformat[0]);
	Swap32((unsigned char*)&hdr.factSize);
	#endif
	char data[4] = {'d', 'a', 't', 'a'};
	SINT32 dataSize = 0;

	if ( fwrite(&hdr, 1, bytesToWrite, fd_) != bytesToWrite ) goto error;

	if ( fwrite(&data, 4, 1, fd_) != 1 ) goto error;

	if ( fwrite(&dataSize, 4, 1, fd_) != 1 ) goto error;

	LOG("FileWrite: creating WAV file: " << file_name);
	HandleError( AudioError::STATUS );
	return true;
error:
	LOG("FileWrite: could not write WAV header for file: " << file_name);
	return false;
}

void FileWrite::CloseWavFile() {
	int bytesPerSample = 1;

	if ( data_type_ == AUDIO_SINT16 )
		bytesPerSample = 2;
	else if ( data_type_ == AUDIO_SINT24 )
		bytesPerSample = 3;
	else if ( data_type_ == AUDIO_SINT32 || data_type_ == AUDIO_FLOAT32 )
		bytesPerSample = 4;
	else if ( data_type_ == AUDIO_FLOAT64 )
		bytesPerSample = 8;

	bool useExtensible = false;
	int dataLocation = 40;

	if ( bytesPerSample > 2 || channels_ > 2 ) {
		useExtensible = true;
		dataLocation = 76;
	}

	SINT32 bytes = (SINT32) (frame_counter_ * channels_ * bytesPerSample);

	if ( bytes % 2 ) {
		signed char sample = 0;
		fwrite( &sample, 1, 1, fd_ );
	}

	#ifndef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&bytes);
	#endif
	fseek( fd_, dataLocation, SEEK_SET );
	fwrite( &bytes, 4, 1, fd_ );
	bytes = (SINT32) (frame_counter_ * channels_ * bytesPerSample + 44);

	if ( useExtensible ) bytes += 36;

	#ifndef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&bytes);
	#endif
	fseek( fd_, 4, SEEK_SET );
	fwrite( &bytes, 4, 1, fd_ );

	if ( useExtensible ) {
		bytes = (SINT32) frame_counter_;
		#ifndef __LITTLE_ENDIAN__
		Swap32((unsigned char*)&bytes);
		#endif
		fseek( fd_, 68, SEEK_SET );
		fwrite( &bytes, 4, 1, fd_ );
	}

	fclose( fd_ );
}

bool FileWrite::SetSndFile( String file_name ) {
	String name( file_name );

	if ( file_name.Find( ".snd" ) == -1 ) file_name += ".snd";

	fd_ = fopen( file_name.Begin(), "wb" );

	if ( !fd_ ) {
		LOG("FileWrite: could not create SND file: " << file_name);
		return false;
	}

	struct SndHeader hdr = {".sn", 40, 0, 3, (SINT32) Audio::GetSampleRate(), 1, "By UScript"};

	hdr.pref[3] = 'd';

	hdr.channel_count = channels_;

	if ( data_type_ == AUDIO_SINT8 )
		hdr.format = 2;
	else if ( data_type_ == AUDIO_SINT16 )
		hdr.format = 3;
	else if ( data_type_ == AUDIO_SINT24 )
		hdr.format = 4;
	else if ( data_type_ == AUDIO_SINT32 )
		hdr.format = 5;
	else if ( data_type_ == AUDIO_FLOAT32 )
		hdr.format = 6;
	else if ( data_type_ == AUDIO_FLOAT64 )
		hdr.format = 7;

	byte_swap_ = false;
	#ifdef __LITTLE_ENDIAN__
	byte_swap_ = true;
	Swap32 ((unsigned char*)&hdr.headerBytes);
	Swap32 ((unsigned char*)&hdr.format);
	Swap32 ((unsigned char*)&hdr.sampleRate);
	Swap32 ((unsigned char*)&hdr.channel_count);
	#endif

	if ( fwrite(&hdr, 4, 10, fd_) != 10 ) {
		LOG("FileWrite: Could not write SND header for file " << file_name << '.');
		return false;
	}

	LOG("FileWrite: creating SND file: " << file_name);
	HandleError( AudioError::STATUS );
	return true;
}

void FileWrite::CloseSndFile() {
	int bytesPerSample = 1;

	if ( data_type_ == AUDIO_SINT16 )
		bytesPerSample = 2;
	else if ( data_type_ == AUDIO_SINT24 )
		bytesPerSample = 3;
	else if ( data_type_ == AUDIO_SINT32 )
		bytesPerSample = 4;
	else if ( data_type_ == AUDIO_FLOAT32 )
		bytesPerSample = 4;
	else if ( data_type_ == AUDIO_FLOAT64 )
		bytesPerSample = 8;

	SINT32 bytes = (SINT32) (frame_counter_ * bytesPerSample * channels_);
	#ifdef __LITTLE_ENDIAN__
	Swap32 ((unsigned char*)&bytes);
	#endif
	fseek(fd_, 8, SEEK_SET);
	fwrite(&bytes, 4, 1, fd_);
	fclose(fd_);
}

bool FileWrite::SetAifFile( String file_name ) {
	String name( file_name );

	if ( file_name.Find( ".aif" ) == -1 ) file_name += ".aif";

	fd_ = fopen( file_name.Begin(), "wb" );

	if ( !fd_ ) {
		LOG("FileWrite: could not create AIF file: " << file_name);
		return false;
	}

	struct AifHeader hdr = {{'F', 'O', 'R', 'M'}, 46, {'A', 'I', 'F', 'F'}, {'C', 'O', 'M', 'M'}, 18, 0, 0, 16, "0"};

	struct AifSsnd ssnd = {{'S', 'S', 'N', 'D'}, 8, 0, 0};

	hdr.channel_count = channels_;

	if ( data_type_ == AUDIO_SINT8 )
		hdr.sampleSize = 8;
	else if ( data_type_ == AUDIO_SINT16 )
		hdr.sampleSize = 16;
	else if ( data_type_ == AUDIO_SINT24 )
		hdr.sampleSize = 24;
	else if ( data_type_ == AUDIO_SINT32 )
		hdr.sampleSize = 32;
	else if ( data_type_ == AUDIO_FLOAT32 ) {
		hdr.aiff[3] = 'C';
		hdr.sampleSize = 32;
		hdr.commSize = 24;
	}
	else if ( data_type_ == AUDIO_FLOAT64 ) {
		hdr.aiff[3] = 'C';
		hdr.sampleSize = 64;
		hdr.commSize = 24;
	}

	SINT16 i;
	int exp;
	int rate = (int) Audio::GetSampleRate();
	memset( hdr.srate, 0, 10 );
	exp = rate;

	for ( i = 0; i < 32; i++ ) {
		exp >>= 1;

		if ( !exp ) break;
	}

	i += 16383;
	#ifdef __LITTLE_ENDIAN__
	Swap16((unsigned char*)&i);
	#endif
	memcpy( hdr.srate, &i, sizeof(SINT16) );

	for ( i = 32; i; i-- ) {
		if ( rate & 0x80000000 ) break;

		rate <<= 1;
	}

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&rate);
	#endif
	memcpy( hdr.srate + 2, &rate, sizeof(rate) );
	byte_swap_ = false;
	#ifdef __LITTLE_ENDIAN__
	byte_swap_ = true;
	Swap32((unsigned char*)&hdr.formSize);
	Swap32((unsigned char*)&hdr.commSize);
	Swap16((unsigned char*)&hdr.channel_count);
	Swap16((unsigned char*)&hdr.sampleSize);
	Swap32((unsigned char*)&ssnd.ssndSize);
	Swap32((unsigned char*)&ssnd.offset);
	Swap32((unsigned char*)&ssnd.blockSize);
	#endif

	if ( fwrite(&hdr, 4, 5, fd_) != 5 ) goto error;

	if ( fwrite(&hdr.channel_count, 2, 1, fd_) != 1 ) goto error;

	if ( fwrite(&hdr.sampleFrames, 4, 1, fd_) != 1 ) goto error;

	if ( fwrite(&hdr.sampleSize, 2, 1, fd_) != 1 ) goto error;

	if ( fwrite(&hdr.srate, 10, 1, fd_) != 1 ) goto error;

	if ( data_type_ == AUDIO_FLOAT32 ) {
		char type[4] = {'f', 'l', '3', '2'};
		char zeroes[2] = { 0, 0 };

		if ( fwrite(&type, 4, 1, fd_) != 1 ) goto error;

		if ( fwrite(&zeroes, 2, 1, fd_) != 1 ) goto error;
	}
	else if ( data_type_ == AUDIO_FLOAT64 ) {
		char type[4] = {'f', 'l', '6', '4'};
		char zeroes[2] = { 0, 0 };

		if ( fwrite(&type, 4, 1, fd_) != 1 ) goto error;

		if ( fwrite(&zeroes, 2, 1, fd_) != 1 ) goto error;
	}

	if ( fwrite(&ssnd, 4, 4, fd_) != 4 ) goto error;

	LOG("FileWrite: creating AIF file: " << file_name);
	HandleError( AudioError::STATUS );
	return true;
error:
	LOG("FileWrite: could not write AIF header for file: " << file_name);
	return false;
}

void FileWrite::CloseAifFile() {
	int frames = (int) frame_counter_;
	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&frames);
	#endif
	fseek(fd_, 22, SEEK_SET);
	fwrite(&frames, 4, 1, fd_);
	int bytesPerSample = 1;

	if ( data_type_ == AUDIO_SINT16 )
		bytesPerSample = 2;

	if ( data_type_ == AUDIO_SINT24 )
		bytesPerSample = 3;
	else if ( data_type_ == AUDIO_SINT32 || data_type_ == AUDIO_FLOAT32 )
		bytesPerSample = 4;
	else if ( data_type_ == AUDIO_FLOAT64 )
		bytesPerSample = 8;

	int bytes = frame_counter_ * bytesPerSample * channels_ + 46;

	if ( data_type_ == AUDIO_FLOAT32 || data_type_ == AUDIO_FLOAT64 ) bytes += 6;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&bytes);
	#endif
	fseek(fd_, 4, SEEK_SET);
	fwrite(&bytes, 4, 1, fd_);
	bytes = frame_counter_ * bytesPerSample * channels_ + 8;

	if ( data_type_ == AUDIO_FLOAT32 || data_type_ == AUDIO_FLOAT64 ) bytes += 6;

	#ifdef __LITTLE_ENDIAN__
	Swap32((unsigned char*)&bytes);
	#endif

	if ( data_type_ == AUDIO_FLOAT32 || data_type_ == AUDIO_FLOAT64 )
		fseek(fd_, 48, SEEK_SET);
	else
		fseek(fd_, 42, SEEK_SET);

	fwrite(&bytes, 4, 1, fd_);
	fclose( fd_ );
}

bool FileWrite::SetMatFile( String file_name ) {
	if ( file_name.Find( ".mat" ) == -1 ) file_name += ".mat";

	fd_ = fopen( file_name.Begin(), "w+b" );

	if ( !fd_ ) {
		LOG("FileWrite: could not create MAT file: " << file_name);
		return false;
	}

	if ( data_type_ != AUDIO_FLOAT64 ) {
		data_type_ = AUDIO_FLOAT64;
		LOG("FileWrite: using 64-bit floating-point data format for file " << file_name << '.');
		HandleError( AudioError::DEBUG_PRINT );
	}

	struct MatHeader hdr;

	strcpy( hdr.heading, "MATLAB 5.0 MAT-file, Generated using the Synthesis ToolKit in C++ (AUDIO). By Perry R. Cook and Gary P. Scavone." );

	for ( size_t i = strlen(hdr.heading); i < 124; i++ ) hdr.heading[i] = ' ';

	hdr.hff[0] = (SINT16) 0x0100;
	hdr.hff[1] = (SINT16) 'M';
	hdr.hff[1] <<= 8;
	hdr.hff[1] += 'I';
	hdr.fs[0] = (SINT32) 14;
	hdr.fs[1] = (SINT32) 56;
	hdr.fs[2] = (SINT32) 6;
	hdr.fs[3] = (SINT32) 8;
	hdr.fs[4] = (SINT32) 6;
	hdr.fs[5] = (SINT32) 0;
	hdr.fs[6] = (SINT32) 5;
	hdr.fs[7] = (SINT32) 8;
	hdr.fs[8] = (SINT32) 1;
	hdr.fs[9] = (SINT32) 1;
	hdr.fs[10] = 0x00020001;
	hdr.fs[11] = 's' << 8;
	hdr.fs[11] += 'f';
	hdr.fs[12] = 9;
	hdr.fs[13] = 8;
	FLOAT64* sampleRate = (FLOAT64*)&hdr.fs[14];
	*sampleRate = (FLOAT64) Audio::GetSampleRate();
	hdr.adf[0] = (SINT32) 14;
	hdr.adf[1] = (SINT32) 0;
	hdr.adf[2] = (SINT32) 6;
	hdr.adf[3] = (SINT32) 8;
	hdr.adf[4] = (SINT32) 6;
	hdr.adf[5] = (SINT32) 0;
	hdr.adf[6] = (SINT32) 5;
	hdr.adf[7] = (SINT32) 8;
	hdr.adf[8] = (SINT32) channels_;
	hdr.adf[9] = (SINT32) 0;
	String name = file_name;
	size_t found;
	found = FindLastOf(name, "/\\", 0);
	name = name.Mid(found + 1);
	SINT32 nameGetCount = (SINT32) name.GetCount() - 4;

	if ( nameGetCount > 31 ) nameGetCount = 31;

	if ( nameGetCount > 4 )
		hdr.adf[10] = (SINT32) 1;
	else
		hdr.adf[10] = (nameGetCount << 16) + 1;

	SINT32 headsize = 40;

	if ( fwrite(&hdr, 236, 1, fd_) != 1 ) goto error;

	SINT32 tmp;

	if ( nameGetCount > 4 ) {
		if ( fwrite(&nameGetCount, 4, 1, fd_) != 1) goto error;

		if ( fwrite(name.Begin(), nameGetCount, 1, fd_) != 1 ) goto error;

		tmp = (SINT32) ceil((float)nameGetCount / 8);

		if ( fseek(fd_, tmp * 8 - nameGetCount, SEEK_CUR) == -1 ) goto error;

		headsize += tmp * 8;
	}
	else {
		if ( fwrite(name.Begin(), nameGetCount, 1, fd_) != 1 ) goto error;

		tmp = 4 - nameGetCount;

		if ( fseek(fd_, tmp, SEEK_CUR) == -1 ) goto error;
	}

	tmp = 9;

	if ( fwrite(&tmp, 4, 1, fd_) != 1 ) goto error;

	tmp = 0;

	if ( fwrite(&tmp, 4, 1, fd_) != 1 ) goto error;

	headsize += 8;

	if ( fseek(fd_, 196, SEEK_SET) == -1 ) goto error;

	if ( fwrite(&headsize, 4, 1, fd_) != 1 ) goto error;

	if ( fseek(fd_, 0, SEEK_END) == -1 ) goto error;

	byte_swap_ = false;
	LOG("FileWrite: creating MAT-file: " << file_name);
	HandleError( AudioError::STATUS );
	return true;
error:
	LOG("FileWrite: could not write MAT-file header for file " << file_name << '.');
	return false;
}

void FileWrite::CloseMatFile() {
	fseek(fd_, 228, SEEK_SET);
	fwrite(&frame_counter_, 4, 1, fd_);
	SINT32 headsize, temp;
	fseek(fd_, 196, SEEK_SET);

	if (fread(&headsize, 4, 1, fd_) < 4) {
		LOG("FileWrite: could not read MAT-file header size.");
		goto Close_file;
	}

	temp = headsize;
	headsize += (SINT32) (frame_counter_ * 8 * channels_);
	fseek(fd_, 196, SEEK_SET);
	fwrite(&headsize, 4, 1, fd_);
	fseek(fd_, temp + 196, SEEK_SET);
	temp = (SINT32) (frame_counter_ * 8 * channels_);
	fwrite(&temp, 4, 1, fd_);
Close_file:
	fclose(fd_);
}

void FileWrite::write( AudioFrames& buffer ) {
	if ( fd_ == 0 ) {
		LOG("FileWrite::write(): a file has not yet been opened!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( buffer.GetChannelCount() != channels_ ) {
		LOG("FileWrite::write(): number of channels in the AudioFrames argument does not match that specified to Open() function!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
		return;
	}

	int nSamples = buffer.GetCount();

	if ( data_type_ == AUDIO_SINT16 ) {
		SINT16 sample;

		for ( int k = 0; k < nSamples; k++ ) {
			sample = (SINT16) (buffer[k] * 32767.0f);

			if ( byte_swap_ ) Swap16( (unsigned char*)&sample );

			if ( fwrite(&sample, 2, 1, fd_) != 1 ) goto error;
		}
	}
	else if ( data_type_ == AUDIO_SINT8 ) {
		if ( file_type_ == FILE_WAV ) {
			unsigned char sample;

			for ( int k = 0; k < nSamples; k++ ) {
				sample = (unsigned char) (buffer[k] * 127.0 + 128.0f);

				if ( fwrite(&sample, 1, 1, fd_) != 1 ) goto error;
			}
		}
		else {
			signed char sample;

			for ( int k = 0; k < nSamples; k++ ) {
				sample = (signed char) (buffer[k] * 127.0f);

				if ( fwrite(&sample, 1, 1, fd_) != 1 ) goto error;
			}
		}
	}
	else if ( data_type_ == AUDIO_SINT32 ) {
		SINT32 sample;

		for ( int k = 0; k < nSamples; k++ ) {
			sample = (SINT32) (buffer[k] * 2147483647.0f);

			if ( byte_swap_ ) Swap32( (unsigned char*)&sample );

			if ( fwrite(&sample, 4, 1, fd_) != 1 ) goto error;
		}
	}
	else if ( data_type_ == AUDIO_FLOAT32 ) {
		FLOAT32 sample;

		for ( int k = 0; k < nSamples; k++ ) {
			sample = (FLOAT32) (buffer[k]);

			if ( byte_swap_ ) Swap32( (unsigned char*)&sample );

			if ( fwrite(&sample, 4, 1, fd_) != 1 ) goto error;
		}
	}
	else if ( data_type_ == AUDIO_FLOAT64 ) {
		FLOAT64 sample;

		for ( int k = 0; k < nSamples; k++ ) {
			sample = (FLOAT64) (buffer[k]);

			if ( byte_swap_ ) Swap64( (unsigned char*)&sample );

			if ( fwrite(&sample, 8, 1, fd_) != 1 ) goto error;
		}
	}
	else if ( data_type_ == AUDIO_SINT24 ) {
		SINT32 sample;

		for ( int k = 0; k < nSamples; k++ ) {
			sample = (SINT32) (buffer[k] * 8388607.0f);

			if ( byte_swap_ ) {
				Swap32( (unsigned char*)&sample );
				unsigned char* ptr = (unsigned char*) &sample;

				if ( fwrite(ptr + 1, 3, 1, fd_) != 1 ) goto error;
			}
			else if ( fwrite(&sample, 3, 1, fd_) != 1 ) goto error;
		}
	}

	frame_counter_ += buffer.GetFrameCount();
	return;
error:
	LOG("FileWrite::write(): error writing data to file!");
	HandleError( AudioError::FILE_ERROR );
}

NAMESPACE_AUDIO_END
