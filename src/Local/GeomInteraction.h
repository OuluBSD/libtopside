#ifndef _Local_GeomInteraction_h_
#define _Local_GeomInteraction_h_

NAMESPACE_TOPSIDE_BEGIN


class GeomInteraction2D;
class GeomInteraction3D;

class GeomInteraction : RTTIBase {
	
public:
	DrawCommand cmd_begin, cmd_frame, cmd_pre, cmd_post, cmd_end;
	GeomInteraction* owner = NULL;
	Vector<GeomInteraction*> sub;
	
public:
	static  bool do_debug_draw;
	
public:
	bool         ignore_mouse:1;
	bool         hidden:1;
	bool         pending_fx_redraw:1;
	bool         pending_redraw:1;
	bool         pending_layout:1;
	bool         want_focus:1;
	bool         has_focus:1;
	bool         has_focus_deep:1;
	bool         has_mouse:1;
	bool         has_mouse_deep:1;
	bool         modify:1;
	
public:
	RTTI_DECL0(GeomInteraction);
	typedef GeomInteraction CLASSNAME;
	GeomInteraction();
	
	int GetSubCount() const;
	GeomInteraction* GetOwner() const;
	void Add(GeomInteraction& c);
	void AddSub(GeomInteraction* c);
	GeomInteraction* GetLastSub();
	GeomInteraction* GetIndexSub(int i);
	void RemoveSub(GeomInteraction* c);
	void ClearSub();
	
	void Show(bool b=true);
	void Hide() {Show(false);}
	bool IsShown() const;
	bool HasFocus() const {return has_focus;}
	bool HasFocusDeep() const {return has_focus_deep;}
	bool HasMouse() const {return has_mouse;}
	bool HasMouseDeep() const {return has_mouse_deep;}
	void WantFocus(bool b=true) {want_focus = b;}
	void IgnoreMouse(bool b=true) {ignore_mouse = b;}
	DrawCommand& GetCommandBegin() {return cmd_begin;}
	DrawCommand& GetCommandEnd() {return cmd_end;}
	bool IsPendingLayout() const {return pending_layout;}
	void DeepMouseLeave();
	
	void SetPendingLayout() {pending_layout = true;}
	void SetPendingRedraw() {pending_redraw = true;}
	void SetPendingEffectRedraw() {pending_fx_redraw = true;}
	
	void PostCallback(Callback cb);
	void PostRefresh();
	void PostLayoutCallback();
	void SetCapture();
	void ReleaseCapture();
	bool DeepKey(dword key, int count);
	void Layout0();
	void Refresh0();
	
	virtual bool Redraw(bool only_pending) = 0;
	virtual void SetFocus();
	virtual void DeepUnfocus();
	virtual void Refresh() {}
	virtual void Activate() {}
	virtual void Deactivate() {}
	virtual void Layout() {}
	virtual void PostLayout() {}
	virtual void GotFocus() {}
	virtual void LostFocus() {}
	virtual void ChildGotFocus() {}
	virtual void ChildLostFocus() {}
	virtual void Updated() {}
	virtual void MouseLeaveFrame() {}
	virtual bool IsModified() const;
	virtual void SetModify();
	virtual void ClearModify();
	virtual String GetDesc() const;
	virtual bool IsGeomDrawBegin();
	virtual void MouseLeave();
	virtual void PaintPreFrame(ProgPainter& pp) {}
	virtual void PaintPostFrame(ProgPainter& pp) {}
	virtual void PaintDebug(ProgPainter& pp) {}
	
	virtual bool Key(dword key, int count);
	virtual bool HotKey(dword key);
	virtual bool Is2D() const;
	virtual bool Is3D() const;
	virtual GeomInteraction2D* Get2D();
	virtual GeomInteraction3D* Get3D();
	
	
	GeomInteraction* GetCaptured();
	GeomInteraction* GetWithMouse();
	void SetCaptured(GeomInteraction* c);
	void SetWithMouse(GeomInteraction* c);
	
};


