#include "Oulu.h"

NAMESPACE_OULU_BEGIN



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



void AudioEx::SetOffset(off32 packet_count) {
	//AUDIOLOG("AudioEx::SetOffset: offset " << packet_count.ToString());
	this->offset = packet_count;
}




#ifdef flagDEBUG
bool ExchangeSourceProvider::print_debug = true;
#else
bool ExchangeSourceProvider::print_debug = false;
#endif



bool ExchangeSourceProvider::Link(Sink sink, Cookie& src_c, Cookie& sink_c) {
	if (Accept(sink, src_c, sink_c)) {
		base.AddLink(sink);
		sink->base.AddLink(this);
		if (print_debug) {
			TypeId sink_type = sink->GetProviderType();
			TypeId src_type = sink->GetProviderType();
			String s;
			s << src_type.CleanDemangledName() <<
				"<" << GetConfigString() << "> linked to " <<
				sink_type.CleanDemangledName() <<
				"<" << sink->GetConfigString() << ">";
			LOG(s);
		}
		OnLink(sink, src_c, sink_c);
		sink->OnLink(this, src_c, sink_c);
		return true;
	}
	return false;
}

void ExchangeSourceProvider::Unlink(Sink sink) {
	
	TODO
	
}









ExchangePoint::ExchangePoint() {
	
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
	src->AddSink(sink);
	sink->AddSource(src);
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












MetaExchangePoint::MetaExchangePoint() {
	
}

/*void MetaExchangePoint::Init(ConnectorBase* comp) {
	this->comp = comp;
	
}*/

String MetaExchangePoint::ToString() const {
	
	TODO
	
}


void MetaExchangePoint::UnlinkAll() {
	pts.Clear();
}











NAMESPACE_OULU_END
