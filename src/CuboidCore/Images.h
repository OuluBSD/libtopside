#ifndef _CtrlCoreAlt_Images_h_
#define _CtrlCoreAlt_Images_h_


NAMESPACE_UPP


class CtrlImg {
	
public:
	
	#define CTRLIMG(x) static const Image& x();
	CTRLIMG(Network)
	CTRLIMG(Dir)
	CTRLIMG(swap_color_cursor)
	#undef CTRLIMG
	
};

class CtrlsImg {
	
public:
	
	#define CTRLIMG(x) static const Image& x();
	CTRLIMG(I_B)
	CTRLIMG(I_EB)
	#undef CTRLIMG
	
};


END_UPP_NAMESPACE


#endif
