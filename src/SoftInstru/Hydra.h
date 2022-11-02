#ifndef _SoftInstru_Hydra_h_
#define _SoftInstru_Hydra_h_

NAMESPACE_SOFTINSTRU_BEGIN


union HydraGenAmount {
	struct {
		uint8 lo, hi;
	} range;
	
	int16 short_amount;
	uint16 word_amount;
};

struct HydraPresetHeader {
	String name;
	uint16 preset;
	uint16 bank;
	uint16 preset_bag_idx;
	uint32 library;
	uint32 genre;
	uint32 morphology;
	
	void Read(Stream& stream);
};

struct HydraPresetBag {
	uint16 gen_idx;
	uint16 mod_idx;

	void Read(Stream& stream);
};

struct HydraPresetMod {
	uint16 mod_src_op;
	uint16 mod_dst_op;
	int16 mod_amount;
	uint16 mod_amount_src_op;
	uint16 mod_trans_op;
	
	void Read(Stream& stream);
};

struct HydraPresetGen {
	uint16 gen_op;
	union HydraGenAmount gen_amount;
	
	void Read(Stream& stream);
};

struct HydraInstrument {
	String name;
	uint16 bag_idx;
	
	void Read(Stream& stream);
};

struct HydraInstrumentBag {
	uint16 gen_idx;
	uint16 mod_idx;
	
	void Read(Stream& stream);
};

struct HydraInstrumentMod {
	uint16 mod_src_op;
	uint16 mod_dst_op;
	int16 mod_amount;
	uint16 mod_amount_src_op;
	uint16 mod_trans_op;
	
	void Read(Stream& stream);
};

struct HydraInstrumentGen {
	uint16 gen_op;
	union HydraGenAmount gen_amount;
	
	void Read(Stream& stream);
};

struct HydraSampleHeader {
	String name;
	uint32 start;
	uint32 end;
	uint32 start_loop;
	uint32 end_loop;
	uint32 sample_rate;
	uint8 orig_pitch;
	int8 pitch_correction;
	uint16 sample_link;
	uint16 sample_type;
	
	void Read(Stream& stream);
};


struct Hydra
{
	Array<HydraPresetHeader> preset_headers;
	Array<HydraPresetBag> preset_bags;
	Array<HydraPresetMod> preset_mods;
	Array<HydraPresetGen> preset_gens;
	Array<HydraInstrument> instruments;
	Array<HydraInstrumentBag> instrument_bags;
	Array<HydraInstrumentMod> instrument_mods;
	Array<HydraInstrumentGen> instrument_gens;
	Array<HydraSampleHeader> sample_headers;
	/*
	int preset_header_count;
	int preset_bag_count;
	int preset_mod_count;
	int preset_gen_count;
	int instrument_count;
	int instrument_bag_count;
	int instrument_mod_count;
	int instrument_gen_count;
	int sample_header_count;
	*/
	
	int LoadPresets(unsigned int font_sample_count);
};



NAMESPACE_SOFTINSTRU_END

#endif
