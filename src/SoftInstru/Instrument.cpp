#include "SoftInstru.h"

NAMESPACE_SOFTINSTRU_BEGIN


bool Instrument::Load(Stream& stream)
{
	RiffChunk chunk_head;
	RiffChunk chunk_list;
	Hydra hydra;

	if (!RiffChunkRead(NULL, chunk_head, stream) || !FourCCEquals(chunk_head.id, "sfbk"))
	{
		//if (e) *e = INVALID_NOSF2HEADER;
		return false;
	}

	// Read hydra and locate sample data.
	while (RiffChunkRead(&chunk_head, chunk_list, stream))
	{
		RiffChunk chunk;
		if (FourCCEquals(chunk_list.id, "pdta"))
		{
			while (RiffChunkRead(&chunk_list, chunk, stream))
			{
				#define HandleChunk(chunkId, chunkName) \
				(FourCCEquals(chunk.id, #chunkId) && !(chunk.size % chunkName##_SizeInFile)) \
				{ \
					int num = chunk.size / chunkName##_SizeInFile; \
					hydra.chunkName.SetCount(num); \
					for (auto& o : hydra.chunkName) o.Read(stream); \
				}
				enum
				{
					preset_headers_SizeInFile = 38,
					preset_bags_SizeInFile =  4,
					preset_mods_SizeInFile = 10,
					preset_gens_SizeInFile =  4,
					instruments_SizeInFile = 22,
					instrument_bags_SizeInFile =  4,
					instrument_mods_SizeInFile = 10,
					instrument_gens_SizeInFile =  4,
					sample_headers_SizeInFile = 46
				};
					
				if      HandleChunk(phdr, preset_headers)
				else if HandleChunk(pbag, preset_bags)
				else if HandleChunk(pmod, preset_mods)
				else if HandleChunk(pgen, preset_gens)
				else if HandleChunk(inst, instruments)
				else if HandleChunk(ibag, instrument_bags)
				else if HandleChunk(imod, instrument_mods)
				else if HandleChunk(igen, instrument_gens)
				else if HandleChunk(shdr, sample_headers)
				else (*this.*stream.skip)(stream.data, chunk.size);
				#undef HandleChunk
			}
		}
		else if (FourCCEquals(chunk_list.id, "sdta"))
		{
			while (RiffChunkRead(&chunk_list, chunk, stream))
			{
				if (FourCCEquals(chunk.id, "smpl") && font_samples.IsEmpty() && chunk.size >= sizeof(short))
				{
					if (!LoadSamples(font_samples, chunk, stream))
						return false;
				}
				else (*this.*stream.skip)(stream.data, chunk.size);
			}
		}
		else (*this.*stream.skip)(stream.data, chunk_list.size);
	}
	/*if (hydra.preset_headers.IsEmpty() || hydra.preset_bags || !hydra.preset_mods || !hydra.preset_gens || !hydra.instruments || !hydra.instrument_bags || !hydra.instrument_mods || !hydra.instrument_gens || !hydra.sample_headers)
	{
		//if (e) *e = INVALID_INCOMPLETE;
	}
	else if (font_samples == NULL)
	{
		//if (e) *e = INVALID_NOSAMPLEDATA;
	}
	else*/
	{
		if (!LoadPresets(hydra, font_samples.GetCount()))
			return false;
		this->out_sample_rate = 44100.0f;
	}
	
	return true;
}

void Instrument::Copy(const Instrument& i)
{
	if (!i.ref_count)
	{
		i.ref_count = (int*)MALLOC(sizeof(int));
		if (!i.ref_count) return;
		*i.ref_count = 1;
	}
	presets <<= i.presets;
	font_samples <<= i.font_samples;
	//voices <<= i.voices;
	//channels <<= i.channels;
	
	//preset_i = i.preset_i;
	//voice_i = i.voice_i;
	max_voice_count = i.max_voice_count;
	voice_play_idx = i.voice_play_idx;
	
	output_mode = i.output_mode;
	out_sample_rate = i.out_sample_rate;
	global_gain_db = i.global_gain_db;
	ref_count = i.ref_count;
	
	//voice_i = 0;
	//res->channels = NULL;
	(*ref_count)++;
}

/*void Instrument::Close()
{
	if (!ref_count || !--(*ref_count))
	{
		delete this;
	}
}*/

void Instrument::Reset()
{
	int i = 0;
	for(Voice& v : voices) {
		if (v.playing_preset != -1 && (v.amp_env.segment < SEGMENT_RELEASE || v.amp_env.parameters.release))
			EndQuick(v);
	}
	channels.channels.Clear();
}

int Instrument::GetPresetIndex(int bank, int preset_number)
{
	int i = 0;
	for(Preset& p : presets) {
		if (p.preset == preset_number && p.bank == bank)
			return i;
		i++;
	}
	return -1;
}

int Instrument::GetPresetCount()
{
	return presets.GetCount();
}

String Instrument::GetPresetName(int preset)
{
	return (preset < 0 || preset >= presets.GetCount() ? String() : presets[preset].name);
}

String Instrument::GetBankPresetName(int bank, int preset_number)
{
	return GetPresetName(GetPresetIndex(bank, preset_number));
}

void Instrument::SetOutput(enum OutputMode output_mode, int samplerate, float global_gain_db)
{
	this->output_mode = output_mode;
	out_sample_rate = (float)(samplerate >= 1 ? samplerate : 44100.0f);
	this->global_gain_db = global_gain_db;
}

void Instrument::SetVolume(float global_volume)
{
	global_gain_db = (global_volume == 1.0f ? 0 : -GainToDecibels(1.0f / global_volume));
}

void Instrument::SetMaxVoices(int max_voices)
{
	int i = voices.GetCount();
	voices.SetCount(max_voices);
	for (; i < max_voices; i++)
		voices[i].playing_preset = -1;
}

int Instrument::NoteOn(int preset_index, int key, float vel)
{
	short midi_velocity = (short)(vel * 127);
	int voice_play_idx = 0;

	if (preset_index < 0 || preset_index >= presets.GetCount()) return 1;
	if (vel <= 0.0f) { NoteOff(preset_index, key); return 1; }

	// Play all matching regions.
	voice_play_idx++;
	Preset& preset = presets[preset_index];
	for (Region& region : preset.regions)
	{
		bool do_loop;
		float lowpass_filter_qdb, lowpass_fc;
		if (key < region.lokey || key > region.hikey || midi_velocity < region.lovel || midi_velocity > region.hivel)
			continue;

		Voice* voice = NULL;
		Voice* v = voices.Begin();
		Voice* v_end = voices.End();
		
		if (region.group)
		{
			for (; v != v_end; v++)
				if (v->playing_preset == preset_index && v->region->group == region.group)
					EndQuick(*v);
				else if (v->playing_preset == -1 && !voice)
					voice = v;
		}
		else for (; v != v_end; v++) if (v->playing_preset == -1) { voice = v; break; }

		if (!voice)
		{
			//Voice* new_voices;
			if (max_voice_count)
			{
				// voices have been pre-allocated and limited to a maximum, unable to start playing this voice
				continue;
			}
			int new_count = voices.GetCount() + 4;
			voices.SetCount(new_count);
			voice = &voices[new_count - 4];
			voice[1].playing_preset = voice[2].playing_preset = voice[3].playing_preset = -1;
		}

		voice->region = &region;
		voice->playing_preset = preset_index;
		voice->playing_key = key;
		voice->play_idx = voice_play_idx;
		voice->note_gain_db = global_gain_db - region.attenuation - GainToDecibels(1.0f / vel);

		if (channels.active_ch >= 0)
		{
			SetupChannelVoice(*voice);
		}
		else
		{
			voice->CalculatePitchRatio(0, out_sample_rate);
			
			// The SFZ spec is silent about the pan curve, but a 3dB pan law seems common. This sqrt() curve matches what Dimension LE does; Alchemy Free seems closer to sin(adjustedPan * pi/2).
			voice->pan_factor_left  = SQRTF(0.5f - region.pan);
			voice->pan_factor_right = SQRTF(0.5f + region.pan);
		}

		// Offset/end.
		voice->source_sample_position = region.offset;

		// Loop.
		do_loop = (region.loop_mode != LOOPMODE_NONE && region.loop_start < region.loop_end);
		voice->loop_start = (do_loop ? region.loop_start : 0);
		voice->loop_end = (do_loop ? region.loop_end : 0);

		// Setup envelopes.
		voice->amp_env.Setup(region.amp_env, key, midi_velocity, true, out_sample_rate);
		voice->mod_env.Setup(region.mod_env, key, midi_velocity, false, out_sample_rate);

		// Setup lowpass filter.
		lowpass_fc = (region.initial_filter_fc <= 13500 ? Cents2Hertz((float)region.initial_filter_fc) / out_sample_rate : 1.0f);
		lowpass_filter_qdb = region.initial_filter_q / 10.0f;
		voice->lowpass.q_inv = 1.0 / POW(10.0, (lowpass_filter_qdb / 20.0));
		voice->lowpass.z1 = voice->lowpass.z2 = 0;
		voice->lowpass.active = (lowpass_fc < 0.499f);
		if (voice->lowpass.active)
			voice->lowpass.Setup(lowpass_fc);

		// Setup LFO filters.
		voice->mod_lfo.Setup(region.delay_mod_lfo, region.freq_mod_lfo, out_sample_rate);
		voice->vib_lfo.Setup(region.delay_vib_lfo, region.freq_vib_lfo, out_sample_rate);
	}
	return 1;
}

int Instrument::BankNoteOn(int bank, int preset_number, int key, float vel)
{
	int preset_index = GetPresetIndex(bank, preset_number);
	if (preset_index == -1) return 0;
	return NoteOn(preset_index, key, vel);
}

void Instrument::NoteOff(int preset_index, int key)
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	Voice* v_match_first = NULL;
	Voice* v_match_last = NULL;
	
	for (; v != v_end; v++) {
		//Find the first and last entry in the voices list with matching preset, key and look up the smallest play index
		if (v->playing_preset != preset_index || v->playing_key != key || v->amp_env.segment >= SEGMENT_RELEASE)
			continue;
		else if (!v_match_first || v->play_idx < v_match_first->play_idx)
			v_match_first = v_match_last = v;
		else if (v->play_idx == v_match_first->play_idx)
			v_match_last = v;
	}
	if (!v_match_first)
		return;
	for (v = v_match_first; v <= v_match_last; v++) {
		//Stop all voices with matching preset, key and the smallest play index which was enumerated above
		if (v != v_match_first && v != v_match_last &&
			(v->play_idx != v_match_first->play_idx || v->playing_preset != preset_index || v->playing_key != key || v->amp_env.segment >= SEGMENT_RELEASE))
			continue;
		End(*v);
	}
}

int Instrument::BankNoteOff(int bank, int preset_number, int key)
{
	int preset_index = GetPresetIndex(bank, preset_number);
	if (preset_index == -1) return 0;
	NoteOff(preset_index, key);
	return 1;
}

void Instrument::NoteOffAll()
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	for (; v != v_end; v++)
		if (v->playing_preset != -1 && v->amp_env.segment < SEGMENT_RELEASE)
			End(*v);
}

