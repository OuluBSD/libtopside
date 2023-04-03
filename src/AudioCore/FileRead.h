#ifndef _AudioCore_FILEREAD_H
#define _AudioCore_FILEREAD_H


NAMESPACE_AUDIO_BEGIN


class FileRead : public Audio {
public:

	FileRead();

	FileRead( String file_name, bool type_raw = false, int channel_count = 1,
			  AudioFormat format = AUDIO_SINT16, float rate = 22050.0f );
	~FileRead();

	void Open( String file_name, bool type_raw = false, int channel_count = 1,
			   AudioFormat format = AUDIO_SINT16, float rate = 22050.0f );
	void Close();
	bool isOpen();

	int fileSize() const {
		return fileSize_;
	};

	int GetChannelCount() const {
		return channels_;
	};

	AudioFormat format() const {
		return data_type_;
	};

	float fileRate() const {
		return fileRate_;
	};

	void Get( AudioFrames& buffer, int StartFrame = 0, bool doNormalize = true );

protected:


	bool GetRawInfo( const char* file_name, int channel_count,
					 AudioFormat format, float rate );
	bool GetWavInfo( const char* file_name );
	bool GetSndInfo( const char* file_name );
	bool GetAifInfo( const char* file_name );
	bool GetMatInfo( const char* file_name );
	bool FindNextMatArray( SINT32* chunkSize, SINT32* rows, SINT32* columns, SINT32* nametype );

	FILE* fd_;
	bool byte_swap_;
	bool wavFile_;
	int fileSize_;
	int dataOffset_;
	int channels_;
	AudioFormat data_type_;
	float fileRate_;
};

NAMESPACE_AUDIO_END

#endif
