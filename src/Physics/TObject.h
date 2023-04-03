#ifndef _Physics_TObject_h_
#define _Physics_TObject_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Fys>
struct ObjectT : NodeT<Fys> {
	using Node = NodeT<Fys>;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	using NativeGeom = typename Fys::NativeGeom;
	using NativeBody = typename Fys::NativeBody;
	using NativeMass = typename Fys::NativeMass;
	using NativeQuat = typename Fys::NativeQuat;
	
	ModelLoader loader;
	GfxDataObject* fb_obj = 0;
	bool model_err = false;
	
	NativeGeom geom = 0;
	NativeBody body = 0;
	NativeMass mass;
	NativeQuat orient;
	mat4 model_geom = Identity<mat4>();
	
public:
	RTTI_DECL1(ObjectT, Node)
	typedef ObjectT CLASSNAME;
	ObjectT() {orient = Fys::GetDefaultOrientation();}
	virtual ~ObjectT() {}
	
	virtual void LoadModel(GfxDataState& s) override {TODO}
	
	void OnAttach() override {body = Fys::CreateBody(this->GetNativeWorld());}
	void OnDetach() override {DetachContent();}
	virtual void Refresh() override {TODO}
	
	void AttachContent() {TODO}
	void DetachContent() {TODO}
	void SetPosition(float x, float y, float z) {Fys::SetBodyPosition(body, x, y, z);}
	void SetGeomPosition(float x, float y, float z) {Fys::SetGeomPosition(geom, x, y, z);}
	void SetGeomRotationIdentity() {Fys::ResetGeomRotation(geom);}
	void RotateFromAxisAndAngle(float ax, float ay, float az, float angle) {Fys::SetGeomRotationAxisAngle(geom, ax, ay, az, angle);}
	//vec3 GetBodyPosition() {return Gfx::GetBodyPosition(body);}
	//void LoadModel(CpuDataState& state);
	//void LoadModel(OglDataState& state);
	
	Callback GetRefreshCallback() {return THISBACK(Refresh);}
};


NAMESPACE_TOPSIDE_END

#endif
