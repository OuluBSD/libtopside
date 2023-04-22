#include "StaticInterface.h"

NAMESPACE_TOPSIDE_BEGIN


ArrayMap<TypeCls, StaticIfaceBackend>						StaticIfaceFactory::backends;


StaticIfaceBackend& StaticIfaceFactory::GetAdd(const Backend& b) {
	int i = backends.Find(b.type);
	if (i >= 0)
		return backends[i];
	else
		return backends.Add(b.type, b.new_fn());
}

StaticIfaceBackend* StaticIfaceFactory::GetReader(String ext) {
	ASSERT(ext.Left(1) != ".");
	int i = NewFns().Find(ext);
	if (i < 0)
		return 0;
	Vector<Backend>& fns = NewFns()[i];
	for (Backend& b : fns) {
		if (b.read)
			return &GetAdd(b);
	}
	return 0;
}

StaticIfaceBackend* StaticIfaceFactory::GetReader(TypeCls type) {
	int i = backends.Find(type);
	if (i >= 0)
		return &backends[i];
	return 0;
}

StaticIfaceBackend* StaticIfaceFactory::GetWriter(String ext) {
	ASSERT(ext.Left(1) != ".");
	int i = NewFns().Find(ext);
	if (i < 0)
		return 0;
	Vector<Backend>& fns = NewFns()[i];
	for (Backend& b : fns) {
		if (b.write)
			return &GetAdd(b);
	}
	return 0;
}




Image RenderTextBlended(Font fnt, const char* s, SysColor c) {
#if IS_UPP_CORE
	TODO
#else
	SysFont* raw = fnt.GetSysFont();
	if (!raw)
		return Image();
	auto r = TS::StaticIfaceFactory::GetReader(raw->raw->backend);
	if (r)
		return r->RenderTextBlended(*raw, s, c);
	return Image();
#endif
}



NAMESPACE_TOPSIDE_END