int Instrument::ActiveVoiceCount()
{
	int count = 0;
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	for (; v != v_end; v++)
		if (v->playing_preset != -1)
			count++;
	return count;
}

void Instrument::RenderShort(short* buffer, int samples, int flag_mixing)
{
	float output_samples[RENDER_SHORTBUFFERBLOCK];
	int channels = (output_mode == MONO ? 1 : 2);
	int max_channel_samples = RENDER_SHORTBUFFERBLOCK / channels;
	while (samples > 0)
	{
		int channel_samples = (samples > max_channel_samples ? max_channel_samples : samples);
		short* buffer_end = buffer + channel_samples * channels;
		float* float_samples = output_samples;
		RenderFloat(float_samples, channel_samples, false);
		samples -= channel_samples;

		if (flag_mixing) {
			while (buffer != buffer_end)
			{
				float v = *float_samples++;
				int vi = *buffer + (v < -1.00004566f ? (int)-32768 : (v > 1.00001514f ? (int)32767 : (int)(v * 32767.5f)));
				*buffer++ = (vi < -32768 ? (short)-32768 : (vi > 32767 ? (short)32767 : (short)vi));
			}
		}
		else {
			while (buffer != buffer_end)
			{
				float v = *float_samples++;
				*buffer++ = (v < -1.00004566f ? (short)-32768 : (v > 1.00001514f ? (short)32767 : (short)(v * 32767.5f)));
			}
		}
	}
}

