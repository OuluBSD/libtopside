#ifndef _GuboCore_HandleTypes_h_
#define _GuboCore_HandleTypes_h_

#define SURFACE2D_EXCPLICIT_INITIALIZE_CLASS(x) \
	template class x <Ctx2D>;

#define CUBOID3D_EXCPLICIT_INITIALIZE_CLASS(x) \
	template class x <Ctx3D>;

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
	using Cmd = DrawCommand;
	using CmdDraw = ProgDraw;
	using CmdPainter = ProgPainter;
	using Button = Button2;
	using Unit = int;
	
	inline static Rect GetDefaultScopeDimensions() {return RectC(0,0,1280,720);}
	inline static Rect GetDefaultHandleDimensions(int o=0) {return RectC(o,o,320,240);}
	
	inline static Box BoxC(int x, int y, int w, int h) { return Rect(x, y, x + w, y + h); }
	inline static Box BoxC(const Point& tl, const Size& sz) { return Rect(tl.x, tl.y, tl.x + sz.cx, tl.y + sz.cy); }
	
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
	using Cmd = DrawCommand3;
	using CmdDraw = ProgDraw3;
	using CmdPainter = ProgPainter3;
	using Button = Button3;
	using Unit = float;
	
	inline static Cubf GetDefaultScopeDimensions() {return CubfC(0,0,0,1024.f,1024.f,1024.f);}
	inline static Cubf GetDefaultHandleDimensions(float o=0) {return CubfC(o,o,o,256.f,256.f,256.f);}
	
	inline static Box BoxC(float x, float y, float z, float w, float h, float d) { return Box(x, y, z, x + w, y + h, z + d); }
	inline static Box BoxC(const Point3f& tl, const Volf& sz) { return Box(tl.x, tl.y, tl.z, tl.x + sz.cx, tl.y + sz.cy, tl.z + sz.cz); }
	
};


NAMESPACE_GUBO_END

#endif
