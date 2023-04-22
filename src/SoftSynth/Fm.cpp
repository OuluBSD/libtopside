#include "SoftSynth.h"



NAMESPACE_SOFTSYNTH_BEGIN




void FmSynth::InitVoices() {
	memset(voices, 0, sizeof(voices));
	
	for (int i = 0; i < SYNTH_VOICES; i++) {
		Voice& v = voices[i];
		for (int j = 0; j < SYNTH_OPERATORS; j++) {
			VoiceOp& op = v.ops[j];
			op.amp = 1.0f;
			op.pan_amp[0] = 1.0f;
			op.pan_amp[1] = 1.0f;
			op.wheel_amp = 1.0f;
			op.lfo_amp = 1.0f;
			op.lfo_freq_mod = 1.0f;
		}
	}
	bend = 1.0f;
}

void FmSynth::SetDefaultParameters(VoiceParameters& params) {
	#undef set_default
	#define set_default(x, v) do { \
		for (int i = 0; i < SYNTH_OPERATORS; i++) \
		{ \
			params.voices[i].x = v; \
		} \
	} while(0)
    
	set_default(amp, 1.0f);
	set_default(pan, 0.0f);
	
	set_default(freq_mod, 1.0f);
	set_default(freq_offset, 0.0f);
	
	set_default(envelope_target[0], 1.0f);
	set_default(envelope_target[1], 0.5f);
	set_default(envelope_target[2], 0.25f);
	set_default(envelope_delay[0], 0.05f);
	set_default(envelope_delay[1], 0.05f);
	set_default(envelope_delay[2], 0.25f);
	set_default(envelope_release_time, 0.50f);
	
	set_default(keyboard_scaling_mid_point, 440.0f);
	set_default(keyboard_scaling_low_factor, 0.0f);
	set_default(keyboard_scaling_high_factor, 0.0f);
	
	set_default(velocity_sensitivity, 1.0f);
	set_default(mod_sensitivity, 0.0f);
	
	set_default(lfo_amp_depth, 0.0f);
	set_default(lfo_freq_mod_depth, 0.0f);
	
	set_default(enable, 1.0f);
	
	params.voices[0].carriers = 1.0f;
	for (int c = 1; c < SYNTH_OPERATORS; c++) {
		params.voices[c].carriers = 0.0f;
	}
	
	for (int x = 0; x < SYNTH_OPERATORS; x++) {
		set_default(mod_to_carriers[x], 0.0f);
	}
	
	#undef set_default
}

void FmSynth::SetDefaultGlobalParameters(GlobalParameters& params) {
	params.volume = 0.2f;
	params.lfo_freq = 0.1f;
}

void FmSynth::LoadTest() {
	Reset();
	for (unsigned i = 0; i < 8; i++) {
		SetParameter(PARAM_MOD_TO_CARRIERS0 + i, (i + 1) & 7, 2.0f);
		SetParameter(PARAM_FREQ_MOD, i, i + 1.0f);
		SetParameter(PARAM_PAN, i, (i & 1) ? -0.5f : + 0.5f);
		SetParameter(PARAM_CARRIERS, i, 1.0f);
		SetParameter(PARAM_LFO_FREQ_MOD_DEPTH, i, 0.15f);
	}
}


void FmSynth::Reset() {
	InitVoices();
	SetDefaultParameters(params);
	SetDefaultGlobalParameters(global_params);
}

void FmSynth::Init(float freq) {
	this->freq = freq;
	inv_freq = 1.0f / freq;
}

float Voice::PitchBendToRatio(uint16 bend) {
	// Two semitones range.
	return powf(2.0f, (bend - 8192.0f) / (8192.0f * 6.0f));
}

float Voice::NoteToFrequency(byte note) {
	return 440.0f * powf(2.0f, (note - 69.0f) / 12.0f);
}

