#ifndef _TemplatesMach_PacketBuffer_h_
#define _TemplatesMach_PacketBuffer_h_

NAMESPACE_ECS_BEGIN


struct TrackerInfo {
	const RTTI* handler_cls = 0;
	const char* handler_fn = 0;
	const char* file = 0;
	int line = 0;
	
	TrackerInfo() {}
	TrackerInfo(const TrackerInfo& i) {*this = i;}
	TrackerInfo(const RTTI& o) {handler_cls = &o;}
	template <class T> TrackerInfo(const T* o) {handler_cls = &o->GetRTTI();}
	template <class T> TrackerInfo(const T* o, const char* file, int line) : handler_cls(&o->GetRTTI()), file(file), line(line) {}
	TrackerInfo(const char* fn, const char* file, int line) : handler_fn(fn), file(file), line(line) {}
	
	void operator=(const TrackerInfo& i) {
		handler_cls = i.handler_cls;
		handler_fn = i.handler_fn;
		file = i.file;
		line = i.line;
	}
	
	
	String ToString() const;
};




NAMESPACE_ECS_END

#endif