class GeomInteraction2D : public GeomInteraction {
	
protected:
	Rect frame_r;
	
public:
	RTTI_DECL1(GeomInteraction2D, GeomInteraction);
	typedef GeomInteraction2D CLASSNAME;
	GeomInteraction2D();
	
	void DeepLayout();
	int GetCount() const;
	GeomInteraction2D* operator[](int i);
	Rect GetFrameRect() const {return frame_r;}
	Size GetFrameSize() const {return frame_r.GetSize();}
	Rect GetRect() const {return GetFrameRect();}
	
	void SetFrameRect(int x, int y, int w, int h) {SetFrameRect(Rect(x, y, x+w, y+h));}
	
	bool DeepMouseMove(const Point& pt, dword keyflags);
	bool DeepMouse(int mouse_code, const Point& pt, dword keyflags);
	bool DeepMouseWheel(const Point& pt, int zdelta, dword keyflags);
	
	virtual void SetFrameRect(const Rect& r) {}
	virtual void FrameLayout(Rect& r) {}
	virtual void FrameAddSize(Size& sz) {}
	virtual void Paint(Draw& d) {}
	
	virtual void SetGeomRect(const Rect& r) {this->frame_r = r;}
	virtual Size GetMinSize() const {return Size(0,0);}
	virtual Point GetContentPoint(const Point& pt);
	virtual Image FrameMouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual Image MouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual void DeepMouseMoveInFrame(Point pt, dword keyflags);
	virtual bool MouseMoveInFrame(Point pt, dword keyflags);
	virtual bool MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags);
	virtual bool MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags);
	virtual bool MouseWheelInFrame(Point p, int zdelta, dword keyflags);
	virtual void MouseEnter(Point frame_p, dword keyflags);
	virtual void MouseMove(Point content_p, dword keyflags) {}
	virtual void LeftDown(Point p, dword keyflags) {}
	virtual void LeftDouble(Point p, dword keyflags) {}
	virtual void LeftTriple(Point p, dword keyflags) {}
	virtual void LeftDrag(Point p, dword keyflags) {}
	virtual void LeftHold(Point p, dword keyflags) {}
	virtual void LeftRepeat(Point p, dword keyflags) {}
	virtual void LeftUp(Point p, dword keyflags) {}
	virtual void RightDown(Point p, dword keyflags) {}
	virtual void RightDouble(Point p, dword keyflags) {}
	virtual void RightTriple(Point p, dword keyflags) {}
	virtual void RightDrag(Point p, dword keyflags) {}
	virtual void RightHold(Point p, dword keyflags) {}
	virtual void RightRepeat(Point p, dword keyflags) {}
	virtual void RightUp(Point p, dword keyflags) {}
	virtual void MiddleDown(Point p, dword keyflags) {}
	virtual void MiddleDouble(Point p, dword keyflags) {}
	virtual void MiddleTriple(Point p, dword keyflags) {}
	virtual void MiddleDrag(Point p, dword keyflags) {}
	virtual void MiddleHold(Point p, dword keyflags) {}
	virtual void MiddleRepeat(Point p, dword keyflags) {}
	virtual void MiddleUp(Point p, dword keyflags) {}
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) {}
	virtual Image CursorImage(Point p, dword keyflags);
	virtual void PadTouch(int controller, Pointf p) {}
	virtual void PadUntouch(int controller) {}
	
	bool Redraw(bool only_pending) override;
	bool Is2D() const override;
	GeomInteraction2D* Get2D() override;
	
};


class GeomInteraction3D : public GeomInteraction {
	
	
public:
	RTTI_DECL1(GeomInteraction3D, GeomInteraction);
	typedef GeomInteraction3D CLASSNAME;
	GeomInteraction3D();
	
	bool Is3D() const override;
	GeomInteraction3D* Get3D() override;
	bool Redraw(bool only_pending) override;
};


NAMESPACE_TOPSIDE_END

#endif