void Voice::UpdateTargetEnvelope() {
	pos += speed * FRAMES_PER_LFO;
	
	if (state == VOICE_RELEASED) {
		for (int i = 0; i < SYNTH_OPERATORS; i++) {
			VoiceOp& op = ops[i];
			op.target_env *= op.falloff;
			if (pos >= op.end_time) {
				dead |= 1 << i;
			}
		}
	}
	else {
		for (int i = 0; i < SYNTH_OPERATORS; i++) {
			VoiceOp& op = ops[i];
			if (pos >= op.time[3]) {
				op.target_env = op.target[3];
			}
			else if (pos >= op.time[2]) {
				op.target_env = op.target[2] + (pos - op.time[2]) * op.lerp[2];
			}
			else if (pos >= op.time[1]) {
				op.target_env = op.target[1] + (pos - op.time[1]) * op.lerp[1];
			}
			else {
				op.target_env = op.target[0] + (pos - op.time[0]) * op.lerp[0];
			}
		}
	}
	
	for (int i = 0; i < SYNTH_OPERATORS; i++) {
		VoiceOp& op = ops[i];
		op.target_env_step = (op.target_env - op.env) * (1.0f / FRAMES_PER_LFO);
	}
}

void FmSynth::ResetEnvelope(Voice& v) {
	v.pos = 0.0f;
	v.count = 0;
	v.speed = inv_freq;
	v.dead = 0;
	
	for (int i = 0; i < SYNTH_OPERATORS; i++) {
		VoiceOp& op = v.ops[i];
		op.env = op.target[0] = 0.0f;
		op.time[0] = 0.0f;
		
		for (int j = 1; j <= 3; j++) {
			op.target[j] = params.voices[i].envelope_target[j - 1];
			op.time[j] = params.voices[i].envelope_delay[j - 1] + op.time[j - 1];
		}
		
		for (int j = 0; j < 3; j++) {
			op.lerp[j] = (op.target[j + 1] - op.target[j]) / (op.time[j + 1] - op.time[j]);
		}
		
		op.release_time = params.voices[i].envelope_release_time;
		op.falloff = expf(logf(0.001f) * FRAMES_PER_LFO * inv_freq / op.release_time);
	}
	
	v.UpdateTargetEnvelope();
}

void FmSynth::ResetVoice(Voice& v, float volume, float velocity, float freq) {
	v.enable = 0;
	
	for (int i = 0; i < SYNTH_OPERATORS; i++) {
		VoiceOp& op = v.ops[i];
		const SingleVoiceParameters& vp = params.voices[i];
		
		v.phases[i] = 0.25f;
		
		float mod_amp = 1.0f - vp.velocity_sensitivity;
		mod_amp += vp.velocity_sensitivity * velocity;
		
		float ratio = freq / vp.keyboard_scaling_mid_point;
		float factor = ratio > 1.0f ?
					   vp.keyboard_scaling_high_factor :
					   vp.keyboard_scaling_low_factor;
		               
		mod_amp *= powf(ratio, factor);
		
		bool enable = vp.enable > 0.5f;
		v.enable |= enable << i;
		
		if (enable) {
			op.amp = mod_amp * vp.amp;
		}
		else {
			op.amp = 0.0f;
		}
		
		op.wheel_amp = 1.0f - vp.mod_sensitivity + vp.mod_sensitivity * wheel;
		op.pan_amp[0] = volume * min(1.0f - vp.pan, 1.0f) * vp.carriers;
		op.pan_amp[1] = volume * min(1.0f + vp.pan, 1.0f) * vp.carriers;
		        
		op.lfo_amp = 1.0f;
		op.lfo_freq_mod = 1.0f;
	}
	
	v.state = VOICE_RUNNING;
	ResetEnvelope(v);
}

void Voice::VoiceUpdateReadMod() {
	for (int i = 0; i < SYNTH_OPERATORS; i++) {
		VoiceOp& op = ops[i];
		op.read_mod = op.wheel_amp * op.lfo_amp * op.amp;
	}
}

