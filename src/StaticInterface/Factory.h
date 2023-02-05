#ifndef _StaticInterface_Factory_h_
#define _StaticInterface_Factory_h_

NAMESPACE_TOPSIDE_BEGIN


struct StaticIfaceBackend : RTTIBase {
	RTTI_DECL0(StaticIfaceBackend)
	StaticIfaceBackend() {}
	virtual ~StaticIfaceBackend() {}
	
	
	virtual Image LoadStringAny(String str) {Panic("internal error: unimplemented"); return Image();}
	virtual Image LoadFileAny(String path) {Panic("internal error: unimplemented"); return Image();}
	virtual void ClearImage(SysImage& img) {Panic("internal error: unimplemented");}
	
	virtual Font LoadFont(String dir, String name, int ptsize, int weight, bool italic) {Panic("internal error: unimplemented"); return Font();}
	virtual Size GetTextSize(const SysFont& fnt, const String& s) {Panic("internal error: unimplemented"); return Size();}
	virtual void ClearFont(SysFont& fnt) {Panic("internal error: unimplemented");}
	virtual Image RenderTextBlended(const SysFont& fnt, const char* s, SysColor c) {Panic("internal error: unimplemented"); return Image();}
	
};


struct StaticIfaceFactory {
	typedef StaticIfaceBackend* (*NewStatic)();
	
	struct Backend : Moveable<Backend> {
		TypeCls type;
		NewStatic new_fn;
		bool read, write;
	};
	
	static VectorMap<String, Vector<Backend>> new_fns;
	static ArrayMap<TypeCls, StaticIfaceBackend> backends;
	
	
	
	template <class T> static StaticIfaceBackend* New() {return new T();}
	
	template <class T>
	static void AddFileFormat(String ext, bool read, bool write) {
		Vector<Backend>& fns = new_fns.GetAdd(ext);
		Backend& b = fns.Add();
		b.type = GetTypeIdClass<T>();
		b.new_fn = &New<T>;
		b.read = read;
		b.write = write;
	}
	
	static StaticIfaceBackend& GetAdd(const Backend& b);
	static StaticIfaceBackend* GetReader(String ext);
	static StaticIfaceBackend* GetReader(TypeCls type);
	static StaticIfaceBackend* GetWriter(String ext);
	
};


Image RenderTextBlended(Font fnt, const char* s, SysColor c);


NAMESPACE_TOPSIDE_END

#endif
