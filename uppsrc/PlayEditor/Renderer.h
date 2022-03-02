#ifndef _PlayEditor_Renderer_h_
#define _PlayEditor_Renderer_h_

NAMESPACE_TOPSIDE_BEGIN




struct LayoutObject : Moveable<LayoutObject> {
	
	enum {
		COL_NAME,
		COL_TXT,
		COL_CENTER
	};
	
	enum {
		FNT_REGULAR,
		FNT_H1,
		FNT_H2,
	};
	
	int col = -1;
	byte fnt = 0;
	int y = 0;
	int frame_y = 0;
	String txt;
	Size txt_sz;
	
	int time = -1;
	int duration = -1;
	
	
	String ToString() const {return IntStr(time) + "\t" + txt;}
	
};

struct ScriptLayout {
	Vector<LayoutObject> objects;
	
	Font regular;
	Font h1;
	Font h2;
	int regular_h, h1_h, h2_h;
	
	
	int max_name_w = 0;
	
	
	ScriptLayout();
	void Clear() {objects.Clear(); max_name_w = 0;}
	int GetOffset(int time) const;
	
};


Image LiquidBokeh(Size sz, float time);

struct PlayRendererConfig {
	bool render_bg = true;
	bool render_blur = true;
	bool render_text_bending = true;
	bool render_person = true;
	bool render_notes = true;
	bool render_person_background = true;
};

class PlayRenderer {
	PlayScript& script;
	
	int time = 0;
	Size frame_sz;
	
	ScriptLayout layout;
	
	
	void RenderScriptLayout();
	Image RenderScript();
	void CopyImage(ImageBuffer& ib, Point pt, Image img);
	void CopyImageTransparent(ImageBuffer& ib, Point pt, Image img, Color key);
	
public:
	typedef PlayRenderer CLASSNAME;
	
	PlayRenderer(PlayScript& s);
	
	void Seek(int i);
	Image Render(PlayRendererConfig& cfg);
	//Image RenderText();
	
	void Clear() {layout.Clear();}
	
};


NAMESPACE_TOPSIDE_END

#endif
