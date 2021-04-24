#include "ToyHub.h"

NAMESPACE_TOYHUB_BEGIN

ArrayMap<int, OverlayRequest> requests;
int request_counter;

OverlayRequest& NewRequest() {
	int id = request_counter++;
	return requests.Add(id, new OverlayRequest(id));
}

OverlayRequest& GetRequest(int id) {
	int i = requests.Find(id);
	if (i == -1) throw Exc("Request not found");
	return requests[i];
}



OverlayRequest::OverlayRequest(int id) {
	this->id = id;
}

void OverlayRequest::Request(String request, String cookie) {
	this->request = request;
	this->cookie = cookie;
	Thread::Start(THISBACK(Request0));
}


void OverlayRequest::Request0() {
	#ifdef flagSTANDALONE
	static StaticMutex lock;
	lock.Enter();
	content = HandleRequest(request, cookie);
	lock.Leave();
	WhenReady();
	WhenSuccess();
	#else
	
	Panic("TODO");
	
	
	#endif
}



String HandleRequest(String request, String cookie) {
	ValueMap ans_vm;
	
	try {
		ValueMap req_vm = ParseJSON(request);
		
		if (cookie.IsEmpty()) {
			cookie = NewCookie();
			ans_vm.Add("cookie", cookie);
		}
		
		String request_type = req_vm.GetAdd("request");
		
		if (request_type == "page-md") {
			int hub_id = req_vm.GetAdd("hub");
			String title = req_vm.GetAdd("title");
			
			Hub hub;
			Page page;
			if (hub.Load(hub_id) && page.Load(hub, title)) {
				int rev_id = page.GetLatestRevision();
				
				Revision rev;
				if (rev.Load(rev_id)) {
					int64 text_id = rev.GetText();
					String content = LoadText(text_id);
					ans_vm.Add("content", content);
					ans_vm.Add("type", "md");
				}
			}
		}
		
		else if (request_type == "page-html") {
			int hub_id = req_vm.GetAdd("hub");
			String title = req_vm.GetAdd("title");
			
			Hub hub;
			Page page;
			if (hub.Load(hub_id) && page.Load(hub, title)) {
				String content = LoadHtmlFile(page);
				ans_vm.Add("content", content);
				ans_vm.Add("type", "html");
			}
		}
		
	}
	catch (Exc e) {
		LOG(e);
	}
	catch (...) {
		
	}
	
	return AsJSON(ans_vm);
}


NAMESPACE_TOYHUB_END
