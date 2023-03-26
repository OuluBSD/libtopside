#include "SkylarkCache.h"

NAMESPACE_UPP;

namespace Ini {
	INI_BOOL(cache_active, true, "Enables or disables caching");
	INI_INT(cache_max_count, 10000, "Maximum number of cached items, setting to 0 or less deactivates the cache completely");
	INI_INT(cache_max_size, 1048576, "Maximum size of cache");
	INI_BOOL(cache_compress, true, "Should the cache contents be gzipped");
}

GLOBAL_VAR(SkylarkLRUCache, SkylarkCache);

int SkylarkCacheMaker::Make(SkylarkCacheItem& item) const {
	if (!Ini::cache_active)
		return 0;
	if (handler)
		handler(http);
	item.hash = hash;
	item.response = Ini::cache_compress ? ZCompress(http.GetResponse()) : http.GetResponse();
	item.code = http.GetResponseCode();
	item.ctext = http.GetResponseCodeText();
	item.user_data = user_data;
	return item.response.GetCount() + item.ctext.GetCount() + sizeof(SkylarkCacheItem);
}

SkylarkCacheMaker::SkylarkCacheMaker(Http& http, handlerType handler)
	: http(http), handler(handler) {
	if (!Ini::cache_active)
		return;
	String uri = http.GetURI();
	CombineHash ch(uri);
	const VectorMap<String, Value>& set = http.Variables();
	for(int i = 0; i < set.GetCount(); i++) {
		ch << set.GetKey(i) << set[i];
	}
	hash = ch;
}

void InsertToCache(const SkylarkCacheMaker& cache_maker) {
	if (!Ini::cache_active)
		return;
	SkylarkCache().Get(cache_maker);
	SkylarkCache().Shrink(Ini::cache_max_size, Ini::cache_max_count);
}

END_UPP_NAMESPACE;
