#ifndef _Oulu_Exchange_h_
#define _Oulu_Exchange_h_


NAMESPACE_OULU_BEGIN



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

class AudioEx : public ExchangeBase {
	bool storing = false;
	
public:
	
	virtual bool IsLoading() {return !storing;}
	virtual bool IsStoring() {return storing;}
	
	virtual bool Load(int sample_rate, int channels, int var_size, bool var_float, byte* data) {SetFail(); return false;}
	
};

class VideoEx : public ExchangeBase {
	bool storing = false;
	
public:
	
	virtual bool IsLoading() {return !storing;}
	virtual bool IsStoring() {return storing;}
	
};





class ExchangeProviderCookie : public LockedScopeEnabler<ExchangeProviderCookie> {
	
	
public:
	
};

typedef Ref<ExchangeProviderCookie> ExchangeProviderCookieRef;





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
	ExchangeProviderCookieRef	src_cookie;
	ExchangeProviderCookieRef	sink_cookie;
	
public:
	typedef ExchangePoint CLASSNAME;
	ExchangePoint();
	
	void Clear();
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink);
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink, ExchangeProviderCookieRef sink_cookie, ExchangeProviderCookieRef src_cookie);
	
	
	ExchangeSourceProviderRef Source() {return src;}
	ExchangeSinkProviderRef Sink() {return sink;}
	ExchangeProviderCookieRef SourceCookie() {return src_cookie;}
	ExchangeProviderCookieRef SinkCookie() {return sink_cookie;}
	
};




class MetaExchangePoint {
	
protected:
	RefLinkedList<ExchangePoint> pts;
	
public:
	typedef MetaExchangePoint CLASSNAME;
	MetaExchangePoint();
	virtual ~MetaExchangePoint() {}
	
	virtual void UnlinkAll();
	
	ExchangePointRef Add();
	
	String ToString() const;
	
	
};


NAMESPACE_OULU_END


#endif
