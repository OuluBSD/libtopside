#include "StaticInterface.h"

NAMESPACE_TOPSIDE_BEGIN


VectorMap<String, Vector<StaticIfaceFactory::Backend>>		StaticIfaceFactory::new_fns;
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
	int i = new_fns.Find(ext);
	if (i < 0)
		return 0;
	Vector<Backend>& fns = new_fns[i];
	for (Backend& b : fns) {
		if (b.read)
			return &GetAdd(b);
	}
	return 0;
}

StaticIfaceBackend* StaticIfaceFactory::GetWriter(String ext) {
	ASSERT(ext.Left(1) != ".");
	int i = new_fns.Find(ext);
	if (i < 0)
		return 0;
	Vector<Backend>& fns = new_fns[i];
	for (Backend& b : fns) {
		if (b.write)
			return &GetAdd(b);
	}
	return 0;
}


NAMESPACE_TOPSIDE_END
