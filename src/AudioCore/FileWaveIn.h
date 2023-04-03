#ifndef _AudioCore_FILEWVIN_H
#define _AudioCore_FILEWVIN_H


NAMESPACE_AUDIO_BEGIN


class FileWaveIn : public WaveIn {
public:

	FileWaveIn( int chunkThreshold = 1000000, int chunkSize = 1024 );

	FileWaveIn( String file_name, bool raw = false, bool doNormalize = true,
				int chunkThreshold = 1000000, int chunkSize = 1024 );

	~FileWaveIn();

	virtual void OpenFile( String file_name, bool raw = false, bool doNormalize = true );
	virtual void CloseFile();
	virtual void Reset();
	virtual void Normalize();
	virtual void Normalize( float peak );

	virtual int GetSize() const {
		return fileSize_;
	};

	virtual float GetFileRate() const {
		return data_.dataRate();
	};

	bool isOpen() {
		return file_.isOpen();
	};

	bool IsFinished() const {
		return finished_;
	};

	virtual void SetRate( float rate );
	virtual void AddTime( float time );

	void SetInterpolate( bool doInterpolate ) {
		interpolate_ = doInterpolate;
	};

	float GetLastOut( int channel = 0 );
	virtual float Tick( int channel = 0 );
	virtual AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	void SampleRateChanged( float new_rate, float old_rate );

	FileRead file_;
	bool finished_;
	bool interpolate_;
	bool normalizing_;
	bool chunking_;
	float time_;
	float rate_;
	int fileSize_;
	int chunkThreshold_;
	int chunkSize_;
	long chunkPointer_;

};

inline float FileWaveIn::GetLastOut( int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= data_.GetChannelCount() ) {
		LOG("FileWaveIn::GetLastOut(): channel argument and soundfile data are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif

	if ( finished_ ) return 0.0f;

	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif
