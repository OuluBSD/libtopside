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
	using Event = CtrlEvent;
	
};


struct Ctx3D {
	
	
	using Space = Workspace3D;
	using Interface = Absolute3DInterface;
	using InterfaceProxy = Absolute3DProxy;
	using Event = GeomEvent;
	
	
};


NAMESPACE_PARALLEL_END

#endif
