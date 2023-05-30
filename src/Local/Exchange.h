#ifndef _Local_Exchange_h_
#define _Local_Exchange_h_


NAMESPACE_TOPSIDE_BEGIN


class ExchangeBase;
class ExchangeProviderBase;
class ExchangeSinkProvider;
class ExchangeSourceProvider;
class ExchangeSideSinkProvider;
class ExchangeSideSourceProvider;
class ExchangeProviderCookie;
class ExchangePoint;
class MetaDirectoryBase;
class MetaSpaceBase;
class MetaSystemBase;
class MetaMachineBase;

using MetaSystemParent				= RefParent1<MetaMachineBase>;
using ExBaseParent					= RefParent1<MetaSpaceBase>;
using HierExBaseParent				= RefParent2<MetaSystemBase, MetaSpaceBase>;
using DirExBaseParent				= RefParent2<MetaSystemBase, MetaDirectoryBase>;
using ExchangeBaseParent			= RefParent1<MetaSpaceBase>;

using ExchangeBaseRef				= Ref<ExchangeBase,					ExchangeBaseParent>;
using ExchangeProviderBaseRef		= Ref<ExchangeProviderBase,			ExBaseParent>;
using ExchangeSinkProviderRef		= Ref<ExchangeSinkProvider,			ExBaseParent>;
using ExchangeSourceProviderRef		= Ref<ExchangeSourceProvider,		ExBaseParent>;
using ExchangeSideSinkProviderRef	= Ref<ExchangeSideSinkProvider,		ExBaseParent>;
using ExchangeSideSourceProviderRef	= Ref<ExchangeSideSourceProvider,	ExBaseParent>;
using ExchangePointRef				= Ref<ExchangePoint,				RefParent1<MetaSpaceBase>>;
using CookieRef						= Ref<ExchangeProviderCookie,		RefParent1<ExchangePoint>>;


template<class T> class OffsetGen;


template<class T>
struct OffsetLoop {
	using limits = std::numeric_limits<T>;
	using Gen = OffsetGen<T>;
	
	Gen* gen;
	T value;
	
	
	//OffsetLoop() {}
	//OffsetLoop(T value) : value(value) {}
	OffsetLoop(Gen* g, T value) : gen(g), value(value) {}
	OffsetLoop(Gen* g) : gen(g), value(0) {}
	OffsetLoop(Gen& g) : gen(&g), value(0) {}
	OffsetLoop(const OffsetLoop& o) {*this = o;}
	
	OffsetLoop& operator=(const OffsetLoop& o) {gen = o.gen; value = o.value; return *this;}
	
	void Clear() {value = 0;}
	bool operator==(const OffsetLoop& o) const {return o.value == value;}
	bool operator!=(const OffsetLoop& o) const {return o.value != value;}
	void operator+=(const OffsetLoop& o) {value += o.value;}
	void operator-=(const OffsetLoop& o) {value -= o.value;}
	bool operator< (const OffsetLoop& o) {return value <  o.value;}
	bool operator<=(const OffsetLoop& o) {return value <= o.value;}
	bool operator>=(const OffsetLoop& o) {return value >= o.value;}
	bool operator> (const OffsetLoop& o) {return value >  o.value;}
	
	OffsetLoop& operator++() {++value; return *this;}
	OffsetLoop operator++(int) {return OffsetLoop(gen, value++);}
	operator bool() const {return value;}
	operator T() const {return value;}
	
	void SetMax() {value = limits::max();}
	void SetMin() {value = limits::min();}
	void TestSetMin(OffsetLoop v) {if (v.value < value) value = v.value;}
	void TestSetMax(OffsetLoop v) {if (v.value > value) value = v.value;}
	
	String ToString() const {return UPP::AsString(value);}
	
	
	static OffsetLoop GetDifference(OffsetLoop min, OffsetLoop max) {
		OffsetLoop ret(min.gen, 0);
		if (min != max)
			ret.value =
				min.value < max.value ?
					max.value - min.value :
					ret.value = limits::max() - min.value + 1 + max.value - limits::min();
		return ret;
	}
	
	static int64 GetDifferenceI64(OffsetLoop overflow_anchor, OffsetLoop min, OffsetLoop max) {
		int64 anchor = overflow_anchor.value;
		int64 a = (int64)min.value;
		int64 b = (int64)max.value;
		if (b < anchor)
			b += (int64)limits::max() - (int64)limits::min();
		return b - a;
	}
	
};

template<class T>
class OffsetGen {
	using Offset = OffsetLoop<T>;
	
	Offset value;
public:
	
	OffsetGen() : value(this) {}
	
	Offset Create() {return ++value;}
	Offset GetCurrent() const {return value;}
	
	String ToString() const {return "gen(" + value.ToString() + ")";}
	
