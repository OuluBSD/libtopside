#ifndef _IHolograph_Types_h_
#define _IHolograph_Types_h_




#ifdef flagDX11
	#define DX11_HOLOTYPE HOLOTYPE(Dx11Holo)
	#define DX11HOLO_EXCPLICIT_INITIALIZE_CLASS(x) template struct x <Dx11Holo>;
#else
	#define DX11_HOLOTYPE
	#define DX11HOLO_EXCPLICIT_INITIALIZE_CLASS(x)
#endif

#ifdef flagOGL
	#define OGL_HOLOTYPE HOLOTYPE(OglHolo)
	#define OGLHOLO_EXCPLICIT_INITIALIZE_CLASS(x) template struct x <OglHolo>;
#else
	#define OGL_HOLOTYPE
	#define OGLHOLO_EXCPLICIT_INITIALIZE_CLASS(x)
#endif


#define HOLOTYPE_LIST \
	 \
	DX11_HOLOTYPE \
	OGL_HOLOTYPE \


#define HOLO_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	DX11HOLO_EXCPLICIT_INITIALIZE_CLASS(x) \
	OGLHOLO_EXCPLICIT_INITIALIZE_CLASS(x) \



#endif
