#ifndef _AudioCore_INSTRUMENT_H
#define _AudioCore_INSTRUMENT_H


NAMESPACE_AUDIO_BEGIN

class Instrument : public Audio {
public:

	Instrument() {
		last_frame_.SetCount( 1, 1, 0.0 );
	};
	
	virtual void Clear() {};
	virtual void NoteOn( double frequency, double amplitude ) = 0;
	virtual void NoteOff( double amplitude ) = 0;
	virtual void SetFrequency( double frequency );
	virtual void ControlChange(int number, double value);
	
	unsigned int GetChannelsOut() const {
		return last_frame_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	double GetLastOut( unsigned int channel = 0 );
	virtual double Tick( unsigned int channel = 0 ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 ) = 0;

protected:

	AudioFrames last_frame_;

};

inline void Instrument::SetFrequency( double frequency ) {
	LOG("Instrument::SetFrequency: virtual SetFrequency function call!");
	HandleError( AudioError::WARNING );
}

inline double Instrument::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= last_frame_.GetChannelCount() ) {
		LOG("Instrument::GetLastOut(): channel argument is invalid!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline void Instrument::ControlChange( int number, double value ) {
	LOG("Instrument::controlChange: virtual function call!");
	HandleError( AudioError::WARNING );
}

NAMESPACE_AUDIO_END

#endif
