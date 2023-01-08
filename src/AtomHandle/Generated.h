#ifndef _AtomHandle_Generated_h_
#define _AtomHandle_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagSCREEN
class HandleProgEvents : public HandleEventsBase {

public:
	RTTI_DECL1(HandleProgEvents, HandleEventsBase)
	COPY_PANIC(HandleProgEvents)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSCREEN
class PipeProgVideo : public HandleVideoBase {

public:
	RTTI_DECL1(PipeProgVideo, HandleVideoBase)
	COPY_PANIC(PipeProgVideo)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSCREEN
class HandleProgVideo : public HandleVideoBase {

public:
	RTTI_DECL1(HandleProgVideo, HandleVideoBase)
	COPY_PANIC(HandleProgVideo)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

}

}
#endif
