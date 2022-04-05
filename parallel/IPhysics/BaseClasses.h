// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 0:00:44

#ifndef _IPhysics_BaseClasses_h_
#define _IPhysics_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct FysNode : public Atom {
	RTTI_DECL1(FysNode, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FysNode() {}

};

struct FysObject : public Atom {
	RTTI_DECL1(FysObject, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FysObject() {}

};

struct FysJoint : public Atom {
	RTTI_DECL1(FysJoint, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FysJoint() {}

};

struct FysSpace : public Atom {
	RTTI_DECL1(FysSpace, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FysSpace() {}

};

struct FysSystem : public Atom {
	RTTI_DECL1(FysSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~FysSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

