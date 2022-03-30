// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

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

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