void FmSynth::TriggerVoice(Voice& v, byte note, byte velocity) {
	v.note = note;
	v.base_freq = v.NoteToFrequency(note);
	
	float freq = bend * v.base_freq;
	float mod_vel = velocity * (1.0f / 127.0f);
	
	for (int i = 0; i < SYNTH_OPERATORS; i++) {
		VoiceOp& op = v.ops[i];
		const SingleVoiceParameters& vp = params.voices[i];
		op.step_rate =
			(freq * vp.freq_mod + vp.freq_offset) *
			inv_freq;
	}
	
	ResetVoice(v, global_params.volume, mod_vel, v.base_freq);
	v.VoiceUpdateReadMod();
	
	v.lfo_phase = 0.25f;
	v.lfo_step = FRAMES_PER_LFO * global_params.lfo_freq * inv_freq;
	v.count = 0;
}

Status FmSynth::NoteOn(byte note, byte velocity) {
	Voice* voice = NULL;
	for (int i = 0; i < SYNTH_VOICES; i++) {
		if (voices[i].state == VOICE_INACTIVE) {
			voice = &voices[i];
			break;
		}
	}
	
	if (voice) {
		TriggerVoice(*voice, note, velocity);
		return STATUS_OK;
	}
	else {
		return STATUS_BUSY;
	}
}

void Voice::ReleaseVoice() {
	state = VOICE_RELEASED;
	for (int i = 0; i < SYNTH_OPERATORS; i++) {
		VoiceOp& op = ops[i];
		op.end_time = pos + op.release_time;
	}
}

void FmSynth::NoteOff(byte note) {
	for (int i = 0; i < SYNTH_VOICES; i++) {
		Voice& v = voices[i];
		if (v.note == note &&
			v.state == VOICE_RUNNING) {
			if (sustained) {
				v.state = VOICE_SUSTAINED;
			}
			else {
				v.ReleaseVoice();
			}
		}
	}
}

void FmSynth::SetSustain(bool enable) {
	bool releasing = sustained && !enable;
	sustained = enable;
	
	if (releasing) {
		for (int i = 0; i < SYNTH_VOICES; i++) {
			Voice& v = voices[i];
			if (v.state == VOICE_SUSTAINED) {
				v.ReleaseVoice();
			}
		}
	}
}

void FmSynth::SetModWheel(byte wheel) {
	float value = wheel * (1.0f / 127.0f);
	wheel = (byte)value;
	
	for (int i = 0; i < SYNTH_VOICES; i++) {
		Voice& v = voices[i];
		
		if (v.state != VOICE_INACTIVE) {
			for (int j = 0; j < SYNTH_OPERATORS; j++) {
				VoiceOp& op = v.ops[j];
				const SingleVoiceParameters& vp = params.voices[j];
				op.wheel_amp =
					1.0f
					- vp.mod_sensitivity
					+ vp.mod_sensitivity * value;
			}
			
			v.VoiceUpdateReadMod();
		}
	}
}

void FmSynth::SetPitchBend(uint16 value) {
	float bend = Voice::PitchBendToRatio(value);
	this->bend = bend;
	
	for (int i = 0; i < SYNTH_VOICES; i++) {
		Voice& v = voices[i];
		
		if (v.state != VOICE_INACTIVE) {
			for (int j = 0; j < SYNTH_OPERATORS; j++) {
				VoiceOp& op = v.ops[j];
				const SingleVoiceParameters& vp = params.voices[j];
				float freq = bend * v.base_freq;
				op.step_rate = (freq * vp.freq_mod + vp.freq_offset) * inv_freq;
			}
		}
	}
}

void Voice::SetLfoValue(const VoiceParameters& params, float value) {
	for (int i = 0; i < SYNTH_OPERATORS; i++) {
		VoiceOp& op = ops[i];
		const SingleVoiceParameters& vp = params.voices[i];
		op.lfo_amp = 1.0f + vp.lfo_amp_depth * value;
		op.lfo_freq_mod = 1.0f + vp.lfo_freq_mod_depth * value;
	}
	
	VoiceUpdateReadMod();
}

void FmSynth::ReleaseAll() {
	for (int i = 0; i < SYNTH_VOICES; i++) {
		voices[i].ReleaseVoice();
	}
	sustained = false;
}

