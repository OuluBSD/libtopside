#ifndef _SoftInstru_Voice_h_
#define _SoftInstru_Voice_h_

NAMESPACE_SOFTINSTRU_BEGIN


struct Instrument;


struct RiffChunk {
	char id[4];
	uint32 size;
};

struct Envelope {
	float delay;
	float attack;
	float hold;
	float decay;
	float sustain;
	float release;
	float key_idx_to_hold;
	float key_idx_to_decay;
	
	
	
	void ToSecs(bool sustain_is_gain);

};

struct VoiceEnvelope {
	float level;
	float slope;
	int samples_until_next_segment;
	short segment;
	short midi_velocity;
	struct Envelope parameters;
	bool segment_is_exponential;
	bool is_amp_env;
	
	void NextSegment(short active_segment, float out_sample_rate);
	void Setup(Envelope& new_parameters, int midi_note_number, short midi_velocity, bool is_amp_env, float out_sample_rate);
	void Process(int sample_count, float out_sample_rate);
	
};

struct VoiceLowPass {
	double q_inv;
	double a0;
	double a1;
	double b1;
	double b2;
	double z1;
	double z2;
	bool active;
	
	void Setup(float Fc);
	float Process(double In);
	
	
};

struct VoiceLfo {
	int samples_until;
	float level;
	float delta;
	
	
	void Setup(float delay, int freqCents, float out_sample_rate);
	void Process(int block_samples);
	
};

struct Region {
	int loop_mode;
	uint32 sample_rate;
	uint8 lokey;
	uint8 hikey;
	uint8 lovel;
	uint8 hivel;
	uint32 group;
	uint32 offset;
	uint32 end;
	uint32 loop_start;
	uint32 loop_end;
	int transpose;
	int tune;
	int pitch_keycenter;
	int pitch_keytrack;
	float attenuation;
	float pan;
	Envelope amp_env;
	Envelope mod_env;
	int initial_filter_q;
	int initial_filter_fc;
	int mod_env_to_pitch;
	int mod_env_to_filter_fc;
	int mod_lfo_to_filter_fc;
	int mod_lfo_to_volume;
	float delay_mod_lfo;
	int freq_mod_lfo;
	int mod_lfo_to_pitch;
	float delay_vib_lfo;
	int freq_vib_lfo;
	int vib_lfo_to_pitch;
	
	
	
	void Clear(bool for_relative);
	void Operator(uint16 gen_op, union HydraGenAmount* amount, Region* merge_region);

};

struct Preset
{
	String name;
	uint16 preset;
	uint16 bank;
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

struct Voice
{
	int playing_preset;
	int playing_key;
	int playing_channel;
	Region* region;
	double pitch_input_timecents;
	double pitch_output_timecents;
	double source_sample_position;
	float note_gain_db;
	float pan_factor_left;
	float pan_factor_right;
	uint32 play_idx;
	uint32 loop_start;
	uint32 loop_end;
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
	uint16 preset_idx;
	uint16 bank;
	uint16 pitch_wheel;
	uint16 midi_pan;
	uint16 midi_volume;
	uint16 midi_expression;
	uint16 midi_rpn;
	uint16 midi_data;
	float pan_offset;
	float gain_db;
	float pitch_range;
	float tuning;
};

struct Channels
{
	int active_ch = -1;
	Array<Channel> channels;
	
};

// Stream structure for the generic loading
struct Stream
{
	Instrument* i;
	
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
