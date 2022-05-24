// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ISynth_BaseClasses_h_
#define _ISynth_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct SynInstrument : public Atom {
	RTTI_DECL1(SynInstrument, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~SynInstrument() {}

};

NAMESPACE_PARALLEL_END



#endif

