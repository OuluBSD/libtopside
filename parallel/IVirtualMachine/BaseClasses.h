// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 12:22:22

#ifndef _IVirtualMachine_BaseClasses_h_
#define _IVirtualMachine_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct VmVirtualMachine : public Atom {
	RTTI_DECL1(VmVirtualMachine, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VmVirtualMachine() {}

};

struct VmThread : public Atom {
	RTTI_DECL1(VmThread, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VmThread() {}

};

NAMESPACE_PARALLEL_END



#endif

