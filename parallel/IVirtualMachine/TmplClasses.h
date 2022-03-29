// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IVirtualMachine_TmplClasses_h_
#define _IVirtualMachine_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Vm> struct VirtualMachineVirtualMachineT;
template <class Vm> struct VirtualMachineThreadT;


template <class Vm>
struct VirtualMachineVirtualMachineT : VmVirtualMachine {
	
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
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

using TosVirtualMachine = VirtualMachineVirtualMachineT<VmTos>;
using TosThread = VirtualMachineThreadT<VmTos>;


NAMESPACE_PARALLEL_END



#endif

