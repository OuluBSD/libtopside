#ifndef _uppweb_uppweb_h
#define _uppweb_uppweb_h

#include <SkylarkCache/SkylarkCache.h>
#include <RichText/RichText.h>

using namespace Upp;

#define TRUNK ((uppweb&)SkylarkApp::TheApp()).srcdir

struct CachedTopic : public Moveable<CachedTopic> {
	static FileTime lastchange;
	FileTime time;
	RichText parsed;
	Topic topic;

	void Read(const char* text);
	const RichText& ParseQTF() const;
	CachedTopic(){ time.ft=0; }
};

// Reflinks.cpp
void CachedRefLinks(VectorMap<String,String>& links,VectorMap<String,String>& labels);

// Topics.cpp
const CachedTopic& ReadTopic(const String& fn);
void ServeTopic(String file, Http& http, bool serve = true);

// Misc.cpp
String GetDescription(const String& upp);
void SetEscapes(VectorMap<String,String>& escape);
void GetDocs(const String& name, ValueMap& pkgs, Index<String>& x);
void Sources(const String& nest, const String& pkg, Http& http);
String ParseLanguage(Http& http);

class uppweb : public SkylarkApp {
public:
	typedef uppweb CLASSNAME;
	uppweb();
	String basedir;
	String srcdir;
	VectorMap<String,String> menu;
	VectorMap<String,String> menulinks;
};

#endif
