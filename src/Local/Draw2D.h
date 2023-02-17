#ifndef _Local_Draw2D_h_
#define _Local_Draw2D_h_


NAMESPACE_TOPSIDE_BEGIN


#if IS_UPP_CORE
class Draw2 : public Draw, RTTIBase
#else
class Draw2 : public Draw
#endif
{
	
public:
	RTTI_DECL1_(Draw2, Draw);
	
	#if 0
	virtual void CtrlDrawBegin(hash_t) {}
	virtual void CtrlDrawEnd() {}
	
	#if IS_UPP_CORE
	virtual void SetSize(Size sz) = 0;
	virtual void DrawImage(int x, int y, Image img, byte alpha) = 0;
	#endif
	#endif
	
};


NAMESPACE_TOPSIDE_END


#endif