Status FmSynth::ParseMidi(const byte *data) {
	if ((data[0] & 0xf0) == 0x90) {
		if (data[2] != 0) {
			return NoteOn(data[1], data[2]);
		}
		else {
			NoteOff(data[1]);
			return STATUS_OK;
		}
	}
	else if ((data[0] & 0xf0) == 0x80) {
		NoteOff(data[1]);
		return STATUS_OK;
	}
	else if ((data[0] & 0xf0) == 0xb0 && data[1] == 64) {
		SetSustain(data[2] >= 64);
		return STATUS_OK;
	}
	else if ((data[0] & 0xf0) == 0xb0 && data[1] == 1) {
		SetModWheel(data[2]);
		return STATUS_OK;
	}
	else if ((data[0] == 0xff) ||
		(((data[0] & 0xf0) == 0xb0) && data[1] == 120)) {
		// Reset, All Sound Off
		ReleaseAll();
		return STATUS_OK;
	}
	else if ((((data[0] & 0xf0) == 0xb0) && data[1] == 123) || data[0] == 0xfc) {
		// All Notes Off, STOP
		ReleaseAll();
		return STATUS_OK;
	}
	else if ((data[0] & 0xf0) == 0xe0) {
		// Pitch bend
		uint16 bend = data[1] | (data[2] << 7);
		SetPitchBend(bend);
		return STATUS_OK;
	}
	else if (data[0] == 0xf8) {
		// Timing message, just ignore.
		return STATUS_OK;
	}
	else {
		return STATUS_MESSAGE_UNKNOWN;
	}
}

const struct SynthParamData global_parameter_data[] = {
	{ "Amp", 0.0f, 1.0f, 0.2f, false },
	{ "LFO Freq", 0.1f, 64.0f, 0.1f, true },
};

const struct SynthParamData parameter_data[] = {
	{ "Volume", 0.005f, 16.0f, 1.0f, true },
	{ "Pan", -1.0f, 1.0f, 0.0f, false },
	{ "FreqMod", 0.0f, 16.0f, 1.0f, false },
	{ "FreqOffset", -128.0f, 128.0f, 0.0f, false },
	{ "Env T0", 0.0f, 1.0f, 1.0f, false },
	{ "Env T1", 0.0f, 1.0f, 0.5f, false },
	{ "Env T2", 0.0f, 1.0f, 0.25f, false },
	{ "Env D0", 0.005f, 8.0f, 0.05f, true },
	{ "Env D1", 0.005f, 8.0f, 0.05f, true },
	{ "Env D2", 0.005f, 8.0f, 0.25f, true },
	{ "Env Rel", 0.005f, 8.0f, 0.5f, true },
	{ "KeyScale Mid", 50.0f, 5000.0f, 440.0f, true },
	{ "KeyScale LoFactor", -2.0f, 2.0f, 0.0f, false },
	{ "KeyScale HiFactor", -2.0f, 2.0f, 0.0f, false },
	{ "Velocity Sensitivity", 0.0f, 1.0f, 1.0f, false },
	{ "ModWheel Sensitivity", 0.0f, 1.0f, 0.0f, false },
	{ "LFOAmpDepth", 0.0f, 1.0f, 0.0f, false },
	{ "LFOFreqDepth", 0.0f, 0.025f, 0.0f, false },
	{ "Enable", 0.0f, 1.0f, 1.0f, false },
	{ "Carrier", 0.0f, 1.0f, 1.0f, false },
	{ "Mod0ToOperator", 0.0f, 1.0f, 0.0f, false },
	{ "Mod1ToOperator", 0.0f, 1.0f, 0.0f, false },
	{ "Mod2ToOperator", 0.0f, 1.0f, 0.0f, false },
	{ "Mod3ToOperator", 0.0f, 1.0f, 0.0f, false },
	{ "Mod4ToOperator", 0.0f, 1.0f, 0.0f, false },
	{ "Mod5ToOperator", 0.0f, 1.0f, 0.0f, false },
	{ "Mod6ToOperator", 0.0f, 1.0f, 0.0f, false },
	{ "Mod7ToOperator", 0.0f, 1.0f, 0.0f, false },
};

void FmSynth::SetParameter(int parameter, int operator_index, float value) {
	if (parameter < PARAM_END && operator_index < SYNTH_OPERATORS) {
		float* param = (float*)&params.voices[operator_index].amp;
		param += parameter;
		*param = value;
	}
}

