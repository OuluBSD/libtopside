#ifndef _Local_Workspace_h_
#define _Local_Workspace_h_

NAMESPACE_TOPSIDE_BEGIN


class Workspace2D : public GeomInteraction2D {
	
	
public:
	RTTI_DECL1(Workspace2D, GeomInteraction2D)
	virtual ~Workspace2D() {}
	
	virtual bool Init() = 0;
	virtual void AddInterface(Absolute2DProxy&) = 0;
	virtual bool Poll(CtrlEvent& e) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
	virtual bool ProcessCloseQueue() = 0;
	
};


class Workspace3D : public GeomInteraction3D {
	
	
public:
	RTTI_DECL1(Workspace3D, GeomInteraction3D)
	virtual ~Workspace3D() {}
	
	virtual bool Init() = 0;
	virtual void AddInterface(Absolute3DProxy&) = 0;
	virtual bool Poll(GeomEvent& e) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
	virtual bool ProcessCloseQueue() = 0;
	
};


NAMESPACE_TOPSIDE_END

#endif
