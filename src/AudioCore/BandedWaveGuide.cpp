#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BandedWaveGuide::BandedWaveGuide() {
	do_pluck_ = true;
	bowTable_.SetSlope( 3.0f );
	adsr_.SetAllTimes( 0.02f, 0.005f, 0.9f, 0.01f );
	frequency_ = 220.0f;
	this->SetPreset(0);
	bow_position_ = 0;
	base_gain_ = 0.999f;
	integration_constant_ = 0.0f;
	track_velocity_ = false;
	bow_velocity_ = 0.0f;
	bow_target_ = 0.0f;
	strikeAmp_ = 0.0f;
}

BandedWaveGuide::~BandedWaveGuide() {
}

void BandedWaveGuide::Clear() {
	for ( int i = 0; i < mode_count_; i++ ) {
		delay_[i].Clear();
		bandpass_[i].Clear();
	}
}

void BandedWaveGuide::SetPreset( int preset ) {
	int i;

	switch ( preset ) {
	case 1:
		preset_modes_ = 4;
		modes_[0] = (float) 1.0f;
		modes_[1] = (float) 4.0198391420f;
		modes_[2] = (float) 10.7184986595f;
		modes_[3] = (float) 18.0697050938f;

		for (i = 0; i < preset_modes_; i++) {
			basegains_[i] = (float) powf(0.999f, (float) i + 1);
			excitation_[i] = 1.0f;
		}

		break;

	case 2:
		preset_modes_ = 5;
		modes_[0] = (float) 1.0f;
		modes_[1] = (float) 2.32f;
		modes_[2] = (float) 4.25f;
		modes_[3] = (float) 6.63f;
		modes_[4] = (float) 9.38f;

		for (i = 0; i < preset_modes_; i++) {
			basegains_[i] = (float) powf(0.999f, (float) i + 1);
			excitation_[i] = 1.0f;
		}

		break;

	case 3:
		preset_modes_ = 12;
		modes_[0] = 0.996108344f;
		basegains_[0] = 0.999925960128219f;
		excitation_[0] = 11.900357f / 10.0f;
		modes_[1] = 1.0038916562f;
		basegains_[1] = 0.999925960128219f;
		excitation_[1] = 11.900357f / 10.f;
		modes_[2] = 2.979178f;
		basegains_[2] = 0.999982774366897f;
		excitation_[2] = 10.914886f / 10.f;
		modes_[3] = 2.99329767f;
		basegains_[3] = 0.999982774366897f;
		excitation_[3] = 10.914886f / 10.f;
		modes_[4] = 5.704452f;
		basegains_[4] = 1.0f;
		excitation_[4] = 42.995041f / 10.f;
		modes_[5] = 5.704452f;
		basegains_[5] = 1.0f;
		excitation_[5] = 42.995041f / 10.f;
		modes_[6] = 8.9982f;
		basegains_[6] = 1.0f;
		excitation_[6] = 40.063034f / 10.f;
		modes_[7] = 9.01549726f;
		basegains_[7] = 1.0f;
		excitation_[7] = 40.063034f / 10.f;
		modes_[8] = 12.83303f;
		basegains_[8] = 0.999965497558225f;
		excitation_[8] = 7.063034f / 10.f;
		modes_[9] = 12.807382f;
		basegains_[9] = 0.999965497558225f;
		excitation_[9] = 7.063034f / 10.f;
		modes_[10] = 17.2808219f;
		basegains_[10] = 0.9999999999999999999965497558225f;
		excitation_[10] = 57.063034f / 10.f;
		modes_[11] = 21.97602739726f;
		basegains_[11] = 0.999999999999999965497558225f;
		excitation_[11] = 57.063034f / 10.f;
		break;

	default:
		preset_modes_ = 4;
		modes_[0] = (float) 1.0f;
		modes_[1] = (float) 2.756f;
		modes_[2] = (float) 5.404f;
		modes_[3] = (float) 8.933f;

		for (i = 0; i < preset_modes_; i++) {
			basegains_[i] = (float) powf(0.9f, (float) i + 1);
			excitation_[i] = 1.0f;
		}

		break;
	}

	mode_count_ = preset_modes_;
	SetFrequency( frequency_ );
}