void Instrument::RenderFloat(float* buffer, int samples, int flag_mixing)
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	if (!flag_mixing)
		MEMSET(buffer, 0, (output_mode == MONO ? 1 : 2) * sizeof(float) * samples);
	for (; v != v_end; v++)
		if (v->playing_preset != -1)
			Render(*v, buffer, samples);
}

void Instrument::SetupChannelVoice(Voice& v) {
	Channels& ch = this->channels;
	Channel& c = ch.channels[ch.active_ch];
	float newpan = v.region->pan + c.pan_offset;
	v.playing_channel = ch.active_ch;
	v.note_gain_db += c.gain_db;
	v.CalculatePitchRatio(
		(c.pitch_wheel == 8192 ?
			c.tuning :
			((c.pitch_wheel / 16383.0f * c.pitch_range * 2.0f) - c.pitch_range + c.tuning)),
		out_sample_rate);
	if (newpan <= -0.5f) {
		v.pan_factor_left = 1.0f;
		v.pan_factor_right = 0.0f;
	}
	else if (newpan >=  0.5f) {
		v.pan_factor_left = 0.0f;
		v.pan_factor_right = 1.0f;
	}
	else {
		v.pan_factor_left = SQRTF(0.5f - newpan);
		v.pan_factor_right = SQRTF(0.5f + newpan);
	}
}

Channel& Instrument::InitChannel(int channel) {
	Channels& ch = this->channels;
	ASSERT(channel >= 0);
	if (channel < ch.channels.GetCount())
		return ch.channels[channel];
	
	int old_count = ch.channels.GetCount();
	ch.channels.SetCount(channel+1);
	
	for (int i = old_count; i < ch.channels.GetCount(); i++) {
		Channel& c = ch.channels[i];
		c.preset_idx = c.bank = 0;
		c.pitch_wheel = c.midi_pan = 8192;
		c.midi_volume = c.midi_expression = 16383;
		c.midi_rpn = 0xFFFF;
		c.midi_data = 0;
		c.pan_offset = 0.0f;
		c.gain_db = 0.0f;
		c.pitch_range = 2.0f;
		c.tuning = 0.0f;
	}
	return ch.channels[channel];
}


void Instrument::ApplyChannelPitch(int channel, Channel& c)
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	float pitch_shift = (c.pitch_wheel == 8192 ? c.tuning : ((c.pitch_wheel / 16383.0f * c.pitch_range * 2.0f) - c.pitch_range + c.tuning));
	for (; v != v_end; v++)
		if (v->playing_channel == channel && v->playing_preset != -1)
			v->CalculatePitchRatio(pitch_shift, out_sample_rate);
}

void Instrument::SetChannelPresetIndex(int channel, int preset_index)
{
	Channel& c = InitChannel(channel);
	c.preset_idx = (unsigned short)preset_index;
}

bool Instrument::SetChannelPresetNumber(int channel, int preset_number, int flag_mididrums)
{
	int preset_index;
	Channel& c = InitChannel(channel);
	
	if (flag_mididrums) {
		preset_index = GetPresetIndex( 128 | (c.bank & 0x7FFF), preset_number);
		if (preset_index == -1)
			preset_index = GetPresetIndex(128, preset_number);
		if (preset_index == -1)
			preset_index = GetPresetIndex(128, 0);
		if (preset_index == -1)
			preset_index = GetPresetIndex((c.bank & 0x7FFF), preset_number);
	}
	else
		preset_index = GetPresetIndex((c.bank & 0x7FFF), preset_number);
	
	if (preset_index == -1)
		preset_index = GetPresetIndex(0, preset_number);
	
	if (preset_index != -1) {
		c.preset_idx = (unsigned short)preset_index;
		return true;
	}
	
	return false;
}

void Instrument::SetChannelBank(int channel, int bank)
{
	Channel& c = InitChannel(channel);
	
	c.bank = (unsigned short)bank;
}

void Instrument::SetChannelBankPreset(int channel, int bank, int preset_number)
{
	int preset_index;
	Channel& c = InitChannel(channel);
	
	preset_index = GetPresetIndex(bank, preset_number);
	if (preset_index == -1)
		return;
	c.preset_idx = (unsigned short)preset_index;
	c.bank = (unsigned short)bank;
}


void Instrument::SetChannelPan(int channel, float pan)
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	Channel& c = InitChannel(channel);
	
	for (; v != v_end; v++) {
		if (v->playing_channel == channel && v->playing_preset != -1) {
			float newpan = v->region->pan + pan - 0.5f;
			if (newpan <= -0.5f) {
				v->pan_factor_left = 1.0f;
				v->pan_factor_right = 0.0f;
			}
			else
				if (newpan >=  0.5f) {
					v->pan_factor_left = 0.0f;
					v->pan_factor_right = 1.0f;
				}
				else {
					v->pan_factor_left = SQRTF(0.5f - newpan);
					v->pan_factor_right = SQRTF(0.5f + newpan);
				}
		}
	}
	c.pan_offset = pan - 0.5f;
}

void Instrument::SetChannelVolume(int channel, float volume)
{
	float gain_db = GainToDecibels(volume);
	float gain_dbChange;
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	Channel& c = InitChannel(channel);
	
	if (gain_db == c.gain_db)
		return;
	for (gain_dbChange = gain_db - c.gain_db; v != v_end; v++)
		if (v->playing_channel == channel && v->playing_preset != -1)
			v->note_gain_db += gain_dbChange;
	c.gain_db = gain_db;
}

