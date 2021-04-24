#ifndef _LayoutCtrl_Resources_h_
#define _LayoutCtrl_Resources_h_


NAMESPACE_LAYOUT_BEGIN

String GetMasterCss();


struct Cookie : Moveable<Cookie> {
	String id;
	String value;
	String domain;
	String path;
	String raw;
	
	void Serialize(Stream& s) {s % id % value % domain % path % raw;}
	bool Replace(const Cookie& c);
	void Set(const HttpCookie& h) {
		id = h.id;
		value = h.value;
		domain = h.domain;
		path = h.path;
		raw = h.raw;
	}
	bool operator==(const Cookie& c) const {return id == c.id && value == c.value && domain == c.domain;}
	bool operator()(const Cookie& a, const Cookie& b) const {if (domain == b.domain) return a.id < b.id; else return domain < b.domain;}
	unsigned GetHashValue() const {CombineHash ch; ch << id << value << domain; return ch;}
};

void GetHttpCookie(HttpCookie& h, const Cookie& c);

struct ResourceHeader : Moveable<ResourceHeader> {
	enum {
		METHOD_GET     = 0,
		METHOD_POST    = 1,
		METHOD_HEAD    = 2,
		METHOD_PUT     = 3,
		METHOD_DELETE  = 4,
		METHOD_TRACE   = 5,
		METHOD_OPTIONS = 6,
		METHOD_CONNECT = 7,
		METHOD_PATCH   = 8,
	};
	
	
	Vector<Cookie> cookies;
	String base_addr;
	String addr;
	String data;
	int method = 0;
	
	
public:
	ResourceHeader() {}
	ResourceHeader(const ResourceHeader& h) {*this = h;}
	void operator=(const ResourceHeader& h) {
		cookies <<= h.cookies;
		base_addr = h.base_addr;
		addr = h.addr;
		data = h.data;
		method = h.method;
	}
	void Serialize(Stream& s) {s % cookies % base_addr % addr % data % method;}
	String GetResourceFile();
	unsigned GetHashValue() const;
	bool operator==(const ResourceHeader& h) const {
		if (h.cookies.GetCount() != cookies.GetCount()) return false;
		for(int i = 0; i < cookies.GetCount(); i++)
			if (!(cookies[i] == h.cookies[i]))
				return false;
		return /*base_addr == h.base_addr &&*/ addr == h.addr && data == h.data && method == h.method;
	}
};

class ResourceQuery : Moveable<ResourceQuery> {
	Vector<Callback1<ResourceQuery*> > when_ready;
	SpinLock lock;
	Atomic is_processing;
	
protected:
	friend class Resources;
	
	ResourceHeader header;
	
	String data;
	String redirect;
	int status = 0;
	Time expiration;
	Vector<Cookie> return_cookies;
	bool use_cached = false;
	bool is_public = false;
	
	void Process();
	void Load(const ResourceHeader& h);
	void AddCallback(Callback1<ResourceQuery*> cb);
	void StartProcess();
	
	Callback1<ResourceQuery*> WhenReady;
	
public:
	typedef ResourceQuery CLASSNAME;
	
	
	String GetAddr() const {return header.addr;}
	String GetData() const {return data;}
	bool IsUsingCache() const {return use_cached;}
	bool IsRedirect() const {return !redirect.IsEmpty();}
	String GetRedirection() const {return redirect;}
	int GetStatusCode() const {return status;}
	
	void Serialize(Stream& s) {s % header % data % redirect % status % expiration % return_cookies % use_cached;}
	
};

class Resources {
	ArrayMap<ResourceHeader, ResourceQuery> cached;
	Array<ResourceQuery> queries;
	Mutex lock;
	
	ArrayMap<String, Vector<Cookie> > site_cookies;
	Mutex cookie_lock;
	
	
	void UpdateCookies(String base_addr, const Vector<Cookie>& src);
	
	
public:
	typedef Resources CLASSNAME;
	Resources();
	
	void FinishQuery(ResourceQuery* res);
	void GetCookies(ResourceQuery* res);
	void FillCookies(String base_addr, Vector<Cookie>& cookies);
	
	void Query(const ResourceHeader& h, Callback1<ResourceQuery*> when_ready);
	const ResourceQuery& Get(int res_id) const {return queries[res_id];}
	
	void Serialize(Stream& s) {s % site_cookies;}
	void StoreThis() {StoreToFile(*this, ConfigFile("resources.bin"));}
	void LoadThis() {LoadFromFile(*this, ConfigFile("resources.bin"));}
};


inline Resources& GetResources() {return Single<Resources>();}



class CacheObject {
	Image img;
	String text;
public:
	
	Image GetImage() {return img;}
	String GetText() {return text;}
	
	void SetImage(Image i) {img = i;}
	void SetText(String s) {text = s;}
	
};

class ResourceCache {
	ArrayMap<String, CacheObject> site_objects;
	RWMutex lock;
	
public:
	ResourceCache();
	
	int FindObject(String image, String base_url);
	int AddObject(String image, String base_url);
	CacheObject& GetObject(int cache_id);
	
};

inline ResourceCache& GetResourceCache() {return Single<ResourceCache>();}

NAMESPACE_LAYOUT_END


#endif
