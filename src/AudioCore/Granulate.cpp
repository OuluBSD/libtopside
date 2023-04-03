#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Granulate::Granulate() {
	this->SetGrainParameters();
	this->SetRandomFactor();
	g_stretch_ = 0;
	stretch_counter_ = 0;
	gain_ = 1.0f;
}

Granulate::Granulate( int voice_count, String file_name, bool type_raw ) {
	this->SetGrainParameters();
	this->SetRandomFactor();
	g_stretch_ = 0;
	stretch_counter_ = 0;
	this->OpenFile( file_name, type_raw );
	this->SetVoices( voice_count );
}

Granulate::~Granulate() {
}

void Granulate::SetStretch( int stretchFactor ) {
	if ( stretchFactor <= 1 )
		g_stretch_ = 0;
	else if ( g_stretch_ >= 1000 )
		g_stretch_ = 1000;
	else
		g_stretch_ = stretchFactor - 1;
}

void Granulate::SetGrainParameters( int duration, int rampPercent,
									  int offset, int delay ) {
	g_duration_ = duration;

	if ( g_duration_ == 0 ) {
		g_duration_ = 1;
		LOG("Granulate::SetGrainParameters: duration argument cannot be zero ... Setting to 1 millisecond.");
		HandleError( AudioError::WARNING );
	}

	g_ramp_percent_ = rampPercent;

	if ( g_ramp_percent_ > 100 ) {
		g_ramp_percent_ = 100;
		LOG("Granulate::SetGrainParameters: rampPercent argument cannot be greater than 100 ... Setting to 100.");
		HandleError( AudioError::WARNING );
	}

	g_offset_ = offset;
	g_delay_ = delay;
}

void Granulate::SetRandomFactor( float randomness ) {
	if ( randomness < 0.0f ) g_random_factor_ = 0.0f;
	else if ( randomness > 1.0f ) g_random_factor_ = 0.97;

	g_random_factor_ = 0.97 * randomness;
};

void Granulate::OpenFile( String file_name, bool type_raw ) {
	FileRead file( file_name, type_raw );
	data_.SetCount( file.fileSize(), file.GetChannelCount() );
	file.Get( data_ );
	last_frame_.SetCount( 1, file.GetChannelCount(), 0.0f );
	this->Reset();
	#if defined(flagDEBUG)
	LOG("Granulate::openFile: file = " << file_name << ", file frames = " << file.fileSize() << '.');
	HandleError( AudioError::DEBUG_PRINT );
	#endif
}

void Granulate::Reset() {
	g_pointer_ = 0;
	size_t count;
	size_t voice_count = (int)grains_.GetCount();

	for ( int i = 0; i < grains_.GetCount(); i++ ) {
		grains_[i].repeats = 0;
		count = ( i * g_duration_ * 0.001 * Audio::GetSampleRate() / voice_count );
		grains_[i].counter = count;
		grains_[i].state = GRAIN_STOPPED;
	}

	for ( int i = 0; i < last_frame_.GetChannelCount(); i++ )
		last_frame_[i] = 0.0f;
}

void Granulate::SetVoices( int voice_count ) {
	#if defined(flagDEBUG)
	LOG("Granulate::SetVoices: voice_count = " << voice_count << ", existing voices = " << grains_.GetCount() << '.');
	HandleError( AudioError::DEBUG_PRINT );
	#endif
	size_t oldSize = grains_.GetCount();
	grains_.SetCount( voice_count );
	size_t count;

	for ( size_t i = oldSize; i < voice_count; i++ ) {
		grains_[i].repeats = 0;
		count = ( i * g_duration_ * 0.001 * Audio::GetSampleRate() / voice_count );
		grains_[i].counter = count;
		grains_[i].pointer = g_pointer_;
		grains_[i].state = GRAIN_STOPPED;
	}

	gain_ = 1.0f / grains_.GetCount();
}

