#ifndef _SoftInstru_Voice_h_
#define _SoftInstru_Voice_h_

NAMESPACE_SOFTINSTRU_BEGIN


struct Instrument;


struct RiffChunk {
	char id[4];
	uint32 size = 0;
};

struct Envelope {
	float delay = 0;
	float attack = 0;
	float hold = 0;
	float decay = 0;
	float sustain = 0;
	float release = 0;
	float key_idx_to_hold = 0;
	float key_idx_to_decay = 0;
	
	
	
	void ToSecs(bool sustain_is_gain);

};

struct VoiceEnvelope {
	float level = 0;
	float slope = 0;
	int samples_until_next_segment = 0;
	short segment = 0;
	short midi_velocity = 0;
	Envelope parameters;
	bool segment_is_exponential = 0;
	bool is_amp_env = 0;
	
	void NextSegment(short active_segment, float out_sample_rate);
	void Setup(Envelope& new_parameters, int midi_note_number, short midi_velocity, bool is_amp_env, float out_sample_rate);
	void Process(int sample_count, float out_sample_rate);
	
};

struct VoiceLowPass {
	double q_inv = 0;
	double a0 = 0;
	double a1 = 0;
	double b1 = 0;
	double b2 = 0;
	double z1 = 0;
	double z2 = 0;
	bool active = 0;
	
	void Setup(float Fc);
	float Process(double In);
	
	
};

struct VoiceLfo {
	int samples_until = 0;
	float level = 0;
	float delta = 0;
	
	
	void Setup(float delay, int freqCents, float out_sample_rate);
	void Process(int block_samples);
	
};

struct Region {
	int loop_mode = 0;
	uint32 sample_rate = 0;
	uint8 lokey = 0;
	uint8 hikey = 0;
	uint8 lovel = 0;
	uint8 hivel = 0;
	uint32 group = 0;
	uint32 offset = 0;
	uint32 end = 0;
	uint32 loop_start = 0;
	uint32 loop_end = 0;
	int transpose = 0;
	int tune = 0;
	int pitch_keycenter = 0;
	int pitch_keytrack = 0;
	float attenuation = 0;
	float pan = 0;
	Envelope amp_env;
	Envelope mod_env;
	int initial_filter_q = 0;
	int initial_filter_fc = 0;
	int mod_env_to_pitch = 0;
	int mod_env_to_filter_fc = 0;
	int mod_lfo_to_filter_fc = 0;
	int mod_lfo_to_volume = 0;
	float delay_mod_lfo = 0;
	int freq_mod_lfo = 0;
	int mod_lfo_to_pitch = 0;
	float delay_vib_lfo = 0;
	int freq_vib_lfo = 0;
	int vib_lfo_to_pitch = 0;
	
	
	
	void Clear(bool for_relative);
	void Operator(uint16 gen_op, union HydraGenAmount* amount, Region* merge_region);

};

struct Preset
{
	String name;
	uint16 preset = 0;
	uint16 bank = 0;
	Array<Region> regions;
	
	
	Preset() {}
	Preset(const Preset& p) {*this = p;}
	void operator=(const Preset& p) {
		name = p.name;
		preset = p.preset;
		bank = p.bank;
		regions <<= p.regions;
	}
};

struct Voice : Moveable<Voice>
{
	int playing_preset = 0;
	int playing_key = 0;
	int playing_channel = 0;
	Region* region = 0;
	double pitch_input_timecents = 0;
	double pitch_output_timecents = 0;
	double source_sample_position = 0;
	float note_gain_db = 0;
	float pan_factor_left = 0;
	float pan_factor_right = 0;
	uint32 play_idx = 0;
	uint32 loop_start = 0;
	uint32 loop_end = 0;
	VoiceEnvelope amp_env;
	VoiceEnvelope mod_env;
	VoiceLowPass lowpass;
	VoiceLfo mod_lfo;
	VoiceLfo vib_lfo;
	
	
	void Kill();
	void CalculatePitchRatio(float pitch_shift, float out_sample_rate);
	void Render(float* output_buffer, int sample_count);
	
	
};

struct Channel
{
	uint16 preset_idx = 0;
	uint16 bank = 0;
	uint16 pitch_wheel = 0;
	uint16 midi_pan = 0;
	uint16 midi_volume = 0;
	uint16 midi_expression = 0;
	uint16 midi_rpn = 0;
	uint16 midi_data = 0;
	float pan_offset = 0;
	float gain_db = 0;
	float pitch_range = 0;
	float tuning = 0;
};

struct Channels
{
	int active_ch = -1;
	Array<Channel> channels;
	
};

// Stream structure for the generic loading
struct Stream
{
	Instrument* i = 0;
	
    // Custom data given to the functions as the first parameter
    void* data;

    // Function pointer will be called to read 'size' bytes into ptr (returns number of read bytes)
    int (Instrument::*read)(void* data, void* ptr, unsigned int size);

    // Function pointer will be called to skip ahead over 'count' bytes (returns 1 on success, 0 on error)
    int (Instrument::*skip)(void* data, unsigned int count);
};



double Timecents2Secsd(double timecents);
float Timecents2Secsf(float timecents);
float Cents2Hertz(float cents);
float DecibelsToGain(float db);
float GainToDecibels(float gain);
bool RiffChunkRead(RiffChunk* parent, RiffChunk& chunk, Stream& stream);
int LoadSamples(Vector<float>& font_samples, RiffChunk& chunk_smpl, Stream& stream);


NAMESPACE_SOFTINSTRU_END

#endif