void Instrument::SetChannelPitchWheel(int channel, int pitch_wheel)
{
	Channel& c = InitChannel(channel);
	
	if (c.pitch_wheel == pitch_wheel)
		return;
	c.pitch_wheel = (unsigned short)pitch_wheel;
	ApplyChannelPitch(channel, c);
}

void Instrument::SetChannelPitchRange(int channel, float pitch_range)
{
	Channel& c = InitChannel(channel);
	
	if (c.pitch_range == pitch_range)
		return;
	c.pitch_range = pitch_range;
	if (c.pitch_wheel != 8192) ApplyChannelPitch(channel, c);
}

void Instrument::SetChannelTuning(int channel, float tuning)
{
	Channel& c = InitChannel(channel);
	
	if (c.tuning == tuning)
		return;
	c.tuning = tuning;
	ApplyChannelPitch(channel, c);
}

int Instrument::NoteOnChannel(int channel, int key, float vel)
{
	Channels& c = this->channels;
	if (channel < 0 || channel >= c.channels.GetCount())
		return 1;
	c.active_ch = channel;
	return NoteOn(c.channels[channel].preset_idx, key, vel);
}

void Instrument::NoteOffChannel(int channel, int key)
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	Voice* v_match_first = NULL;
	Voice* v_match_last = NULL;
	for (; v != v_end; v++) {
		//Find the first and last entry in the voices list with matching channel, key and look up the smallest play index
		if (v->playing_preset == -1 || v->playing_channel != channel || v->playing_key != key || v->amp_env.segment >= SEGMENT_RELEASE)
			continue;
		else if (!v_match_first || v->play_idx < v_match_first->play_idx)
			v_match_first = v_match_last = v;
		else if (v->play_idx == v_match_first->play_idx)
				v_match_last = v;
	}
	if (!v_match_first)
		return;
	for (v = v_match_first; v <= v_match_last; v++) {
		//Stop all voices with matching channel, key and the smallest play index which was enumerated above
		if (v != v_match_first && v != v_match_last &&
			(v->play_idx != v_match_first->play_idx || v->playing_preset == -1 || v->playing_channel != channel || v->playing_key != key || v->amp_env.segment >= SEGMENT_RELEASE))
			continue;
		End(*v);
	}
}

void Instrument::NoteOffChannelAll(int channel)
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	for (; v != v_end; v++)
		if (v->playing_preset != -1 && v->playing_channel == channel && v->amp_env.segment < SEGMENT_RELEASE)
			End(*v);
}

void Instrument::SoundsOffAllChannel(int channel)
{
	Voice* v = voices.Begin();
	Voice* v_end = voices.End();
	for (; v != v_end; v++)
		if (v->playing_preset != -1 && v->playing_channel == channel && (v->amp_env.segment < SEGMENT_RELEASE || v->amp_env.parameters.release))
			EndQuick(*v);
}

int Instrument::ChannelMidiControl(int channel, int controller, int control_value)
{
	Channel& c = InitChannel(channel);
	
	switch (controller)
	{
		case   7 /*VOLUME_MSB*/      : c.midi_volume     = (unsigned short)((c.midi_volume     & 0x7F  ) | (control_value << 7)); goto TCMC_SET_VOLUME;
		case  39 /*VOLUME_LSB*/      : c.midi_volume     = (unsigned short)((c.midi_volume     & 0x3F80) |  control_value);       goto TCMC_SET_VOLUME;
		case  11 /*EXPRESSION_MSB*/  : c.midi_expression = (unsigned short)((c.midi_expression & 0x7F  ) | (control_value << 7)); goto TCMC_SET_VOLUME;
		case  43 /*EXPRESSION_LSB*/  : c.midi_expression = (unsigned short)((c.midi_expression & 0x3F80) |  control_value);       goto TCMC_SET_VOLUME;
		case  10 /*PAN_MSB*/         : c.midi_pan        = (unsigned short)((c.midi_pan        & 0x7F  ) | (control_value << 7)); goto TCMC_SET_PAN;
		case  42 /*PAN_LSB*/         : c.midi_pan        = (unsigned short)((c.midi_pan        & 0x3F80) |  control_value);       goto TCMC_SET_PAN;
		case   6 /*DATA_ENTRY_MSB*/  : c.midi_data       = (unsigned short)((c.midi_data       & 0x7F)   | (control_value << 7)); goto TCMC_SET_DATA;
		case  38 /*DATA_ENTRY_LSB*/  : c.midi_data       = (unsigned short)((c.midi_data       & 0x3F80) |  control_value);       goto TCMC_SET_DATA;
		case   0 /*BANK_SELECT_MSB*/ : c.bank = (unsigned short)(0x8000 | control_value); return 1; //bank select MSB alone acts like LSB
		case  32 /*BANK_SELECT_LSB*/ : c.bank = (unsigned short)((c.bank & 0x8000 ? ((c.bank & 0x7F) << 7) : 0) | control_value); return 1;
		case 101 /*RPN_MSB*/         : c.midi_rpn = (unsigned short)(((c.midi_rpn == 0xFFFF ? 0 : c.midi_rpn) & 0x7F  ) | (control_value << 7)); return 1;
		case 100 /*RPN_LSB*/         : c.midi_rpn = (unsigned short)(((c.midi_rpn == 0xFFFF ? 0 : c.midi_rpn) & 0x3F80) |  control_value); return 1;
		case  98 /*NRPN_LSB*/        : c.midi_rpn = 0xFFFF; return 1;
		case  99 /*NRPN_MSB*/        : c.midi_rpn = 0xFFFF; return 1;
		case 120 /*ALL_SOUND_OFF*/   : SoundsOffAllChannel(channel); return 1;
		case 123 /*ALL_NOTES_OFF*/   : NoteOffChannelAll(channel);   return 1;
		case 121 /*ALL_CTRL_OFF*/    :
			c.midi_volume = c.midi_expression = 16383;
			c.midi_pan = 8192;
			c.bank = 0;
			c.midi_rpn = 0xFFFF;
			c.midi_data = 0;
			SetChannelVolume(channel, 1.0f);
			SetChannelPan(channel, 0.5f);
			SetChannelPitchRange(channel, 2.0f);
			SetChannelTuning(channel, 0);
			return 1;
	}
	return 1;
TCMC_SET_VOLUME:
	//Raising to the power of 3 seems to result in a decent sounding volume curve for MIDI
	SetChannelVolume(channel, POWF((c.midi_volume / 16383.0f) * (c.midi_expression / 16383.0f), 3.0f));
	return 1;
TCMC_SET_PAN:
	SetChannelPan(channel, c.midi_pan / 16383.0f);
	return 1;
TCMC_SET_DATA:
	if      (c.midi_rpn == 0) SetChannelPitchRange(channel, (c.midi_data >> 7) + 0.01f * (c.midi_data & 0x7F));
	else if (c.midi_rpn == 1) SetChannelTuning(channel, (int)c.tuning + ((float)c.midi_data - 8192.0f) / 8192.0f); //fine tune
	else if (c.midi_rpn == 2 && controller == 6) SetChannelTuning(channel, ((float)control_value - 64.0f) + (c.tuning - (int)c.tuning)); //coarse tune
	return 1;
}

