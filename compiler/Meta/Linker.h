#ifndef _Meta_Linker_h_
#define _Meta_Linker_h_

NAMESPACE_TOPSIDE_BEGIN


class Linker : public ErrorSource {
	const Object* obj = NULL;
	
public:
	typedef Linker CLASSNAME;
	Linker();
	
	void Add(const CompilationUnit& unit);
	bool Link();
	const Object& GetObject() const {return *obj;}
	
};


NAMESPACE_TOPSIDE_END

#endif