float FmSynth::ConvertFromNormalized(const SynthParamData& data, float value) {
	if (data.logarithmic) {
		float minlog = log2f(data.minimum);
		float maxlog = log2f(data.maximum);
		return exp2f(minlog * (1.0f - value) + maxlog * value);
	}
	else
		return data.minimum * (1.0f - value) + data.maximum * value;
}

float FmSynth::ConvertToNormalized(const SynthParamData& data, float value) {
	if (data.logarithmic) {
		float minlog = log2f(data.minimum);
		float maxlog = log2f(data.maximum);
		float l = log2f(value);
		return (l - minlog) / (maxlog - minlog);
	}
	else
		return (value - data.minimum) / (data.maximum - data.minimum);
}

float FmSynth::ConvertToNormalizedGlobalParameter(int parameter, float value) {
	if (parameter < GLOBAL_PARAM_END) {
		const SynthParamData& data = global_parameter_data[parameter];
		return ConvertToNormalized(data, value);
	}
	else
		return 0.0f;
}

float FmSynth::ConvertFromNormalizedGlobalParameter(int parameter, float value) {
	if (parameter < GLOBAL_PARAM_END) {
		const SynthParamData& data = global_parameter_data[parameter];
		return ConvertFromNormalized(data, value);
	}
	else
		return 0.0f;
}

float FmSynth::ConvertToNormalizedParameter(int parameter, float value) {
	if (parameter < PARAM_END) {
		const SynthParamData& data = parameter_data[parameter];
		return ConvertToNormalized(data, value);
	}
	else
		return 0.0f;
}

float FmSynth::ConvertFromNormalizedParameter(int parameter, float value) {
	if (parameter < PARAM_END) {
		const SynthParamData& data = parameter_data[parameter];
		return ConvertFromNormalized(data, value);
	}
	else
		return 0.0f;
}

float FmSynth::GetParameter(int parameter, int operator_index) {
	if (parameter < PARAM_END && operator_index < SYNTH_OPERATORS) {
		const SingleVoiceParameters& vp = params.voices[operator_index];
		const float* param = &vp.amp;
		return param[parameter];
	}
	else
		return 0.0f;
}

void FmSynth::SetGlobalParameter(int parameter, float value) {
	if (parameter < GLOBAL_PARAM_END) {
		float *param = &global_params.volume;
		param[parameter] = value;
	}
}

float FmSynth::GetGlobalParameter(int parameter) {
	if (parameter < GLOBAL_PARAM_END) {
		float *param = &global_params.volume;
		return param[parameter];
	}
	else
		return 0.0f;
}

bool Voice::UpdateActive() {
	if (enable & (~dead)) {
		return true;
	}
	else {
		state = VOICE_INACTIVE;
		return false;
	}
}

float FmSynth::Oscillator(float phase) {
	float x = phase < 0.5f ? (phase - 0.25f) : (0.75f - phase);
	
	float x2 = x * x;
	float x3 = x2 * x;
	x *= 2.0f * M_PIf;
	x -= x3 * INV_FACTORIAL_3_2PIPOW3;
	
	float x5 = x3 * x2;
	x += x5 * INV_FACTORIAL_5_2PIPOW5;
	
	float x7 = x5 * x2;
	x -= x7 * INV_FACTORIAL_7_2PIPOW7;
	
	return x;
}


