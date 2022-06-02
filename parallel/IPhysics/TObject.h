#ifndef _IPhysics_TObject_h_
#define _IPhysics_TObject_h_

NAMESPACE_PARALLEL_BEGIN


template <class Fys>
struct ObjectT : NodeT<Fys> {
	using Base = ObjectT<Fys>;
	using Node = NodeT<Fys>;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	using NativeGeom = typename Fys::NativeGeom;
	using NativeBody = typename Fys::NativeBody;
	using NativeMass = typename Fys::NativeMass;
	using NativeQuat = typename Fys::NativeQuat;
	using Space = typename Fys::Space;
	
	ModelLoader loader;
	bool model_err = false;
	
	NativeGeom geom;
	NativeBody body;
	NativeMass mass;
	NativeQuat orient;
	
	bool is_override_phys_geom = false;
	mat4 override_geom;
	mat4 model_geom = identity<mat4>();
	
public:
	RTTI_DECL1(ObjectT, Node)
	typedef ObjectT CLASSNAME;
	ObjectT();
	virtual ~ObjectT();
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Node>(this); vis % loader;}
	
	void OnAttach() override {Fys::CreateBody(this->GetNativeWorld(), body);}
	void OnDetach() override {DetachContent();}
	void Refresh() override;
	
	void AttachContent();
	void DetachContent();
	void RotateFromAxisAndAngle(double ax, double ay, double az, double angle) {Fys::SetBodyRotationAxisAngle(body, ax, ay, az, angle);}
	vec3 GetBodyPosition() {return Fys::GetBodyPosition(body);}
	//void LoadModel(CpuDataState& state);
	//void LoadModel(OglDataState& state);
	bool LoadModel(GfxDataState& s) override;
	//bool LoadModel(ModelLoader& l, GfxDataObject& o) override;
	String ToString() const override {return Fys::Id() + "Object";}
	
	ObjectT& SetRotationX(double angle) {Fys::SetGeomRotationAxisAngle(geom, 1, 0, 0, angle); return *this;}
	ObjectT& SetRotationY(double angle) {Fys::SetGeomRotationAxisAngle(geom, 0, 1, 0, angle); return *this;}
	ObjectT& SetRotationZ(double angle) {Fys::SetGeomRotationAxisAngle(geom, 0, 0, 1, angle); return *this;}
	ObjectT& SetPosition(double x, double y, double z) {Fys::SetGeomPosition(geom, x, y, z); return *this;}
	ObjectT& SetGeomPosition(double x, double y, double z) {Fys::SetGeomPosition(geom, x, y, z); return *this;}
	ObjectT& SetGeomRotationIdentity() {Fys::ResetGeomRotation(geom); return *this;}
	ObjectT& SetOrientation(const vec3& axis, float angle) {Fys::SetQuatFromAxisAngle(orient, axis, angle); return *this;}
	
	ObjectT& Reset(double x, double y, double z) {
		Fys::SetBodyPosition(body, x, y, z);
		Fys::SetBodyQuaternion(body, identity<quat>());
		Fys::SetBodyLinearVelocity(body, vec3(0,0,0));
		Fys::SetBodyAngularVelocity(body, vec3(0,0,0));
		return *this;
	}
	
	Callback GetRefreshCallback() {return THISBACK(Refresh);}
};


NAMESPACE_PARALLEL_END

#endif
