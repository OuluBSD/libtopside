#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BandedWaveGuide::BandedWaveGuide() {
	do_pluck_ = true;
	bowTable_.SetSlope( 3.0 );
	adsr_.SetAllTimes( 0.02, 0.005, 0.9, 0.01 );
	frequency_ = 220.0;
	this->SetPreset(0);
	bow_position_ = 0;
	base_gain_ = 0.999;
	integration_constant_ = 0.0;
	track_velocity_ = false;
	bow_velocity_ = 0.0;
	bow_target_ = 0.0;
	strikeAmp_ = 0.0;
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
		modes_[0] = (double) 1.0;
		modes_[1] = (double) 4.0198391420;
		modes_[2] = (double) 10.7184986595;
		modes_[3] = (double) 18.0697050938;

		for (i = 0; i < preset_modes_; i++) {
			basegains_[i] = (double) pow(0.999, (double) i + 1);
			excitation_[i] = 1.0;
		}

		break;

	case 2:
		preset_modes_ = 5;
		modes_[0] = (double) 1.0;
		modes_[1] = (double) 2.32;
		modes_[2] = (double) 4.25;
		modes_[3] = (double) 6.63;
		modes_[4] = (double) 9.38;

		for (i = 0; i < preset_modes_; i++) {
			basegains_[i] = (double) pow(0.999, (double) i + 1);
			excitation_[i] = 1.0;
		}

		break;

	case 3:
		preset_modes_ = 12;
		modes_[0] = 0.996108344;
		basegains_[0] = 0.999925960128219;
		excitation_[0] = 11.900357 / 10.0;
		modes_[1] = 1.0038916562;
		basegains_[1] = 0.999925960128219;
		excitation_[1] = 11.900357 / 10.;
		modes_[2] = 2.979178;
		basegains_[2] = 0.999982774366897;
		excitation_[2] = 10.914886 / 10.;
		modes_[3] = 2.99329767;
		basegains_[3] = 0.999982774366897;
		excitation_[3] = 10.914886 / 10.;
		modes_[4] = 5.704452;
		basegains_[4] = 1.0;
		excitation_[4] = 42.995041 / 10.;
		modes_[5] = 5.704452;
		basegains_[5] = 1.0;
		excitation_[5] = 42.995041 / 10.;
		modes_[6] = 8.9982;
		basegains_[6] = 1.0;
		excitation_[6] = 40.063034 / 10.;
		modes_[7] = 9.01549726;
		basegains_[7] = 1.0;
		excitation_[7] = 40.063034 / 10.;
		modes_[8] = 12.83303;
		basegains_[8] = 0.999965497558225;
		excitation_[8] = 7.063034 / 10.;
		modes_[9] = 12.807382;
		basegains_[9] = 0.999965497558225;
		excitation_[9] = 7.063034 / 10.;
		modes_[10] = 17.2808219;
		basegains_[10] = 0.9999999999999999999965497558225;
		excitation_[10] = 57.063034 / 10.;
		modes_[11] = 21.97602739726;
		basegains_[11] = 0.999999999999999965497558225;
		excitation_[11] = 57.063034 / 10.;
		break;

	default:
		preset_modes_ = 4;
		modes_[0] = (double) 1.0;
		modes_[1] = (double) 2.756;
		modes_[2] = (double) 5.404;
		modes_[3] = (double) 8.933;

		for (i = 0; i < preset_modes_; i++) {
			basegains_[i] = (double) pow(0.9, (double) i + 1);
			excitation_[i] = 1.0;
		}

		break;
	}

	mode_count_ = preset_modes_;
	SetFrequency( frequency_ );
}

void BandedWaveGuide::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("BandedWaveGuide::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif

	if (frequency > 1568.0) frequency = 1568.0;

	double radius;
	double base = Audio::GetSampleRate() / frequency;
	double GetCount;

	for (int i = 0; i < preset_modes_; i++) {
		GetCount = (int)(base / modes_[i]);

		if ( GetCount > 2.0) {
			delay_[i].SetDelay( GetCount );
			gains_[i] = basegains_[i];
		}
		else	{
			mode_count_ = i;
			break;
		}

		radius = 1.0 - PI * 32 / Audio::GetSampleRate();

		if ( radius < 0.0 ) radius = 0.0;

		bandpass_[i].SetResonance(frequency * modes_[i], radius, true);
		delay_[i].Clear();
		bandpass_[i].Clear();
	}
}

