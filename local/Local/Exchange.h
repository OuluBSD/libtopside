#ifndef _Local_Exchange_h_
#define _Local_Exchange_h_


NAMESPACE_TOPSIDE_BEGIN


class Entity;
class ExchangeBase;
class ExchangeProviderBase;
class ExchangeSinkProvider;
class ExchangeSourceProvider;
class ExchangeProviderCookie;
class ExchangePoint;
class MetaExchangePoint;
class Pool;
class ComponentBase;
using ExchangeBaseRef				= Ref<ExchangeBase,				RefParent1<ExchangeProviderBase>>;
using ExchangeProviderBaseRef		= Ref<ExchangeProviderBase,		RefParent1<Entity>>;
using ExchangeSinkProviderRef		= Ref<ExchangeSinkProvider,		RefParent1<Entity>>;
using ExchangeSourceProviderRef		= Ref<ExchangeSourceProvider,	RefParent1<Entity>>;
using CookieRef						= Ref<ExchangeProviderCookie,	RefParent1<ExchangePoint>>;
using ExchangePointRef				= Ref<ExchangePoint,			RefParent1<MetaExchangePoint>>;
using MetaExchangePointRef			= Ref<MetaExchangePoint,		RefParent1<Pool>>;


template<class T>
struct OffsetLoop {
	using limits = std::numeric_limits<T>;
	
	T value = 0;
	
	
	//OffsetLoop() {}
	//OffsetLoop(T value) : value(value) {}
	
	void Clear() {value = 0;}
	bool operator==(const OffsetLoop& o) const {return o.value == value;}
	bool operator!=(const OffsetLoop& o) const {return o.value != value;}
	void operator+=(const OffsetLoop& o) {value += o.value;}
	void operator-=(const OffsetLoop& o) {value -= o.value;}
	void operator++() {++value;}
	operator bool() const {return value;}
	
	void SetMax() {value = limits::max();}
	void SetMin() {value = limits::min();}
	void TestSetMin(OffsetLoop v) {if (v.value < value) value = v.value;}
	void TestSetMax(OffsetLoop v) {if (v.value > value) value = v.value;}
	
	String ToString() const {return Upp::AsString(value);}
	
	
	static OffsetLoop GetDifference(OffsetLoop min, OffsetLoop max) {
		OffsetLoop ret;
		if (min != max)
			ret.value =
				min.value < max.value ?
					max.value - min.value :
					ret.value = limits::max() - min.value + 1 + max.value - limits::min();
		return ret;
	}
	
	
};

using off32 = OffsetLoop<dword>;




struct RealtimeSourceConfig {
	double dt = 0;
	double sync_dt = 3.0;
	double sync_age = 0;
    dword last_sync_src_frame = 0;
	dword frames_after_sync = 0;
	dword src_frame = 0;
	bool sync = 0;
	bool render = 0;
	off32 begin_offset, end_offset;
	
	void Update(double dt, bool buffer_full);
	void SetOffset(off32 begin, off32 end) {begin_offset = begin; end_offset = end;}
};

#define MIN_AUDIO_BUFFER_SAMPLES 1024





class ExchangeBase :
	public RefScopeEnabler<ExchangeBase,ExchangeProviderBase>
{
	bool fail = false;
	
protected:
	
	
public:
	RTTI_DECL_R0(ExchangeBase)
	ExchangeBase();
	virtual ~ExchangeBase();
	
	
	virtual bool IsLoading() {return false;}
	virtual bool IsStoring() {return false;}
	
	bool IsFail() const {return fail;}
	void SetFail() {fail = true;}
	void ClearFail() {fail = false;}
};













class ExchangeProviderCookie :
	public RefScopeEnabler<ExchangeProviderCookie,ExchangePoint>
{
	
public:
	RTTI_DECL_R0(ExchangeProviderCookie)
	
	
};






template <class R>
class ExchangeProviderT {
	
public:
	
	struct Link :
		Moveable<Link>,
		RTTIBase
	{
		RTTI_DECL0(Link)
		
		ExchangePointRef expt;
		R dst;
		
		template <class K> Ref<K> As() const {return dst;}
		template <class K> operator Ref<K>() const {return dst;}
		void Visit(RuntimeVisitor& vis) {vis & expt & dst;}
	};
	
private:
	LinkedList<Link> links;
	bool multi_conn = false;
	
protected:
	friend class ExchangeSinkProvider;
	friend class ExchangeSourceProvider;
	int FindLink(R r) const {
		int i = 0;
		LinkedList<Link>& links = const_cast<LinkedList<Link>&>(this->links);
		for(auto iter = links.begin(); iter; ++iter) {
			if (iter().dst == r)
				return i;
			++i;
		}
		return -1;
	}
	void AddLink(ExchangePointRef expt, R r) {
		ASSERT(FindLink(r) < 0);
		ASSERT(links.IsEmpty() || multi_conn);
		Link& l = links.Add();
		l.expt = expt;
		l.dst = r;
	}
	
	LinkedList<Link>& GetConnections() {return links;}
	
public:
	
	void Visit(RuntimeVisitor& vis) {for (auto iter = links.begin(); iter; ++iter) vis % iter();}
	void SetMultiConnection(bool b) {multi_conn = b;}
	const LinkedList<Link>& GetConnections() const {return links;}
	
	void Unlink(R o) {
		for(auto iter = links.begin(); iter; ++iter) {
			Link& l = iter();
			if (l.dst == o) {
				l.expt->Destroy();
				links.Remove(iter);
				break;
			}
		}
	}
	
