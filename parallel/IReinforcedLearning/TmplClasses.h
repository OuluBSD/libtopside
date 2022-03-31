// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

#ifndef _IReinforcedLearning_TmplClasses_h_
#define _IReinforcedLearning_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Rl> struct ReinforcedLearningSystemT;


template <class Rl>
struct ReinforcedLearningSystemT : RlSystem {
	using CLASSNAME = ReinforcedLearningSystemT<Rl>;
	RTTI_DECL1(CLASSNAME, RlSystem)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<RlSystem>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