void FmSynth::ProcessFrames(Voice& voice, float *left, float *right, int samples, bool interleaved) {
	float cached[SYNTH_OPERATORS];
	float cached_modulator[SYNTH_OPERATORS];
	float steps[SYNTH_OPERATORS];

	for (int f = 0; f < samples; f++) {
		for (int i = 0; i < SYNTH_OPERATORS; i++) {
			VoiceOp& op = voice.ops[i];
			steps[i] = op.lfo_freq_mod * op.step_rate;
		}
		
		for (int i = 0; i < SYNTH_OPERATORS; i++) {
			VoiceOp& op = voice.ops[i];
			float value = op.env * op.read_mod *
						  Oscillator(voice.phases[i]);
			
			if (!IsFin(value))
				value = 0;
			
			cached[i] = value;
			cached_modulator[i] = value * op.step_rate;
			op.env += op.target_env_step;
		}
		
		for (int i = 0; i < SYNTH_OPERATORS; i++) {
			const SingleVoiceParameters& vp = params.voices[i];
			float scalar = cached_modulator[i];
			for (int j = 0; j < SYNTH_OPERATORS; j++)
				steps[j] += scalar * vp.mod_to_carriers[j];
		}
		
		for (int i = 0; i < SYNTH_OPERATORS; i++) {
			VoiceOp& op = voice.ops[i];
			voice.phases[i] += steps[i];
			voice.phases[i] -= floorf(voice.phases[i]);
		}
		
		if (interleaved) {
			for (int i = 0; i < SYNTH_OPERATORS; i++) {
				VoiceOp& op = voice.ops[i];
				left[f*2+0]  += cached[i] * op.pan_amp[0];
				right[f*2+1] += cached[i] * op.pan_amp[1];
			}
		}
		else {
			for (int i = 0; i < SYNTH_OPERATORS; i++) {
				VoiceOp& op = voice.ops[i];
				ASSERT(IsFin(cached[i]));
				ASSERT(IsFin(op.pan_amp[0]));
				ASSERT(IsFin(op.pan_amp[1]));
				float l = cached[i] * op.pan_amp[0];
				float r = cached[i] * op.pan_amp[1];
				if (IsInf(l)) l = 0;
				if (IsInf(r)) r = 0;
				left[f]  += l;
				right[f] += r;
			}
		}
	}
}

void FmSynth::RenderVoice(Voice& voice, float *left, float *right, int samples, bool interleaved) {
	while (samples) {
		int to_Render = min(FRAMES_PER_LFO - voice.count, samples);
		
		ProcessFrames(voice, left, right, to_Render, interleaved);
		
		if (interleaved) {
			left += 2 * to_Render;
			right += 2 * to_Render;
		}
		else {
			left += to_Render;
			right += to_Render;
		}
		samples -= to_Render;
		voice.count += to_Render;
		
		if (voice.count == FRAMES_PER_LFO) {
			float lfo_value = Oscillator(voice.lfo_phase);
			voice.lfo_phase += voice.lfo_step;
			voice.lfo_phase -= floorf(voice.lfo_phase);
			voice.count = 0;
			
			voice.SetLfoValue(params, lfo_value);
			voice.UpdateTargetEnvelope();
		}
	}
}

int FmSynth::Render(float* left, float* right, int samples, bool interleaved) {
	//LOG("FmSynth::Render");
	int active_voices = 0;
	for (int i = 0; i < SYNTH_VOICES; i++) {
		Voice& v = voices[i];
		if (v.state != VOICE_INACTIVE) {
			//LOG("	" << i << ": " << (int)v.note);
			RenderVoice(v, left, right, samples, interleaved);
			if (v.UpdateActive()) {
				active_voices++;
			}
		}
	}
	
	return active_voices;
}

int FmSynth::RenderInterleaved(float* f, int samples) {
	return Render(f, f, samples, true);
}

size_t FmSynth::GetPresetSize(void) {
	return
		8 +
		sizeof(struct PresetMetadata) +
		PARAM_END * SYNTH_OPERATORS * sizeof(uint32) +
		GLOBAL_PARAM_END * sizeof(uint32);
}

// We don't need full precision mantissa.
// Allows packing floating point in 32-bit in a portable way.
uint32 FmSynth::PackFloat(float value) {
	int exponent;
	float mantissa = frexpf(value, &exponent);
	
	int32 fixed_mantissa = (int32_t)roundf(mantissa * 0x8000);
	int16 fractional;
	if (fixed_mantissa > 0x7fff) {
		fractional = 0x7fff;
	}
	else if (fixed_mantissa < -0x8000) {
		fractional = -0x8000;
	}
	else {
		fractional = (int16)fixed_mantissa;
	}
		
	return (((uint32)exponent & 0xffff) << 16) | (uint16)fractional;
}

