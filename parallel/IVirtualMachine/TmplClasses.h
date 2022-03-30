// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

#ifndef _IVirtualMachine_TmplClasses_h_
#define _IVirtualMachine_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Vm> struct VirtualMachineVirtualMachineT;
template <class Vm> struct VirtualMachineThreadT;


template <class Vm>
struct VirtualMachineVirtualMachineT : VmVirtualMachine {
	using CLASSNAME = VirtualMachineVirtualMachineT<Vm>;
	RTTI_DECL1(CLASSNAME, VmVirtualMachine)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VmVirtualMachine>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Vm>
struct VirtualMachineThreadT : VmThread {
	using CLASSNAME = VirtualMachineThreadT<Vm>;
	RTTI_DECL1(CLASSNAME, VmThread)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VmThread>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

#if 0
using TosVirtualMachine = VirtualMachineVirtualMachineT<VmTos>;
using TosThread = VirtualMachineThreadT<VmTos>;
#endif


NAMESPACE_PARALLEL_END



#endif

