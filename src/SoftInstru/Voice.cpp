#include "SoftInstru.h"

NAMESPACE_SOFTINSTRU_BEGIN


double Timecents2Secsd(double timecents) {
	return POW(2.0, timecents / 1200.0);
}

float Timecents2Secsf(float timecents) {
	return POWF(2.0f, timecents / 1200.0f);
}

float Cents2Hertz(float cents) {
	return 8.176f * POWF(2.0f, cents / 1200.0f);
}

float DecibelsToGain(float db) {
	return (db > -100.f ? POWF(10.0f, db * 0.05f) : 0);
}

float GainToDecibels(float gain) {
	return (gain <= .00001f ? -100.f : (float)(20.0 * LOG10(gain)));
}

bool RiffChunkRead(RiffChunk* parent, RiffChunk& c, Stream& s)
{
	bool is_riff, is_list;
	
	if (parent && sizeof(dword) + sizeof(uint32) > parent->size)
		return false;
	
	if (!(*s.i.*s.read)(s.data, &c.id, sizeof(dword)) || *c.id <= ' ' || *c.id >= 'z')
		return false;
	
	if (!(*s.i.*s.read)(s.data, &c.size, sizeof(uint32)))
		return false;
	
	if (parent && sizeof(dword) + sizeof(uint32) + c.size > parent->size)
		return false;
	
	if (parent)
		parent->size -= sizeof(dword) + sizeof(uint32) + c.size;
	is_riff = FourCCEquals(c.id, "RIFF"), is_list = FourCCEquals(c.id, "LIST");
	
	if (is_riff && parent)
		return false; //not allowed
	
	if (!is_riff && !is_list)
		return true; //custom type without sub type
	
	if (!(*s.i.*s.read)(s.data, &c.id, sizeof(dword)) || *c.id <= ' ' || *c.id >= 'z')
		return false;
	
	c.size -= sizeof(dword);
	return true;
}




void Region::Clear(bool for_relative)
{
	MEMSET(this, 0, sizeof(Region));
	hikey = hivel = 127;
	pitch_keycenter = 60; // C4
	if (for_relative) return;

	pitch_keytrack = 100;

	pitch_keycenter = -1;

	// SF2 defaults in timecents.
	amp_env.delay = amp_env.attack = amp_env.hold = amp_env.decay = amp_env.release = -12000.0f;
	mod_env.delay = mod_env.attack = mod_env.hold = mod_env.decay = mod_env.release = -12000.0f;

	initial_filter_fc = 13500;

	delay_mod_lfo = -12000.0f;
	delay_vib_lfo = -12000.0f;
}

