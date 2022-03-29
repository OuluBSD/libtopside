// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IPhysics_TmplClasses_h_
#define _IPhysics_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Fys> struct PhysicsNodeT;
template <class Fys> struct PhysicsObjectT;
template <class Fys> struct PhysicsJointT;
template <class Fys> struct PhysicsSpaceT;
template <class Fys> struct PhysicsSystemT;


template <class Fys>
struct PhysicsNodeT : FysNode {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Fys>
struct PhysicsObjectT : FysObject {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Fys>
struct PhysicsJointT : FysJoint {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Fys>
struct PhysicsSpaceT : FysSpace {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Fys>
struct PhysicsSystemT : FysSystem {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

using TosNode = PhysicsNodeT<FysTos>;
using TosObject = PhysicsObjectT<FysTos>;
using TosJoint = PhysicsJointT<FysTos>;
using TosSpace = PhysicsSpaceT<FysTos>;
using TosSystem = PhysicsSystemT<FysTos>;
using OdeNode = PhysicsNodeT<FysOde>;
using OdeObject = PhysicsObjectT<FysOde>;
using OdeJoint = PhysicsJointT<FysOde>;
using OdeSpace = PhysicsSpaceT<FysOde>;
using OdeSystem = PhysicsSystemT<FysOde>;


NAMESPACE_PARALLEL_END



#endif

