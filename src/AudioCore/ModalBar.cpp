#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

ModalBar::ModalBar()
	: Modal() {
	wave_ = new FileWaveIn( (Audio::GetRawWavePath() + "marmstk1.raw").Begin(), true );
	wave_->SetRate( 0.5f * 22050.0f / Audio::GetSampleRate() );
	this->SetPreset( 0 );
}

ModalBar::~ModalBar() {
	delete wave_;
}

void ModalBar::SetStickHardness( float hardness ) {
	if ( hardness < 0.0f || hardness > 1.0f ) {
		LOG("ModalBar::SetStickHardness: parameter is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	stickHardness_ = hardness;
	wave_->SetRate( (0.25 * powf(4.0, stickHardness_) ) );
	masterGain_ = 0.1 + (1.8 * stickHardness_);
}

void ModalBar::SetStrikePosition( float position ) {
	if ( position < 0.0f || position > 1.0f ) {
		LOG("ModalBar::SetStrikePosition: parameter is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	strike_position_ = position;
	float temp2 = position * PI;
	float temp = sin(temp2);
	this->SetModeGain(0, 0.12f * temp);
	temp = sin(0.05f + (3.9f * temp2));
	this->SetModeGain(1, -0.03f * temp);
	temp = sin(-0.05f + (11 * temp2));
	this->SetModeGain(2, 0.11f * temp);
}

void ModalBar::SetPreset( int preset ) {
	static float presets[9][4][4] = {
		{	{1.0f, 3.99, 10.65, -2443},
			{0.9996, 0.9994, 0.9994, 0.999},
			{0.04, 0.01, 0.01, 0.008},
			{0.429688, 0.445312, 0.093750}
		},
		{	{1.0f, 2.01, 3.9, 14.37},
			{0.99995, 0.99991, 0.99992, 0.9999},
			{0.025, 0.015, 0.015, 0.015 },
			{0.390625, 0.570312, 0.078125}
		},
		{	{1.0f, 4.08, 6.669, -3725.0},
			{0.999, 0.999, 0.999, 0.999},
			{0.06, 0.05, 0.03, 0.02},
			{0.609375, 0.359375, 0.140625}
		},
		{	{1.0f, 2.777, 7.378, 15.377},
			{0.996, 0.994, 0.994, 0.99},
			{0.04, 0.01, 0.01, 0.008},
			{0.460938, 0.375000, 0.046875}
		},
		{	{1.0f, 2.777, 7.378, 15.377},
			{0.99996, 0.99994, 0.99994, 0.9999},
			{0.02, 0.005, 0.005, 0.004},
			{0.453125, 0.250000, 0.101562}
		},
		{	{1.0f, 1.777, 2.378, 3.377},
			{0.996, 0.994, 0.994, 0.99},
			{0.04, 0.01, 0.01, 0.008},
			{0.312500, 0.445312, 0.109375}
		},
		{	{1.0f, 1.004, 1.013, 2.377},
			{0.9999, 0.9999, 0.9999, 0.999},
			{0.02, 0.005, 0.005, 0.004},
			{0.398438, 0.296875, 0.070312}
		},
		{	{1.0f, 4.0, -1320.0f, -3960.0f},
			{0.9996, 0.999, 0.9994, 0.999},
			{0.04, 0.01, 0.01, 0.008},
			{0.453125, 0.453125, 0.070312}
		},
		{	{1.0f, 1.217, 1.475, 1.729},
			{0.999, 0.999, 0.999, 0.999},
			{0.03, 0.03, 0.03, 0.03 },
			{0.390625, 0.570312, 0.078125}
		},
	};
	int temp = (preset % 9);

	for (int i = 0; i < mode_count_; i++) {
		this->SetRatioAndRadius(i, presets[temp][0][i], presets[temp][1][i]);
		this->SetModeGain(i, presets[temp][2][i]);
	}

	this->SetStickHardness(presets[temp][3][0]);
	this->SetStrikePosition(presets[temp][3][1]);
	directGain_ = presets[temp][3][2];

	if (temp == 1)
		vibrato_gain_ = 0.2;
	else
		vibrato_gain_ = 0.0f;
}

void ModalBar::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0 ) == false ) {
		LOG("ModalBar::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_StickHardness_)
		this->SetStickHardness( normalizedValue );
	else if (number == __SK_StrikePosition_)
		this->SetStrikePosition( normalizedValue );
	else if (number == __SK_ProphesyRibbon_)
		this->SetPreset((int) value);
	else if (number == __SK_Balance_)
		vibrato_gain_ = normalizedValue * 0.3;
	else if (number == __SK_ModWheel_)
		directGain_ = normalizedValue;
	else if (number == __SK_ModFrequency_)
		vibrato_.SetFrequency( normalizedValue * 12.0 );
	else if (number == __SK_AfterTouch_Cont_)
		envelope_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("ModalBar::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
