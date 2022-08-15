#ifndef _AudioCore_FILEREAD_H
#define _AudioCore_FILEREAD_H


NAMESPACE_AUDIO_BEGIN


class FileRead : public Audio {
public:

	FileRead();

	FileRead( String file_name, bool type_raw = false, unsigned int channel_count = 1,
			  AudioFormat format = AUDIO_SINT16, double rate = 22050.0 );
	~FileRead();

	void Open( String file_name, bool type_raw = false, unsigned int channel_count = 1,
			   AudioFormat format = AUDIO_SINT16, double rate = 22050.0 );
	void Close();
	bool isOpen();

	unsigned long fileSize() const {
		return fileSize_;
	};

	unsigned int GetChannelCount() const {
		return channels_;
	};

	AudioFormat format() const {
		return data_type_;
	};

	double fileRate() const {
		return fileRate_;
	};

	void Get( AudioFrames& buffer, unsigned long StartFrame = 0, bool doNormalize = true );

protected:


	bool GetRawInfo( const char* file_name, unsigned int channel_count,
					 AudioFormat format, double rate );
	bool GetWavInfo( const char* file_name );
	bool GetSndInfo( const char* file_name );
	bool GetAifInfo( const char* file_name );
	bool GetMatInfo( const char* file_name );
	bool FindNextMatArray( SINT32* chunkSize, SINT32* rows, SINT32* columns, SINT32* nametype );

	FILE* fd_;
	bool byte_swap_;
	bool wavFile_;
	unsigned long fileSize_;
	unsigned long dataOffset_;
	unsigned int channels_;
	AudioFormat data_type_;
	double fileRate_;
};

NAMESPACE_AUDIO_END

#endif
