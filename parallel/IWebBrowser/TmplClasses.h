// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IWebBrowser_TmplClasses_h_
#define _IWebBrowser_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Web> struct WebBrowserWebBrowserT;


template <class Web>
struct WebBrowserWebBrowserT : WebWebBrowser {
	using CLASSNAME = WebBrowserWebBrowserT<Web>;
	RTTI_DECL1(CLASSNAME, WebWebBrowser)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<WebWebBrowser>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

