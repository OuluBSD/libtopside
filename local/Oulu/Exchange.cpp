#include "Oulu.h"

NAMESPACE_OULU_BEGIN





bool ExchangeSourceProvider::Link(Sink sink, Cookie& src_c, Cookie& sink_c) {
	if (Accept(sink, src_c, sink_c)) {
		base.AddLink(sink);
		sink->base.AddLink(this);
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

void ExchangePoint::Set(ExchangeSourceProviderRef src, ExchangeSinkProviderRef sink, ExchangeProviderCookieRef sink_cookie, ExchangeProviderCookieRef src_cookie) {
	Clear();
	this->src_cookie	= src_cookie;
	this->sink_cookie	= sink_cookie;
	this->src	= src;
	this->sink	= sink;
	src->AddSink(sink);
	sink->AddSource(src);
}












MetaExchangePoint::MetaExchangePoint() {
	
}

/*void MetaExchangePoint::Init(ConnectorBase* comp) {
	this->comp = comp;
	
}*/

String MetaExchangePoint::ToString() const {
	
	TODO
	
}

ExchangePointRef MetaExchangePoint::Add() {
	ExchangePointRef pt = pts.Add();
	
	return pt;
}

void MetaExchangePoint::UnlinkAll() {
	pts.Clear();
}


NAMESPACE_OULU_END
