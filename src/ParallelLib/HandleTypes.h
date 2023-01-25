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
	using Pt = Point;
	using Box = Rect;
	using DrawT = Draw;
	using CmdDraw = ProgDraw;
	using CmdPainter = ProgPainter;
	
	inline static Rect GetDefaultScopeDimensions() {return RectC(0,0,1280,720);}
	inline static Rect GetDefaultHandleDimensions(int o=0) {return RectC(o,o,320,240);}
	
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
	using Pt = Point3f;
	using Box = Cubf;
	using DrawT = Draw3;
	using CmdDraw = ModelDraw;
	using CmdPainter = ModelPainter;
	
	inline static Cubf GetDefaultScopeDimensions() {return CubC(0,0,0,1024,1024,1024);}
	inline static Cubf GetDefaultHandleDimensions(int o=0) {return CubC(o,o,o,256,256,256);}
	
};


NAMESPACE_PARALLEL_END

#endif
