#ifndef _SoftRend_Framebuffer_h_
#define _SoftRend_Framebuffer_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftFramebuffer {
	bool inited = false;
	
protected:
	friend class SoftRend;
	SDL_Texture* tex = 0;
	
public:
	typedef SoftFramebuffer CLASSNAME;
	SoftFramebuffer();
	
	void Clear();
	bool Create();
	void ClearData(GVar::BufferType type);
	void ClearDataAll();
	
	void SetParam(int type, GVar::Filter filter, GVar::Wrap repeat);
	
	SDL_Texture* GetTex() const {return tex;}
	
	void operator=(SDL_Texture* tex);
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	
};


NAMESPACE_TOPSIDE_END

#endif
