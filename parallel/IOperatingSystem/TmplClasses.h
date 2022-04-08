// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.8 19:22:44

#ifndef _IOperatingSystem_TmplClasses_h_
#define _IOperatingSystem_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Os> struct OperatingSystemMessageBusT;
template <class Os> struct OperatingSystemProcessManagerT;
template <class Os> struct OperatingSystemDesktopManagerT;


template <class Os>
struct OperatingSystemMessageBusT : OsMessageBus {
	using CLASSNAME = OperatingSystemMessageBusT<Os>;
	RTTI_DECL1(CLASSNAME, OsMessageBus)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OsMessageBus>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Os>
struct OperatingSystemProcessManagerT : OsProcessManager {
	using CLASSNAME = OperatingSystemProcessManagerT<Os>;
	RTTI_DECL1(CLASSNAME, OsProcessManager)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OsProcessManager>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Os>
struct OperatingSystemDesktopManagerT : OsDesktopManager {
	using CLASSNAME = OperatingSystemDesktopManagerT<Os>;
	RTTI_DECL1(CLASSNAME, OsDesktopManager)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OsDesktopManager>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

