#ifndef _AudioCore_FILELOOP_H
#define _AudioCore_FILELOOP_H


NAMESPACE_AUDIO_BEGIN


class FileLoop : protected FileWaveIn {
public:

	FileLoop( int chunkThreshold = 1000000, int chunkSize = 1024 );

	FileLoop( String file_name, bool raw = false, bool doNormalize = true,
			  int chunkThreshold = 1000000, int chunkSize = 1024 );
	~FileLoop();

	void OpenFile( String file_name, bool raw = false, bool doNormalize = true );


	void CloseFile() {
		FileWaveIn::CloseFile();
	};

	void Reset() {
		FileWaveIn::Reset();
	};

	int GetChannelsOut() const {
		return data_.GetChannelCount();
	};

	void Normalize() {
		FileWaveIn::Normalize( 1.0f );
	};

	void Normalize( float peak ) {
		FileWaveIn::Normalize( peak );
	};

	int GetSize() const {
		return data_.GetFrameCount();
	};

	float GetFileRate() const {
		return data_.dataRate();
	};

	void SetRate( float rate );

	void SetFrequency( float frequency ) {
		this->SetRate( fileSize_ * frequency / Audio::GetSampleRate() );
	};

	void AddTime( float time );
	void AddPhase( float angle );
	void AddPhaseOffset( float angle );

	float GetLastOut( int channel = 0 ) {
		return FileWaveIn::GetLastOut( channel );
	};

	float Tick( int channel = 0 );
	virtual AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	AudioFrames first_frame_;
	float phase_offset_;

};

NAMESPACE_AUDIO_END

#endif
