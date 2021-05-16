#ifndef _ProtoGrammar_Bootstrap_h_
#define _ProtoGrammar_Bootstrap_h_


NAMESPACE_TOPSIDE_BEGIN


class BootstrapGenerator {
	
	
public:
	typedef BootstrapGenerator CLASSNAME;
	BootstrapGenerator();
	
	bool Process(String title, const ParsingUnit& pu);
	
};




struct ReduceTemplate : Moveable<ReduceTemplate> {
	String func_name;
	String pre_func;
	VectorMap<String, Value> func_args;
	Vector<Value> content;
	
	ReduceTemplate();
	void Dump(String key);
};

typedef VectorMap<String, VectorMap<int, ReduceTemplate> > ReduceMap;


class MultiValuePrinter {
	VectorMap<String, Value> map;
	const ReduceTemplate* rt = 0;
	
	void Add(String key, Value value);
public:
	MultiValuePrinter();
	
	void Init(const ReduceTemplate& rt);
	
	String ExportDeclarations(int indent);
	String ExportVisit(int indent);
	String ExportCall(int indent);
	
};

class ReduceParser {
	CParser p;
	String err;
	ReduceMap& tmpls;
	ReduceTemplate* tmpl = 0;
	
	void FileInput();
	void Statement();
	void Key();
	void Function();
	void FunctionArguments();
	void FunctionArgument();
	void ReadValue(ValueArray& arr);
	void ReturnContent();
	
public:
	typedef ReduceParser CLASSNAME;
	ReduceParser(ReduceMap& tmpls);
	
	bool Parse(String content);
	void DumpErrors();
	
};

class MetaBootstrapGenerator {
	ReduceMap tmpls;
	
	void Parse(String path);
	
public:
	typedef MetaBootstrapGenerator CLASSNAME;
	MetaBootstrapGenerator();
	
	bool Process(String title, const ParsingUnit& pu);
	
};


NAMESPACE_TOPSIDE_END


#endif
