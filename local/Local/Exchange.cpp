#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN



void RealtimeSourceConfig::Update(double dt, bool buffer_full) {
	sync_age += dt;
	
	this->dt += dt;
	++src_frame;
	
	if (enable_sync && sync_age >= sync_dt) {
		if (sync_age > 2 * sync_dt)
			sync_age = sync_dt;
		else
			sync_age = Modulus(sync_age, sync_dt);
		
		last_sync_src_frame = src_frame;
		
		frames_after_sync = 0;
		sync = true;
		
		render = true;
	}
	else if (!buffer_full) {
		sync = false;
		frames_after_sync = src_frame > last_sync_src_frame ? src_frame - last_sync_src_frame : 0;
		
		render = true;
	}
	else {
		render = false;
	}
}



ExchangeBase::ExchangeBase() {
	//DBG_CONSTRUCT
}

ExchangeBase::~ExchangeBase() {
	//DBG_DESTRUCT
}
	






#ifdef flagDEBUG
bool ExchangeSourceProvider::print_debug = true;
#else
bool ExchangeSourceProvider::print_debug = false;
#endif



void ExchangeSourceProvider::Link(ExchangePointRef expt, SinkProv sink, Cookie& src_c, Cookie& sink_c) {
	ASSERT(expt);
	ASSERT_(CastPtr<LockedScopeRefCounter>(this) != CastPtr<LockedScopeRefCounter>(&*sink), "Linking to itself is not allowed");
	base.SetLink(expt, sink);
	sink->base.SetLink(expt, AsRefT());
	if (print_debug) {
		String s;
		s << GetRTTI().GetDynamicName() <<
			"<" << GetConfigString() << "> linked to " <<
			sink->GetRTTI().GetDynamicName() <<
			"<" << sink->GetConfigString() << ">";
		LOG(s);
	}
	OnLink(sink, src_c, sink_c);
	sink->OnLink(AsRefT(), src_c, sink_c);
}











ExchangeSinkProvider::ExchangeSinkProvider() {
	DBG_CONSTRUCT
}

ExchangeSinkProvider::~ExchangeSinkProvider() {
	DBG_DESTRUCT
}







ExchangeSourceProvider::ExchangeSourceProvider() {
	DBG_CONSTRUCT
}

ExchangeSourceProvider::~ExchangeSourceProvider() {
	DBG_DESTRUCT
}








void FwdScope::Clear() {
	cur = 0;
	for(int i = 0; i < QUEUE_SIZE; i++)
		next[i] = 0;
	read_i = 0;
	write_i = 0;
	cfg = 0;
	first = 0;
	is_failed = false;
}

void FwdScope::Forward() {
	if (cur) {
		int pos = read_i-1;
		RTLOG("FwdScope::Forward: " << pos << " (at " << cur->GetDynamicName() << ")");
		cur->ForwardSetup(*this);
		cur->Forward(*this);
		cur->ForwardExchange(*this);
	}
}

void FwdScope::AddNext(PacketForwarder* cb) {
	if (cb) {
		ASSERT_(cb != cur, "Duplicate forward is not allowed");
		if (!first)
			first = cb;
		//else if (cb == first)
		//	return;
		int prev_write_i = write_i > 0 ? write_i - 1 : QUEUE_SIZE-1;
		if (next[prev_write_i] == cb)
			return;
		ASSERT(!next[write_i]);
		next[write_i] = cb;
		write_i = (write_i + 1) % QUEUE_SIZE;
	}
}

void FwdScope::ActivateNext() {
	cur = next[read_i];
	next[read_i] = 0;
	read_i = (read_i + 1) % QUEUE_SIZE;
}











ExchangePoint::ExchangePoint() {
	DBG_CONSTRUCT
}

ExchangePoint::~ExchangePoint() {
	DBG_DESTRUCT
}

void ExchangePoint::Clear() {
	src.Clear();
	sink.Clear();
	src_cookie.Clear();
	sink_cookie.Clear();
}

void ExchangePoint::Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink) {
	Clear();
	this->src	= src;
	this->sink	= sink;
	ExchangePointRef thisref = AsRef<ExchangePoint>();
	src->SetSink(thisref, sink);
	sink->SetSource(thisref, src);
}

void ExchangePoint::Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink, CookieRef sink_cookie, CookieRef src_cookie) {
	Clear();
	this->src_cookie	= src_cookie;
	this->sink_cookie	= sink_cookie;
	this->src	= src;
	this->sink	= sink;
	ASSERT(src->IsSink(sink));
	ASSERT(sink->IsSource(src));
}

void ExchangePoint::Destroy() {
	ASSERT(meta_expt);
	meta_expt->Remove(this);
}












MetaExchangePoint::MetaExchangePoint() {
	DBG_CONSTRUCT
}

MetaExchangePoint::~MetaExchangePoint() {
	DBG_DESTRUCT
}

String MetaExchangePoint::ToString() const {
	String s = GetDynamicName();
	s << " [expts: " << pts.GetCount() << "]";
	return s;
}

void MetaExchangePoint::Remove(ExchangePoint* expt) {
	for (auto iter = pts.begin(); iter; ++iter) {
		if (*iter == expt) {
			pts.Remove(iter);
			return;
		}
	}
	THROW(Exc("MetaExchangePoint::Remove: internal error"));
}

void MetaExchangePoint::UnlinkAll() {
	pts.Clear();
}

ExchangePointRef MetaExchangePoint::Add(TypeCls expt) {
	const auto& m = ExptDataMap();
	const auto& d = m.Get(expt);
	ExchangePoint* o = d.new_fn();
	pts.Add(o);
	o->SetParent(this);
	o->meta_expt = AsRefT();
	return o->AsRefT();
}











NAMESPACE_TOPSIDE_END