void Region::Operator(uint16 gen_op, union HydraGenAmount* amount, Region* merge_region)
{
	Region* region = this;
	
	enum
	{
		_GEN_TYPE_MASK       = 0x0F,
		GEN_FLOAT            = 0x01,
		GEN_INT              = 0x02,
		GEN_UINT_ADD         = 0x03,
		GEN_UINT_ADD15       = 0x04,
		GEN_KEYRANGE         = 0x05,
		GEN_VELRANGE         = 0x06,
		GEN_LOOPMODE         = 0x07,
		GEN_GROUP            = 0x08,
		GEN_KEYCENTER        = 0x09,

		_GEN_LIMIT_MASK      = 0xF0,
		GEN_INT_LIMIT12K     = 0x10, //min -12000, max 12000
		GEN_INT_LIMITFC      = 0x20, //min 1500, max 13500
		GEN_INT_LIMITQ       = 0x30, //min 0, max 960
		GEN_INT_LIMIT960     = 0x40, //min -960, max 960
		GEN_INT_LIMIT16K4500 = 0x50, //min -16000, max 4500
		GEN_FLOAT_LIMIT12K5K = 0x60, //min -12000, max 5000
		GEN_FLOAT_LIMIT12K8K = 0x70, //min -12000, max 8000
		GEN_FLOAT_LIMIT1200  = 0x80, //min -1200, max 1200
		GEN_FLOAT_LIMITPAN   = 0x90, //* .001f, min -.5f, max .5f,
		GEN_FLOAT_LIMITATTN  = 0xA0, //* .1f, min 0, max 144.0
		GEN_FLOAT_MAX1000    = 0xB0, //min 0, max 1000
		GEN_FLOAT_MAX1440    = 0xC0, //min 0, max 1440

		_GEN_MAX = 59,
	};
	#define _TSFREGIONOFFSET(TYPE, FIELD) (unsigned char)(((TYPE*)&((Region*)0)->FIELD) - (TYPE*)0)
	#define _TSFREGIONENVOFFSET(TYPE, ENV, FIELD) (unsigned char)(((TYPE*)&((&(((Region*)0)->ENV))->FIELD)) - (TYPE*)0)
	const struct { unsigned char mode, offset; } genMetas[_GEN_MAX] =
	{
		{ GEN_UINT_ADD                     , _TSFREGIONOFFSET(unsigned int, offset               ) }, // 0 StartAddrsOffset
		{ GEN_UINT_ADD                     , _TSFREGIONOFFSET(unsigned int, end                  ) }, // 1 EndAddrsOffset
		{ GEN_UINT_ADD                     , _TSFREGIONOFFSET(unsigned int, loop_start           ) }, // 2 StartloopAddrsOffset
		{ GEN_UINT_ADD                     , _TSFREGIONOFFSET(unsigned int, loop_end             ) }, // 3 EndloopAddrsOffset
		{ GEN_UINT_ADD15                   , _TSFREGIONOFFSET(unsigned int, offset               ) }, // 4 StartAddrsCoarseOffset
		{ GEN_INT   | GEN_INT_LIMIT12K     , _TSFREGIONOFFSET(         int, mod_lfo_to_pitch        ) }, // 5 ModLfoToPitch
		{ GEN_INT   | GEN_INT_LIMIT12K     , _TSFREGIONOFFSET(         int, vib_lfo_to_pitch        ) }, // 6 VibLfoToPitch
		{ GEN_INT   | GEN_INT_LIMIT12K     , _TSFREGIONOFFSET(         int, mod_env_to_pitch        ) }, // 7 ModEnvToPitch
		{ GEN_INT   | GEN_INT_LIMITFC      , _TSFREGIONOFFSET(         int, initial_filter_fc      ) }, // 8 InitialFilterFc
		{ GEN_INT   | GEN_INT_LIMITQ       , _TSFREGIONOFFSET(         int, initial_filter_q       ) }, // 9 InitialFilterQ
		{ GEN_INT   | GEN_INT_LIMIT12K     , _TSFREGIONOFFSET(         int, mod_lfo_to_filter_fc     ) }, //10 ModLfoToFilterFc
		{ GEN_INT   | GEN_INT_LIMIT12K     , _TSFREGIONOFFSET(         int, mod_env_to_filter_fc     ) }, //11 ModEnvToFilterFc
		{ GEN_UINT_ADD15                   , _TSFREGIONOFFSET(unsigned int, end                  ) }, //12 EndAddrsCoarseOffset
		{ GEN_INT   | GEN_INT_LIMIT960     , _TSFREGIONOFFSET(         int, mod_lfo_to_volume       ) }, //13 ModLfoToVolume
		{ 0                                , (0                                                  ) }, //   Unused
		{ 0                                , (0                                                  ) }, //15 ChorusEffectsSend (unsupported)
		{ 0                                , (0                                                  ) }, //16 ReverbEffectsSend (unsupported)
		{ GEN_FLOAT | GEN_FLOAT_LIMITPAN   , _TSFREGIONOFFSET(       float, pan                  ) }, //17 Pan
		{ 0                                , (0                                                  ) }, //   Unused
		{ 0                                , (0                                                  ) }, //   Unused
		{ 0                                , (0                                                  ) }, //   Unused
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K5K , _TSFREGIONOFFSET(       float, delay_mod_lfo          ) }, //21 DelayModLFO
		{ GEN_INT   | GEN_INT_LIMIT16K4500 , _TSFREGIONOFFSET(         int, freq_mod_lfo           ) }, //22 FreqModLFO
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K5K , _TSFREGIONOFFSET(       float, delay_vib_lfo          ) }, //23 DelayVibLFO
		{ GEN_INT   | GEN_INT_LIMIT16K4500 , _TSFREGIONOFFSET(         int, freq_vib_lfo           ) }, //24 FreqVibLFO
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K5K , _TSFREGIONENVOFFSET(    float, mod_env, delay        ) }, //25 DelayModEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K8K , _TSFREGIONENVOFFSET(    float, mod_env, attack       ) }, //26 AttackModEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K5K , _TSFREGIONENVOFFSET(    float, mod_env, hold         ) }, //27 HoldModEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K8K , _TSFREGIONENVOFFSET(    float, mod_env, decay        ) }, //28 DecayModEnv
		{ GEN_FLOAT | GEN_FLOAT_MAX1000    , _TSFREGIONENVOFFSET(    float, mod_env, sustain      ) }, //29 SustainModEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K8K , _TSFREGIONENVOFFSET(    float, mod_env, release      ) }, //30 ReleaseModEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT1200  , _TSFREGIONENVOFFSET(    float, mod_env, key_idx_to_hold ) }, //31 KeynumToModEnvHold
		{ GEN_FLOAT | GEN_FLOAT_LIMIT1200  , _TSFREGIONENVOFFSET(    float, mod_env, key_idx_to_decay) }, //32 KeynumToModEnvDecay
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K5K , _TSFREGIONENVOFFSET(    float, amp_env, delay        ) }, //33 DelayVolEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K8K , _TSFREGIONENVOFFSET(    float, amp_env, attack       ) }, //34 AttackVolEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K5K , _TSFREGIONENVOFFSET(    float, amp_env, hold         ) }, //35 HoldVolEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K8K , _TSFREGIONENVOFFSET(    float, amp_env, decay        ) }, //36 DecayVolEnv
		{ GEN_FLOAT | GEN_FLOAT_MAX1440    , _TSFREGIONENVOFFSET(    float, amp_env, sustain      ) }, //37 SustainVolEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT12K8K , _TSFREGIONENVOFFSET(    float, amp_env, release      ) }, //38 ReleaseVolEnv
		{ GEN_FLOAT | GEN_FLOAT_LIMIT1200  , _TSFREGIONENVOFFSET(    float, amp_env, key_idx_to_hold ) }, //39 KeynumToVolEnvHold
		{ GEN_FLOAT | GEN_FLOAT_LIMIT1200  , _TSFREGIONENVOFFSET(    float, amp_env, key_idx_to_decay) }, //40 KeynumToVolEnvDecay
		{ 0                                , (0                                                  ) }, //   Instrument (special)
		{ 0                                , (0                                                  ) }, //   Reserved
		{ GEN_KEYRANGE                     , (0                                                  ) }, //43 KeyRange
		{ GEN_VELRANGE                     , (0                                                  ) }, //44 VelRange
		{ GEN_UINT_ADD15                   , _TSFREGIONOFFSET(unsigned int, loop_start           ) }, //45 StartloopAddrsCoarseOffset
		{ 0                                , (0                                                  ) }, //46 Keynum (special)
		{ 0                                , (0                                                  ) }, //47 Velocity (special)
		{ GEN_FLOAT | GEN_FLOAT_LIMITATTN  , _TSFREGIONOFFSET(       float, attenuation          ) }, //48 InitialAttenuation
		{ 0                                , (0                                                  ) }, //   Reserved
		{ GEN_UINT_ADD15                   , _TSFREGIONOFFSET(unsigned int, loop_end             ) }, //50 EndloopAddrsCoarseOffset
		{ GEN_INT                          , _TSFREGIONOFFSET(         int, transpose            ) }, //51 CoarseTune
		{ GEN_INT                          , _TSFREGIONOFFSET(         int, tune                 ) }, //52 FineTune
		{ 0                                , (0                                                  ) }, //   SampleID (special)
		{ GEN_LOOPMODE                     , _TSFREGIONOFFSET(         int, loop_mode            ) }, //54 SampleModes
		{ 0                                , (0                                                  ) }, //   Reserved
		{ GEN_INT                          , _TSFREGIONOFFSET(         int, pitch_keytrack       ) }, //56 ScaleTuning
		{ GEN_GROUP                        , _TSFREGIONOFFSET(unsigned int, group                ) }, //57 ExclusiveClass
		{ GEN_KEYCENTER                    , _TSFREGIONOFFSET(         int, pitch_keycenter      ) }, //58 OverridingRootKey
	};
	#undef _TSFREGIONOFFSET
	#undef _TSFREGIONENVOFFSET
	if (amount)
	{
		int offset;
		if (gen_op >= _GEN_MAX) return;
		offset = genMetas[gen_op].offset;
		switch (genMetas[gen_op].mode & _GEN_TYPE_MASK)
		{
		case GEN_FLOAT:
			((float*)region)[offset]  = amount->short_amount;
			return;
			
		case GEN_INT:
			((int*)region)[offset]  = amount->short_amount;
			return;
			
		case GEN_UINT_ADD:
			((unsigned int*)region)[offset] += amount->short_amount;
			return;
			
		case GEN_UINT_ADD15:
			((unsigned int*)region)[offset] += amount->short_amount << 15;
			return;
			
		case GEN_KEYRANGE:
			region->lokey = amount->range.lo;
			region->hikey = amount->range.hi;
			return;
			
		case GEN_VELRANGE:
			region->lovel = amount->range.lo;
			region->hivel = amount->range.hi;
			return;
			
		case GEN_LOOPMODE:
			region->loop_mode = ((amount->word_amount & 3) == 3 ? LOOPMODE_SUSTAIN : ((amount->word_amount & 3) == 1 ? LOOPMODE_CONTINUOUS : LOOPMODE_NONE));
			return;
			
		case GEN_GROUP:
			region->group = amount->word_amount;
			return;
			
		case GEN_KEYCENTER:
			region->pitch_keycenter = amount->short_amount;
			return;
		}

	}
	else //merge regions and clamp values
	{
		for (gen_op = 0; gen_op != _GEN_MAX; gen_op++)
		{
			int offset = genMetas[gen_op].offset;
			switch (genMetas[gen_op].mode & _GEN_TYPE_MASK)
			{
				case GEN_FLOAT:
				{
					float *val = &((float*)region)[offset], vfactor, vmin, vmax;
					*val += ((float*)merge_region)[offset];
					switch (genMetas[gen_op].mode & _GEN_LIMIT_MASK)
					{
						case GEN_FLOAT_LIMIT12K5K: vfactor =   1.0f; vmin = -12000.0f; vmax = 5000.0f; break;
						case GEN_FLOAT_LIMIT12K8K: vfactor =   1.0f; vmin = -12000.0f; vmax = 8000.0f; break;
						case GEN_FLOAT_LIMIT1200:  vfactor =   1.0f; vmin =  -1200.0f; vmax = 1200.0f; break;
						case GEN_FLOAT_LIMITPAN:   vfactor = 0.001f; vmin =     -0.5f; vmax =    0.5f; break;
						case GEN_FLOAT_LIMITATTN:  vfactor =   0.1f; vmin =      0.0f; vmax =  144.0f; break;
						case GEN_FLOAT_MAX1000:    vfactor =   1.0f; vmin =      0.0f; vmax = 1000.0f; break;
						case GEN_FLOAT_MAX1440:    vfactor =   1.0f; vmin =      0.0f; vmax = 1440.0f; break;
						default: continue;
					}
					*val *= vfactor;
					if      (*val < vmin) *val = vmin;
					else if (*val > vmax) *val = vmax;
					continue;
				}
				case GEN_INT:
				{
					int *val = &((int*)region)[offset], vmin, vmax;
					*val += ((int*)merge_region)[offset];
					switch (genMetas[gen_op].mode & _GEN_LIMIT_MASK)
					{
						case GEN_INT_LIMIT12K:     vmin = -12000; vmax = 12000; break;
						case GEN_INT_LIMITFC:      vmin =   1500; vmax = 13500; break;
						case GEN_INT_LIMITQ:       vmin =      0; vmax =   960; break;
						case GEN_INT_LIMIT960:     vmin =   -960; vmax =   960; break;
						case GEN_INT_LIMIT16K4500: vmin = -16000; vmax =  4500; break;
						default: continue;
					}
					if      (*val < vmin) *val = vmin;
					else if (*val > vmax) *val = vmax;
					continue;
				}
				case GEN_UINT_ADD:
				{
					((unsigned int*)region)[offset] += ((unsigned int*)merge_region)[offset];
					continue;
				}
			}
		}
	}
}



