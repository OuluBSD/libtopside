// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IFont_TmplClasses_h_
#define _IFont_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Fnt> struct FontFontT;


template <class Fnt>
struct FontFontT : FntFont {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};



NAMESPACE_PARALLEL_END



#endif

