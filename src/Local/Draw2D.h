#ifndef _Local_Draw2D_h_
#define _Local_Draw2D_h_


NAMESPACE_TOPSIDE_BEGIN


class Draw2 : public Draw {
	
	
public:
	RTTI_DECL1_(Draw2, Draw);
	virtual void CtrlDrawBegin(hash_t) {}
	virtual void CtrlDrawEnd() {}
	virtual void SetSize(Size sz) = 0;
	virtual void DrawImage(int x, int y, Image img, byte alpha) = 0;
	
};


NAMESPACE_TOPSIDE_END


#endif
