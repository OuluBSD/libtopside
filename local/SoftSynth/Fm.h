#ifndef _SoftSynth_Fm_h_
#define _SoftSynth_Fm_h_


// Forked from libfmsynth (see Copying file)


NAMESPACE_SOFTSYNTH_BEGIN



#define SYNTH_VOICES 128
#define SYNTH_OPERATORS 8



// Parameters for the synth which are unique per FM operator.

enum SynthParam {
	PARAM_AMP = 0, /**< Linear amplitude for the operator. */
	PARAM_PAN,     /**< Panning for operator when it's used as a carrier. -1.0 is left, +1.0 is right, +0.0 is centered. */
	
	PARAM_FREQ_MOD, /**< Frequency mod factor. The base frequency of the operator is note frequency times the freq mod.
                             E.g. A4 with freq mod of 2.0 would be 880 Hz. */
	PARAM_FREQ_OFFSET, /**< A constant frequency offset applied to the Oscillator. */
	
	PARAM_ENVELOPE_TARGET0, /**< The linear amplitude reached in the envelope after PARAM_DELAY0 seconds. Initial amplitude is 0. */
	PARAM_ENVELOPE_TARGET1, /**< The linear amplitude reached in the envelope after (PARAM_DELAY0 + PARAM_DELAY1) seconds. */
	PARAM_ENVELOPE_TARGET2, /**< The linear amplitide reached in the envelope after (PARAM_DELAY0 + PARAM_DELAY1 + PARAM_DELAY2) seconds. */
	PARAM_DELAY0, /**< The time in seconds for the envelope to reach PARAM_ENVELOPE_TARGET0. */
	PARAM_DELAY1, /**< The time in seconds for the envelope to reach PARAM_ENVELOPE_TARGET1. */
	PARAM_DELAY2, /**< The time in seconds for the envelope to reach PARAM_ENVELOPE_TARGET2. */
	PARAM_RELEASE_TIME, /**< After releasing the key, the time it takes for the operator to attenuate 60 dB. */
	
	PARAM_KEYBOARD_SCALING_MID_POINT, /**< The frequency which splits the keyboard into a "low" and "high" section.
                                           This frequency only depends on the note itself, not PARAM_FREQ_MOD, etc. */
	PARAM_KEYBOARD_SCALING_LOW_FACTOR, /**< Amplitude scaling factor pow(note_frequency / SCALING_MID_POINT, SCALING_LOW_FACTOR) if the key pressed
                                            is in the "low" section of the keyboard.
                                            Negative values will boost amplitide for lower frequency keys and attenuate amplitude for higher frequency keys.
                                            E.g. A value of -1.0 will add a 6 dB attenuation per octave. */
	PARAM_KEYBOARD_SCALING_HIGH_FACTOR, /**< Amplitude scaling factor pow(note_frequency / SCALING_MID_POINT, SCALING_HIGH_FACTOR) if the key pressed
                                             is in the "high" section of the keyboard.
                                             Negative values will boost amplitide for lower frequency keys and attenuate amplitude for higher frequency keys.
                                             E.g. A value of -1.0 will add a 6 dB attenuation per octave. */

	PARAM_VELOCITY_SENSITIVITY, /**< Controls velocity sensitivity. If 0.0, operator amplitude is independent of key velocity.
                                     If 1.0, the operator amplitude is fully dependent on key velocity.
                                     `factor = (1.0 - VELOCITY_SENSITIVITY) + VELOCITY_SENSITIVITY * velocity`.
                                     velocity` is normalized to [0, 1]. */
	PARAM_MOD_WHEEL_SENSITIVITY, /**< If 0.0, operator amplitude is independent of mod wheel state.
                                      If 1.0, operator amplitude is fully dependent on mod wheel state.
                                      `factor = (1.0 - MOD_WHEEL_SENSITIVITY) + MOD_WHEEL_SENSITIVITY * mod_wheel`.
                                      `mod_wheel` is normalized to [0, 1]. */

