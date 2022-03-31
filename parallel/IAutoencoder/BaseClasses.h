// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IAutoencoder_BaseClasses_h_
#define _IAutoencoder_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct AencSystem : public Atom {
	RTTI_DECL1(AencSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~AencSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

