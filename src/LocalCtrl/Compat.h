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

class CtrlGeomProxy : public CtrlGeomBase {
	Ctrl* p = 0;
	Image img;
	
public:
	typedef CtrlGeomProxy CLASSNAME;
	RTTI_DECL1(CtrlGeomProxy, CtrlGeomBase);
	CtrlGeomProxy();
	CtrlGeomProxy(Ctrl& o);
	void SetTargetCtrl(Ctrl& o);
	
	template <class K> void LinkInvalidate(K& k) {
		k.WhenInvalidate << THISBACK(OnInvalidate);
	}
	
	void OnInvalidate();
	bool IsFocusCtrl() const;
	void Layout() override;
	void Paint(Draw& d) override;
	
	#if IS_UPP_CORE
	
	bool DeepMouseMove(const Point& pt, dword keyflags) override;
	bool Key(dword key, int count) override;
	void MouseMove(Point pt, dword keyflags) override;
	void MouseWheel(Point pt, int zdelta, dword keyflags) override;
	void MouseLeave() override;
	void LeftDown(Point pt, dword keyflags) override;
	void LeftUp(Point pt, dword keyflags) override;
	void RightDown(Point pt, dword keyflags) override;
	void RightUp(Point pt, dword keyflags) override;
	
	#endif
	
	Ctrl* operator->();
	Ctrl& operator*();
	
	Ctrl* GetCtrl() override;
	
	
};

template<class T>
class CtrlGeom :
	public CtrlGeomProxy
{
	T c;
	
public:
	typedef CtrlGeom CLASSNAME;
	RTTI_DECL1(CtrlGeom, CtrlGeomBase);
	CtrlGeom() : CtrlGeomProxy(c) {}
	
};

template <class T> using CG = CtrlGeom<T>;

#if 0
class CtrlInterfaceGeom :
	public CtrlGeomProxy,
	public Absolute2DProxy {
	
public:
	RTTI_DECL2(CtrlInterfaceGeom, CtrlGeomBase, Absolute2DProxy);
	CtrlInterfaceGeom() {}
	
	
	
};




class GuboGeomBase : public GeomInteraction3D {
	
public:
	typedef GuboGeomBase CLASSNAME;
	RTTI_DECL1(GuboGeomBase, GeomInteraction3D);
	GuboGeomBase() {}
	
	virtual Gubo* GetGubo() = 0;
	
};

class GuboGeomProxy : public GuboGeomBase {
	
	
public:
	typedef GuboGeomProxy CLASSNAME;
	RTTI_DECL1(GuboGeomProxy, GuboGeomBase);
	GuboGeomProxy() {}
	
	Gubo* GetGubo() override {TODO}
	
};

#endif


NAMESPACE_TOPSIDE_END


#endif
