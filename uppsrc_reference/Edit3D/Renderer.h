#ifndef _Edit3D_Renderer_h_
#define _Edit3D_Renderer_h_

NAMESPACE_TOPSIDE_BEGIN


struct Edit3D;


struct EditRenderer : public Ctrl {
	Edit3D* owner = 0;
	ViewMode view_mode;
	
	Point cap_mouse_pos;
	vec3 cap_begin_pos;
	bool is_captured_mouse = false;
	
public:
	typedef EditRenderer CLASSNAME;
	EditRenderer();
	
	void Paint(Draw& d) override;
	void LeftDown(Point p, dword keyflags) override;
	void LeftUp(Point p, dword keyflags) override;
	void MouseMove(Point p, dword keyflags) override;
	
	void SetViewMode(ViewMode i) {view_mode = i;}

	
};


NAMESPACE_TOPSIDE_END

#endif