int Instrument::GetChannelPresetIndex(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? channels.channels[channel].preset_idx : 0);
}

int Instrument::GetChannelPresetBank(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? (channels.channels[channel].bank & 0x7FFF) : 0);
}

int Instrument::GetChannelPresetNumber(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? presets[channels.channels[channel].preset_idx].preset : 0);
}

float Instrument::GetChannelPan(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? channels.channels[channel].pan_offset - 0.5f : 0.5f);
}

float Instrument::GetChannelVolume(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? DecibelsToGain(channels.channels[channel].gain_db) : 1.0f);
}

int Instrument::GetChannelPitchWheel(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? channels.channels[channel].pitch_wheel : 8192);
}

float Instrument::GetChannelPitchRange(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? channels.channels[channel].pitch_range : 2.0f);
}

float Instrument::GetChannelTuning(int channel)
{
	return (channel >= 0 && channel < channels.channels.GetCount() ? channels.channels[channel].tuning : 0.0f);
}

bool Instrument::LoadFilename(String filename) {
	struct Stream stream = {
		this,
		NULL,
		(int(Instrument::*)(void*, void*, unsigned int))&Instrument::StreamReadStdio,
		(int(Instrument::*)(void*, unsigned int))&Instrument::StreamSkipStdio
	};
#if __STDC_WANT_SECURE_LIB__
	FILE* f = NULL;
	fopen_s(&f, filename, "rb");
#else
	FILE* f = fopen(filename, "rb");
#endif
	if (!f) {
		//if (e) *e = FILENOTFOUND;
		return false;
	}
	stream.data = f;
	Load(stream);
	fclose(f);
	return true;
}


bool Instrument::LoadMemory(const void* buffer, int size)
{
	Stream stream = {
		this,
		NULL,
		(int(Instrument::*)(void*, void*, unsigned int))&Instrument::StreamMemory_read,
		(int(Instrument::*)(void*, unsigned int))&Instrument::StreamMemory_skip
	};
	StreamMemory f = {
		0, 0, 0
	};
	f.buffer = buffer;
	f.total = size;
	stream.data = &f;
	return Load(stream);
}

void Instrument::End(Voice& v)
{
	// if max_voice_count is set, assume that voice rendering and note queuing are on separate threads
	// so to minimize the chance that voice rendering would advance the segment at the same time
	// we just do it twice here and hope that it sticks
	int repeats = (max_voice_count ? 2 : 1);
	while (repeats--)
	{
		v.amp_env.NextSegment(SEGMENT_SUSTAIN, out_sample_rate);
		v.mod_env.NextSegment(SEGMENT_SUSTAIN, out_sample_rate);
		if (v.region->loop_mode == LOOPMODE_SUSTAIN)
		{
			// Continue playing, but stop looping.
			v.loop_end = v.loop_start;
		}
	}
}

void Instrument::EndQuick(Voice& v)
{
	// if max_voice_count is set, assume that voice rendering and note queuing are on separate threads
	// so to minimize the chance that voice rendering would advance the segment at the same time
	// we just do it twice here and hope that it sticks
	int repeats = (max_voice_count ? 2 : 1);
	while (repeats--)
	{
		v.amp_env.parameters.release = 0.0f;
		v.amp_env.NextSegment(SEGMENT_SUSTAIN, out_sample_rate);
		
		v.mod_env.parameters.release = 0.0f;
		v.mod_env.NextSegment(SEGMENT_SUSTAIN, out_sample_rate);
	}
}

