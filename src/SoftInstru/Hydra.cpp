#include "SoftInstru.h"


NAMESPACE_SOFTINSTRU_BEGIN


#define TSFR(FIELD) (*stream.i.*stream.read)(stream.data, &FIELD, sizeof(FIELD));

void HydraPresetHeader::Read(Stream& stream) {
	char cname[20];
	TSFR(cname) TSFR(preset) TSFR(bank) TSFR(preset_bag_idx) TSFR(library) TSFR(genre) TSFR(morphology)
	name.Set(cname, (int)strnlen(cname, 20));
}

void HydraPresetBag::Read(Stream& stream) {
	TSFR(gen_idx) TSFR(mod_idx)
}


void HydraPresetMod::Read(Stream& stream) {
	TSFR(mod_src_op) TSFR(mod_dst_op) TSFR(mod_amount) TSFR(mod_amount_src_op) TSFR(mod_trans_op)
}

void HydraPresetGen::Read(Stream& stream) {
	TSFR(gen_op) TSFR(gen_amount)
}

void HydraInstrument::Read(Stream& stream) {
	char cname[20];
	TSFR(cname) TSFR(bag_idx)
	name.Set(cname, (int)strnlen(cname, 20));
}

void HydraInstrumentBag::Read(Stream& stream) {
	TSFR(gen_idx) TSFR(mod_idx)
}

void HydraInstrumentMod::Read(Stream& stream) {
	TSFR(mod_src_op) TSFR(mod_dst_op) TSFR(mod_amount) TSFR(mod_amount_src_op) TSFR(mod_trans_op)
}

void HydraInstrumentGen::Read(Stream& stream) {
	TSFR(gen_op) TSFR(gen_amount)
}

void HydraSampleHeader::Read(Stream& stream) {
	char cname[20];
	TSFR(cname) TSFR(start) TSFR(end) TSFR(start_loop) TSFR(end_loop) TSFR(sample_rate) TSFR(orig_pitch) TSFR(pitch_correction) TSFR(sample_link) TSFR(sample_type)
	name.Set(cname, (int)strnlen(cname, 20));
}

#undef TSFR


NAMESPACE_SOFTINSTRU_END