void Granulate::CalculateGrain( Granulate::Grain& grain ) {
	if ( grain.repeats > 0 ) {
		grain.repeats--;
		grain.pointer = grain.StartPointer;

		if ( grain.attackCount > 0 ) {
			grain.eScaler = 0.0f;
			grain.eRate = -grain.eRate;
			grain.counter = grain.attackCount;
			grain.state = GRAIN_FADEIN;
		}
		else {
			grain.counter = grain.sustainCount;
			grain.state = GRAIN_SUSTAIN;
		}

		return;
	}

	float seconds = g_duration_ * 0.001f;
	seconds += ( seconds * g_random_factor_ * noise.Tick() );
	int count = (int) ( seconds * Audio::GetSampleRate() );
	grain.attackCount = (int) ( g_ramp_percent_ * 0.005 * count );
	grain.decayCount = grain.attackCount;
	grain.sustainCount = count - 2 * grain.attackCount;
	grain.eScaler = 0.0f;

	if ( grain.attackCount > 0 ) {
		grain.eRate = 1.0f / grain.attackCount;
		grain.counter = grain.attackCount;
		grain.state = GRAIN_FADEIN;
	}
	else {
		grain.counter = grain.sustainCount;
		grain.state = GRAIN_SUSTAIN;
	}

	seconds = g_delay_ * 0.001f;
	seconds += ( seconds * g_random_factor_ * noise.Tick() );
	count = (int) ( seconds * Audio::GetSampleRate() );
	grain.delayCount = count;
	grain.repeats = g_stretch_;
	seconds = g_offset_ * 0.001f;
	seconds += ( seconds * g_random_factor_ * std::abs( noise.Tick() ) );
	int offset = (int) ( seconds * Audio::GetSampleRate() );
	seconds = g_duration_ * 0.001 * g_random_factor_ * noise.Tick();
	offset += (int) ( seconds * Audio::GetSampleRate() );
	grain.pointer += offset;

	while ( grain.pointer >= data_.GetFrameCount() ) grain.pointer -= data_.GetFrameCount();

	if ( grain.pointer <  0 ) grain.pointer = 0;

	grain.StartPointer = grain.pointer;
}

float Granulate::Tick( int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= data_.GetChannelCount() ) {
		LOG("Granulate::Tick(): channel argument and soundfile data are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	int i, j, channel_count = last_frame_.GetChannelCount();

	for ( j = 0; j < channel_count; j++ ) last_frame_[j] = 0.0f;

	if ( data_.GetCount() == 0 ) return 0.0f;

	float sample;

	for ( i = 0; i < grains_.GetCount(); i++ ) {
		if ( grains_[i].counter == 0 ) {
			switch ( grains_[i].state ) {
			case GRAIN_STOPPED:
				this->CalculateGrain( grains_[i] );
				break;

			case GRAIN_FADEIN:
				if ( grains_[i].sustainCount > 0 ) {
					grains_[i].counter = grains_[i].sustainCount;
					grains_[i].state = GRAIN_SUSTAIN;
					break;
				}

			case GRAIN_SUSTAIN:
				if ( grains_[i].decayCount > 0 ) {
					grains_[i].counter = grains_[i].decayCount;
					grains_[i].eRate = -grains_[i].eRate;
					grains_[i].state = GRAIN_FADEOUT;
					break;
				}

			case GRAIN_FADEOUT:
				if ( grains_[i].delayCount > 0 ) {
					grains_[i].counter = grains_[i].delayCount;
					grains_[i].state = GRAIN_STOPPED;
					break;
				}

				this->CalculateGrain( grains_[i] );
			}
		}

		if ( grains_[i].state > 0 ) {
			for ( j = 0; j < channel_count; j++ ) {
				sample = data_[ channel_count * grains_[i].pointer + j ];

				if ( grains_[i].state == GRAIN_FADEIN || grains_[i].state == GRAIN_FADEOUT ) {
					sample *= grains_[i].eScaler;
					grains_[i].eScaler += grains_[i].eRate;
				}

				last_frame_[j] += sample;
			}

			grains_[i].pointer++;

			if ( grains_[i].pointer >= data_.GetFrameCount() )
				grains_[i].pointer = 0;
		}

		grains_[i].counter--;
	}

	if ( stretch_counter_++ == g_stretch_ ) {
		g_pointer_++;

		if ( (int) g_pointer_ >= data_.GetFrameCount() ) g_pointer_ = 0;

		stretch_counter_ = 0;
	}

	return last_frame_[channel];
}

NAMESPACE_AUDIO_END