	PARAM_LFO_AMP_SENSITIVITY, /**< Specifies how much the LFO modulates amplitude.
                                    Modulation factor is: 1.0 + lfo_value * LFO_AMP_SENSITIVITY.
                                    lfo_value has a range of [-1, 1]. */
	PARAM_LFO_FREQ_MOD_DEPTH,  /**< Specifies how much the LFO modulates frequency.
                                    Modulation factor is: 1.0 + lfo_value * LFO_FREQ_MOD_DEPTH.
                                    lfo_value has a range of [-1, 1]. */

	PARAM_ENABLE,              /**< Enable operator if value > 0.5, otherwise, disable. */
	
	PARAM_CARRIERS,            /**< Set carrier mixing factor. If > 0.0, the operator will generate audio that is mixed into the final output. */
	PARAM_MOD_TO_CARRIERS0,    /**< Sets how much the operator will modulate carrier `N`. Use `PARAM_MOD_TO_CARRIERS0 + N` to specify which operator is the modulator target. */
	
	PARAM_END = PARAM_MOD_TO_CARRIERS0 + SYNTH_OPERATORS, /**< The number of parameters available. */
	PARAM_ENSURE_INT = INT_MAX /**< Ensure the enum is sizeof(int). */
};

// Parameters which are global to the entire synth.
enum GlobalParameter {
	GLOBAL_PARAM_VOLUME = 0, /**< Overall volume of the synth. */
	GLOBAL_PARAM_LFO_FREQ, /**< LFO frequency in Hz. */
	
	GLOBAL_PARAM_END, /**< The number of global parameters available. */
	GLOBAL_PARAM_ENSURE_INT = INT_MAX /**< Ensure the enum is sizeof(int). */
};

// Generic status code for certain functions.
typedef enum {
	STATUS_OK = 0, /**< Operation completed successfully. */
	STATUS_BUSY, /**< Operation could not complete due to insufficient resources at the moment. */
	
	STATUS_BUFFER_TOO_SMALL, /**< Provided buffer is too small. */
	STATUS_NO_NUL_TERMINATE, /**< Metadata string was not properly NUL-terminated. */
	STATUS_INVALID_FORMAT,   /**< Provided buffer does not adhere to specified format. */
	
	STATUS_MESSAGE_UNKNOWN,  /**< Provided MIDI message is unknown. */
	
	STATUS_ENSURE_INT = INT_MAX /**< Ensure the enum is sizeof(int). */
} Status;


struct SingleVoiceParameters {
	float amp;
	float pan;
	float freq_mod;
	float freq_offset;
	
	float envelope_target[3];
	float envelope_delay[3];
	float envelope_release_time;
	
	float keyboard_scaling_mid_point;
	float keyboard_scaling_low_factor;
	float keyboard_scaling_high_factor;
	
	float velocity_sensitivity;
	float mod_sensitivity;
	
	float lfo_amp_depth;
	float lfo_freq_mod_depth;
	
	float enable;
	
	float carriers;
	float mod_to_carriers[SYNTH_OPERATORS];
};

struct VoiceParameters {
	SingleVoiceParameters voices[SYNTH_OPERATORS];
	
};

struct GlobalParameters {
	float volume;
	float lfo_freq;
};

enum VoiceState {
	VOICE_INACTIVE = 0,
	VOICE_RUNNING,
	VOICE_SUSTAINED,
	VOICE_RELEASED
};

struct SynthParamData {
	const char *name;
	float minimum;
	float maximum;
	float default_value;
	bool logarithmic;
};

struct VoiceOp {
	float env;
	float read_mod;
	float target_env_step;
	float step_rate;
	float lfo_freq_mod;
	float pan_amp[2];
	
	// Using when updating envelope (every N sample).
	float falloff;
	float end_time;
	float target_env;
	
	float release_time;
	float target[4];
	float time[4];
	float lerp[3];
	
	float amp;
	float wheel_amp;
	float lfo_amp;
	
};