	//operator Offset() {return ++value;}
};


using off32 = OffsetLoop<dword>;
using off32_gen = OffsetGen<dword>;





struct RealtimeSourceConfig {
	double time_delta = 0;
	double time_total = 0;
	double sync_dt = 3.0;
	double sync_age = 0;
    dword last_sync_src_frame = 0;
	dword frames_after_sync = 0;
	dword src_frame = 0;
	bool enable_sync = false;
	bool sync = 0;
	bool render = 0;
	off32 cur_offset, prev_offset;
	
	
	RealtimeSourceConfig(off32_gen& gen) : cur_offset(gen), prev_offset(gen) {}
	
	void Update(double dt, bool buffer_full);
	//void SetOffset(off32 begin, off32 end) {begin_offset = begin; end_offset = end;}
};

using RTSrcConfig = RealtimeSourceConfig;

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
class ExchangeProviderT : RTTIBase {
	using ExchangeProviderTmpl = ExchangeProviderT<R>;
	
private:
	ExchangePointRef expt;
	R dst;
	
protected:
	friend class ExchangeSinkProvider;
	friend class ExchangeSourceProvider;
	friend class ExchangeSideSinkProvider;
	friend class ExchangeSideSourceProvider;
	
	int IsLink(R r) const {return r == dst;}
	
	void SetLink(ExchangePointRef expt, R dst) {
		ASSERT_(!this->dst, "Link is already set");
		this->expt = expt;
		this->dst = dst;
	}
	
	
public:
	RTTI_DECL0(ExchangeProviderTmpl);
	void Visit(RuntimeVisitor& vis) {(vis & expt) & dst;}
	
	
	void				ClearLink() {expt.Clear(); dst.Clear();}
	ExchangePointRef	GetExPt() const {return expt;}
	R					GetLink() const {return dst;}
	
};


class ExchangeProviderBase :
	public RefScopeEnabler<ExchangeProviderBase, MetaSpaceBase>
{
	
public:
	RTTI_DECL_R0(ExchangeProviderBase)
	
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
	
	void SetSource(ExchangePointRef expt, ExchangeSourceProviderRef src) {base.SetLink(expt, src);}
	int IsSource(ExchangeSourceProviderRef src) {return base.IsLink(src);}
	
	virtual void OnLink(SourceProv src, Cookie src_c, Cookie sink_c) {}
	
public:
	ExchangeSinkProvider();
	virtual ~ExchangeSinkProvider();
	
	void						ClearLink() {base.ClearLink();}
	void						Visit(RuntimeVisitor& vis) {vis % base;}
	ExchangePointRef			GetExPt() const {return base.GetExPt();}
	ExchangeSourceProviderRef	GetSinkLink() const {return base.GetLink();}
	
};



class ExchangeSourceProvider :
	public ExchangeProviderBase
{
public:
	using ExProv = ExchangeProviderT<ExchangeSinkProviderRef>;
	
private:
	ExProv base;
	
	static bool print_debug;
	
public:
	using SinkProv = ExchangeSinkProviderRef;
	using SourceProv = ExchangeSourceProviderRef;
	using Cookie = CookieRef;
	RTTI_DECL1(ExchangeSourceProvider, ExchangeProviderBase)
	
protected:
	friend class ExchangePoint;
	
	void SetSink(ExchangePointRef expt, ExchangeSinkProviderRef sink) {base.SetLink(expt, sink);}
	int IsSink(ExchangeSinkProviderRef sink) {return base.IsLink(sink);}
	virtual void OnLink(SinkProv sink, Cookie src_c, Cookie sink_c) {}
	
public:
	ExchangeSourceProvider();
	virtual ~ExchangeSourceProvider();
	
	virtual bool				Accept(SinkProv sink, Cookie& src_c, Cookie& sink_c) {return true;}
	void						Link(ExchangePointRef expt, SinkProv sink, Cookie& src_c, Cookie& sink_c);
	void						ClearLink() {base.ClearLink();}
	void						Visit(RuntimeVisitor& vis) {base.Visit(vis);}
	ExchangePointRef			GetExPt() const {return base.GetExPt();}
	ExchangeSinkProviderRef		GetSourceLink() const {return base.GetLink();}
	
};

typedef ExchangeSourceProviderRef ExchangeSourceProviderRef;








