#ifndef _Sequencer_ExprCtrl_h_
#define _Sequencer_ExprCtrl_h_


NAMESPACE_TOPSIDE_BEGIN


class ExprParentCtrl;

class ExprCtrl {
protected:
	friend class ExprParentCtrl;
	Vector<ExprCtrl*> sub;
	Rect rect;
	bool want_focus;
	bool has_focus;
	bool visible;
	
	void* parent;
	byte parent_id;
	
	enum {PARENT_NONE, PARENT_EXPR, PARENT_PARENTEXPR};
	
public:
	
	ExprCtrl();
	
	void Add(ExprCtrl& ec);
	void RemoveChild(ExprCtrl* ec);
	String AsString(int indent=0);
	
	void WantFocus(bool b=true);
	bool IsWantFocus();
	
	bool HasFocusDeep() const;
	bool HasFocus() const;
	
	
	void SetFocus();
	
	void Refresh();
	
	
	void SetRect(int x, int y, int w, int h);
	void SetRect(const Rect& r);
	
	void Show(bool b);
	bool IsVisible() const;
	
	Rect GetRect() const;
	Rect GetScreenRect() const;
	Rect GetExprParentCtrlRect() const;
	Size GetSize() const;
	
	ExprCtrl* GetParent();
	ExprParentCtrl* GetParentCtrl();
	TopWindow* GetTopWindow();
	
	
	
	void RefreshLayout();
	void SetCapture();
	void ReleaseCapture();
	bool IsCaptured();
	
	virtual void Layout();
	virtual void Paint(Draw& d);
	virtual bool Key(dword key, int count);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void LeftDouble(Point p, dword keyflags);
	virtual void RightDown(Point p, dword keyflags);
	virtual void GotFocus();
	virtual void LostFocus();
	virtual void ChildGotFocus();
	virtual void ChildLostFocus();
	virtual void MouseMove(Point p, dword keyflags);
	virtual void MouseEnter(Point p, dword keyflags);
	virtual void MouseLeave();
	virtual void MouseWheel(Point, int zdelta, dword);
	
	void LayoutDeep();
	void PaintDeep(Draw& d, int x, int y);
	bool KeyDeep(dword key, int count);
	void LeftDownDeep(Point p, dword keyflags, int x, int y);
	void LeftUpDeep(Point p, dword keyflags, int x, int y);
	void LeftDoubleDeep(Point p, dword keyflags, int x, int y);
	void RightDownDeep(Point p, dword keyflags, int x, int y);
	void GotFocusDeep();
	void LostFocusDeep();
	void MouseMoveDeep(Point p, dword keyflags, int x, int y);
	void MouseEnterDeep(Point p, dword keyflags, int x, int y);
	void MouseLeaveDeep();
	void MouseWheelDeep(Point pt, int zdelta, dword kf, int x, int y);
};


class ExprParentCtrl : public NodeParentCtrl {
	ExprCtrl* ec;
	ExprCtrl* captured = NULL;
	
public:
	ExprParentCtrl();
	
	ExprCtrl* GetFocusExprCtrl();
	
	void Set(ExprCtrl& ec);
	void SetCapture(ExprCtrl& ec);
	bool IsCaptured(ExprCtrl& ec);
	void ReleaseCapture();
	Point GetCapturedPoint(Point pt);
	
	virtual void Layout();
	virtual void Paint(Draw& d);
	
	virtual bool Key(dword key, int count);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void LeftDouble(Point p, dword keyflags);
	virtual void RightDown(Point p, dword keyflags);
	virtual void GotFocus();
	virtual void LostFocus();
	virtual void MouseMove(Point p, dword keyflags);
	virtual void MouseEnter(Point p, dword keyflags);
	virtual void MouseLeave();
	virtual void MouseWheel(Point, int zdelta, dword);
};


NAMESPACE_TOPSIDE_END

#endif
