// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 12:22:22

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

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};


NAMESPACE_PARALLEL_END



#endif

