#ifndef _LocalCtrl_Compat_h_
#define _LocalCtrl_Compat_h_


NAMESPACE_TOPSIDE_BEGIN

#if 0
class CtrlGeomBase : RTTIBase {
	
public:
	typedef CtrlGeomBase CLASSNAME;
	RTTI_DECL0(CtrlGeomBase);
	CtrlGeomBase() {}
	
	virtual Ctrl* GetCtrl() = 0;
	
	Rect GetFrameSize() const;
	
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
	void Layout();
	
	virtual void Paint(Draw& d);
	
	#if IS_TS_CORE
	bool DeepMouseMove(const Point& pt, dword keyflags) override;
	#endif
	
	bool Key(dword key, int count) override;
	void MouseMove(Point pt, dword keyflags) override;
	void MouseWheel(Point pt, int zdelta, dword keyflags) override;
	void MouseLeave() override;
	void LeftDown(Point pt, dword keyflags) override;
	void LeftUp(Point pt, dword keyflags) override;
	void RightDown(Point pt, dword keyflags) override;
	void RightUp(Point pt, dword keyflags) override;
	
	
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

#endif
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




template <class T, class B=decltype(T::GetFrameSize)>
inline B GetFrameSize(const T& o) {
	return o.GetFrameSize();
}

template <>
inline Size GetFrameSize<Ctrl,Size>(const Ctrl& c) {
	return c.GetSize();
}


template <class T, class B>
inline void SetFrameBox(T& o, const B& v) {
	o.SetFrameBox(v);
}

template <>
inline void SetFrameBox(Ctrl& o, const Rect& v) {
	o.SetRect(v);
}



template <class T, class B=decltype(T::GetFrameBox)>
inline B GetFrameBox(const T& o) {
	return o.GetFrameBox();
}

template <>
inline Rect GetFrameBox<Ctrl,Rect>(const Ctrl& c) {
	return c.GetRect();
}


NAMESPACE_TOPSIDE_END


#endif
