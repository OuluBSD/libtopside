// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IThree_BaseClasses_h_
#define _IThree_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct ThrModel : public Atom {
	RTTI_DECL1(ThrModel, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ThrModel() {}

};

NAMESPACE_PARALLEL_END



#endif

