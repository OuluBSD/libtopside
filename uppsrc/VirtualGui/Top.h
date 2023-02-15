//$ class TopWindow {
public:
	virtual void   State(int reason);

private:
	TopWindowFrame *frame;
	
	void SyncRect();
	void SyncFrameRect(const Rect& r);
	void DestroyFrame();
	
	friend class Ctrl;

public:
	void GripResize();
	
public:
	// libtopside additions
	void FocusEvent();
	void CreateGeom2DComponent();
	void SetTopWindowFrame(TopWindowFrame& twf) {frame = &twf;}
	
	
	Event<> WhenInvalidate;
	
//$ };
