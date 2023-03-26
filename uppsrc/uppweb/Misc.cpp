#include "uppweb.h"

String GetDescription(const String& upp){
	String s = LoadFile(upp);
	String description;
	CParser p(s);
	try {
		while(!p.IsEof()) {
			if(p.Id("description")) {
				description = p.ReadString();
				const char *q = strchr(description, 255);
				if(q)
					description = String(~description, q);
				break;
			} else
				p.SkipTerm();
		}
	} catch (...) {
		LOG("Error in upp parsing");
	}
	return description;
}


void SetEscapes(VectorMap<String,String>& escape){
	//TODO: This should be global variable, refreshed periodically
	String release = "5485";
	escape.Add("RELEASE", release);
	escape.Add("RELEASET", release);
	escape.Add("UPDATETIME", Format("%`", GetUtcTime()));
	escape.Add("LATESTSVN", "TODO");
	escape.Add("PAYPAL", LoadFile(TRUNK+"/uppbox/uppweb/donations.txt"));
}


void GetDocs(const String& name, ValueMap& pkgs, Index<String>& x){
	if(x.Find(name) >= 0)
		return;
	x.Add(name);
	ValueMap pkg;
	ValueMap docs;
	bool hasDocs = false;
	String upp = AppendFileName(TRUNK+"/uppsrc/"+name, name+".upp");
	pkg.Add("DESCRIPTION", GetDescription(upp));
	for(FindFile ff(TRUNK+"/uppsrc/"+name+"/srcdoc.tpp/*_en-us.tpp"); ff; ff.Next()){
		String n = ff.GetName();
		n.Trim(n.GetCount()-10);
		docs.Add(ReadTopic(ff.GetPath()).topic.title, Format("/topic/%s/srcdoc/%s", name, n));
	}
	if(docs.GetCount()){
		pkg.Add("SRCDOC", docs);
		hasDocs = true;
		docs.Clear();
	}
	for(FindFile ff(TRUNK+"/uppsrc/"+name+"/src.tpp/*_en-us.tpp"); ff; ff.Next()){
		String n = ff.GetName();
		n.Trim(n.GetCount()-10);
		docs.Add(ReadTopic(ff.GetPath()).topic.title, Format("/topic/%s/src/%s", name, n));
	}
	if(docs.GetCount()){
		pkg.Add("SRC", docs);
		hasDocs = true;
	}
	if(hasDocs)
		pkgs.Add(name, pkg);
}

void Sources(const String& nest, const String& pkg, Http& http){
	const char* types[] = {
		"h", "hpp", "cpp", "icpp", "witz", "usc",
		"lay", "key", "brc", "sch", "xml"
	};
	ValueMap vm;
	for(int i = 0; i < 11; i++){
		for(FindFile ff(TRUNK+nest+"/"+pkg+"/*."+String(types[i])); ff; ff.Next()){
			ValueMap src;
			src.Add("TYPE",types[i]);
			src.Add("CODE",LoadFile(ff.GetPath()));
			vm.Add(ff.GetName(), src);
		}
	}
	http("SOURCES", vm);
	http.RenderResult("uppweb/sources");
}

String ParseLanguage(Http& http) {
	String language = http["lang"];
	if (!language.IsEmpty())
		http.SetCookie("lang", language);
	else {
		language = http["@lang"];
		if (language.IsEmpty())
			language = "en-us";
	}
	int lang = LNGFromText(language);
	
	// set renderer language (but not into session, we have cookie)
	((Renderer*)&http)->SetLanguage(lang);
	SetLanguage(lang);
	
	return language;
}