void Envelope::ToSecs(bool sustain_is_gain) {
	// EG times need to be converted from timecents to seconds.
	// Pin very short EG segments.  Timecents don't get to zero, and our EG is
	// happier with zero values.
	delay   = (delay   < -11950.0f ? 0.0f : Timecents2Secsf(delay));
	attack  = (attack  < -11950.0f ? 0.0f : Timecents2Secsf(attack));
	release = (release < -11950.0f ? 0.0f : Timecents2Secsf(release));
	
	// If we have dynamic hold or decay times depending on key number we need
	// to keep the values in timecents so we can calculate it during startNote
	if (!key_idx_to_hold)
		hold  = (hold  < -11950.0f ? 0.0f : Timecents2Secsf(hold));
	if (!key_idx_to_decay)
		decay = (decay < -11950.0f ? 0.0f : Timecents2Secsf(decay));
		
	if (sustain < 0.0f)
		sustain = 0.0f;
	else if (sustain_is_gain)
		sustain = DecibelsToGain(-sustain / 10.0f);
	else
		sustain = 1.0f - (sustain / 1000.0f);
}


int LoadSamples(Vector<float>& font_samples, RiffChunk& chunk_smpl, Stream& stream)
{
	// Read sample data into float format buffer.
	float* out;
	unsigned int font_sample_count, samples_left, samples_to_read, samples_to_convert;
	samples_left = font_sample_count = chunk_smpl.size / sizeof(short);
	font_samples.SetCount(font_sample_count);
	out = font_samples.Begin();
	
	if (!out) return 0;
	
	for (; samples_left; samples_left -= samples_to_read)
	{
		short sample_buffer[1024], *in = sample_buffer;
		samples_to_read = (samples_left > 1024 ? 1024 : samples_left);
		(*stream.i.*stream.read)(stream.data, sample_buffer, samples_to_read * sizeof(short));

		// Convert from signed 16-bit to float.
		for (samples_to_convert = samples_to_read; samples_to_convert > 0; --samples_to_convert)
			// If we ever need to compile for big-endian platforms, we'll need to byte-swap here.
			*out++ = (float)(*in++ / 32767.0);
	}
	return 1;
}

