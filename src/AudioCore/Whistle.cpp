#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

const int CAN_RADIUS = 100;
const int PEA_RADIUS = 30;
const int BUMP_RADIUS = 5;

const float NORM_CAN_LOSS = 0.97;

const float GRAVITY = 20.0f;

const float NORM_TICK_SIZE = 0.004;


const float ENV_RATE = 0.001f;

Whistle::Whistle() {
	sine_.SetFrequency( 2800.0f );
	can_.SetRadius( CAN_RADIUS );
	can_.SetPosition(0, 0, 0);
	can_.SetVelocity(0, 0, 0);
	onepole_.SetPole(0.95f);
	bumper_.SetRadius( BUMP_RADIUS );
	bumper_.SetPosition(0.0f, CAN_RADIUS - BUMP_RADIUS, 0);
	bumper_.SetPosition(0.0f, CAN_RADIUS - BUMP_RADIUS, 0);
	pea_.SetRadius( PEA_RADIUS );
	pea_.SetPosition(0, CAN_RADIUS / 2, 0);
	pea_.SetVelocity(35, 15, 0);
	envelope_.SetRate( ENV_RATE );
	envelope_.KeyOn();
	fipple_freq_mod_ = 0.5f;
	fipple_gain_mod_ = 0.5f;
	blow_freq_mod_ = 0.25f;
	noise_gain_ = 0.125f;
	base_frequency_ = 2000;
	tick_size_ = NORM_TICK_SIZE;
	can_loss_ = NORM_CAN_LOSS;
	sub_sample_ = 1;
	sub_samp_count_ = sub_sample_;
}

Whistle::~Whistle() {
	#ifdef WHISTLE_ANIMATION
	printf("Exit, Whistle bye bye!!\n");
	#endif
}

void Whistle::Clear() {
}

void Whistle::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Whistle::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_frequency_ = frequency * 4;
}

void Whistle::StartBlowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("Whistle::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( ENV_RATE );
	envelope_.SetTarget( amplitude );
}

void Whistle::StopBlowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("Whistle::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.KeyOff();
}

void Whistle::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( amplitude * 2.0 , amplitude * 0.2f );
}

void Whistle::NoteOff( float amplitude ) {
	this->StopBlowing( amplitude * 0.02 );
}

int frameCount = 0;

float Whistle::Tick( int ) {
	float soundMix, tempFreq;
	float envOut = 0, temp, temp1, temp2, tempX, tempY;
	float phi, cosphi, sinphi;
	float gain = 0.5, mod = 0.0f;

	if ( --sub_samp_count_ <= 0 )	{
		temp_vector_p_ = pea_.GetPosition();
		sub_samp_count_ = sub_sample_;
		temp = bumper_.isInside( temp_vector_p_ );
		#ifdef WHISTLE_ANIMATION
		frameCount += 1;

		if ( frameCount >= (1470 / sub_sample_) ) {
			frameCount = 0;
			printf("%f %f %f\n", temp_vector_p_->data[0], temp_vector_p_->data[1], envOut);
			fflush(stdout);
		}

		#endif
		envOut = envelope_.Tick();

		if (temp < (BUMP_RADIUS + PEA_RADIUS)) {
			tempX = envOut * tick_size_ * 2000 * noise_.Tick();
			tempY = -envOut * tick_size_ * 1000 * (1.0f + noise_.Tick());
			pea_.AddVelocity( tempX, tempY, 0 );
			pea_.Tick( tick_size_ );
		}

		mod  = exp(-temp * 0.01);
		temp = onepole_.Tick(mod);
		gain = (1.0f - (fipple_gain_mod_ * 0.5)) + (2.0 * fipple_gain_mod_ * temp);
		gain *= gain;
		tempFreq = 1.0f + fipple_freq_mod_ * (0.25 - temp) + blow_freq_mod_ * (envOut - 1.0f);
		tempFreq *= base_frequency_;
		sine_.SetFrequency(tempFreq);
		temp_vector_p_ = pea_.GetPosition();
		temp = can_.isInside(temp_vector_p_);
		temp  = -temp;

		if (temp < (PEA_RADIUS * 1.25)) {
			pea_.GetVelocity( &temp_vector_ );
			tempX = temp_vector_p_->data[0];
			tempY = temp_vector_p_->data[1];
			phi = -atan2(tempY, tempX);
			cosphi = cos(phi);
			sinphi = sin(phi);
			temp1 = (cosphi * temp_vector_.data[0]) - (sinphi * temp_vector_.data[1]);
			temp2 = (sinphi * temp_vector_.data[0]) + (cosphi * temp_vector_.data[1]);
			temp1 = -temp1;
			tempX = (cosphi * temp1) + (sinphi * temp2);
			tempY = (-sinphi * temp1) + (cosphi * temp2);
			pea_.SetVelocity(tempX, tempY, 0);
			pea_.Tick(tick_size_);
			pea_.SetVelocity( tempX * can_loss_, tempY * can_loss_, 0 );
			pea_.Tick(tick_size_);
		}

		temp = temp_vector_p_->GetLength();

		if (temp > 0.01) {
			tempX = temp_vector_p_->data[0];
			tempY = temp_vector_p_->data[1];
			phi = atan2( tempY, tempX );
			phi += 0.3 * temp / CAN_RADIUS;
			cosphi = cos(phi);
			sinphi = sin(phi);
			tempX = 3.0 * temp * cosphi;
			tempY = 3.0 * temp * sinphi;
		}
		else {
			tempX = 0.0f;
			tempY = 0.0f;
		}

		temp = (0.9 + 0.1 * sub_sample_ * noise_.Tick()) * envOut * 0.6 * tick_size_;
		pea_.AddVelocity( temp * tempX, (temp * tempY) - (GRAVITY * tick_size_), 0 );
		pea_.Tick( tick_size_ );
	}

	temp = envOut * envOut * gain / 2;
	soundMix = temp * ( sine_.Tick() + ( noise_gain_ * noise_.Tick() ) );
	last_frame_[0] = 0.20 * soundMix;
	return last_frame_[0];
}

void Whistle::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0 ) == false ) {
		LOG("Whistle::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if ( number == __SK_NoiseLevel_ )
		noise_gain_ = 0.25 * normalizedValue;
	else if ( number == __SK_ModFrequency_ )
		fipple_freq_mod_ = normalizedValue;
	else if ( number == __SK_ModWheel_ )
		fipple_gain_mod_ = normalizedValue;
	else if ( number == __SK_AfterTouch_Cont_ )
		envelope_.SetTarget( normalizedValue * 2.0 );
	else if ( number == __SK_Breath_ )
		blow_freq_mod_ = normalizedValue * 0.5;
	else if ( number == __SK_Sustain_ )	{
		sub_sample_ = (int) value;

		if ( sub_sample_ < 1.0f ) sub_sample_ = 1;

		envelope_.SetRate( ENV_RATE / sub_sample_ );
	}

	#if defined(flagDEBUG)
	else {
		LOG("Whistle::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
