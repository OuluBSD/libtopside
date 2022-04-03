// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 22:44:00

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

