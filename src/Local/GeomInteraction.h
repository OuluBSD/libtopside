#ifndef _Local_GeomInteraction_h_
#define _Local_GeomInteraction_h_

NAMESPACE_TOPSIDE_BEGIN


class GeomInteraction : RTTIBase {
	
public:
	static  bool do_debug_draw;
	
public:
	RTTI_DECL0(GeomInteraction);
	typedef GeomInteraction CLASSNAME;
	GeomInteraction();
	
	
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
	virtual bool IsModified() const;
	virtual void SetModify();
	virtual void ClearModify();
	virtual String GetDesc() const;
	virtual bool IsGeomDrawBegin();
	
	virtual bool Key(dword key, int count);
	virtual bool HotKey(dword key);
	
};


class GeomInteraction2D : public GeomInteraction {
	
protected:
	Rect frame_r;
	DrawCommand cmd_begin, cmd_frame, cmd_pre, cmd_post, cmd_end;
	bool         pending_fx_redraw:1;
	bool         pending_redraw:1;
	bool         pending_layout:1;
	
public:
	RTTI_DECL1(GeomInteraction2D, GeomInteraction);
	typedef GeomInteraction2D CLASSNAME;
	GeomInteraction2D();
	
	Rect GetFrameRect() const {return frame_r;}
	Size GetFrameSize() const {return frame_r.GetSize();}
	DrawCommand& GetCommandBegin() {return cmd_begin;}
	DrawCommand& GetCommandEnd() {return cmd_end;}
	bool IsPendingLayout() const {return pending_layout;}
	
	void SetFrameRect(int x, int y, int w, int h) {SetFrameRect(Rect(x, y, x+w, y+h));}
	void SetFrameRect0(const Rect& r) {this->frame_r = r;}
	void SetPendingLayout() {pending_layout = true;}
	void SetPendingRedraw() {pending_redraw = true;}
	void SetPendingEffectRedraw() {pending_fx_redraw = true;}
	
	virtual void SetFrameRect(const Rect& r) {}
	virtual void FrameLayout(Rect& r) {}
	virtual void FrameAddSize(Size& sz) {}
	virtual void Paint(Draw& d) {}
	virtual bool Redraw(bool only_pending) {return false;}
	
	virtual Size GetMinSize() const {return Size(0,0);}
	virtual Image FrameMouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual Image MouseEvent(int event, Point p, int zdelta, dword keyflags);
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
	virtual void MouseLeave();
	virtual Image CursorImage(Point p, dword keyflags);
	virtual void PadTouch(int controller, Pointf p) {}
	virtual void PadUntouch(int controller) {}
	
	
};


class GeomInteraction3D : public GeomInteraction {
	
	
public:
	RTTI_DECL1(GeomInteraction3D, GeomInteraction);
	typedef GeomInteraction3D CLASSNAME;
	GeomInteraction3D();
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
