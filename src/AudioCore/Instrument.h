#ifndef _AudioCore_INSTRUMENT_H
#define _AudioCore_INSTRUMENT_H


NAMESPACE_AUDIO_BEGIN

class Instrument : public Audio {
public:

	Instrument();
	
	virtual void Clear() {};
	virtual void NoteOn( float frequency, float amplitude ) = 0;
	virtual void NoteOff( float amplitude ) = 0;
	virtual void SetFrequency( float frequency );
	virtual void ControlChange(int number, float value);
	
	void HandleEvent(const MidiIO::Event& e, int track_i=-1);
	
	int GetChannelsOut() const {
		return last_frame_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	float GetLastOut( int channel = 0 );
	virtual float Tick( int channel = 0 ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, int channel = 0 ) = 0;
	virtual void LoadState(const ArrayMap<String, Object>& state) {}

protected:

	AudioFrames last_frame_;

};

inline void Instrument::SetFrequency( float frequency ) {
	LOG("Instrument::SetFrequency: virtual SetFrequency function call!");
	HandleError( AudioError::WARNING );
}

inline float Instrument::GetLastOut( int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= last_frame_.GetChannelCount() ) {
		LOG("Instrument::GetLastOut(): channel argument is invalid!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline void Instrument::ControlChange( int number, float value ) {
	LOG("Instrument::controlChange: virtual function call!");
	HandleError( AudioError::WARNING );
}

NAMESPACE_AUDIO_END

#endif
