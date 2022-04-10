// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ICrypt_BaseClasses_h_
#define _ICrypt_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct CryCrypt : public Atom {
	RTTI_DECL1(CryCrypt, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~CryCrypt() {}

};

NAMESPACE_PARALLEL_END



#endif

