// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IMidiHw_BaseClasses_h_
#define _IMidiHw_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct MidSource : public Atom {
	RTTI_DECL1(MidSource, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~MidSource() {}

};

NAMESPACE_PARALLEL_END



#endif

