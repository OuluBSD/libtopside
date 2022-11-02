#ifndef _SoftInstru_Instrument_h_
#define _SoftInstru_Instrument_h_

NAMESPACE_SOFTINSTRU_BEGIN


struct Hydra;


struct Instrument
{
	Array<Preset> presets;
	Vector<float> font_samples;
	Vector<Voice> voices;
	Channels channels;

	//int preset_i;
	//int voice_i;
	int max_voice_count;
	unsigned int voice_play_idx;

	enum OutputMode output_mode;
	float out_sample_rate;
	float global_gain_db;
	mutable int* ref_count;
	
	
	
private:
	void SetupChannelVoice(Voice& v);
	void ApplyChannelPitch(int channel, Channel& c);
	int LoadPresets(Hydra& hydra, unsigned int font_sample_count);
	Channel& InitChannel(int channel);
	
public:

    // Directly load a SoundFont from a .sf2 file path
    bool LoadFilename(String filename);

    // Load a SoundFont from a block of memory
    bool LoadMemory(const void* buffer, int size);

    // Generic SoundFont loading method using the stream structure above
    bool Load(Stream& stream);

    // Copy a Instrument instance from an existing one, use close to close it as well.
    // All copied Instrument instances and their original instance are linked, and share the underlying soundfont.
    // This allows loading a soundfont only once, but using it for multiple independent playbacks.
    // (This function isn't thread-safe without locking.)
    void Copy(const Instrument& i);

    // Free the memory related to this Instrument instance
    //void Close();

    // Stop all playing notes immediately and reset all channel parameters
    void Reset();

    // Returns the preset index from a bank and preset number, or -1 if it does not exist in the loaded SoundFont
    int GetPresetIndex(int bank, int preset_number);

    // Returns the number of presets in the loaded SoundFont
    int GetPresetCount();

    // Returns the name of a preset index >= 0 and < GetPresetCount()
    String GetPresetName(int preset_index);

    // Returns the name of a preset by bank and preset number
    String GetBankPresetName(int bank, int preset_number);



    // Thread safety:
    //
    // 1. Rendering / voices:
    //
    // Your audio output which calls the render* functions will most likely
    // run on a different thread than where the playback note* functions
    // are called. In which case some sort of concurrency control like a
    // mutex needs to be used so they are not called at the same time.
    // Alternatively, you can pre-allocate a maximum number of voices that can
    // play simultaneously by calling SetMaxVoices after loading.
    // That way memory re-allocation will not happen during NoteOn and
    // TSF should become mostly thread safe.
    // There is a theoretical chance that ending notes would negatively influence
    // a voice that is rendering at the time but it is hard to say.
    // Also be aware, this has not been tested much.
    //
    // 2. Channels:
    //
    // Calls to channel_set_... functions may allocate new channels
    // if no channel with that number was previously used. Make sure to
    // create all channels at the beginning as required if you call render*
    // from a different thread.

    // Setup the parameters for the voice render methods
    //   output_mode: if mono or stereo and how stereo channel data is ordered
    //   samplerate: the number of samples per second (output frequency)
    //   global_gain_db: volume gain in decibels (>0 means higher, <0 means lower)
    void SetOutput(enum OutputMode output_mode, int samplerate, float global_gain_db);

    // Set the global gain as a volume factor
    //   global_gain: the desired volume where 1.0 is 100%
    void SetVolume(float global_gain);

    // Set the maximum number of voices to play simultaneously
    // Depending on the soundfond, one note can cause many new voices to be started,
    // so don't keep this number too low or otherwise sounds may not play.
    //   max_voices: maximum number to pre-allocate and set the limit to
    void SetMaxVoices(int max_voices);

    // Start playing a note
    //   preset_index: preset index >= 0 and < GetPresetCount()
    //   key: note value between 0 and 127 (60 being middle C)
    //   vel: velocity as a float between 0.0 (equal to note off) and 1.0 (full)
    //   bank: instrument bank number (alternative to preset_index)
    //   preset_number: preset number (alternative to preset_index)
    //   (NoteOn returns 0 if the allocation of a new voice failed, otherwise 1)
    //   (BankNoteOn returns 0 if preset does not exist or allocation failed, otherwise 1)
    int NoteOn(int preset_index, int key, float vel);
    int BankNoteOn(int bank, int preset_number, int key, float vel);

