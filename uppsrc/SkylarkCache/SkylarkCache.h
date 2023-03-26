#ifndef _SkylarkCache_SkylarkCache_h
#define _SkylarkCache_SkylarkCache_h

#include <Skylark/Skylark.h>

NAMESPACE_UPP;

struct SkylarkCacheItem : Moveable<SkylarkCacheItem> {
	unsigned hash;
	int code;
	String ctext;
	String response;
	Value user_data;
};

typedef void (*handlerType)(Http&);
typedef LRUCache<SkylarkCacheItem, unsigned> SkylarkLRUCache;

namespace Ini {
	extern IniBool cache_active;
	
	extern IniInt cache_max_count;
	extern IniInt cache_max_size;
	extern IniBool cache_compress;
}

struct SkylarkCacheMaker : LRUCache<SkylarkCacheItem,unsigned>::Maker {
	int hash;
	Http& http;
	Value user_data;
	handlerType handler;

	void SetUserData(const Value& data) { user_data = data; }

	virtual unsigned Key() const { return hash; }
	virtual int Make(SkylarkCacheItem& item) const;

	SkylarkCacheMaker(Http& http, handlerType handler = NULL);
	virtual ~SkylarkCacheMaker() {}
};

SkylarkLRUCache& SkylarkCache();

struct CachePredicates {
	int count;
	
	bool FileOlderThan(const SkylarkCacheItem& item, ValueMap data);
	template <class P>
	bool Count(const SkylarkCacheItem& item, P predicate);
	int GetCount() { return count; }
	int Clear() { count = 0; return 0; }
	
	CachePredicates() : count(0) {};
};

#define CACHED_SKYLARK(name, path) \
	void COMBINE__(inner_, name)(Http& http); \
	SKYLARK(name, path){ \
		if(!Ini::cache_active) \
			return COMBINE__(inner_, name)(http); \
		SkylarkCacheItem& item = SkylarkCache().Get(SkylarkCacheMaker(http, COMBINE__(inner_, name))); \
		if (http.GetResponse().GetCount() == 0) \
			http.Response(item.code, item.ctext) << (Ini::cache_compress ? ZDecompress(item.response) : item.response); \
		else \
			SkylarkCache().Shrink(Ini::cache_max_size, Ini::cache_max_count); \
	} \
	void COMBINE__(inner_, name)(Http& http)

void InsertToCache(const SkylarkCacheMaker& cache_maker);


template <class P>
struct counter_predicate {
	int& count;
	P& p;
	counter_predicate(P& predicate, int& count) : count(count), p(predicate) {}
	bool operator()(const SkylarkCacheItem& item){
		if(p(item)) ++count;
		RDUMP(count);
		return false;
	}
};

template <class P>
bool GetFromCache(SkylarkCacheMaker& m, P& predicate) {
	if (!Ini::cache_active)
		return false;

	int cnt = 0;
	counter_predicate<P&> counter(predicate, cnt);
	SkylarkCache().Remove(counter);

	if (cnt == 0)
		return false;

	SkylarkCacheItem& item = SkylarkCache().Get(m);
	m.http.Response(item.code, item.ctext);
	m.http << (Ini::cache_compress ? ZDecompress(item.response) : item.response);
	return true;
}

END_UPP_NAMESPACE;

#endif
