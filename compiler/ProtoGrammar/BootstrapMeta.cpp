#include "Grammar.h"

NAMESPACE_TOPSIDE_BEGIN

MultiValuePrinter::MultiValuePrinter() {
	
}

void MultiValuePrinter::Init(const ReduceTemplate& rt) {
	this->rt = &rt;
	for(int i = 0; i < rt.func_args.GetCount(); i++)
		Add(rt.func_args.GetKey(i), rt.func_args[i]);
	for(int i = 0; i < rt.content.GetCount(); i++)
		Add("content" + IntStr(i), rt.content[i]);
}

void MultiValuePrinter::Add(String key, Value value) {
	map.Add(key, value);
}

String MultiValuePrinter::ExportDeclarations(int indent) {
	String s;
	if (map.GetCount()) {
		s.Cat('\t', indent);
		s << "Recycler<NodeVec> ";
		for(int i = 0; i < map.GetCount(); i++) {
			String key = map.GetKey(i);
			Value value = map[i];
			
			if (i) s << ", ";
			s << key << "(pool)";
		}
		s << ";\n";
		
		
		for(int i = 0; i < map.GetCount(); i++) {
			String key = map.GetKey(i);
			Value value = map[i];
			ValueArray arr = value;
			
			s.Cat('\t', indent);
			s << "static int " << key << "_count = " << arr.GetCount() << ";\n";
			
			s.Cat('\t', indent);
			s << "static int " << key << "_pos_i[] = {";
			for(int j = 0; j < arr.GetCount(); j++) {
				if (j) s << ", ";
				Value v = arr[j];
				if (v.Is<int>())
					s << v.ToString();
				else
					s << "-1";
			}
			s << "};\n";
			
			
			s.Cat('\t', indent);
			s << "static int " << key << "_pos_type[] = {";
			for(int j = 0; j < arr.GetCount(); j++) {
				if (j) s << ", ";
				Value v = arr[j];
				if (v.Is<String>()) {
					String type = v.ToString();
					String caps = ToCaps(type);
					if (type == "__all__")
						s << "-2";
					else if (type == "__name__")
						s << "-3";
					else
						s << "Meta::NODE_" << caps;
				}
				else
					s << "-1";
			}
			s << "};\n";
		}
	}
	return s;
}

String MultiValuePrinter::ExportVisit(int indent) {
	String s;
	
	if (rt->pre_func.GetCount()) {
		s.Cat('\t', indent);
		s << rt->pre_func << "();\n";
	}
	
	if (map.GetCount()) {
		for(int i = 0; i < map.GetCount(); i++) {
			String key = map.GetKey(i);
			
			s.Cat('\t', indent);
			s << "if (!Visit(n, *"
			  << key << ", "
			  << key << "_pos_i" << ", "
			  << key << "_pos_type" << ", "
			  << key << "_count)) return 0;\n";
		}
	}
	return s;
}

String MultiValuePrinter::ExportCall(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "return " << rt->func_name << "(";
	if (map.GetCount()) {
		for(int i = 0; i < map.GetCount(); i++) {
			String key = map.GetKey(i);
			if (i) s << ", ";
			s << "*" << key;
		}
	}
	s << ");\n";
	return s;
}










ReduceParser::ReduceParser(ReduceMap& tmpls) : tmpls(tmpls) {
	
}

bool ReduceParser::Parse(String content) {
	tmpls.Clear();
	tmpl = 0;
	p.Set(content);
	try {
		FileInput();
		return true;
	}
	catch (Exc e) {
		err = e;
		return false;
	}
}

void ReduceParser::FileInput() {
	while (!p.IsEof()) {
		Statement();
	}
}

void ReduceParser::Statement() {
	Key();
}

void ReduceParser::Key() {
	String key = p.ReadId();
	p.PassChar(',');
	int block = p.ReadInt();
	p.PassChar('=');
	tmpl = &tmpls.GetAdd(key).Add(block);
	Function();
	p.PassChar(';');
}

void ReduceParser::Function() {
	if (p.Char('<'))
		tmpl->pre_func = p.ReadId();
	
	if (!p.IsId()) p.ThrowError("Expected id");
	tmpl->func_name = p.ReadId();
	
	if (p.IsChar('<'))
		FunctionArguments();
	
	ReturnContent();
}

void ReduceParser::FunctionArguments() {
	p.PassChar('<');
	do {
		FunctionArgument();
	}
	while (p.Char(','));
	p.PassChar('>');
}

void ReduceParser::FunctionArgument() {
	String key = p.ReadId();
	p.PassChar('=');
	
	ValueArray value;
	ReadValue(value);
	
	tmpl->func_args.Add(key, value);
}

void ReduceParser::ReadValue(ValueArray& arr) {
	p.PassChar('[');
	do {
		if (p.Char('*'))
			arr.Add("__all__");
		else if (p.IsId())
			arr.Add(p.ReadId());
		else
			arr.Add(p.ReadInt());
	}
	while (p.Char(','));
	p.PassChar(']');
}

