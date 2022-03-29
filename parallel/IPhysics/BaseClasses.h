// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IPhysics_BaseClasses_h_
#define _IPhysics_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct FysNode : public Atom {
	RTTI_DECL1(FysNode, Atom)
	
	virtual ~FysNode() {}

};

struct FysObject : public Atom {
	RTTI_DECL1(FysObject, Atom)
	
	virtual ~FysObject() {}

};

struct FysJoint : public Atom {
	RTTI_DECL1(FysJoint, Atom)
	
	virtual ~FysJoint() {}

};

struct FysSpace : public Atom {
	RTTI_DECL1(FysSpace, Atom)
	
	virtual ~FysSpace() {}

};

struct FysSystem : public Atom {
	RTTI_DECL1(FysSystem, Atom)
	
	virtual ~FysSystem() {}

};

NAMESPACE_PARALLEL_END



#endif

