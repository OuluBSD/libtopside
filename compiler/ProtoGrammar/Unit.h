#ifndef _Parser_Unit_h_
#define _Parser_Unit_h_

NAMESPACE_TOPSIDE_BEGIN


class ParsingUnit : public ErrorSourceBuffered {
	UppProject* prj = NULL;
	UppAssembly* as = NULL;
	
	
	
	void OnMessage(ProcMsg msg);
	
public:
	typedef ParsingUnit CLASSNAME;
	
	ParsingUnit();
	
	//bool Load(UppProject& prj, UppAssembly& as);
	bool LoadFile(String filepath);
	
	void Dump();
	
	
	One<Node> root;
	
};


NAMESPACE_TOPSIDE_END

#endif
