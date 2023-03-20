#ifndef _GuboCore_HandleTypes_h_
#define _GuboCore_HandleTypes_h_

#define SURFACE2D_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <Ctx2D>;

#define CUBOID3D_EXCPLICIT_INITIALIZE_CLASS(x) \
	template struct x <Ctx3D>;

#define HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	SURFACE2D_EXCPLICIT_INITIALIZE_CLASS(x) \
	CUBOID3D_EXCPLICIT_INITIALIZE_CLASS(x) \


NAMESPACE_GUBO_BEGIN


struct Ctx2D {
	using Container = Surface;
	using ContainerFrame = SurfaceFrame;
	using Event = CtrlEvent;
	using EventCollection = CtrlEventCollection;
	using Interaction = GeomInteraction2D;
	using TopContainer = TopSurface;
	using Sz = Size;
	using Pt = Point;
	using Box = Rect;
	using DrawT = Draw;
	using CmdDraw = ProgDraw;
	using CmdPainter = ProgPainter;
	using Button = Button2;
	
	inline static Rect GetDefaultScopeDimensions() {return RectC(0,0,1280,720);}
	inline static Rect GetDefaultHandleDimensions(int o=0) {return RectC(o,o,320,240);}
	
};


struct Ctx3D {
	using Container = Gubo;
	using ContainerFrame = GuboFrame;
	using Event = GeomEvent;
	using EventCollection = GeomEventCollection;
	using Interaction = GeomInteraction3D;
	using TopContainer = TopGubo;
	using Sz = Volf;
	using Pt = Point3f;
	using Box = Cubf;
	using DrawT = Draw3;
	using CmdDraw = ProgDraw3;
	using CmdPainter = ProgPainter3;
	using Button = Button3;
	
	inline static Cubf GetDefaultScopeDimensions() {return CubC(0,0,0,1024,1024,1024);}
	inline static Cubf GetDefaultHandleDimensions(int o=0) {return CubC(o,o,o,256,256,256);}
	
};


NAMESPACE_GUBO_END

#endif
