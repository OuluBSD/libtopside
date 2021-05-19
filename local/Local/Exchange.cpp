#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN



void RealtimeSourceConfig::Update(double dt, bool buffer_full) {
	sync_age += dt;
	
	this->dt += dt;
	++src_frame;
	
	if (sync_age >= sync_dt) {
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



void ExchangeSourceProvider::Link(ExchangePointRef expt, Sink sink, Cookie& src_c, Cookie& sink_c) {
	ASSERT(expt);
	base.AddLink(expt, sink);
	sink->base.AddLink(expt, AsRefT());
	if (print_debug) {
		TypeId src_type = GetProviderType();
		TypeId sink_type = sink->GetProviderType();
		String s;
		s << src_type.CleanDemangledName() <<
			"<" << GetConfigString() << "> linked to " <<
			sink_type.CleanDemangledName() <<
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
	src->AddSink(thisref, sink);
	sink->AddSource(thisref, src);
}

void ExchangePoint::Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink, CookieRef sink_cookie, CookieRef src_cookie) {
	Clear();
	this->src_cookie	= src_cookie;
	this->sink_cookie	= sink_cookie;
	this->src	= src;
	this->sink	= sink;
	ASSERT(src->FindSink(sink) >= 0);
	ASSERT(sink->FindSource(src) >= 0);
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

/*void MetaExchangePoint::Init(ConnectorBase* comp) {
	this->comp = comp;
	
}*/

String MetaExchangePoint::ToString() const {
	
	TODO
	
}

void MetaExchangePoint::Remove(ExchangePoint* expt) {
	for (auto iter = pts.begin(); iter; ++iter) {
		if (*iter == expt) {
			pts.Remove(iter);
			return;
		}
	}
	throw Exc("MetaExchangePoint::Remove: internal error");
}

void MetaExchangePoint::UnlinkAll() {
	pts.Clear();
}











NAMESPACE_TOPSIDE_END