void VoiceEnvelope::NextSegment(short active_segment, float out_sample_rate)
{
	switch (active_segment)
	{
	case SEGMENT_NONE:
		samples_until_next_segment = (int)(parameters.delay * out_sample_rate);
		if (samples_until_next_segment > 0)
		{
			segment = SEGMENT_DELAY;
			segment_is_exponential = false;
			level = 0.0;
			slope = 0.0;
			return;
		}
		/* fall through */
	case SEGMENT_DELAY:
		samples_until_next_segment = (int)(parameters.attack * out_sample_rate);
		if (samples_until_next_segment > 0)
		{
			if (!is_amp_env)
			{
				//mod env attack duration scales with velocity (velocity of 1 is full duration, max velocity is 0.125 times duration)
				samples_until_next_segment = (int)(parameters.attack * ((145 - midi_velocity) / 144.0f) * out_sample_rate);
			}
			segment = SEGMENT_ATTACK;
			segment_is_exponential = false;
			level = 0.0f;
			slope = 1.0f / samples_until_next_segment;
			return;
		}
		/* fall through */
	case SEGMENT_ATTACK:
		samples_until_next_segment = (int)(parameters.hold * out_sample_rate);
		if (samples_until_next_segment > 0)
		{
			segment = SEGMENT_HOLD;
			segment_is_exponential = false;
			level = 1.0f;
			slope = 0.0f;
			return;
		}
		/* fall through */
	case SEGMENT_HOLD:
		samples_until_next_segment = (int)(parameters.decay * out_sample_rate);
		if (samples_until_next_segment > 0)
		{
			segment = SEGMENT_DECAY;
			level = 1.0f;
			if (is_amp_env)
			{
				// I don't truly understand this; just following what LinuxSampler does.
				float mysterySlope = -9.226f / samples_until_next_segment;
				slope = EXPF(mysterySlope);
				segment_is_exponential = true;
				if (parameters.sustain > 0.0f)
				{
					// Again, this is following LinuxSampler's example, which is similar to
					// SF2-style decay, where "decay" specifies the time it would take to
					// get to zero, not to the sustain level.  The SFZ spec is not that
					// specific about what "decay" means, so perhaps it's really supposed
					// to specify the time to reach the sustain level.
					samples_until_next_segment = (int)(LOG_(parameters.sustain) / mysterySlope);
				}
			}
			else
			{
				slope = -1.0f / samples_until_next_segment;
				samples_until_next_segment = (int)(parameters.decay * (1.0f - parameters.sustain) * out_sample_rate);
				segment_is_exponential = false;
			}
			return;
		}
		/* fall through */
	case SEGMENT_DECAY:
		segment = SEGMENT_SUSTAIN;
		level = parameters.sustain;
		slope = 0.0f;
		samples_until_next_segment = 0x7FFFFFFF;
		segment_is_exponential = false;
		return;
	case SEGMENT_SUSTAIN:
		segment = SEGMENT_RELEASE;
		samples_until_next_segment = (int)((parameters.release <= 0 ? FASTRELEASETIME : parameters.release) * out_sample_rate);
		if (is_amp_env)
		{
			// I don't truly understand this; just following what LinuxSampler does.
			float mysterySlope = -9.226f / samples_until_next_segment;
			slope = EXPF(mysterySlope);
			segment_is_exponential = true;
		}
		else
		{
			slope = -level / samples_until_next_segment;
			segment_is_exponential = false;
		}
		return;
	case SEGMENT_RELEASE:
	default:
		segment = SEGMENT_DONE;
		segment_is_exponential = false;
		level = slope = 0.0f;
		samples_until_next_segment = 0x7FFFFFF;
	}
}

