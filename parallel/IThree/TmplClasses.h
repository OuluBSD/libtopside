// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

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

	bool PostInitialize() override {
		if (!Thr::Model_PostInitialize(model, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Thr::Model_Start(model, *this);
	}

	void Stop() override {
		Thr::Model_Stop(model, *this);
	}

	void Uninitialize() override {
		Thr::Model_Uninitialize(model, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Thr::Model_Send(model, *this, cfg, out, src_ch))
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

