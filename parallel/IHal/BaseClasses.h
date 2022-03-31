// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IHal_BaseClasses_h_
#define _IHal_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct HalAudioSinkDevice : public Atom {
	RTTI_DECL1(HalAudioSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalAudioSinkDevice() {}

};

struct HalContextBase : public Atom {
	RTTI_DECL1(HalContextBase, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalContextBase() {}

};

NAMESPACE_PARALLEL_END



#endif

