#include "uppweb.h"

FileTime CachedTopic::lastchange = 0;

void CachedTopic::Read(const char* text) {
	CParser p(text);
	try {
		if(p.Id("topic")) {
			topic.title = p.ReadString();
			p.Char(';');
			topic.text = p.GetPtr();
			parsed = ::ParseQTF(topic.text);
			return;
		}
		while(!p.IsEof()) {
			if(p.Id("TITLE")) {
				p.PassChar('(');
				topic.title = p.ReadString();
				p.PassChar(')');
			}
			else
			if(p.Id("REF")) {
				p.PassChar('(');
				p.ReadString();
				p.PassChar(')');
			}
			else
			if(p.Id("TOPIC_TEXT")) {
				p.PassChar('(');
				topic.text << p.ReadString();
				p.PassChar(')');
			}
			else
			if(p.Id("COMPRESSED")) {
				StringBuffer b;
				b.Reserve(1024);
				while(p.IsInt()) {
					b.Cat(p.ReadInt());
					p.PassChar(',');
				}
				topic.text = b;
			}
			else {
				topic.text << p.GetPtr();
				break;
			}
		}
	}
	catch(CParser::Error e) {
		topic.text = String::GetVoid();
		topic.title = e;
	}
	parsed = ::ParseQTF(topic.text);
}

const RichText& CachedTopic::ParseQTF() const {
	return parsed;
}


const CachedTopic& ReadTopic(const String& fn){
	static VectorMap<String, CachedTopic> cache;
	int q = cache.Find(fn);
	if (q >= 0)
		return cache[q];
	CachedTopic& t = cache.Add(fn);
	t.Read(LoadFile(fn));
	return t;
}

struct predicate {
	SkylarkCacheMaker& m;
	predicate(SkylarkCacheMaker& maker) : m(maker) {};
	inline bool operator()(const SkylarkCacheItem& item) {
		return m.hash == item.hash &&
			IsValueMap(item.user_data) && IsValueMap(m.user_data) &&
			item.user_data["TIME"].Is<Time>() && Time(m.user_data["TIME"]) >= Time(item.user_data["TIME"]) &&
			item.user_data["FILE"].Is<String>() && String(m.user_data["FILE"]) == String(item.user_data["FILE"]);
	}
};

void ServeTopic(String file, Http& http, bool serve){
	//parse language
	String language = ParseLanguage(http);
	
	SkylarkCacheMaker maker(http);
	
	//find file in proper language
	String topicfile(file);
	topicfile.Replace("en-us", language);
	if(!FileExists(topicfile))
		topicfile = file;
	
	//caching
	ValueMap data;
	data.Set("FILE", file);
	data.Set("TIME", (Time)GetFileTime(file));
	maker.SetUserData(data);
	predicate p(maker);
	if (serve && GetFromCache(maker, p))
		return;
	
	//read topic && encode html
	Index<String> css;
	VectorMap<String, String> links;
	VectorMap<String, String> labels;
	VectorMap<String, String> escape;
	const String outdir = ((uppweb&)SkylarkApp::TheApp()).basedir;
	const String basename = "/static/" + MD5String(file);
	
	SetEscapes(escape);
	CachedRefLinks(links, labels);
	
	const CachedTopic& t = ReadTopic(topicfile);
	String content = EncodeHtml(t.ParseQTF(), css, links, labels, outdir, basename, Zoom(8, 40), escape, 40);
	http("CONTENT", Raw(content))
	    ("CSS", Raw(AsCss(css)))
	    ("TOPIC", t.topic.title);
	
	if(serve){
		http.RenderResult("base");
		InsertToCache(maker);
	}
}
