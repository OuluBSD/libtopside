#ifndef _Oulu_Exchange_h_
#define _Oulu_Exchange_h_


NAMESPACE_OULU_BEGIN



struct RealtimeSourceConfig {
	double dt = 0;
	double sync_dt = 0;
	double sync_age = 0;
    dword last_sync_src_frame = 0;
	dword frames_after_sync = 0;
	dword src_frame = 0;
	bool sync = 0;
	bool render = 0;
	
	void Update(double dt, bool buffer_full);
};






class ExchangeBase : public LockedScopeEnabler<ExchangeBase> {
	bool fail = false;
	
protected:
	
	
public:
	virtual ~ExchangeBase() {}
	
	
	virtual bool IsLoading() {return false;}
	virtual bool IsStoring() {return false;}
	
	bool IsFail() const {return fail;}
	void SetFail() {fail = true;}
	void ClearFail() {fail = false;}
};

typedef Ref<ExchangeBase> ExchangeBaseRef;







class SemanticEx : public ExchangeBase {
	
	
};


class Audio;
class AudioExchangePoint;

class AudioEx : public ExchangeBase {
	bool storing = false;
	AudioExchangePoint* expt = 0;
	Audio* src = 0;
	Audio* sink = 0;
	const RealtimeSourceConfig* src_conf = 0;
	
public:
	AudioEx(AudioExchangePoint* expt) : expt(expt) {}
	
	Audio& Sink() const {return *sink;}
	Audio& Source() const {return *src;}
	const RealtimeSourceConfig& SourceConfig() const {return *src_conf;}
	
	void SetLoading(Audio& src, const RealtimeSourceConfig& conf) {storing = false; this->src = &src; this->sink = 0; src_conf = &conf;}
	void SetStoring(Audio& sink, const RealtimeSourceConfig& conf) {storing = true; this->src = 0; this->sink = &sink; src_conf = &conf;}
	
	AudioExchangePoint& GetExchangePoint() {return *expt;}
	
	virtual bool IsLoading() {return !storing;}
	virtual bool IsStoring() {return storing;}
	
	
};


class Video;
class VideoExchangePoint;

class VideoEx : public ExchangeBase {
	bool storing = false;
	VideoExchangePoint* expt = 0;
	Video* src = 0;
	Video* sink = 0;
public:
	VideoEx(VideoExchangePoint* expt) : expt(expt) {}
	
	void SetLoading(Video& src) {storing = false; this->src = &src; this->sink = 0;}
	void SetStoring(Video& sink) {storing = true; this->src = 0; this->sink = &sink;}
	
	VideoExchangePoint& GetExchangePoint() {return *expt;}
	
	virtual bool IsLoading() {return !storing;}
	virtual bool IsStoring() {return storing;}
	
};





class ExchangeProviderCookie : public LockedScopeEnabler<ExchangeProviderCookie> {
	
	
public:
	
};

typedef Ref<ExchangeProviderCookie> CookieRef;





class ExchangeProviderBase;
class ExchangePoint;
typedef Ref<ExchangePoint> ExchangePointRef;
typedef Ref<ExchangeProviderBase> ExchangeProviderBaseRef;



template <class T>
class ExchangeProviderT {
	using R = Ref<T>;
	Vector<R> links;
	bool multi_conn = false;
	
protected:
	friend class ExchangeSinkProvider;
	friend class ExchangeSourceProvider;
	int FindLink(R r) {
		int i = 0;
		for(R& l : links) {
			if (l == r)
				return i;
			++i;
		}
		return -1;
	}
	void AddLink(Ref<ExchangeProviderBase> link) {
		R r = link;
		ASSERT(FindLink(r) < 0);
		ASSERT(links.IsEmpty() || multi_conn);
		links << r;
	}
	
public:
	
	void SetMultiConnection(bool b) {
		multi_conn = b;
	}
	void UnlinkAll() {
		TODO
	}
	
	const Vector<R>& GetConnections() const {return links;}
	
};


class ExchangeProviderBase : public LockedScopeEnabler<ExchangeProviderBase> {
	
public:
	
