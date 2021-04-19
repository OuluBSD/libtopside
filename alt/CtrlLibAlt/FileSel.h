#ifndef _CtrlLibAlt_FileSel_h_
#define _CtrlLibAlt_FileSel_h_


NAMESPACE_UPP


class FileSel : public TopWindow {
	
	
public:
	
	void ActiveDir(String path);
	
	operator Callback1<Stream&>();
	
};


END_UPP_NAMESPACE


#endif
