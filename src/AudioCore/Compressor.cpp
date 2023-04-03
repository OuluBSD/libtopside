#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN


float LinearToDb(float linear_value)
{
	return 20.0f * log10f(linear_value);
}
float DbToLinear(float db_value)
{
	return powf(10, 0.05f * db_value);
}

void CompressorParameter::SetDefault(float freq) {
	gain_db =		 0;			// pre-gain level (dB)
	ratio =			10;			// compress ratio
	th_db =			-9;			// threshold level (dB)
	w_db =			 3;			// knee-width (dB)
	att =			 0;			// attack time (ms)
	rlt =			 0;			// release time (ms)
	clip_db =		-2;			// clipping level (dB)
	is_auto_makeup = 1;
	
	Init(freq);
}

void CompressorParameter::Init(float freq)
{
	this->freq = freq;
	
	// Apply parameters limits
	if (gain_db > 20)
		gain_db = 20;
	else if (gain_db < -10)
		gain_db = -10;
	else if (ratio < 1)
		ratio = 1;
				
	if (th_db > 0)
		th_db = 0;
		
	if (w_db < 0)
		w_db = 0;
	else if (w_db > -th_db)
		w_db = -th_db;
			
	if (att > 500)
		att = 500;
		
	if (att < 0)
		att = 0;
		
	if (rlt > 1000)
		rlt = 1000;
		
	if (rlt < 0)
		rlt = 0;
		
	if (clip_db > -2)
		clip_db = -2;
	else if (clip_db < -20)
		clip_db = -20;
			
	w_db_x2_inv = 1.f / (4.f * w_db);
	k1_db = th_db - w_db;						// knee minimum level (dB)
	k2_db = th_db + w_db;						// knee maximum level (dB)
	ratio = 1 / ratio;							// ratio to multiply instead divide
	tau_attack = att * 0.001f;					// attack time
	tau_release = rlt * 0.001f;					// release time
	
	alpha_attack = expf(-1 / (tau_attack * freq));
	alpha_release = expf(-1 / (tau_release * freq));
}



Compressor::Compressor() {
	last_frame_.SetCount( 1, 2, 0.0f );
	param.SetDefault(GetSampleRate());
	this->Clear();
}

void Compressor::Init() {
	param.Init(GetSampleRate());
	sign = 1;
}

float Compressor::PreGainDb() {
	float pre_gain_db = param.gain_db;
	return pre_gain_db;
}

void Compressor::SignDetection() {
	if (sample < 0)
		this->sign = -1;
	else
		this->sign = +1;
}


void Compressor::Limit()
{
	if (sample > param.clip_db) {
		sample = param.clip_db;
	}
}


float Compressor::GainStageDb(float sample_db)
{
	float gain_compstage_db;
	
	if (sample_db < param.k1_db) {
		gain_compstage_db = 0;
	}
	else if (sample_db <= param.k2_db) {
		gain_compstage_db = (param.ratio - 1) *
				(sample_db - param.k1_db) *
				(sample_db - param.k1_db) *
				param.w_db_x2_inv;
	}
	
	else {
		gain_compstage_db =
			(param.ratio - 1) *
			(sample_db - param.th_db);
	}
	
	return gain_compstage_db;
}


float Compressor::BallisticsStageDb(float gain_compstage_db)
{
	static float gain_ballisctics_stage_db = 0;
	
	if (gain_compstage_db <= gain_ballisctics_stage_db) {
		gain_ballisctics_stage_db =
			this->param.alpha_attack * gain_ballisctics_stage_db +
			(1 - this->param.alpha_attack) * gain_compstage_db;
	}
	
	else {
		gain_ballisctics_stage_db =
			this->param.alpha_release * gain_ballisctics_stage_db +
			(1 - this->param.alpha_release) * gain_compstage_db;
	}
	
	return gain_ballisctics_stage_db;
}


float Compressor::AutoMakeupStageDb()
{
	float gain_makeup_stage_db;
	float sample_db = 0;

	gain_makeup_stage_db = -GainStageDb(sample_db)/2;

	return gain_makeup_stage_db;
}

void Compressor::Clear() {
	sample = 0;
}

float Compressor::Tick(float input, int channel) {
	this->sample = input;
	SignDetection();
	
	this->sample = LinearToDb(this->sign * this->sample);
	static float gain_db = 0;
	
	gain_db = PreGainDb();
	this->sample += gain_db;
	
	gain_db = GainStageDb(this->sample);
	gain_db = BallisticsStageDb(gain_db);
	
	if (param.is_auto_makeup)
		gain_db += AutoMakeupStageDb();
	
	this->sample += gain_db;
	
	Limit();
	
	float output = this->sign * DbToLinear(this->sample);
	last_frame_[channel] = output;
	
	return output;
}

float Compressor::Tick2( float input1, float input2, int channel ) {
	this->sample = input1;
	SignDetection();
	
	this->sample = LinearToDb(this->sign * this->sample);
	static float gain_db = 0;
	
	int input2_sign = input2 < 0 ? -1 : +1;
	input2 = LinearToDb(input2_sign * input2);
	
	gain_db = PreGainDb();
	this->sample += gain_db;
	
	gain_db = GainStageDb(input2);
	gain_db = BallisticsStageDb(gain_db);
	
	if (param.is_auto_makeup)
		gain_db += AutoMakeupStageDb();
	
	this->sample += gain_db;
	
	Limit();
	
	float output = this->sign * DbToLinear(this->sample);
	last_frame_[channel] = output;
	
	return output;
}

void Compressor::LoadState(const ArrayMap<String, Object>& state) {
	int i;
	
	i = state.Find(".gain");
	if (i >= 0)
		param.gain_db = state[i].ToFloat();
	
	i = state.Find(".treshold");
	if (i >= 0)
		param.th_db = state[i].ToFloat();
	
	i = state.Find(".knee");
	if (i >= 0)
		param.w_db = state[i].ToFloat();
	
	i = state.Find(".ratio");
	if (i >= 0)
		param.ratio = state[i].ToFloat();
	
	i = state.Find(".attack");
	if (i >= 0)
		param.att = state[i].ToFloat();
	
	i = state.Find(".release");
	if (i >= 0)
		param.rlt = state[i].ToFloat();
	
	i = state.Find(".auto.makeup");
	if (i >= 0)
		param.is_auto_makeup = state[i].ToBool();
	
	param.Init(param.freq);
}


NAMESPACE_AUDIO_END