	bool UnlinkManually(ExchangeProviderBase& p);
	virtual TypeId GetProviderType() = 0;
	virtual String GetConfigString() {return String();}
	
};

class ExchangeSourceProvider;

class ExchangeSinkProvider : public ExchangeProviderBase {
	
protected:
	friend class ExchangeSourceProvider;
	
	ExchangeProviderT<ExchangeSourceProvider> base;
	
public:
	using Sink = Ref<ExchangeSinkProvider>;
	using Source = Ref<ExchangeSourceProvider>;
	using Cookie = Ref<ExchangeProviderCookie>;
	
protected:
	friend class ExchangePoint;
	
	void AddSource(Ref<ExchangeSourceProvider> src) {base.AddLink(src);}
	int FindSource(Ref<ExchangeSourceProvider> src) {return base.FindLink(src);}
	virtual void OnLink(Source src, Cookie src_c, Cookie sink_c) {}
	
public:
	
	virtual ~ExchangeSinkProvider() {}
	
	
	void SetMultiConnection(bool b=true) {base.SetMultiConnection(b);}
	void UnlinkAll() {base.UnlinkAll();}
	void Unlink(Source src);
	
	const Vector<Source>& GetConnections() const {return base.GetConnections();}
	
};

typedef Ref<ExchangeSinkProvider> ExchangeSinkProviderRef;


class ExchangeSourceProvider : public ExchangeProviderBase {
	ExchangeProviderT<ExchangeSinkProvider> base;
	
	static bool print_debug;
	
public:
	using Sink = Ref<ExchangeSinkProvider>;
	using Source = Ref<ExchangeSourceProvider>;
	using Cookie = Ref<ExchangeProviderCookie>;
	
protected:
	friend class ExchangePoint;
	
	void AddSink(Ref<ExchangeSinkProvider> sink) {base.AddLink(sink);}
	int FindSink(Ref<ExchangeSinkProvider> sink) {return base.FindLink(sink);}
	virtual bool Accept(Sink sink, Cookie& src_c, Cookie& sink_c) {return true;}
	virtual void OnLink(Sink sink, Cookie src_c, Cookie sink_c) {}
	
public:
	
	virtual ~ExchangeSourceProvider() {}
	
	
	bool Link(Sink sink, Cookie& src_c, Cookie& sink_c);
	void SetMultiConnection(bool b=true) {base.SetMultiConnection(b);}
	void UnlinkAll() {base.UnlinkAll();}
	void Unlink(Sink sink);
	
	const Vector<Sink>& GetConnections() const {return base.GetConnections();}
	
};

typedef Ref<ExchangeSourceProvider> ExchangeSourceProviderRef;





class ExchangePoint : public LockedScopeEnabler<ExchangePoint> {
	
protected:
	friend class MetaExchangePoint;
	
	ExchangeSourceProviderRef	src;
	ExchangeSinkProviderRef		sink;
	CookieRef					src_cookie;
	CookieRef					sink_cookie;
	
public:
	typedef ExchangePoint CLASSNAME;
	ExchangePoint();
	
	virtual ~ExchangePoint() {}
	
	virtual void Update(double dt) = 0;
	
	void Clear();
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink);
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink, CookieRef sink_cookie, CookieRef src_cookie);
	
	
	ExchangeSourceProviderRef Source() {return src;}
	ExchangeSinkProviderRef Sink() {return sink;}
	CookieRef SourceCookie() {return src_cookie;}
	CookieRef SinkCookie() {return sink_cookie;}
	
};




class MetaExchangePoint {
	
protected:
	RefLinkedListIndirect<ExchangePoint> pts;
	
public:
	typedef MetaExchangePoint CLASSNAME;
	MetaExchangePoint();
	virtual ~MetaExchangePoint() {}
	
	virtual void UnlinkAll();
	
	template <class T>
	Ref<T> Add(T* o=NULL) {
		if (!o)
			o = new T();
		Ref<T> pt = pts.Add(o);
		
		return pt;
	}

	
	String ToString() const;
	
	
};


NAMESPACE_OULU_END


#endif