int Instrument::LoadPresets(Hydra& hydra, unsigned int font_sample_count) {
	ASSERT(hydra.preset_headers.GetCount() > 0);
	if (hydra.preset_headers.IsEmpty())
		return 0;
	
	enum {
		GenInstrument = 41,
		GenKeyRange = 43,
		GenVelRange = 44,
		GenSampleID = 53
	};
	
	// Read each preset.
	this->presets.SetCount(hydra.preset_headers.GetCount() - 1); // last one is 'range end'
	
	if (this->presets.IsEmpty())
		return 0;
	
	for (int pphdr_i = 0; pphdr_i < hydra.preset_headers.GetCount()-1; pphdr_i++) {
		HydraPresetHeader& pphdr = hydra.preset_headers[pphdr_i];
		HydraPresetHeader& next_pphdr = hydra.preset_headers[pphdr_i + 1];
		int sorted_i = 0;
		int region_i = 0;
		Region global_region;
		
		for (int pphdr_j = 0; pphdr_j < hydra.preset_headers.GetCount()-1; pphdr_j++) {
			HydraPresetHeader& other_phdr = hydra.preset_headers[pphdr_j];
			if (&other_phdr == &pphdr || other_phdr.bank > pphdr.bank)
				continue;
			else if (other_phdr.bank < pphdr.bank)
				sorted_i++;
			else if (other_phdr.preset > pphdr.preset)
				continue;
			else if (other_phdr.preset < pphdr.preset)
				sorted_i++;
			else if (&other_phdr < &pphdr)
				sorted_i++;
		}
		
		Preset& preset = this->presets[sorted_i];
		preset.name = pphdr.name;
		preset.bank = pphdr.bank;
		preset.preset = pphdr.preset;
		preset.regions.Clear();
		int preset_region_count = 0;
		
		//count regions covered by this preset
		int begin_i = pphdr.preset_bag_idx;
		int end_i = next_pphdr.preset_bag_idx;
		for (int i = begin_i; i < end_i; i++) {
			HydraPresetBag& ppbag = hydra.preset_bags[i];
			HydraPresetBag& next_ppbag = hydra.preset_bags[i+1];
			uint8 plokey = 0;
			uint8 phikey = 127;
			uint8 plovel = 0;
			uint8 phivel = 127;
			
			int begin_j = ppbag.gen_idx;
			int end_j = next_ppbag.gen_idx;
			for (int j = begin_j; j < end_j; j++) {
				HydraPresetGen& ppgen = hydra.preset_gens[j];
				
				if (ppgen.gen_op == GenKeyRange) {
					plokey = ppgen.gen_amount.range.lo;
					phikey = ppgen.gen_amount.range.hi;
					continue;
				}
				if (ppgen.gen_op == GenVelRange) {
					plovel = ppgen.gen_amount.range.lo;
					phivel = ppgen.gen_amount.range.hi;
					continue;
				}
				if (ppgen.gen_op != GenInstrument)
					continue;
				if (ppgen.gen_amount.word_amount >= hydra.instruments.GetCount())
					continue;
				
				HydraInstrument& pinst = hydra.instruments[ppgen.gen_amount.word_amount];
				HydraInstrument& next_pinst = hydra.instruments[ppgen.gen_amount.word_amount+1];
				int begin_k = pinst.bag_idx;
				int end_k = next_pinst.bag_idx;
				for(int k = begin_k; k < end_k; k++) {
					HydraInstrumentBag& pibag = hydra.instrument_bags[k];
					HydraInstrumentBag& next_pibag = hydra.instrument_bags[k+1];
					unsigned char ilokey = 0;
					unsigned char ihikey = 127;
					unsigned char ilovel = 0;
					unsigned char ihivel = 127;
					int begin_l = pibag.gen_idx;
					int end_l = next_pibag.gen_idx;
					for (int l = begin_l; l < end_l; l++) {
						HydraInstrumentGen& pigen = hydra.instrument_gens[l];
						if (pigen.gen_op == GenKeyRange) {
							ilokey = pigen.gen_amount.range.lo;
							ihikey = pigen.gen_amount.range.hi;
							continue;
						}
						if (pigen.gen_op == GenVelRange) {
							ilovel = pigen.gen_amount.range.lo;
							ihivel = pigen.gen_amount.range.hi;
							continue;
						}
						if (pigen.gen_op == GenSampleID) {
							if (ihikey >= plokey &&
								ilokey <= phikey &&
								ihivel >= plovel &&
								ilovel <= phivel)
								preset_region_count++;
						}
					}
				}
			}
		}
		
		preset.regions.SetCount(preset_region_count);
		global_region.Clear(true);
		
		// Zones.
		for (int i = begin_i; i < end_i; i++) {
			HydraPresetBag& ppbag = hydra.preset_bags[i];
			HydraPresetBag& next_ppbag = hydra.preset_bags[i+1];
			
			Region preset_region = global_region;
			bool had_gen_instrument = false;
			
			// Generators.
			int begin_j = ppbag.gen_idx;
			int end_j = next_ppbag.gen_idx;
			for (int j = begin_j; j < end_j; j++) {
				HydraPresetGen& ppgen = hydra.preset_gens[j];
				
				// Instrument.
				if (ppgen.gen_op == GenInstrument) {
					Region inst_region;
					uint16 which_inst = ppgen.gen_amount.word_amount;
					if (which_inst >= hydra.instruments.GetCount())
						continue;
						
					inst_region.Clear(false);
					HydraInstrument& pinst = hydra.instruments[which_inst];
					HydraInstrument& next_pinst = hydra.instruments[which_inst+1];
					int begin_k = pinst.bag_idx;
					int end_k = next_pinst.bag_idx;
					for(int k = begin_k; k < end_k; k++) {
						HydraInstrumentBag& pibag = hydra.instrument_bags[k];
						HydraInstrumentBag& next_pibag = hydra.instrument_bags[k+1];
						
						// Generators.
						Region zone_region = inst_region;
						int had_sample_id = 0;
						int begin_l = pibag.gen_idx;
						int end_l = next_pibag.gen_idx;
						for (int l = begin_l; l < end_l; l++) {
							HydraInstrumentGen& pigen = hydra.instrument_gens[l];
							
							if (pigen.gen_op == GenSampleID) {
								
								//preset region key and vel ranges are a filter for the zone regions
								if (zone_region.hikey < preset_region.lokey || zone_region.lokey > preset_region.hikey)
									continue;
								if (zone_region.hivel < preset_region.lovel || zone_region.lovel > preset_region.hivel)
									continue;
								if (preset_region.lokey > zone_region.lokey)
									zone_region.lokey = preset_region.lokey;
								if (preset_region.hikey < zone_region.hikey)
									zone_region.hikey = preset_region.hikey;
								if (preset_region.lovel > zone_region.lovel)
									zone_region.lovel = preset_region.lovel;
								if (preset_region.hivel < zone_region.hivel)
									zone_region.hivel = preset_region.hivel;
									
								//sum regions
								zone_region.Operator(0, NULL, &preset_region);
								
								// EG times need to be converted from timecents to seconds.
								zone_region.amp_env.ToSecs(true);
								zone_region.mod_env.ToSecs(false);
								
								// LFO times need to be converted from timecents to seconds.
								zone_region.delay_mod_lfo = (zone_region.delay_mod_lfo < -11950.0f ? 0.0f : Timecents2Secsf(zone_region.delay_mod_lfo));
								zone_region.delay_vib_lfo = (zone_region.delay_vib_lfo < -11950.0f ? 0.0f : Timecents2Secsf(zone_region.delay_vib_lfo));
								
								// Fixup sample positions
								HydraSampleHeader& pshdr = hydra.sample_headers[pigen.gen_amount.word_amount];
								zone_region.offset += pshdr.start;
								zone_region.end += pshdr.end;
								zone_region.loop_start += pshdr.start_loop;
								zone_region.loop_end += pshdr.end_loop;
								if (pshdr.end_loop > 0)
									zone_region.loop_end -= 1;
								if (zone_region.pitch_keycenter == -1)
									zone_region.pitch_keycenter = pshdr.orig_pitch;
								zone_region.tune += pshdr.pitch_correction;
								zone_region.sample_rate = pshdr.sample_rate;
								if (zone_region.end && zone_region.end < font_sample_count)
									zone_region.end++;
								else
									zone_region.end = font_sample_count;
									
								preset.regions[region_i] = zone_region;
								region_i++;
								had_sample_id = 1;
							}
							else
								zone_region.Operator(pigen.gen_op, &pigen.gen_amount, NULL);
						}
						
						// Handle instrument's global zone.
						if (k == pinst.bag_idx && !had_sample_id)
							inst_region = zone_region;
							
						// Modulators (TODO)
						//if (ibag->mod_idx < ibag[1].mod_idx) addUnsupportedOpcode("any modulator");
					}
					had_gen_instrument = true;
				}
				else
					preset_region.Operator(ppgen.gen_op, &ppgen.gen_amount, NULL);
			}
			
			// Modulators (TODO)
			//if (pbag->mod_idx < pbag[1].mod_idx) addUnsupportedOpcode("any modulator");
			
			// Handle preset's global zone.
			if (i == pphdr.preset_bag_idx && !had_gen_instrument)
				global_region = preset_region;
		}
	}
	return 1;
}

