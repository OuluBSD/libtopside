// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IOperatingSystem_TmplClasses_h_
#define _IOperatingSystem_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Os> struct OperatingSystemMessageBusT;
template <class Os> struct OperatingSystemProcessManagerT;
template <class Os> struct OperatingSystemDesktopManagerT;


template <class Os>
struct OperatingSystemMessageBusT : OsMessageBus {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Os>
struct OperatingSystemProcessManagerT : OsProcessManager {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Os>
struct OperatingSystemDesktopManagerT : OsDesktopManager {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};



NAMESPACE_PARALLEL_END



#endif

