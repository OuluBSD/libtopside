#ifndef _SoftRend_Framebuffer_h_
#define _SoftRend_Framebuffer_h_

NAMESPACE_TOPSIDE_BEGIN


/*struct SoftBuffer : Moveable<SoftBuffer> {
	bool inited = false;
	
public:
	Texture tex;
	
public:
	typedef SoftBuffer CLASSNAME;
	
	
	
	void Clear() {inited = false;}
	bool Create() {ASSERT(!inited); inited = true; return true;}
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
};*/



class SoftFramebuffer {
	
protected:
	friend class SoftRend;
	
	/*NativeTexture tex = 0;
	ByteImage* gtex = 0;
	One<ByteImage> owned;*/
	DepthImage* depth = 0;
	ByteImage* color[TEXTYPE_COUNT];
	Size sz;
	
	GVar::Wrap wrap[TEXTYPE_COUNT] {GVar::WRAP_REPEAT, GVar::WRAP_REPEAT};
	GVar::Filter filter[TEXTYPE_COUNT] {GVar::FILTER_NEAREST, GVar::FILTER_NEAREST, GVar::FILTER_NEAREST};
public:
	typedef SoftFramebuffer CLASSNAME;
	SoftFramebuffer();
	
	void Clear();
	void ClearData(GVar::BufferType type);
	void ClearDataAll();
	
	//void SetLocalData(Size sz, byte channels);
	void SetParam(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap repeat);
	void SetColor(TexType tgt, ByteImage* fb);
	void SetDepth(DepthImage* fb) {depth = fb;}
	void SetSize(GVar::RenderTarget tgt, Size sz);
	void Zero(GVar::RenderTarget tgt, RGBA clr);
	
	//const NativeTexture& GetTex() const {ASSERT(tex); return tex;}
	//ByteImage& GetGeomTex() const {ASSERT(gtex); return *gtex;}
	DepthImage* GetDepth() const {return depth;}
	Size GetSize() const {return sz;}
	
	//void operator=(NativeTexture& tex);
	//void SetTexture(ByteImage* t) {ASSERT(tex == 0); gtex = t;}
	void operator=(const Nuller&) {Clear();}
	void operator=(const SoftFramebuffer&) = delete;
	
	//NativeTexture& GetNativeTexture() {return tex;}
	ByteImage* GetFirst(GVar::RenderTarget tgt);
	ByteImage* Get(int i) {return color[i];}
	
};


NAMESPACE_TOPSIDE_END

#endif
