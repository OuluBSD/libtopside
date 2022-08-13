#include "SoftInstru.h"


NAMESPACE_SOFTINSTRU_BEGIN


#define TSFR(FIELD) (*stream.i.*stream.read)(stream.data, &FIELD, sizeof(FIELD));

void HydraPresetHeader::Read(Stream& stream) {
	TSFR(preset_name) TSFR(preset) TSFR(bank) TSFR(preset_bag_idx) TSFR(library) TSFR(genre) TSFR(morphology)
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
	TSFR(name) TSFR(bag_idx)
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
	TSFR(name) TSFR(start) TSFR(end) TSFR(start_loop) TSFR(end_loop) TSFR(sample_rate) TSFR(orig_pitch) TSFR(pitch_correction) TSFR(sample_link) TSFR(sample_type)
}

#undef TSFR


NAMESPACE_SOFTINSTRU_END
