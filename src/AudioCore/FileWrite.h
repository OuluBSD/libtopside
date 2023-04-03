#ifndef _AudioCore_FILEWRITE_H
#define _AudioCore_FILEWRITE_H


NAMESPACE_AUDIO_BEGIN



class FileWrite : public Audio {
public:

	typedef int FILE_TYPE;

	static const FILE_TYPE FILE_RAW;
	static const FILE_TYPE FILE_WAV;
	static const FILE_TYPE FILE_SND;
	static const FILE_TYPE FILE_AIF;
	static const FILE_TYPE FILE_MAT;


	FileWrite();
	FileWrite( String file_name, int channel_count = 1, FILE_TYPE type = FILE_WAV, Audio::AudioFormat format = AUDIO_SINT16 );
	virtual ~FileWrite();

	void Open( String file_name, int channel_count = 1,
			   FileWrite::FILE_TYPE type = FILE_WAV, Audio::AudioFormat format = AUDIO_SINT16 );
	void Close();
	bool isOpen();
	void write( AudioFrames& buffer );

protected:

	bool SetRawFile( String file_name );
	bool SetWavFile( String file_name );
	void CloseWavFile();
	bool SetSndFile( String file_name );
	void CloseSndFile();
	bool SetAifFile( String file_name );
	void CloseAifFile();
	bool SetMatFile( String file_name );
	void CloseMatFile();

	FILE* fd_;
	FILE_TYPE file_type_;
	AudioFormat data_type_;
	int channels_;
	int frame_counter_;
	bool byte_swap_;

};

NAMESPACE_AUDIO_END

#endif
