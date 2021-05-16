#ifndef _CoreAlt_Internet_h_
#define _CoreAlt_Internet_h_


NAMESPACE_UPP



struct HttpCookie : Moveable<HttpCookie> {
	String id;
	String value;
	String domain;
	String path;
	String raw;

	void Clear();
	bool Parse(const String& cookie);
};


struct HttpHeader {
	String                        first_line;
	String                        f1, f2, f3;
	VectorMap<String, String>     fields;
	VectorMap<String, HttpCookie> cookies;
	bool                          scgi;
	
	String operator[](const char *id) const                  { return fields.Get(id, Null); }
	String GetCookie(const char *id) const;

	bool   Response(String& protocol, int& code, String& reason) const;
	bool   Request(String& method, String& uri, String& version) const;
	
	String GetProtocol() const                               { return f1; }
	int    GetCode() const;
	String GetReason() const                                 { return f3; }
	
	String GetMethod() const                                 { return f1; }
	String GetURI() const                                    { return f2; }
	String GetVersion() const                                { return f3; }

	bool   HasContentLength() const;
	int64  GetContentLength() const;

	void   Clear();
	bool   ParseAdd(const String& hdrs);
	bool   Parse(const String& hdrs);
	bool   ParseSCGI(const String& scgi_hdr);

	bool   Read(TcpSocket& socket);
	
	HttpHeader()                                             { scgi = false; }

private:
	void   Add(const String& id, const String& value);
	HttpHeader(const HttpHeader&);
};


class HttpRequest {
	
	
public:
	typedef HttpRequest CLASSNAME;
	HttpRequest();
	
	
	HttpRequest&		UserAgent(String s);
	HttpRequest&		Cookie(HttpCookie& c);
	HttpRequest&		Method(int i);
	HttpRequest&		PostData(String s);
	HttpRequest&		Url(String url);
	HttpRequest&		Trace(bool b=true);
	
	String				Execute();
	String				GetRedirectUrl();
	int					GetStatusCode() const;
	const HttpHeader&	GetHttpHeader() const;
	
};

END_UPP_NAMESPACE


#endif