float FmSynth::UnpackFloat(uint32 value) {
	if (value == 0) {
		return 0.0f;
	}
	
	int exp = (int16)(value >> 16);
	float fractional = (float)(int16)(value & 0xffff) / 0x8000;
	
	return ldexpf(fractional, exp);
}

void FmSynth::WriteU32(byte *buffer, uint32 value) {
	buffer[0] = (byte)(value >> 24);
	buffer[1] = (byte)(value >> 16);
	buffer[2] = (byte)(value >>  8);
	buffer[3] = (byte)(value >>  0);
}

uint32 FmSynth::ReadU32(const byte *buffer) {
	return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3] << 0);
}

Status FmSynth::SavePreset(const PresetMetadata& metadata, void *buffer, size_t size) {
	return SavePreset(global_params, params, metadata, buffer, size);
}

#define PRESET_STRING_SIZE 64

Status FmSynth::SavePreset(
		GlobalParameters& global_params,
		VoiceParameters& voice_params,
		const PresetMetadata& metadata,
		void *buffer_, size_t size) {
	byte *buffer = (byte*)buffer_;
	
	if (size < GetPresetSize()) {
		return STATUS_BUFFER_TOO_SMALL;
	}
	
	memcpy(buffer, "FMSYNTH1", 8);
	buffer += 8;
	
	char str[PRESET_STRING_SIZE];
	
	memset(str, 0, sizeof(str));
	#ifdef flagWIN32
	strncpy_s(str, metadata.name.Begin(), min(PRESET_STRING_SIZE-1, metadata.name.GetCount()));
	#else
	strncpy(str, metadata.name.Begin(), min(PRESET_STRING_SIZE-1, metadata.name.GetCount()));
	#endif
	memcpy(buffer, str, sizeof(str));
	buffer += PRESET_STRING_SIZE;
	
	memset(str, 0, sizeof(str));
	#ifdef flagWIN32
	strncpy_s(str, metadata.author.Begin(), min(PRESET_STRING_SIZE-1, metadata.name.GetCount()));
	#else
	strncpy(str, metadata.author.Begin(), min(PRESET_STRING_SIZE-1, metadata.name.GetCount()));
	#endif
	memcpy(buffer, str, sizeof(str));
	buffer += PRESET_STRING_SIZE;
	
	const float *globals = &global_params.volume;
	for (int i = 0; i < GLOBAL_PARAM_END; i++) {
		WriteU32(buffer, PackFloat(globals[i]));
		buffer += sizeof(uint32);
	}
	
	for(int j = 0; j < PARAM_END; j++) {
		for(int i = 0; i < SYNTH_OPERATORS; i++) {
			float* f = &voice_params.voices[i].amp;
			WriteU32(buffer, PackFloat(*f++));
			buffer += sizeof(uint32);
		}
	}
	
	
	return STATUS_OK;
}

Status FmSynth::LoadPreset(PresetMetadata& metadata, const void *buffer, size_t size) {
	return LoadPreset(global_params, params, metadata, buffer, size);
}

Status FmSynth::LoadPreset(GlobalParameters& global_params,
		VoiceParameters& voice_params,
		PresetMetadata& metadata,
		const void *buffer_, size_t size) {
	Reset();
	
	const byte* buffer = (const byte*)buffer_;
	
	if (size < GetPresetSize()) {
		return STATUS_BUFFER_TOO_SMALL;
	}
	
	if (memcmp(buffer, "FMSYNTH1", 8) != 0) {
		return STATUS_INVALID_FORMAT;
	}
	buffer += 8;
	
	if (buffer[PRESET_STRING_SIZE - 1] != '\0') {
		return STATUS_NO_NUL_TERMINATE;
	}
	
	char str[PRESET_STRING_SIZE];
	
	memcpy(str, buffer, sizeof(str));
	metadata.name.Set(str, (int)strnlen(str, PRESET_STRING_SIZE));
	buffer += PRESET_STRING_SIZE;
	
	memcpy(str, buffer, sizeof(str));
	metadata.author.Set(str, (int)strnlen(str, PRESET_STRING_SIZE));
	buffer += PRESET_STRING_SIZE;
	
	float *globals = &global_params.volume;
	for (int i = 0; i < GLOBAL_PARAM_END; i++) {
		globals[i] = UnpackFloat(ReadU32(buffer));
		buffer += sizeof(uint32);
	}
	
	for(int j = 0; j < PARAM_END; j++) {
		for(int i = 0; i < SYNTH_OPERATORS; i++) {
			float* f = &voice_params.voices[i].amp;
			f[j] = UnpackFloat(ReadU32(buffer));
			buffer += sizeof(uint32);
		}
	}
	
	return STATUS_OK;
}


