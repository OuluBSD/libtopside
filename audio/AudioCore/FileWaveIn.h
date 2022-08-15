#ifndef _AudioCore_FILEWVIN_H
#define _AudioCore_FILEWVIN_H


NAMESPACE_AUDIO_BEGIN


class FileWaveIn : public WaveIn {
public:

	FileWaveIn( unsigned long chunkThreshold = 1000000, unsigned long chunkSize = 1024 );

	FileWaveIn( String file_name, bool raw = false, bool doNormalize = true,
				unsigned long chunkThreshold = 1000000, unsigned long chunkSize = 1024 );

	~FileWaveIn();

	virtual void OpenFile( String file_name, bool raw = false, bool doNormalize = true );
	virtual void CloseFile();
	virtual void Reset();
	virtual void Normalize();
	virtual void Normalize( double peak );

	virtual unsigned long GetSize() const {
		return fileSize_;
	};

	virtual double GetFileRate() const {
		return data_.dataRate();
	};

	bool isOpen() {
		return file_.isOpen();
	};

	bool IsFinished() const {
		return finished_;
	};

	virtual void SetRate( double rate );
	virtual void AddTime( double time );

	void SetInterpolate( bool doInterpolate ) {
		interpolate_ = doInterpolate;
	};

	double GetLastOut( unsigned int channel = 0 );
	virtual double Tick( unsigned int channel = 0 );
	virtual AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	void SampleRateChanged( double new_rate, double old_rate );

	FileRead file_;
	bool finished_;
	bool interpolate_;
	bool normalizing_;
	bool chunking_;
	double time_;
	double rate_;
	unsigned long fileSize_;
	unsigned long chunkThreshold_;
	unsigned long chunkSize_;
	long chunkPointer_;

};

inline double FileWaveIn::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= data_.GetChannelCount() ) {
		LOG("FileWaveIn::GetLastOut(): channel argument and soundfile data are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif

	if ( finished_ ) return 0.0;

	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif
