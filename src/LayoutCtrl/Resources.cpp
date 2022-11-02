#include "LayoutCtrl.h"



NAMESPACE_LAYOUT_BEGIN

String GetMasterCss() {
	return LoadFile(ShareDirFile(AppendFileName("html", "master.css")));
}

void GetHttpCookie(HttpCookie& h, const Cookie& c) {
	h.id = c.id;
	h.value = c.value;
	h.domain = c.domain;
	h.path = c.path;
	h.raw = c.raw;
}

bool Cookie::Replace(const Cookie& c) {
	if (domain == c.domain && id == c.id) {
		value = c.value;
		path = c.path;
		raw = c.raw;
		return true;
	}
	return false;
}

String ResourceHeader::GetResourceFile() {
	StringStream ss;
	ss % *this;
	String addr_md5 = MD5String(ss.GetResult());
	String dir = ConfigFile("cache");
	RealizeDirectory(dir);
	String file = dir + DIR_SEPS + addr_md5;
	return file;
}

unsigned ResourceHeader::GetHashValue() const {
	CombineHash ch;
	for(int i = 0; i < cookies.GetCount(); i++)
		ch.Put(cookies[i].GetHashValue());
	ch << base_addr << addr << data << method;
	return ch;
}

void ResourceQuery::Process() {
	if (AtomicInc(is_processing) == 1)
		Thread::Start(THISBACK(Process));
	else
		AtomicDec(is_processing);
}

void ResourceQuery::AddCallback(Callback1<ResourceQuery*> cb) {
	lock.Enter();
	when_ready.Add(cb);
	lock.Leave();
}

void ResourceQuery::Load(const ResourceHeader& h) {
	header = h;
	
	String file = header.GetResourceFile();
	if (FileExists(file)) {
		FileIn fin(file);
		fin % *this;
	}
}

void ResourceQuery::StartProcess() {
	if (use_cached && GetUtcTime() >= expiration)
		use_cached = false;
	
	if (!use_cached) {
		UrlParser p;
		p.Parse(header.addr);
		if (p.GetProtocol() == "file") {
			String file = p.GetWithoutProtocol();
			if (FileExists(file)) {
				data = LoadFile(file);
				status = 200;
			}
			else {
				status = 404;
			}
			expiration = GetUtcTime();
		}
		else {
			HttpRequest h;
			#ifdef flagPOSIX
			h.UserAgent("Mozilla/5.0 (OS X11) libtopside");
			#elif defined(flagWIN32)
			h.UserAgent("Mozilla/5.0 (Windows) libtopside");
			#else
			h.UserAgent("Mozilla/5.0 (Unknown) libtopside");
			#endif
			
			for(int i = 0; i < header.cookies.GetCount(); i++) {
				HttpCookie hc;
				GetHttpCookie(hc, header.cookies[i]);
				h.Cookie(hc);
			}
			h.Method(header.method);
			h.PostData(header.data);
			h.Url(header.addr);
			h.Trace();
			data = h.Execute();
			
			status = h.GetStatusCode();
			
			String r = h.GetRedirectUrl();
			if (r.GetCount() && r != header.addr) {
				redirect = r;
			}
			
			expiration = GetUtcTime();
			const HttpHeader& header = h.GetHttpHeader();
			for(int i = 0; i < header.fields.GetCount(); i++) {
				String key = header.fields.GetKey(i);
				if (key == "Cache-Control" || key == "cache-control") {
					String value = header.fields[i];
					int j = value.Find("=");
					if (j >= 0) {
						String arg_key = value.Left(j);
						String arg_value = value.Mid(j+1);
						if (arg_key == "max-age") {
							int64 sec = ScanInt64(arg_value);
							expiration += sec;
							use_cached = true;
						}
					}
					else {
						if (value == "private") {
							// This IS private resource manager
							use_cached = true;
						}
						else if (value == "public") {
							use_cached = true;
						}
						else if (value == "must-revalidate") {
							use_cached = false;
						}
						else if (value == "no-cache") {
							use_cached = false;
						}
					}
				}
			}
			return_cookies.Clear();
			for(int i = 0; i < header.cookies.GetCount(); i++)
				return_cookies.Add().Set(header.cookies[i]);
			Sort(return_cookies, Cookie());
			
			String file = this->header.GetResourceFile();
			FileOut fout(file);
			fout % *this;
		}
	}
	
	
	Vector<Callback1<ResourceQuery*> > when_ready;
	lock.Enter();
	Swap(when_ready, this->when_ready);
	lock.Leave();
	
	for(int i = 0; i < when_ready.GetCount(); i++)
		when_ready[i](this);
	
	AtomicDec(is_processing);
	
	WhenReady(this);
}