void FmSynth::ChannelMidiControl(int channel, int num, int value) {
	
}

void FmSynth::HandleEvent(const MidiIO::Event& e, int track_i) {
	int channel = e.GetChannel();

	if (e.IsController()) {
		if (track_i < 0 || channel == track_i) {
			int num = e.GetP1();
			int value = e.GetP2();
			LOG("Configure event: " <<
				e.ToString() << ": " <<
				MidiIO::GetEventCtrlString(num) << " = " << value);
			ChannelMidiControl(channel, num, value);
		}
	}
	else if (e.IsMeta()) {
		bool send = false;
		int mnum = e.GetP1();
		int strlen = e.GetP2();
		String str;
		for(int i = 3; i < 3 + strlen; i++) {
			int chr = e[i];
			str.Cat(chr);
		}
		switch (mnum) {
			case MidiIO::MIDIMETA_SEQNUM:
				break;
			case MidiIO::MIDIMETA_TEXT:
				LOG("Midi-string: " << str);
				break;
			case MidiIO::MIDIMETA_COPYRIGHT:
				LOG("Copyright: " << str);
				break;
			case MidiIO::MIDIMETA_TRACKNAME:
				LOG("Track name: " << str);
				break;
			case MidiIO::MIDIMETA_INSTRNAME:
				LOG("Instrument name: " << str);
				break;
			case MidiIO::MIDIMETA_LYRICS:
				break;
			case MidiIO::MIDIMETA_MARKER:
				break;
			case MidiIO::MIDIMETA_CUEPOINT:
				break;
			case MidiIO::MIDIMETA_CHPREFIX:
				break;
			case MidiIO::MIDIMETA_TRACKEND:
				break;
			case MidiIO::MIDIMETA_TEMPO:
				break;
			case MidiIO::MIDIMETA_SMPTE:
				break;
			case MidiIO::MIDIMETA_TIMESIG:
				break;
			case MidiIO::MIDIMETA_KEYSIG:
				break;
			case MidiIO::MIDIMETA_CUSTOM:
				break;
		}
		
	}
	else if (e.IsNoteOff()) {
		if (track_i < 0 || channel == track_i)
			NoteOff(e.GetP1());
	}
	else if (e.IsNoteOn()) {
		if (track_i < 0 || channel == track_i)
			NoteOn(e.GetP1(), e.GetP2());
	}
	else if (e.IsNote()) {
		LOG("Ignore note: " << e.ToString());
	}
	else if (e.IsAftertouch()) {
		LOG("Ignore aftertouch: " << e.ToString());
	}
	else if (e.IsTimbre() || e.IsPatchChange()) {
		LOG("Ignore preset change: " << e.ToString());
		/*int channel = e.GetChannel();
		int value = e.GetP1();
		if (track_i < 0 || channel == track_i) {
			LOG("Changing channel patch: channel " << channel << " to " << value << ": " << e.ToString());
			int bank = 0;
			// if channel is the midi-standard drum channel
			if (channel == 9) {
				bank = 128;
			}
			SetChannelBankPreset(channel, bank, value);
		}*/
	}
	else if (e.IsPressure()) {
		LOG("Ignore pressure: " << e.ToString());
	}
	else if (e.IsPitchbend()) {
		int channel = e.GetChannel();
		int value = e.GetP1();
		if (track_i < 0 || channel == track_i) {
			LOG("Setting pitch bend: channel " << channel << " to " << value);
			int fs_pbend = (128 + value) * 0x4000 / 256;
			SetPitchBend(fs_pbend);
		}
	}
	else {
		LOG("Unexpected configure event: " << e.ToString());
	}
}

NAMESPACE_SOFTSYNTH_END

