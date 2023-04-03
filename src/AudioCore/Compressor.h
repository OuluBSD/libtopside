#ifndef _AudioCore_Compressor_h_
#define _AudioCore_Compressor_h_


NAMESPACE_AUDIO_BEGIN


struct CompressorParameter {
	float freq;
    float gain_db;		// gain_db is the pre-gain or input-gain level (dB)
    float ratio;		// ratio is the compression ratio
    float th_db;		// th_db is the threshold level (dB)
    float w_db;			// w_db is the knee-width (dB)
    float w_db_x2_inv;
    float k1_db;
    float k2_db;
    float att;			// att is the attack time (ms)
    float rlt;			// rlt is the release time (ms)
    float tau_attack;
    float tau_release;
    float clip_db;		// clip_db is the clip level (dB)
    float alpha_attack;
    float alpha_release;
    float makeup_db;	// makeup_db is the makeup gain level (dB)
    bool is_auto_makeup;
    
	void SetDefault(float freq);
	void Init(float freq);
};




class Compressor : public Effect {
public:
	Compressor();
	void Clear() override;
	float Tick( float input, int channel ) override;
	float Tick2( float input1, float input2, int channel ) override;
	void LoadState(const ArrayMap<String, Object>& state) override;
	
protected:
    CompressorParameter param;
    float sample;
    int sign;
    
	
	void Init();
	float PreGainDb();
	void SignDetection();
	void Limit();
	float GainStageDb(float sample_db);
	float BallisticsStageDb(float gain_compstage_db);
	float AutoMakeupStageDb();
	
};


float LinearToDb(float linear_value);
float DbToLinear(float db_value);


NAMESPACE_AUDIO_END


#endif