void Instrument::Render(Voice& v, float* output_buffer, int sample_count)
{
	ASSERT(v.region);
	Region& region = *v.region;
	Vector<float>& input = this->font_samples;
	float* out_l = output_buffer;
	float* out_r = (this->output_mode == STEREO_UNWEAVED ? out_l + sample_count : NULL);

	// Cache some values, to give them at least some chance of ending up in registers.
	bool update_mod_env = (region.mod_env_to_pitch || region.mod_env_to_filter_fc);
	bool update_mod_lfo = (v.mod_lfo.delta && (region.mod_lfo_to_pitch || region.mod_lfo_to_filter_fc || region.mod_lfo_to_volume));
	bool update_vib_lfo = (v.vib_lfo.delta && (region.vib_lfo_to_pitch));
	bool is_looping = (v.loop_start < v.loop_end);
	unsigned int tmp_loop_start = v.loop_start;
	unsigned int tmp_loop_end = v.loop_end;
	double tmp_sample_end_dbl = (double)region.end;
	double tmp_loop_end_dbl = (double)tmp_loop_end + 1.0;
	double tmp_source_sample_position = v.source_sample_position;
	VoiceLowPass tmp_lowpass = v.lowpass;

	bool dynamic_lowpass = (region.mod_lfo_to_filter_fc || region.mod_env_to_filter_fc);
	float tmp_sample_rate = this->out_sample_rate, tmp_initial_filter_fc, tmp_mod_lfo_to_filter_fc, tmp_mod_env_to_filter_fc;

	bool dynamic_pitch_ratio = (region.mod_lfo_to_pitch || region.mod_env_to_pitch || region.vib_lfo_to_pitch);
	double pitch_ratio;
	float tmp_mod_lfo_to_pitch, tmp_vib_lfo_to_pitch, tmp_mod_env_to_pitch;

	bool dynamic_gain = (region.mod_lfo_to_volume != 0);
	float note_gain = 0, tmp_mod_lfo_to_volume;

	if (dynamic_lowpass) tmp_initial_filter_fc = (float)region.initial_filter_fc, tmp_mod_lfo_to_filter_fc = (float)region.mod_lfo_to_filter_fc, tmp_mod_env_to_filter_fc = (float)region.mod_env_to_filter_fc;
	else tmp_initial_filter_fc = 0, tmp_mod_lfo_to_filter_fc = 0, tmp_mod_env_to_filter_fc = 0;

	if (dynamic_pitch_ratio) pitch_ratio = 0, tmp_mod_lfo_to_pitch = (float)region.mod_lfo_to_pitch, tmp_vib_lfo_to_pitch = (float)region.vib_lfo_to_pitch, tmp_mod_env_to_pitch = (float)region.mod_env_to_pitch;
	else pitch_ratio = Timecents2Secsd(v.pitch_input_timecents) * v.pitch_output_timecents, tmp_mod_lfo_to_pitch = 0, tmp_vib_lfo_to_pitch = 0, tmp_mod_env_to_pitch = 0;

	if (dynamic_gain) tmp_mod_lfo_to_volume = (float)region.mod_lfo_to_volume * 0.1f;
	else note_gain = DecibelsToGain(v.note_gain_db), tmp_mod_lfo_to_volume = 0;

	while (sample_count)
	{
		float gain_mono, gain_left, gain_right;
		int block_samples = (sample_count > RENDER_EFFECTSAMPLEBLOCK ? RENDER_EFFECTSAMPLEBLOCK : sample_count);
		sample_count -= block_samples;

		if (dynamic_lowpass)
		{
			float fres = tmp_initial_filter_fc + v.mod_lfo.level * tmp_mod_lfo_to_filter_fc + v.mod_env.level * tmp_mod_env_to_filter_fc;
			float lowpass_fc = (fres <= 13500 ? Cents2Hertz(fres) / tmp_sample_rate : 1.0f);
			tmp_lowpass.active = (lowpass_fc < 0.499f);
			if (tmp_lowpass.active)
				tmp_lowpass.Setup(lowpass_fc);
		}

		if (dynamic_pitch_ratio)
			pitch_ratio = Timecents2Secsd(v.pitch_input_timecents + (v.mod_lfo.level * tmp_mod_lfo_to_pitch + v.vib_lfo.level * tmp_vib_lfo_to_pitch + v.mod_env.level * tmp_mod_env_to_pitch)) * v.pitch_output_timecents;

		if (dynamic_gain)
			note_gain = DecibelsToGain(v.note_gain_db + (v.mod_lfo.level * tmp_mod_lfo_to_volume));

		gain_mono = note_gain * v.amp_env.level;

		// Update EG.
		v.amp_env.Process(block_samples, tmp_sample_rate);
		if (update_mod_env)
			v.mod_env.Process(block_samples, tmp_sample_rate);

		// Update LFOs.
		if (update_mod_lfo) v.mod_lfo.Process(block_samples);
		if (update_vib_lfo) v.vib_lfo.Process(block_samples);

		switch (this->output_mode)
		{
		case STEREO_INTERLEAVED:
			gain_left = gain_mono * v.pan_factor_left, gain_right = gain_mono * v.pan_factor_right;
			while (block_samples-- && tmp_source_sample_position < tmp_sample_end_dbl)
			{
				unsigned int pos = (unsigned int)tmp_source_sample_position, nextPos = (pos >= tmp_loop_end && is_looping ? tmp_loop_start : pos + 1);

				// Simple linear interpolation.
				float alpha = (float)(tmp_source_sample_position - pos), val = (input[pos] * (1.0f - alpha) + input[nextPos] * alpha);

				// Low-pass filter.
				if (tmp_lowpass.active) val = tmp_lowpass.Process(val);

				*out_l++ += val * gain_left;
				*out_l++ += val * gain_right;

				// Next sample.
				tmp_source_sample_position += pitch_ratio;
				if (tmp_source_sample_position >= tmp_loop_end_dbl && is_looping) tmp_source_sample_position -= (tmp_loop_end - tmp_loop_start + 1.0);
			}
			break;

		case STEREO_UNWEAVED:
			gain_left = gain_mono * v.pan_factor_left, gain_right = gain_mono * v.pan_factor_right;
			while (block_samples-- && tmp_source_sample_position < tmp_sample_end_dbl)
			{
				unsigned int pos = (unsigned int)tmp_source_sample_position, nextPos = (pos >= tmp_loop_end && is_looping ? tmp_loop_start : pos + 1);

				// Simple linear interpolation.
				float alpha = (float)(tmp_source_sample_position - pos), val = (input[pos] * (1.0f - alpha) + input[nextPos] * alpha);

				// Low-pass filter.
				if (tmp_lowpass.active) val = tmp_lowpass.Process(val);

				*out_l++ += val * gain_left;
				*out_r++ += val * gain_right;

				// Next sample.
				tmp_source_sample_position += pitch_ratio;
				if (tmp_source_sample_position >= tmp_loop_end_dbl && is_looping) tmp_source_sample_position -= (tmp_loop_end - tmp_loop_start + 1.0);
			}
			break;

		case MONO:
			while (block_samples-- && tmp_source_sample_position < tmp_sample_end_dbl)
			{
				unsigned int pos = (unsigned int)tmp_source_sample_position, nextPos = (pos >= tmp_loop_end && is_looping ? tmp_loop_start : pos + 1);

				// Simple linear interpolation.
				float alpha = (float)(tmp_source_sample_position - pos), val = (input[pos] * (1.0f - alpha) + input[nextPos] * alpha);

				// Low-pass filter.
				if (tmp_lowpass.active) val = tmp_lowpass.Process(val);

				*out_l++ += val * gain_mono;

				// Next sample.
				tmp_source_sample_position += pitch_ratio;
				if (tmp_source_sample_position >= tmp_loop_end_dbl && is_looping) tmp_source_sample_position -= (tmp_loop_end - tmp_loop_start + 1.0);
			}
			break;
		}

		if (tmp_source_sample_position >= tmp_sample_end_dbl || v.amp_env.segment == SEGMENT_DONE)
		{
			v.Kill();
			return;
		}
	}

	v.source_sample_position = tmp_source_sample_position;
	if (tmp_lowpass.active || dynamic_lowpass) v.lowpass = tmp_lowpass;
}