void VoiceEnvelope::Setup(Envelope& new_parameters, int midi_note_number, short midi_velocity, bool is_amp_env, float out_sample_rate)
{
	parameters = new_parameters;
	if (parameters.key_idx_to_hold)
	{
		parameters.hold += parameters.key_idx_to_hold * (60.0f - midi_note_number);
		parameters.hold = (parameters.hold < -10000.0f ? 0.0f : Timecents2Secsf(parameters.hold));
	}
	if (parameters.key_idx_to_decay)
	{
		parameters.decay += parameters.key_idx_to_decay * (60.0f - midi_note_number);
		parameters.decay = (parameters.decay < -10000.0f ? 0.0f : Timecents2Secsf(parameters.decay));
	}
	midi_velocity = midi_velocity;
	is_amp_env = is_amp_env;
	
	NextSegment(SEGMENT_NONE, out_sample_rate);
}

void VoiceEnvelope::Process(int sample_count, float out_sample_rate)
{
	if (slope)
	{
		if (segment_is_exponential) level *= POWF(slope, (float)sample_count);
		else level += (slope * sample_count);
	}
	if ((samples_until_next_segment -= sample_count) <= 0)
		NextSegment(segment, out_sample_rate);
}



void VoiceLowPass::Setup(float Fc)
{
	// Lowpass filter from http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
	double K = TAN(M_PI * Fc), KK = K * K;
	double norm = 1 / (1 + K * q_inv + KK);
	a0 = KK * norm;
	a1 = 2 * a0;
	b1 = 2 * (KK - 1) * norm;
	b2 = (1 - K * q_inv + KK) * norm;
}

