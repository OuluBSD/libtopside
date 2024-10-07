#include "OrgLib.h"


BEGIN_TEXTLIB_NAMESPACE


CppFileWriter::CppFileWriter() {
	
}

void CppFileWriter::WriteHeader(Node& n, const String& h_path, const Vector<String>& inc_strs) {
	FileOut s(h_path);
	
	String name = n.name;
	String h_name = "_" + name + "_" + name + "_h_";
	
	s << "#ifndef " << h_name << "\n"
		 << "#define " << h_name << "\n\n\n";
	
	for(int i = 0; i < inc_strs.GetCount(); i++) {
		String inc = inc_strs[i];
		if (inc == "time")
			inc = "ctime";
		
		s << "#include <" << inc << ">\n";
	}
	
	if (inc_strs.GetCount())
		s << "using namespace std;\n\n";
	
	if (n.type == NODE_CLASS) {
		s << GetClassHeaderString(n);
		s << "\n\n";
	}
	else if (n.type == NODE_PACKAGE) {
		Vector<Node*> classes;
		n.FindChildDeep(classes, NODE_CLASS);
		
		for(int i = 0; i < classes.GetCount(); i++) {
			Node& cls = *classes[i];
			s << "#include \"" << cls.name << ".h\"\n";
		}
		
		s << "\n\n";
		
		Vector<Node*> funcs;
		n.FindChildDeep(funcs, NODE_FUNCTION);
		
		for(int i = 0; i < funcs.GetCount(); i++) {
			Node& fn = *funcs[i];
			s << GetFunctionHeaderString(fn);
			s << "\n";
		}
		
		s << "\n\n";
		
	}
	else TODO
	
	s << "#endif\n";
}

void CppFileWriter::WriteImplementation(Node& n, const String& path, const String& incl_file) {
	FileOut s(path);
	
	String name = n.name;
	
	if (incl_file.GetCount())
		s << "#include \"" << incl_file << "\"\n\n";
	
	
	if (n.type == NODE_CLASS) {
		s << GetClassImplString(n);
		s << "\n\n";
	}
	else if (n.type == NODE_PACKAGE) {
		Vector<Node*> classes;
		n.FindChildDeep(classes, NODE_CLASS);
		
		#if 0
		for(int i = 0; i < classes.GetCount(); i++) {
			Node& cls = *classes[i];
			s << GetClassImplString(cls);
			s << "\n\n";
		}
		
		s << "\n\n";
		#endif
		
		Vector<Node*> funcs;
		n.FindChildDeep(funcs, NODE_FUNCTION);
		
		for(int i = 0; i < funcs.GetCount(); i++) {
			Node& fn = *funcs[i];
			s << GetFunctionImplString(fn, 0);
			s << "\n";
		}
		
		s << "\n\n";
		
	}
	else TODO
	
}

String CppFileWriter::GetFunctionHeaderString(Node& n) {
	String s;
	s << n.data.GetAdd("ret") << " ";
	s << n.name;
	
	s << "(";
	ValueArray& params = ValueToArray(n.data.GetAdd("params"));
	for(int i = 0; i < params.GetCount(); i++) {
		ValueMap& p = ValueToMap(params.At(i));
		String name = p.GetAdd("name");
		String type = p.GetAdd("type");
		if (i) s << ", ";
		s << type << " " << name;
	}
	s << ")";
	
	s << ";";
	return s;
}

String CppFileWriter::GetFunctionImplString(Node& n, Node* cls_path) {
	String s;
	String ret = n.data.GetAdd("ret");
	s << ret << " ";
	if (cls_path)
		s << cls_path->name << "::";
	s << n.name;
	
	s << "(";
	ValueArray& params = ValueToArray(n.data.GetAdd("params"));
	for(int i = 0; i < params.GetCount(); i++) {
		ValueMap& p = ValueToMap(params.At(i));
		String name = p.GetAdd("name");
		String type = p.GetAdd("type");
		if (i) s << ", ";
		s << type << " " << name;
	}
	s << ")";
	
	s << " {\n";
	
	s << "\t\n";
	if (ret != "void")
		s << "\treturn " << ret << "();\n";
	s << "}\n\n";
	
	return s;
}

String CppFileWriter::GetClassHeaderString(Node& n) {
	String s;
	
	s << "class " << n.name << " {\n";
	s << "public:\n";
	s << "\n";
	
	Vector<Node*> funcs;
	n.FindChildDeep(funcs, NODE_FUNCTION);
	
	for(int i = 0; i < funcs.GetCount(); i++) {
		Node& fn = *funcs[i];
		
		s << "\t";
		s << GetFunctionHeaderString(fn);
		s << "\n";
	}
	
	s << "\n";
	s << "};\n\n";
	
	return s;
}

String CppFileWriter::GetClassImplString(Node& n) {
	String s;
	
	Vector<Node*> funcs;
	n.FindChildDeep(funcs, NODE_FUNCTION);
	
	for(int i = 0; i < funcs.GetCount(); i++) {
		Node& fn = *funcs[i];
		
		s << GetFunctionImplString(fn, &n);
		s << "\n";
	}
	
	return s;
}


END_TEXTLIB_NAMESPACE
