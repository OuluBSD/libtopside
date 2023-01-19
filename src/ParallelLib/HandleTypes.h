#ifndef _ParallelLib_HandleTypes_h_
#define _ParallelLib_HandleTypes_h_

#define SURFACE2D_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <Ctx2D>;

#define CUBOID3D_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <Ctx3D>;

#define HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	SURFACE2D_EXCPLICIT_INITIALIZE_CLASS(x) \
	CUBOID3D_EXCPLICIT_INITIALIZE_CLASS(x) \


NAMESPACE_PARALLEL_BEGIN


struct Ctx2D {
	using Space = Workspace2D;
	using Interface = Absolute2DInterface;
	using InterfaceProxy = Absolute2DProxy;
	using Container = Ctrl;
	using ContainerFrame = CtrlFrame;
	using Event = CtrlEvent;
	using Interaction = GeomInteraction2D;
	using TopContainer = TopWindow;
	using Sz = Size;
	using Box = Rect;
	
	inline static Rect GetDefaultScopeDimensions() {return Rect(0,0,1280,720);}
	inline static Rect GetDefaultHandleDimensions(int o=0) {return Rect(o,o,640+o,480+o);}
	
};


struct Ctx3D {
	using Space = Workspace3D;
	using Interface = Absolute3DInterface;
	using InterfaceProxy = Absolute3DProxy;
	using Container = Gubo;
	using ContainerFrame = GuboFrame;
	using Event = GeomEvent;
	using Interaction = GeomInteraction3D;
	using TopContainer = TopGubo;
	using Sz = Volf;
	using Box = Cubf;
	
	inline static Cubf GetDefaultScopeDimensions() {return Cubf(0,0,0,1024,1024,1024);}
	inline static Cubf GetDefaultHandleDimensions(int o=0) {return Cubf(o,o,o,256+o,256+o,256+o);}
	
};


NAMESPACE_PARALLEL_END

#endif
