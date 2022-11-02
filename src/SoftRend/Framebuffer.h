#ifndef _SoftRend_Framebuffer_h_
#define _SoftRend_Framebuffer_h_

NAMESPACE_TOPSIDE_BEGIN




class SoftFramebuffer {
	
protected:
	friend class SoftRend;
	
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
	
	void SetParam(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap repeat);
	void SetColor(TexType tgt, ByteImage* fb);
	void SetDepth(DepthImage* fb) {depth = fb;}
	void SetSize(GVar::RenderTarget tgt, Size sz);
	void Zero(GVar::RenderTarget tgt, RGBA clr);
	
	DepthImage* GetDepth() const {return depth;}
	Size GetSize() const {return sz;}
	
	void operator=(const Nuller&) {Clear();}
	void operator=(const SoftFramebuffer&) = delete;
	
	ByteImage* GetFirst(GVar::RenderTarget tgt);
	ByteImage* Get(int i) {return color[i];}
	
};


NAMESPACE_TOPSIDE_END

#endif