	void UnlinkAll() {
		links.Clear();
	}
};


class ExchangeProviderBase :
	public RefScopeEnabler<ExchangeProviderBase,Entity>
{
	
public:
	RTTI_DECL_R0(ExchangeProviderBase)
	
	//bool UnlinkManually(ExchangeProviderBase& p);
	virtual TypeId GetProviderType() = 0;
	virtual String GetConfigString() {return String();}
	
};


class ExchangeSinkProvider :
	public ExchangeProviderBase
{
	
protected:
	friend class ExchangeSourceProvider;
	
	using ExProv = ExchangeProviderT<ExchangeSourceProviderRef>;
	
	ExProv base;
	
public:
	using SinkProv = ExchangeSinkProviderRef;
	using SourceProv = ExchangeSourceProviderRef;
	using Cookie = CookieRef;
	RTTI_DECL1(ExchangeSinkProvider, ExchangeProviderBase)
	
protected:
	friend class ExchangePoint;
	
	void AddSource(ExchangePointRef expt, ExchangeSourceProviderRef src) {base.AddLink(expt, src);}
	int FindSource(ExchangeSourceProviderRef src) {return base.FindLink(src);}
	virtual void OnLink(SourceProv src, Cookie src_c, Cookie sink_c) {}
	
public:
	ExchangeSinkProvider();
	virtual ~ExchangeSinkProvider();
	
	
	void SetMultiConnection(bool b=true) {base.SetMultiConnection(b);}
	void UnlinkAll() {base.UnlinkAll();}
	void Unlink(SourceProv src) {base.Unlink(src);}
	void Visit(RuntimeVisitor& vis) {base.Visit(vis);}
	
	const LinkedList<ExProv::Link>& GetConnections() const {return base.GetConnections();}
	
};



class ExchangeSourceProvider :
	public ExchangeProviderBase
{
	using ExProv = ExchangeProviderT<ExchangeSinkProviderRef>;
	
	ExProv base;
	
	static bool print_debug;
	
public:
	using SinkProv = ExchangeSinkProviderRef;
	using SourceProv = ExchangeSourceProviderRef;
	using Cookie = CookieRef;
	RTTI_DECL1(ExchangeSourceProvider, ExchangeProviderBase)
	
protected:
	friend class ExchangePoint;
	
	void AddSink(ExchangePointRef expt, ExchangeSinkProviderRef sink) {base.AddLink(expt, sink);}
	int FindSink(ExchangeSinkProviderRef sink) {return base.FindLink(sink);}
	virtual void OnLink(SinkProv sink, Cookie src_c, Cookie sink_c) {}
	
public:
	ExchangeSourceProvider();
	virtual ~ExchangeSourceProvider();
	
	
	virtual bool Accept(SinkProv sink, Cookie& src_c, Cookie& sink_c) {return true;}
	void Link(ExchangePointRef expt, SinkProv sink, Cookie& src_c, Cookie& sink_c);
	void SetMultiConnection(bool b=true) {base.SetMultiConnection(b);}
	void UnlinkAll() {base.UnlinkAll();}
	void Unlink(SinkProv sink) {base.Unlink(sink);}
	void Visit(RuntimeVisitor& vis) {base.Visit(vis);}
	
	const LinkedList<ExProv::Link>& GetConnections() const {return base.GetConnections();}
	
};

typedef ExchangeSourceProviderRef ExchangeSourceProviderRef;





class ExchangePoint :
	public RefScopeEnabler<ExchangePoint,MetaExchangePoint>
{
	
protected:
	friend class MetaExchangePoint;
	
	MetaExchangePointRef		meta_expt;
	ExchangeSourceProviderRef	src;
	ExchangeSinkProviderRef		sink;
	CookieRef					src_cookie;
	CookieRef					sink_cookie;
	
public:
	RTTI_DECL_R0(ExchangePoint)
	typedef ExchangePoint CLASSNAME;
	ExchangePoint();
	virtual ~ExchangePoint();
	
	virtual void Update(double dt) = 0;
	
	void Clear();
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink);
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink, CookieRef sink_cookie, CookieRef src_cookie);
	void Destroy();
	void Visit(RuntimeVisitor& vis) {vis & meta_expt & src & sink & src_cookie & sink_cookie;}
	
	ExchangeSourceProviderRef Source() {return src;}
	ExchangeSinkProviderRef Sink() {return sink;}
	CookieRef SourceCookie() {return src_cookie;}
	CookieRef SinkCookie() {return sink_cookie;}
	
};




class MetaExchangePoint :
	public RefScopeEnabler<MetaExchangePoint,Pool>
{
	
protected:
	RefLinkedListIndirect<ExchangePoint> pts;
	
public:
	RTTI_DECL_R0(MetaExchangePoint)
	typedef MetaExchangePoint CLASSNAME;
	MetaExchangePoint();
	virtual ~MetaExchangePoint();
	
	virtual void UnlinkAll();
	
	template <class T>
	Ref<T> Add(T* o=NULL) {
		if (!o)
			o = new T();
		pts.Add(o);
		o->SetParent(this);
		o->meta_expt = AsRefT();
		return o->AsRefT();
	}

	void Remove(ExchangePoint* expt);
	
	String ToString() const;
	
	void Visit(RuntimeVisitor& vis) {vis || pts;}
	
};


NAMESPACE_TOPSIDE_END


#endif
