#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

AudioFrames SineWave::table_;

SineWave::SineWave()
	: time_(0.0f), rate_(1.0f), phase_offset_(0.0f) {
	if ( table_.IsEmpty() ) {
		table_.SetCount( TABLE_SIZE + 1, 1 );
		float temp = 1.0f / TABLE_SIZE;

		for ( int i = 0; i <= TABLE_SIZE; i++ )
			table_[i] = sin( TWO_PI * i * temp );
	}

	Audio::AddSampleRateAlert( this );
}

SineWave::~SineWave() {
	Audio::RemoveSampleRateAlert( this );
}

void SineWave::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ )
		this->SetRate( old_rate * rate_ / new_rate );
}

void SineWave::Reset() {
	time_ = 0.0f;
	last_frame_[0] = 0;
}

void SineWave::SetFrequency( float frequency ) {
	this->SetRate( TABLE_SIZE * frequency / Audio::GetSampleRate() );
}

void SineWave::AddTime( float time ) {
	time_ += time;
}

void SineWave::AddPhase( float phase ) {
	time_ += TABLE_SIZE * phase;
}

void SineWave::AddPhaseOffset( float phaseOffset ) {
	time_ += ( phaseOffset - phase_offset_ ) * TABLE_SIZE;
	phase_offset_ = phaseOffset;
}

NAMESPACE_AUDIO_END
