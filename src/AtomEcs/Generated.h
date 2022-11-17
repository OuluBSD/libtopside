#ifndef _AtomEcs_Generated_h_
#define _AtomEcs_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagSCREEN
class EcsProgEvents : public EcsEventsBase {

public:
	RTTI_DECL1(EcsProgEvents, EcsEventsBase)
	COPY_PANIC(EcsProgEvents)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSCREEN
class PipeProgVideo : public EcsVideoBase {

public:
	RTTI_DECL1(PipeProgVideo, EcsVideoBase)
	COPY_PANIC(PipeProgVideo)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if defined flagSCREEN
class EcsProgVideo : public EcsVideoBase {

public:
	RTTI_DECL1(EcsProgVideo, EcsVideoBase)
	COPY_PANIC(EcsProgVideo)
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
