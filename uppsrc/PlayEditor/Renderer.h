#ifndef _PlayEditor_Renderer_h_
#define _PlayEditor_Renderer_h_

NAMESPACE_TOPSIDE_BEGIN


Image LiquidBokeh(Size sz, float time);

class PlayRenderer {
	PlayScript& script;
	
	int time = 0;
	Size frame_sz;
	
public:
	typedef PlayRenderer CLASSNAME;
	
	PlayRenderer(PlayScript& s);
	
	void Seek(int i);
	Image Render();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
