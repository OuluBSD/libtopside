#ifndef _ToyHub_Request_h_
#define _ToyHub_Request_h_


NAMESPACE_TOYHUB_BEGIN


class OverlayRequest {
	int id = -1;
	String request, cookie, content;
	
	
	void Request0();
	
public:
	typedef OverlayRequest CLASSNAME;
	OverlayRequest(int id);
	
	void Request(String request, String cookie);
	void Request(ValueMap request, String cookie) {Request(AsJSON(request), cookie);}
	
	int GetId() const {return id;}
	String GetContent() const {return content;}
	ValueMap GetContentJson() const {return ParseJSON(content);}
	
	operator int () const {return id;}
	
	Callback WhenSuccess, WhenFail, WhenReady;
};

OverlayRequest& NewRequest();
OverlayRequest& GetRequest(int id);



String HandleRequest(String request, String cookie);


NAMESPACE_TOYHUB_END

#endif