float VoiceLowPass::Process(double In)
{
	double Out = In * a0 + z1;
	z1 = In * a1 + z2 - b1 * Out;
	z2 = In * a0 - b2 * Out;
	return (float)Out;
}



void VoiceLfo::Setup(float delay, int freqCents, float out_sample_rate)
{
	samples_until = (int)(delay * out_sample_rate);
	delta = (4.0f * Cents2Hertz((float)freqCents) / out_sample_rate);
	level = 0;
}

void VoiceLfo::Process(int block_samples)
{
	if (samples_until > block_samples) {
		samples_until -= block_samples;
		return;
	}
	
	level += delta * block_samples;
	
	if (level >  1.0f) {
		delta = -delta;
		level =  2.0f - level;
	}
	else if (level < -1.0f) {
		delta = -delta;
		level = -2.0f - level;
	}
}





void Voice::Kill()
{
	playing_preset = -1;
}

void Voice::CalculatePitchRatio(float pitch_shift, float out_sample_rate)
{
	double note = playing_key + region->transpose + region->tune / 100.0;
	double adjustedPitch = region->pitch_keycenter + (note - region->pitch_keycenter) * (region->pitch_keytrack / 100.0);
	if (pitch_shift) adjustedPitch += pitch_shift;
	pitch_input_timecents = adjustedPitch * 100.0;
	pitch_output_timecents = region->sample_rate / (Timecents2Secsd(region->pitch_keycenter * 100.0) * out_sample_rate);
}



NAMESPACE_SOFTINSTRU_END
