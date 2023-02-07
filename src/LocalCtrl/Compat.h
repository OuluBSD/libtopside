#ifndef _LocalCtrl_Compat_h_
#define _LocalCtrl_Compat_h_

NAMESPACE_TOPSIDE_BEGIN

class CtrlGeomBase : public GeomInteraction2D {
	
public:
	typedef CtrlGeomBase CLASSNAME;
	RTTI_DECL1(CtrlGeomBase, GeomInteraction2D);
	CtrlGeomBase() {}
	
	virtual Ctrl* GetCtrl() = 0;
	
};

template<class T>
class CtrlGeom : public CtrlGeomBase {
	T c;
	
public:
	typedef CtrlGeom CLASSNAME;
	RTTI_DECL1(CtrlGeom, CtrlGeomBase);
	CtrlGeom() {}
	
	/*void Create() {
		c.Clear();
		c = new T();
	}*/
	
	void Layout() override {
		Size sz = GetFrameSize();
		c.SetRect(sz);
	}
	
	void Paint(Draw& d) override {
		#if IS_UPP_CORE
		TODO
		#else
		c.Paint(d);
		#endif
	}
	
	T* operator->() {return &c;}
	
	Ctrl* GetCtrl() override {return &c;}
	
};

template <class T> using CG = CtrlGeom<T>;


NAMESPACE_TOPSIDE_END

#endif
