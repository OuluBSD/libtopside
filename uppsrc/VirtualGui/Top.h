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
	
	
	
	Event<> WhenInvalidate;
	
//$ };
