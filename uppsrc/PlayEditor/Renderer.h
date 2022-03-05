#ifndef _PlayEditor_Renderer_h_
#define _PlayEditor_Renderer_h_

NAMESPACE_TOPSIDE_BEGIN




struct LayoutObject {
	
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
	Image img;
	Size img_sz;
	Color clr;
	
	int time = -1;
	int duration = -1;
	
	
	String ToString() const {return IntStr(time) + "\t" + txt;}
	
};

struct ScriptLayout {
	Array<LayoutObject> objects;
	
	Font regular;
	Font h1;
	Font h2;
	int regular_h, h1_h, h2_h;
	
	
	int max_name_w = 0;
	
	
	ScriptLayout();
	void Clear() {objects.Clear(); max_name_w = 0;}
	int GetOffset(int time) const;
	Font GetFont(int fnt) const;
	
};


Image LiquidBokeh(Size sz, float time, Color a, Color b);

struct PlayRendererConfig {
	bool render_bg = true;
	bool render_blur = true;
	bool render_text_bending = true;
	bool render_person = true;
	bool render_notes = true;
	bool render_person_background = true;
};

class PlayRenderer {
	static const int fps = 25;
	static const int color_av = 6;
	double notes_fps = 15;
	
	PlayScript& script;
	
	int time = 0;
	Size frame_sz;
	
	ScriptLayout layout;
	
	Vector<Vector<float>> gaussians;
	
	PNGRaster png;
	
	void RenderScriptLayout();
	Image RenderScript();
	Image LoadNotes();
	void CopyImage(ImageBuffer& ib, Point pt, Image img);
	void CopyImageTransparent(ImageBuffer& ib, Point pt, Image img, Color key);
	void CopyImageSemiTransparent(ImageBuffer& ib, Point pt, Image img, int alpha);
	void CopyImageSemiTransparentDark(ImageBuffer& ib, Point pt, Image img, int base_alpha);
	void CopyImageSemiTransparentDark(ImageBuffer& ib, Point pt, Image img, int gray, int alpha);
	void CopyImageSemiTransparent(ImageBuffer& ib, Point pt, Image img, Color key, int alpha);
	void CopyImageTransparentBent(ImageBuffer& ib, Point pt, Image img, Color key, float top_bend, float bottom_bend);
	void CopyImageTransparentBentBlurred(ImageBuffer& ib, Point pt, Image img, Color key, float top_bend, float bottom_bend, int max_blur);
	RGBA GetBoxBlurredTransparent(int x0, int y0, const RGBA* src, const Size& ssz, float max_blur, const RGBA& transparent);
	RGBA GetGaussianBlurTransparent(int x0, int y0, const RGBA* src, const Size& ssz, const Vector<float>& kernel, int edge, const RGBA& transparent);
	
public:
	typedef PlayRenderer CLASSNAME;
	
	PlayRenderer(PlayScript& s);
	
	void SetFrameSize(Size sz) {frame_sz = sz;}
	void Seek(int i);
	Image Render(PlayRendererConfig& cfg);
	//Image RenderText();
	
	void Clear() {layout.Clear();}
	
};


NAMESPACE_TOPSIDE_END

#endif
