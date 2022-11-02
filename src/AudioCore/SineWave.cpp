#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

AudioFrames SineWave::table_;

SineWave::SineWave()
	: time_(0.0), rate_(1.0), phase_offset_(0.0) {
	if ( table_.IsEmpty() ) {
		table_.SetCount( TABLE_SIZE + 1, 1 );
		double temp = 1.0 / TABLE_SIZE;

		for ( unsigned long i = 0; i <= TABLE_SIZE; i++ )
			table_[i] = sin( TWO_PI * i * temp );
	}

	Audio::AddSampleRateAlert( this );
}

SineWave::~SineWave() {
	Audio::RemoveSampleRateAlert( this );
}

void SineWave::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ )
		this->SetRate( old_rate * rate_ / new_rate );
}

void SineWave::Reset() {
	time_ = 0.0;
	last_frame_[0] = 0;
}

void SineWave::SetFrequency( double frequency ) {
	this->SetRate( TABLE_SIZE * frequency / Audio::GetSampleRate() );
}

void SineWave::AddTime( double time ) {
	time_ += time;
}

void SineWave::AddPhase( double phase ) {
	time_ += TABLE_SIZE * phase;
}

void SineWave::AddPhaseOffset( double phaseOffset ) {
	time_ += ( phaseOffset - phase_offset_ ) * TABLE_SIZE;
	phase_offset_ = phaseOffset;
}

NAMESPACE_AUDIO_END
