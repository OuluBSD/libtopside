// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

#ifndef _IThree_TmplClasses_h_
#define _IThree_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Thr> struct ThreeModelT;


template <class Thr>
struct ThreeModelT : ThrModel {
	using CLASSNAME = ThreeModelT<Thr>;
	RTTI_DECL1(CLASSNAME, ThrModel)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ThrModel>(this);}
	
	typename Thr::NativeModel model;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Thr::Model_Initialize(model, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Thr::Model_Uninitialize(model);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Thr::Model_ProcessPacket(model, v))
			return false;
		return true;
	}

	bool CreateModel() {
		return Thr::Model_CreateModel(this->model);
	}
	
	void ClearModel() {
		Thr::Model_ClearModel(this->model);
	}
	
	
};


NAMESPACE_PARALLEL_END



#endif

