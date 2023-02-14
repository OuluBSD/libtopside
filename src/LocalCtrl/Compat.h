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
class CtrlGeomProxy : public CtrlGeomBase {
	T* p = 0;
	Image img;
	
public:
	typedef CtrlGeomProxy CLASSNAME;
	RTTI_DECL1(CtrlGeomProxy, CtrlGeomBase);
	CtrlGeomProxy() {}
	CtrlGeomProxy(T& o) : p(&o) {}
	
	void SetTargetCtrl(T& o) {
		p = &o;
	}
	
	template <class K> void LinkInvalidate(K& k) {
		k.WhenInvalidate << THISBACK(OnInvalidate);
	}
	
	void OnInvalidate() {
		SetPendingRedrawDeep();
	}
	
	bool IsFocusCtrl() const {
		const Ctrl* pc = p;
		const Ctrl* c = Ctrl::GetFocusCtrl();
		while (c) {
			if (pc == c)
				return true;
			c = c->GetParent();
		}
		return false;
	}
	void Layout() override {
		if (!p) return;
		Size sz = GetFrameSize();
		p->SetRect(sz);
	}
	
	void Paint(Draw& d) override {
		if (!p) return;
		#if IS_UPP_CORE
		
		#if 1
		Size sz = p->GetRect().GetSize();
		Rect rect = sz;
		Rect orect = rect.Inflated(p->GetOverpaint());
		ImageDraw id(sz);
		id.DrawImage(0,0,img);
		SystemDraw sd;
		sd.SetTarget(&id);
		p->PubCtrlPaint(sd, orect);
		img = id;
		d.DrawImage(0,0,img);
		#elif 1
		Rect rect = p->GetRect().GetSize();
		Rect orect = rect.Inflated(p->GetOverpaint());
		//d.Clipoff(rz);
		p->PubCtrlPaint(d, orect);
		//d.End();
		#elif 1
		Size sz = GetFrameSize();
		d.Clipoff(sz);
		p->Paint(d);
		d.End();
		#else
		Size sz = GetFrameSize();
		ImageDraw id(sz);
		c.Paint(id);
		Image img = id;
		d.DrawImage(0,0,img);
		#endif
		
		#else
		c.Paint(d);
		#endif
	}
	
	#if IS_UPP_CORE
	
	bool DeepMouseMove(const Point& pt, dword keyflags) override {
		Rect r = GetContentRect();
		Point cpt = GetContentPoint(pt);
		if (r.Contains(cpt)) {
			p->DispatchMousePub(UPP::Ctrl::MOUSEMOVE, cpt, 0);
			has_mouse = p->HasMouse();
			has_mouse_deep = p->HasMouseDeep();
			return has_mouse_deep;
		}
		has_mouse = false;
		has_mouse_deep = false;
		return false;
	}
	
	bool Key(dword key, int count) override {
		// this is such a hack
		if (p && IsFocusCtrl())
			UPP::Ctrl::DispatchKeyPub(key, count);
		return false;
	}
	
	void MouseMove(Point pt, dword keyflags) override {
		if (p) p->DispatchMousePub(UPP::Ctrl::MOUSEMOVE, pt, 0);
	}
	
	void MouseWheel(Point pt, int zdelta, dword keyflags) override {
		if (p) p->DispatchMousePub(UPP::Ctrl::MOUSEWHEEL, pt, zdelta);
	}
	
	void MouseLeave() override {
		// pass
		has_mouse = false;
		has_mouse_deep = false;
	}
	
	void LeftDown(Point pt, dword keyflags) override {
		if (p) p->DispatchMousePub(UPP::Ctrl::LEFTDOWN, pt, 0);
	}
	
	void LeftUp(Point pt, dword keyflags) override {
		if (p) p->DispatchMousePub(UPP::Ctrl::LEFTUP, pt, 0);
	}
	
	void RightDown(Point pt, dword keyflags) override {
		if (p) p->DispatchMousePub(UPP::Ctrl::RIGHTDOWN, pt, 0);
	}
	
	void RightUp(Point pt, dword keyflags) override {
		if (p) p->DispatchMousePub(UPP::Ctrl::RIGHTUP, pt, 0);
	}
	
	#endif
	
	T* operator->() {return p;}
	T& operator*() {ASSERT(p); return *p;}
	
	Ctrl* GetCtrl() override {return p;}
	
	
};

template<class T>
class CtrlGeom :
	public CtrlGeomProxy<T>
{
	T c;
	
public:
	typedef CtrlGeom CLASSNAME;
	RTTI_DECL1(CtrlGeom, CtrlGeomBase);
	CtrlGeom() : CtrlGeomProxy<T>(c) {}
	
};

template <class T> using CG = CtrlGeom<T>;

template<class T>
class CtrlInterfaceGeom :
	public CtrlGeomProxy<T>,
	public Absolute2DProxy {
	
public:
	RTTI_DECL2(CtrlInterfaceGeom, CtrlGeomBase, Absolute2DProxy);
	CtrlInterfaceGeom() {}
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
