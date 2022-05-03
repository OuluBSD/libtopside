// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IFont_TmplClasses_h_
#define _IFont_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Fnt> struct FontFontT;


template <class Fnt>
struct FontFontT : FntFont {
	using CLASSNAME = FontFontT<Fnt>;
	RTTI_DECL1(CLASSNAME, FntFont)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FntFont>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

