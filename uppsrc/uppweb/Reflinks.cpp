#include "uppweb.h"

StaticCriticalSection     reflink_lock;

struct ScanTopicIterator : RichText::Iterator {
	String link;
	VectorMap<String, String>& reflink;

	ScanTopicIterator(VectorMap<String, String>& reflink_):reflink(reflink_){};

	virtual bool operator()(int pos, const RichPara& para)
	{
		if(!IsNull(para.format.label)) {
			INTERLOCKED_(reflink_lock)
				reflink.Add(para.format.label, link);
		}
		return false;
	}
};

void GatherRefLinks(const char *upp, VectorMap<String, String>& reflink, Vector<String>& topics){
	RTIMING("GatherRefLinks");
	for(FindFile pff(AppendFileName(upp, "*.*")); pff; pff.Next()) {
		if(pff.IsFolder()) {
			String package = pff.GetName();
			String pdir = AppendFileName(upp, package);
			TopicLink tl;
			tl.package = package;
			for(FindFile ff(AppendFileName(pdir, "*.tpp")); ff; ff.Next()) {
				if(ff.IsFolder()) {
					String group = GetFileTitle(ff.GetName());
					tl.group = group;
					String dir = AppendFileName(pdir, ff.GetName());
					for(FindFile ft(AppendFileName(dir, "*.tpp")); ft; ft.Next()) {
						if(ft.IsFile()) {
							String path = AppendFileName(dir, ft.GetName());
							tl.topic = GetFileTitle(ft.GetName());
							String link = TopicLinkString(tl);
							topics.Add(link);
							ScanTopicIterator sti(reflink);
							sti.link = link;
							ReadTopic(path).parsed.Iterate(sti);
						}
					}
				}
			}
		}
	}
}

int CharFilterLbl(int c){
	return IsAlNum(c) ? c : '_';
}

bool ContainsAt(const String &source, const String &pattern, int pos)
{
	return    pos >= 0
	       && pos + pattern.GetLength() <= source.GetLength()
	       && 0 == memcmp(source.Begin() + pos, pattern.Begin(), pattern.GetLength());
}
bool EndsWith(const String &source, const String &pattern)
{
	return ContainsAt(source, pattern, source.GetLength() - pattern.GetLength());
}

String TopicFileNameHtml(const char *topic){
	TopicLink tl = ParseTopicLink(topic);
	tl.package.Replace("\\","/");
	int n = tl.topic.Find('$');
	if (n>0)
		tl.topic.Trim(n);
	return "/topic/" + tl.package +  "/" + tl.group + "/" + tl.topic;
}


void RefLinks(VectorMap<String,String>& links,VectorMap<String,String>& labels){
	RTIMING("RefLinks");
	VectorMap<String, String> reflink;
	Vector<String> topics;
	GatherRefLinks(TRUNK+"/uppsrc", reflink, topics);
	GatherRefLinks(TRUNK+"/bazaar", reflink, topics);
	GatherRefLinks(TRUNK+"/uppbox", reflink, topics);
	
	{RTIMING("links.add");
	for(int i = 0; i < topics.GetCount(); i++) {
		const String& topic = topics[i];
		String& s= links.Add(topic, memcmp(topic, "topic://", 8) ? topic : TopicFileNameHtml(topic));
	}}
	
	VectorMap<String,String>& menulinks = ((uppweb*)&SkylarkApp::TheApp())->menulinks;
	for(int i = 0; i < menulinks.GetCount(); i++){
		links.GetAdd(menulinks.GetKey(i)) = menulinks[i];
	}
	
	RTIMING("labels");
	for(int i = 0; i < reflink.GetCount(); i++) {
		String l = reflink.GetKey(i);
		String lbl = Filter(l, CharFilterLbl);
		String f = links.Get(reflink[i], Null) + '#' + lbl;
		links.Add(l, f);
		static const char *x[] = { "::struct", "::class", "::union" };
		for(int ii = 0; ii < 3; ii++) {
			String e = x[ii];
			if(EndsWith(l, e)) {
				links.Add(l.Mid(0, l.GetLength() - e.GetLength()), f);
			}
		}
		labels.Add(l, lbl);
	}
}

void CachedRefLinks(VectorMap<String,String>& links, VectorMap<String,String>& labels) {
	RTIMING("CachedRefLinks");
	static Time t;
	static VectorMap<String,String> lnks;
	static VectorMap<String,String> lbls;
	
	if(t < CachedTopic::lastchange) {
		lnks.Clear();
		lbls.Clear();
		RefLinks(lnks,lbls);
		t=GetSysTime().AsFileTime();
	}
	links = VectorMap<String,String>(lnks,1);
	labels = VectorMap<String,String>(lbls,1);
}
