// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 0:00:44

#ifndef _IMidi_BaseClasses_h_
#define _IMidi_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct MidMidiSinkDevice : public Atom {
	RTTI_DECL1(MidMidiSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~MidMidiSinkDevice() {}

};

struct MidMidiSourceDevice : public Atom {
	RTTI_DECL1(MidMidiSourceDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~MidMidiSourceDevice() {}

};

NAMESPACE_PARALLEL_END



#endif

