#ifndef _ParallelLib_HandleTypes_h_
#define _ParallelLib_HandleTypes_h_


NAMESPACE_PARALLEL_BEGIN


#define UPPCTRL2D_EXCPLICIT_INITIALIZE_CLASS(x) \
	template class x <CtxUpp2D>;

#if IS_UPP_CORE
#define PLIB_TYPE_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	UPPCTRL2D_EXCPLICIT_INITIALIZE_CLASS(x)
#endif

#if IS_TS_CORE
#define PLIB_TYPE_EXCPLICIT_INITIALIZE_CLASS(x)
#endif




#if IS_UPP_CORE
struct CtxUpp2D {
	using Container = Ctrl;
	using ContainerFrame = CtrlFrame;
	using Event = CtrlEvent;
	using EventCollection = CtrlEventCollection;
	using TopContainer = TopWindow;
	using Sz = Size;
	using Pt = Point;
	using Box = Rect;
	using DrawT = Draw;
	using CmdDraw = ProgDraw;
	using CmdPainter = ProgPainter;
	using Desktop = UPP::StaticRect;
	using Button = UPP::Button;

	inline static Rect GetDefaultScopeDimensions() {return RectC(0,0,1280,720);}
	inline static Rect GetDefaultHandleDimensions(int o=0) {return RectC(o,o,640,480);}
	inline static Rect EmptyBox() {return Rect(0,0,0,0);}
	inline static Pt UnitPoint() {return Pt(1,1);}

};
#endif

NAMESPACE_PARALLEL_END


#endif