void BandedWaveGuide::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("BandedWaveGuide::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif

	if (frequency > 1568.0f) frequency = 1568.0f;

	float radius;
	float base = Audio::GetSampleRate() / frequency;
	float GetCount;

	for (int i = 0; i < preset_modes_; i++) {
		GetCount = floorf(base / modes_[i]);

		if ( GetCount > 2.0f) {
			delay_[i].SetDelay( GetCount );
			gains_[i] = basegains_[i];
		}
		else	{
			mode_count_ = i;
			break;
		}

		radius = 1.0f - PI * 32 / Audio::GetSampleRate();

		if ( radius < 0.0f ) radius = 0.0f;

		bandpass_[i].SetResonance(frequency * modes_[i], radius, true);
		delay_[i].Clear();
		bandpass_[i].Clear();
	}
}

void BandedWaveGuide::SetStrikePosition( float position ) {
	strike_position_ = (int)(delay_[0].GetDelay() * position / 2.0f);
}

void BandedWaveGuide::StartBowing( float amplitude, float rate ) {
	adsr_.SetAttackRate(rate);
	adsr_.KeyOn();
	max_velocity_ = 0.03f + (0.1f * amplitude);
}

void BandedWaveGuide::StopBowing( float rate ) {
	adsr_.SetReleaseRate(rate);
	adsr_.KeyOff();
}

void BandedWaveGuide::Pluck( float amplitude ) {
	int j;
	float min_len = delay_[mode_count_ - 1].GetDelay();

	for (int i = 0; i < mode_count_; i++)
		for (j = 0; j < (int)(delay_[i].GetDelay() / min_len); j++)
			delay_[i].Tick( excitation_[i]*amplitude / mode_count_ );
}

void BandedWaveGuide::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );

	if ( do_pluck_ )
		this->Pluck( amplitude );
	else
		this->StartBowing( amplitude, amplitude * 0.001f );
}

void BandedWaveGuide::NoteOff( float amplitude ) {
	if ( !do_pluck_ )
		this->StopBowing( (1.0f - amplitude) * 0.005f );
}

float BandedWaveGuide::Tick( int ) {
	int k;
	float input = 0.0f;

	if ( do_pluck_ )
		input = 0.0f;
	else {
		if ( integration_constant_ == 0.0f )
			velocity_input_ = 0.0f;
		else
			velocity_input_ = integration_constant_ * velocity_input_;

		for ( k = 0; k < mode_count_; k++ )
			velocity_input_ += base_gain_ * delay_[k].GetLastOut();

		if ( track_velocity_ )  {
			bow_velocity_ *= 0.9995f;
			bow_velocity_ += bow_target_;
			bow_target_ *= 0.995f;
		}
		else
			bow_velocity_ = adsr_.Tick() * max_velocity_;

		input = bow_velocity_ - velocity_input_;
		input = input * bowTable_.Tick(input);
		input = input / (float)mode_count_;
	}

	float data = 0.0f;

	for ( k = 0; k < mode_count_; k++ ) {
		bandpass_[k].Tick(input + gains_[k] * delay_[k].GetLastOut());
		delay_[k].Tick(bandpass_[k].GetLastOut());
		data += bandpass_[k].GetLastOut();
	}

	last_frame_[0] = data * 4;
	return last_frame_[0];
}

void BandedWaveGuide::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( value < 0 || ( number != 101 && value > 128.0 ) ) {
		LOG("BandedWaveGuide::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_BowPressure_) {
		if ( normalizedValue == 0.0f )
			do_pluck_ = true;
		else {
			do_pluck_ = false;
			bowTable_.SetSlope( 10.0f - (9.0f * normalizedValue));
		}
	}
	else if (number == 4)	{
		if ( !track_velocity_ ) track_velocity_ = true;

		bow_target_ += 0.005f * (normalizedValue - bow_position_);
		bow_position_ = normalizedValue;
	}
	else if (number == 8)
		this->SetStrikePosition( normalizedValue );
	else if (number == __SK_AfterTouch_Cont_) {
		if ( track_velocity_ ) track_velocity_ = false;

		max_velocity_ = 0.13f * normalizedValue;
		adsr_.SetTarget(normalizedValue);
	}
	else if (number == __SK_ModWheel_) {
		base_gain_ = 0.8999999999999999f + (0.1f * normalizedValue);

		for (int i = 0; i < mode_count_; i++)
			gains_[i] = (float) basegains_[i] * base_gain_;
	}
	else if (number == __SK_ModFrequency_)
		integration_constant_ = normalizedValue;
	else if (number == __SK_Sustain_)	{
		if (value < 65) do_pluck_ = true;
		else do_pluck_ = false;
	}
	else if (number == __SK_Portamento_)	{
		if (value < 65) track_velocity_ = false;
		else track_velocity_ = true;
	}
	else if (number == __SK_ProphesyRibbon_)
		this->SetPreset((int) value);

	#if defined(flagDEBUG)
	else {
		LOG("BandedWaveGuide::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