struct Voice {
	enum VoiceState state;
	byte note;
	byte enable;
	byte dead;
	
	float base_freq;
	float env_speed;
	float pos;
	float speed;
	
	float lfo_step;
	float lfo_phase;
	int count;
	
	// Used in ProcessFrames(). Should be local in cache.
	ALIGNED_CACHE_PRE float phases[SYNTH_OPERATORS] ALIGNED_CACHE_POST;
	ALIGNED_CACHE_PRE VoiceOp  ops[SYNTH_OPERATORS] ALIGNED_CACHE_POST;
	
	
	
	void VoiceUpdateReadMod();
	void UpdateTargetEnvelope();
	void ReleaseVoice();
	bool UpdateActive();
	void SetLfoValue(const VoiceParameters& params, float value);
	
	static float PitchBendToRatio(uint16 bend);
	static float NoteToFrequency(byte note);
	
};


class FmSynth {
	float freq;
	float inv_freq;
	
	float bend;
	float wheel;
	bool sustained;
	
	ALIGNEDVAR(Voice voices[SYNTH_VOICES]);
	
public:
	ALIGNEDVAR(VoiceParameters params);
	ALIGNEDVAR(GlobalParameters global_params);
	
	
	void Init(float freq);
	void LoadTest();
	void Reset();
	void InitVoices();
	void SetParameter(int parameter, int operator_index, float value);
	float GetParameter(int parameter, int operator_index);
	float ConvertFromNormalizedParameter(int parameter, float value);
	float ConvertToNormalizedParameter(int parameter, float value);
	
	void SetGlobalParameter(int parameter, float value);
	float GetGlobalParameter(int parameter);
	float ConvertFromNormalizedGlobalParameter(int parameter, float value);
	float ConvertToNormalizedGlobalParameter(int parameter, float value);
	float ConvertFromNormalized(const SynthParamData& data, float value);
	float ConvertToNormalized(const SynthParamData& data, float value);
	
	struct PresetMetadata {
		String name;
		String author;
	};
	
	size_t GetPresetSize();
	
	Status SavePreset(const PresetMetadata& metadata, void *buffer, size_t size);
	Status LoadPreset(PresetMetadata& metadata, const void *buffer, size_t size);
	int Render(float* left, float* right, int samples, bool interleaved=false);
	int RenderInterleaved(float* f, int samples);
	
	Status NoteOn(byte note, byte velocity);
	void NoteOff(byte note);
	void SetSustain(bool enable);
	void SetModWheel(byte wheel);
	void SetPitchBend(uint16 value);
	void ReleaseAll();
	Status ParseMidi(const byte *midi_data);
	
	void SetDefaultGlobalParameters(GlobalParameters& params);
	void ProcessFrames(Voice& voice, float* oleft, float* oright, int samples, bool interleaved);
	
	void TriggerVoice(Voice& v, byte note, byte velocity);
	void ResetVoice(Voice& v, float volume, float velocity, float freq);
	void ResetEnvelope(Voice& v);
	
	void HandleEvent(const MidiIO::Event& e, int track_i=-1);
	void ChannelMidiControl(int channel, int num, int value);
	
	static void SetDefaultParameters(VoiceParameters& params);
	static float Oscillator(float phase);
	
private:
	Status LoadPreset(
			GlobalParameters& global_params,
			VoiceParameters& params,
			PresetMetadata& metadata,
			const void *buffer_, size_t size);
	        
	Status SavePreset(
			GlobalParameters& global_params,
			VoiceParameters& params,
			const PresetMetadata& metadata,
			void *buffer_, size_t size);
	
	void RenderVoice(Voice& voice, float *left, float *right, int samples, bool interleaved);
	
	uint32 PackFloat(float value);
	float UnpackFloat(uint32 value);
	void WriteU32(byte *buffer, uint32 value);
	uint32 ReadU32(const byte *buffer);
	
};






        
        
        
NAMESPACE_SOFTSYNTH_END

#endif