int Instrument::StreamReadStdio(FILE* f, void* ptr, unsigned int size) {
	return (int)fread(ptr, 1, size, f);
}

int Instrument::StreamSkipStdio(FILE* f, unsigned int count) {
	return !fseek(f, count, SEEK_CUR);
}

int Instrument::StreamMemory_read(StreamMemory* m, void* ptr, unsigned int size) {
	if (size > m->total - m->pos)
		size = m->total - m->pos;
	MEMCPY(ptr, (byte*)m->buffer + m->pos, size);
	m->pos += size;
	return size;
}

int Instrument::StreamMemory_skip(StreamMemory* m, unsigned int count) {
	if (m->pos + count > m->total)
		return 0;
	m->pos += count;
	return 1;
}

void Instrument::HandleEvent(const MidiIO::Event& e, int track_i) {
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
		NoteOffChannel(channel, e.GetP1());
	}
	else if (e.IsNoteOn()) {
		NoteOnChannel(channel, e.GetP1(), e.GetP2() / 127.0f);
	}
	else if (e.IsNote()) {
		LOG("Ignore note: " << e.ToString());
	}
	else if (e.IsAftertouch()) {
		LOG("Ignore aftertouch: " << e.ToString());
	}
	else if (e.IsTimbre() || e.IsPatchChange()) {
		int channel = e.GetChannel();
		int value = e.GetP1();
		if (track_i < 0 || channel == track_i) {
			LOG("Changing channel patch: channel " << channel << " to " << value << ": " << e.ToString());
			int bank = 0;
			// if channel is the midi-standard drum channel
			if (channel == 9) {
				bank = 128;
			}
			SetChannelBankPreset(channel, bank, value);
		}
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
			SetChannelPitchWheel(channel, fs_pbend);
		}
	}
	else {
		LOG("Unexpected configure event: " << e.ToString());
	}
}


NAMESPACE_SOFTINSTRU_END