class ExchangeSideSinkProvider :
	public ExchangeProviderBase
{
	
protected:
	friend class ExchangeSideSourceProvider;
	
	using ExProv = ExchangeProviderT<ExchangeSideSourceProviderRef>;
	
	ExProv base;
	
public:
	using SideSinkProv = ExchangeSideSinkProviderRef;
	using SideSourceProv = ExchangeSideSourceProviderRef;
	using Cookie = CookieRef;
	RTTI_DECL1(ExchangeSideSinkProvider, ExchangeProviderBase)
	
protected:
	friend class ExchangePoint;
	
	void SetSideSource(ExchangePointRef expt, ExchangeSideSourceProviderRef src) {base.SetLink(expt, src);}
	int IsSideSource(ExchangeSideSourceProviderRef src) {return base.IsLink(src);}
	
	virtual void OnLink(SideSourceProv src, Cookie src_c, Cookie sink_c) {}
	
public:
	ExchangeSideSinkProvider();
	virtual ~ExchangeSideSinkProvider();
	
	void							ClearLink() {base.ClearLink();}
	void							Visit(RuntimeVisitor& vis) {base.Visit(vis);}
	ExchangePointRef				GetExPt() const {return base.GetExPt();}
	ExchangeSideSourceProviderRef	GetSideSinkLink() const {return base.GetLink();}
	
};

class ExchangeSideSourceProvider :
	public ExchangeProviderBase
{
public:
	using ExProv = ExchangeProviderT<ExchangeSideSinkProviderRef>;
	
private:
	ExProv base;
	
	static bool print_debug;
	
public:
	using SideSinkProv = ExchangeSideSinkProviderRef;
	using SideSourceProv = ExchangeSideSourceProviderRef;
	using Cookie = CookieRef;
	RTTI_DECL1(ExchangeSideSourceProvider, ExchangeProviderBase)
	
protected:
	friend class ExchangePoint;
	
	void SetSideSink(ExchangePointRef expt, ExchangeSideSinkProviderRef sink) {base.SetLink(expt, sink);}
	int IsSideSink(ExchangeSideSinkProviderRef sink) {return base.IsLink(sink);}
	virtual void OnLink(SideSinkProv sink, Cookie src_c, Cookie sink_c) {}
	
public:
	ExchangeSideSourceProvider();
	virtual ~ExchangeSideSourceProvider();
	
	virtual bool					Accept(SideSinkProv sink, Cookie& src_c, Cookie& sink_c) {return true;}
	void							Link(ExchangePointRef expt, SideSinkProv sink, Cookie& src_c, Cookie& sink_c);
	void							ClearLink() {base.ClearLink();}
	void							Visit(RuntimeVisitor& vis) {base.Visit(vis);}
	ExchangePointRef				GetExPt() const {return base.GetExPt();}
	ExchangeSideSinkProviderRef		GetSideSourceLink() const {return base.GetLink();}
	
};

typedef ExchangeSideSourceProviderRef ExchangeSideSourceProviderRef;




class PacketForwarder;

class FwdScope {
	static const int QUEUE_SIZE = 16;
	PacketForwarder* next[QUEUE_SIZE];
	PacketForwarder* cur;
	PacketForwarder* first;
	int read_i, write_i;
	RealtimeSourceConfig* cfg;
	bool is_failed = false;
	bool is_break = false;
	bool is_once = false;
	bool is_looped = false;
	
public:
	
	
	FwdScope() {Clear();}
	FwdScope(PacketForwarder* cb, RealtimeSourceConfig& cfg) {Clear(); SetCfg(cfg); AddNext(cb); ActivateNext();}
	FwdScope(PacketForwarder& cb, RealtimeSourceConfig& cfg) {Clear(); SetCfg(cfg); AddNext(cb); ActivateNext();}
	
	void Clear();
	void ForwardWeak();
	void Forward();
	void ForwardAddNext();
	
	void SetCfg(RealtimeSourceConfig& cfg) {this->cfg = &cfg;}
	void SetFailed(bool b=true) {is_failed = b;}
	void SetOnce(bool b=true) {is_once = b;}
	void Break(bool b=true) {is_break = b;}
	void LoopComplete(bool b=true) {is_looped = b;}
	void AddNext(PacketForwarder& cb) {AddNext(&cb);}
	void AddNext(PacketForwarder* cb);
	void ActivateNext();
	
	bool HasCurrent() const {return !is_failed && cur != 0 && !is_looped && !is_once;}
	RealtimeSourceConfig& Cfg() {ASSERT(cfg); return *cfg;}
	bool IsFailed() const {return is_failed;}
	bool IsBreak() const {return is_break;}
	bool IsOnce() const {return is_once;}
	bool IsLoopComplete() const {return is_looped;}
	int GetPos() const {return read_i-1;}
	PacketForwarder* GetCurrent() const {return cur;}
	String GetFlagString() const;
	
	void operator++(int) {ActivateNext();}
	operator bool() const {return HasCurrent();}
	
};