    // Stop playing a note
    //   (BankNoteOff returns 0 if preset does not exist, otherwise 1)
    void NoteOff(int preset_index, int key);
    int  BankNoteOff(int bank, int preset_number, int key);

    // Stop playing all notes (end with sustain and release)
    void NoteOffAll();

    // Returns the number of active voices
    int ActiveVoiceCount();

    // Render output samples into a buffer
    // You can either render as signed 16-bit values (RenderShort) or
    // as 32-bit float values (RenderFloat)
    //   buffer: target buffer of size samples * output_channels * sizeof(type)
    //   samples: number of samples to render
    //   flag_mixing: if 0 clear the buffer first, otherwise mix into existing data
    void RenderShort(short* buffer, int samples, int flag_mixing);
    void RenderFloat(float* buffer, int samples, int flag_mixing);

    // Higher level channel based functions, set up channel parameters
    //   channel: channel number
    //   preset_index: preset index >= 0 and < GetPresetCount()
    //   preset_number: preset number (alternative to preset_index)
    //   flag_mididrums: 0 for normal channels, otherwise apply MIDI drum channel rules
    //   bank: instrument bank number (alternative to preset_index)
    //   pan: stereo panning value from 0.0 (left) to 1.0 (right) (default 0.5 center)
    //   volume: linear volume scale factor (default 1.0 full)
    //   pitch_wheel: pitch wheel position 0 to 16383 (default 8192 unpitched)
    //   pitch_range: range of the pitch wheel in semitones (default 2.0, total +/- 2 semitones)
    //   tuning: tuning of all playing voices in semitones (default 0.0, standard (A440) tuning)
    //   (set_preset_number and set_bank_preset return 0 if preset does not exist, otherwise 1)
    void SetChannelPresetIndex(int channel, int preset_index);
    bool SetChannelPresetNumber(int channel, int preset_number, int flag_mididrums);
    void SetChannelBank(int channel, int bank);
    void SetChannelBankPreset(int channel, int bank, int preset_number);
    void SetChannelPan(int channel, float pan);
    void SetChannelVolume(int channel, float volume);
    void SetChannelPitchWheel(int channel, int pitch_wheel);
    void SetChannelPitchRange(int channel, float pitch_range);
    void SetChannelTuning(int channel, float tuning);

    // Start or stop playing notes on a channel (needs channel preset to be set)
    //   channel: channel number
    //   key: note value between 0 and 127 (60 being middle C)
    //   vel: velocity as a float between 0.0 (equal to note off) and 1.0 (full)
    //   (NoteOnChannel returns 0 on allocation failure of new voice, otherwise 1)
    int NoteOnChannel(int channel, int key, float vel);
    void NoteOffChannel(int channel, int key);
    void NoteOffChannelAll(int channel); //end with sustain and release
    void SoundsOffAllChannel(int channel); //end immediately

    // Apply a MIDI control change to the channel (not all controllers are supported!)
    //    (ChannelMidiControl returns 0 on allocation failure of new channel, otherwise 1)
    int ChannelMidiControl(int channel, int controller, int control_value);

    // Get current values set on the channels
    int GetChannelPresetIndex(int channel);
    int GetChannelPresetBank(int channel);
    int GetChannelPresetNumber(int channel);
    float GetChannelPan(int channel);
    float GetChannelVolume(int channel);
    int GetChannelPitchWheel(int channel);
    float GetChannelPitchRange(int channel);
    float GetChannelTuning(int channel);
    
	void End(Voice& v);
	void EndQuick(Voice& v);
    
public:
	
	
	struct StreamMemory {
		const void* buffer;
		uint32 total;
		uint32 pos;
	};

	int StreamReadStdio(FILE* f, void* ptr, unsigned int size);
	int StreamSkipStdio(FILE* f, unsigned int count);
	int StreamMemory_read(StreamMemory* mp, void* ptr, unsigned int size);
	int StreamMemory_skip(StreamMemory* mp, unsigned int count);
	
	void Render(Voice& v, float* output_buffer, int sample_count);
	
	void HandleEvent(const MidiIO::Event& ev, int track_i=-1);
	
};









NAMESPACE_SOFTINSTRU_END

#endif