void BandedWaveGuide::SetStrikePosition( double position ) {
	strike_position_ = (int)(delay_[0].GetDelay() * position / 2.0);
}

void BandedWaveGuide::StartBowing( double amplitude, double rate ) {
	adsr_.SetAttackRate(rate);
	adsr_.KeyOn();
	max_velocity_ = 0.03 + (0.1 * amplitude);
}

void BandedWaveGuide::StopBowing( double rate ) {
	adsr_.SetReleaseRate(rate);
	adsr_.KeyOff();
}

void BandedWaveGuide::Pluck( double amplitude ) {
	int j;
	double min_len = delay_[mode_count_ - 1].GetDelay();

	for (int i = 0; i < mode_count_; i++)
		for (j = 0; j < (int)(delay_[i].GetDelay() / min_len); j++)
			delay_[i].Tick( excitation_[i]*amplitude / mode_count_ );
}

void BandedWaveGuide::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );

	if ( do_pluck_ )
		this->Pluck( amplitude );
	else
		this->StartBowing( amplitude, amplitude * 0.001 );
}

void BandedWaveGuide::NoteOff( double amplitude ) {
	if ( !do_pluck_ )
		this->StopBowing( (1.0 - amplitude) * 0.005 );
}

double BandedWaveGuide::Tick( unsigned int ) {
	int k;
	double input = 0.0;

	if ( do_pluck_ )
		input = 0.0;
	else {
		if ( integration_constant_ == 0.0 )
			velocity_input_ = 0.0;
		else
			velocity_input_ = integration_constant_ * velocity_input_;

		for ( k = 0; k < mode_count_; k++ )
			velocity_input_ += base_gain_ * delay_[k].GetLastOut();

		if ( track_velocity_ )  {
			bow_velocity_ *= 0.9995;
			bow_velocity_ += bow_target_;
			bow_target_ *= 0.995;
		}
		else
			bow_velocity_ = adsr_.Tick() * max_velocity_;

		input = bow_velocity_ - velocity_input_;
		input = input * bowTable_.Tick(input);
		input = input / (double)mode_count_;
	}

	double data = 0.0;

	for ( k = 0; k < mode_count_; k++ ) {
		bandpass_[k].Tick(input + gains_[k] * delay_[k].GetLastOut());
		delay_[k].Tick(bandpass_[k].GetLastOut());
		data += bandpass_[k].GetLastOut();
	}

	last_frame_[0] = data * 4;
	return last_frame_[0];
}

void BandedWaveGuide::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( value < 0 || ( number != 101 && value > 128.0 ) ) {
		LOG("BandedWaveGuide::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if (number == __SK_BowPressure_) {
		if ( normalizedValue == 0.0 )
			do_pluck_ = true;
		else {
			do_pluck_ = false;
			bowTable_.SetSlope( 10.0 - (9.0 * normalizedValue));
		}
	}
	else if (number == 4)	{
		if ( !track_velocity_ ) track_velocity_ = true;

		bow_target_ += 0.005 * (normalizedValue - bow_position_);
		bow_position_ = normalizedValue;
	}
	else if (number == 8)
		this->SetStrikePosition( normalizedValue );
	else if (number == __SK_AfterTouch_Cont_) {
		if ( track_velocity_ ) track_velocity_ = false;

		max_velocity_ = 0.13 * normalizedValue;
		adsr_.SetTarget(normalizedValue);
	}
	else if (number == __SK_ModWheel_) {
		base_gain_ = 0.8999999999999999 + (0.1 * normalizedValue);

		for (int i = 0; i < mode_count_; i++)
			gains_[i] = (double) basegains_[i] * base_gain_;
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