void ReduceParser::ReturnContent() {
	p.PassChar('(');
	if (!p.IsChar(')')) {
		do {
			ValueArray arr;
			ReadValue(arr);
			tmpl->content.Add(arr);
		}
		while (p.Char(','));
	}
	p.PassChar(')');
}

void ReduceParser::DumpErrors() {
	if (err.GetCount())
		LOG("ReduceParser: error: " << err);
}



ReduceTemplate::ReduceTemplate() {
	
}

void ReduceTemplate::Dump(String key) {
	LOG(key << ":");
	LOG("\tname: " << func_name);
	if (func_args.GetCount()) {
		LOG("\targs:");
		for(int i = 0; i < func_args.GetCount(); i++) {
			String s("\t\t");
			s << func_args.GetKey(i) << ": ";
			Value v = func_args[i];
			if (v.Is<ValueArray>()) {
				s << "[";
				ValueArray arr = v;
				for(int j = 0; j < arr.GetCount(); j++) {
					if(j) s << ",";
					s << arr[j].ToString();
				}
				s << "]";
			}
			else {
				s << v.ToString();
			}
			LOG(s);
		}
	}
	
	LOG("\tcontent:");
	for(int i = 0; i < content.GetCount(); i++) {
		Value v = content[i];
		LOG("\t\t" << v.ToString());
	}
}





MetaBootstrapGenerator::MetaBootstrapGenerator() {
	
	Parse(GetDataFile("MetaSimplifier.g"));
	
}

void MetaBootstrapGenerator::Parse(String path) {
	String content = LoadFile(path);
	
	ReduceParser p(tmpls);
	
	if (!p.Parse(content)) {
		p.DumpErrors();
		Panic("Parsing failed");
	}
}

bool MetaBootstrapGenerator::Process(String title, const ParsingUnit& pu) {
	String c_out, h_out;
	//c_out << "#if 0\n";
	c_out << "#ifndef flagBOOTSTRAP\n";
	c_out << "#include \"Grammar.h\"\n\nNAMESPACE_TOPSIDE_BEGIN\n\n";
	
	String cls_name = title + "Simplifier";
	
	
	
	h_out << "Ast::Node* VisitNode(const Node& n);\n\n";
	c_out << "Ast::Node* " << cls_name << "::VisitNode(const Node& n) {\n";
	c_out << "\tswitch(n.GetType()) {\n";
	
	for(int i = 0; i < tmpls.GetCount(); i++) {
		String name = tmpls.GetKey(i);
		String caps_name = ToCaps(name);
		
		c_out << "\t\tcase Meta::NODE_" << caps_name << ": return " << name << "(n);\n";
	}
	c_out << "\t\tcase NODE_TOKEN: return AstToken(n);\n";
	c_out << "\t\tdefault: break;\n";
	c_out << "\t}\n";
	c_out << "\tPushError(\"Invalid node type \" + IntStr(n.GetType()));\n";
	c_out << "\treturn 0;\n";
	c_out << "}\n\n";
	
	
	
	for(int i = 0; i < tmpls.GetCount(); i++) {
		String name = tmpls.GetKey(i);
		String caps_name = ToCaps(name);
		const VectorMap<int, ReduceTemplate>& rtvec = tmpls[i];
		
		h_out << "Ast::Node* " << name << "(const Node& n);\n";
			
		c_out << "Ast::Node* " << cls_name << "::" << name << "(const Node& n) {\n";
		c_out << "\tASSERT_TYPE(n, Meta::NODE_" << caps_name << ");\n";
		c_out << "\tREF_BLOCK;\n";
		
		for(int j = 0; j < rtvec.GetCount(); j++) {
			int block = rtvec.GetKey(j);
			const ReduceTemplate& rt = rtvec[j];
			
			MultiValuePrinter mvp;
			mvp.Init(rt);
			
			if (!j) {
				c_out << "\tif (IS_BLOCK(" << block << ")) {\n";
			}
			else {
				c_out << "\telse if (IS_BLOCK(" << block << ")) {\n";
			}
			
			c_out << mvp.ExportDeclarations(2);
			c_out << mvp.ExportVisit(2);
			c_out << mvp.ExportCall(2);
			
			
			c_out << "\t}\n";
		}
		
		c_out << "\telse {PushError(\"Unimplemented block\"); return 0;}\n";
		
		
		c_out << "}\n\n";
	}
	
	
	c_out << "}\n\n#endif\n\n";
	
	
	
	FileOut file_h_out(GetDataFile("Generated_" + title + "Simplifier.inl"));
	FileOut file_c_out(GetDataFile("Generated_" + title + "Simplifier.cpp"));
	
	file_h_out << h_out;
	file_c_out << c_out;
	
	file_h_out.Close();
	file_c_out.Close();
	
	return true;
}


NAMESPACE_TOPSIDE_END