class PacketForwarder :
	RTTIBase
{
public:
	RTTI_DECL0(PacketForwarder)
	virtual void ForwardSetup(FwdScope& fwd) {}
	virtual void ForwardAtom(FwdScope& fwd) {Panic("not implemented in " + String(GetDynamicName()));}
	virtual void ForwardExchange(FwdScope& fwd) {Panic("not implemented " + String(GetDynamicName()));}
	virtual bool IsPacketStuck() {Panic("not implemented " + String(GetDynamicName())); return true;}
	virtual bool IsLoopComplete(FwdScope& fwd) {Panic("not implemented " + String(GetDynamicName())); return true;}
	virtual String GetSecondaryName() {return "";}
	virtual void* GetSecondaryPtr() {return 0;}
	PacketForwarder& GetPacketForwarder() {return *this;}
	
};

class PacketForwarderData :
	RTTIBase
{
public:
	RTTI_DECL0(PacketForwarderData)
	
};

class ExchangePoint :
	virtual public PacketForwarder,
	public RefScopeEnabler<ExchangePoint,MetaSpaceBase>
{
	
protected:
	friend class MetaSpaceBase;
	
	ExchangeSourceProviderRef	src;
	ExchangeSinkProviderRef		sink;
	CookieRef					src_cookie;
	CookieRef					sink_cookie;
	
public:
	RTTI_DECL_R1(ExchangePoint, PacketForwarder)
	typedef ExchangePoint CLASSNAME;
	ExchangePoint();
	virtual ~ExchangePoint();
	
	virtual void Init(MetaSpaceBase* mdir) = 0;
	
	void Clear();
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink);
	void Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink, CookieRef sink_cookie, CookieRef src_cookie);
	void Visit(RuntimeVisitor& vis) {vis & src & sink & src_cookie & sink_cookie;}
	bool IsLoopComplete(FwdScope& fwd) override {return false;}
	
	ExchangeSourceProviderRef Source() {return src;}
	ExchangeSinkProviderRef Sink() {return sink;}
	CookieRef SourceCookie() {return src_cookie;}
	CookieRef SinkCookie() {return sink_cookie;}
	
};


class MetaMachineBase :
	public RefScopeEnabler<MetaMachineBase,RefRoot>
{
	
public:
	
};

class MetaSystemBase :
	public RefScopeEnabler<MetaSystemBase, MetaMachineBase>
{
	
public:
	virtual ~MetaSystemBase() {}
	using RScope = RefScopeEnabler<MetaSystemBase, MetaMachineBase>;
	
};

class MetaSpaceBase :
	public RefScopeEnabler<MetaSpaceBase, MetaSystemBase, RefParent2<MetaSystemBase, MetaSpaceBase>>
{
	
protected:
	RefLinkedListIndirect<ExchangePoint> pts;
	
public:
	RTTI_DECL_R0(MetaSpaceBase)
	typedef MetaSpaceBase CLASSNAME;
	MetaSpaceBase();
	virtual ~MetaSpaceBase();
	
	virtual void UnlinkAll();
	
	template <class T>
	Ref<T> Add() {
		T* o = new T();
		pts.Add(o);
		o->SetParent(this);
		return o->AsRefT();
	}

	template <class T>
	Ref<T> Add(T* o) {
		if (o) {
			pts.Add(o);
			o->SetParent(this);
			return o->AsRefT();
		}
		else return Ref<T>();
	}
	
	ExchangePointRef Add(TypeCls expt);

	//Ref<ExchangePoint> Add(TypeCls valdev_spec);
	
	void Remove(ExchangePoint* expt);
	
	String ToString() const;
	
	void Visit(RuntimeVisitor& vis) {vis || pts;}
	
	
	
public:
	
	typedef ExchangePoint* (*NewExpt)();
	struct ExptData : Moveable<ExptData> {
		NewExpt new_fn;
	};
	typedef ArrayMap<TypeCls,ExptData> ExptMap;
	static ArrayMap<TypeCls,ExptData>& ExptDataMap() {MAKE_STATIC(ExptMap, m); return m;}
	template <class T> static ExchangePoint* New() {return new T();}
	template <class T> static void RegisterExchangePoint() {
		ExptData& d = ExptDataMap().GetAdd(AsTypeCls<T>());
		d.new_fn = &New<T>;
	}
	
};

class MetaDirectoryBase :
	public RefScopeEnabler<MetaDirectoryBase, MetaSystemBase, RefParent2<MetaSystemBase, MetaDirectoryBase>>
{
	
public:
	RTTI_DECL_R0(MetaDirectoryBase)
	typedef MetaDirectoryBase CLASSNAME;
	MetaDirectoryBase();
	virtual ~MetaDirectoryBase();
	
	String ToString() const;
	
	void Visit(RuntimeVisitor& vis) {}
	
};


NAMESPACE_TOPSIDE_END


#endif
