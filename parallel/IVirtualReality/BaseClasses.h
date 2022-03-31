// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IVirtualReality_BaseClasses_h_
#define _IVirtualReality_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct VrMotionController : public Atom {
	RTTI_DECL1(VrMotionController, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrMotionController() {}

};

struct VrMotionControllerSystem : public Atom {
	RTTI_DECL1(VrMotionControllerSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrMotionControllerSystem() {}

};

struct VrAppView : public Atom {
	RTTI_DECL1(VrAppView, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrAppView() {}

};

struct VrCameraResources : public Atom {
	RTTI_DECL1(VrCameraResources, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrCameraResources() {}

};

struct VrControllerModelCache : public Atom {
	RTTI_DECL1(VrControllerModelCache, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrControllerModelCache() {}

};

struct VrDeviceResources : public Atom {
	RTTI_DECL1(VrDeviceResources, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrDeviceResources() {}

};

struct VrHolographicRenderer : public Atom {
	RTTI_DECL1(VrHolographicRenderer, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrHolographicRenderer() {}

};

struct VrHolographicScene : public Atom {
	RTTI_DECL1(VrHolographicScene, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrHolographicScene() {}

};

struct VrSpatialInteractionSystem : public Atom {
	RTTI_DECL1(VrSpatialInteractionSystem, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrSpatialInteractionSystem() {}

};

struct VrRenderer : public Atom {
	RTTI_DECL1(VrRenderer, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~VrRenderer() {}

};

NAMESPACE_PARALLEL_END



#endif