Resources::Resources() {
	cookie_lock.Enter();
	LoadThis();
	cookie_lock.Leave();
}

void Resources::Query(const ResourceHeader& h, Callback1<ResourceQuery*> when_ready) {
	lock.Enter();
	int ci = cached.Find(h);
	ResourceQuery* q = NULL;
	if (ci >= 0) {
		q = &cached[ci];
	}
	else {
		One<ResourceQuery> query;
		query.Create();
		query->Load(h);
		if (query->IsUsingCache()) {
			ResourceHeader h(query->header);
			q = &cached.Add(h, query.Detach());
			UpdateCookies(q->header.base_addr, q->header.cookies);
		}
		else {
			q = &queries.Add(query.Detach());
		}
	}
	
	q->AddCallback(when_ready);
	q->WhenReady = THISBACK(FinishQuery);
	q->StartProcess();
	
	lock.Leave();
}

void Resources::FinishQuery(ResourceQuery* res) {
	GetCookies(res);
	
	lock.Enter();
	for(int i = 0; i < queries.GetCount(); i++) {
		if (&queries[i] == res) {
			if (res->IsUsingCache() && cached.Find(res->header) == -1)
				cached.Add(res->header, queries.Detach(i));
			else
				queries.Remove(i);
			break;
		}
	}
	lock.Leave();
}

void Resources::GetCookies(ResourceQuery* res) {
	UpdateCookies(res->header.base_addr, res->return_cookies);
}

void Resources::UpdateCookies(String base_addr, const Vector<Cookie>& src) {
	cookie_lock.Enter();
	Vector<Cookie>& cookies = site_cookies.GetAdd(base_addr);
	bool is_modified = false;
	for(int i = 0; i < src.GetCount(); i++) {
		const Cookie& src_cookie = src[i];
		bool is_replacing = false, exists = false;
		for(int j = 0; j < cookies.GetCount(); j++) {
			Cookie& dst_cookie = cookies[j];
			if (dst_cookie == src_cookie)
				exists = true;
			else if (dst_cookie.Replace(src_cookie)) {
				is_replacing = true;
				is_modified = true;
			}
		}
		if (!is_replacing && !exists) {
			cookies.Add(src_cookie);
			is_modified = true;
		}
	}
	if (is_modified)
		StoreThis();
	cookie_lock.Leave();
	
}

void Resources::FillCookies(String base_addr, Vector<Cookie>& cookies) {
	cookie_lock.Enter();
	cookies <<= site_cookies.GetAdd(base_addr);
	cookie_lock.Leave();
}











ResourceCache::ResourceCache() {
	
}

int ResourceCache::FindObject(String image, String base_url) {
	String id = base_url + "|" + image;
	lock.EnterRead();
	int i = site_objects.Find(id);
	lock.LeaveRead();
	return i;
}

CacheObject& ResourceCache::GetObject(int cache_id) {
	lock.EnterRead();
	CacheObject* obj = &site_objects[cache_id];
	lock.LeaveRead();
	return *obj;
}

int ResourceCache::AddObject(String image, String base_url) {
	String id = base_url + "|" + image;
	lock.EnterWrite();
	int i = site_objects.Find(id);
	if (i == -1) {
		i = site_objects.GetCount();
		site_objects.Add(id);
	}
	lock.LeaveWrite();
	return i;
}

NAMESPACE_LAYOUT_END
