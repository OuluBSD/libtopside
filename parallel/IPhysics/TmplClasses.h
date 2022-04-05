// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 0:00:44

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
	using CLASSNAME = PhysicsNodeT<Fys>;
	RTTI_DECL1(CLASSNAME, FysNode)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FysNode>(this);}
	
	
	
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

template <class Fys>
struct PhysicsObjectT : FysObject {
	using CLASSNAME = PhysicsObjectT<Fys>;
	RTTI_DECL1(CLASSNAME, FysObject)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FysObject>(this);}
	
	
	
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

template <class Fys>
struct PhysicsJointT : FysJoint {
	using CLASSNAME = PhysicsJointT<Fys>;
	RTTI_DECL1(CLASSNAME, FysJoint)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FysJoint>(this);}
	
	
	
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

template <class Fys>
struct PhysicsSpaceT : FysSpace {
	using CLASSNAME = PhysicsSpaceT<Fys>;
	RTTI_DECL1(CLASSNAME, FysSpace)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FysSpace>(this);}
	
	
	
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

template <class Fys>
struct PhysicsSystemT : FysSystem {
	using CLASSNAME = PhysicsSystemT<Fys>;
	RTTI_DECL1(CLASSNAME, FysSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<FysSystem>(this);}
	
	
	
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

#if 0
using TosNode = PhysicsNodeT<FysTos>;
using TosObject = PhysicsObjectT<FysTos>;
using TosJoint = PhysicsJointT<FysTos>;
using TosSpace = PhysicsSpaceT<FysTos>;
using TosSystem = PhysicsSystemT<FysTos>;
#endif

#if 0
using OdeNode = PhysicsNodeT<FysOde>;
using OdeObject = PhysicsObjectT<FysOde>;
using OdeJoint = PhysicsJointT<FysOde>;
using OdeSpace = PhysicsSpaceT<FysOde>;
using OdeSystem = PhysicsSystemT<FysOde>;
#endif


NAMESPACE_PARALLEL_END



#endif

