#include "IfaceCore.h"

NAMESPACE_PLAN_BEGIN

String Class::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Class " << name << "\n";
	return s;
}

String EnumValue::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "EnumValue " << name << " = " << value << "\n";
	return s;
}

EnumValue& Enum::AddKey(String key, String value) {
	ASSERT(keys.Find(key) < 0);
	return keys.Add(key).SetName(key).Set(value);
}

String Enum::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Enum " << name << "\n";
	for(int i = 0; i < keys.GetCount(); i++)
		s << keys[i].GetTreeString(indent+1);
	return s;
}

Enum& Namespace::AddEnum(String name) {
	ASSERT(enums.Find(name) < 0);
	return enums.Add(name).SetName(name);
}

Class& Namespace::AddClass(String name) {
	ASSERT(classes.Find(name) < 0);
	return classes.Add(name).SetName(name);
}

String Namespace::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Namespace\n";
	for(int i = 0; i < enums.GetCount(); i++)
		s << enums[i].GetTreeString(indent+1);
	for(int i = 0; i < classes.GetCount(); i++)
		s << classes[i].GetTreeString(indent+1);
	return s;
}

Function& Function::Arg(String param) {
	arg_str.Add(param);
	return *this;
}

Function& Function::Ret(String type) {
	ASSERT(ret_str.IsEmpty())
	ret_str = type;
	return *this;
}

String Function::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Function " << name;
	if (ret_str.GetCount())	s << ": " << ret_str;
	else					s << ": void";
	if (arg_str.GetCount()) {
		s << ": ";
		for(int i = 0; i < arg_str.GetCount(); i++) {
			if (i) s << ", ";
			s << arg_str[i];
		}
	}
	s << "\n";
	return s;
}

String Function::GetDeclarationString() const {
	String s;
	if (ret_str.IsEmpty())
		s << "void";
	else
		s << ret_str;
	s << " " << name << "(";
	for(int i = 0; i < arg_str.GetCount(); i++) {
		if (i) s << ", ";
		s << arg_str[i];
	}
	s << ");";
	return s;
}

Class& Interface::AddNativeClass(String name) {
	ASSERT(nat_cls.Find(name) < 0);
	return nat_cls.Add(name).SetName(name);
}

Class& Interface::AddUtilClass(String name) {
	ASSERT(util_cls.Find(name) < 0);
	return util_cls.Add(name).SetName(name);
}

Function& Interface::AddFunction(String name) {
	ASSERT(funcs.Find(name) < 0);
	return funcs.Add(name).SetName(name);
}

String Interface::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Interface\n";
	for(int i = 0; i < nat_cls.GetCount(); i++)
		s << nat_cls[i].GetTreeString(indent+1);
	for(int i = 0; i < util_cls.GetCount(); i++)
		s << util_cls[i].GetTreeString(indent+1);
	for(int i = 0; i < funcs.GetCount(); i++)
		s << funcs[i].GetTreeString(indent+1);
	return s;
}

String Vendor::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Vendor " << name << "\n";
	return s;
}




Package::Package() {
	clr.r = 64;
	clr.g = 64;
	clr.b = 64;
};

Vendor& Package::AddVendor(String name) {
	ASSERT(vendors.Find(name) < 0);
	return vendors.Add(name).SetName(name);
}

String Package::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << GetTitle() << " (" << GetAbbreviation() << ")\n";
	s << ns.GetTreeString(indent+1);
	s << iface.GetTreeString(indent+1);
	for(int i = 0; i < vendors.GetCount(); i++)
		s << vendors[i].GetTreeString(indent+1);
	return s;
}

void Package::Dump() {
	LOG(GetTreeString(0));
}

bool Package::Export(CompilationUnit& cu) {
	
	// This will be implemented in same way as Plan::Factory::Export.
	// It is more difficult to implement, so do it only for the final prototype.
	
	TODO
}

    
bool Package::Export() {
	String dir = GetDataDirectory();
	dir = GetParentDirectory(dir);
	
	if (GetFileName(dir) != "eonplan") {
		LOG("error: expected dir 'eonplan': " << dir);
		return false;
	}
	dir = GetParentDirectory(dir);
	String parallel_dir = AppendFileName(dir, "parallel");
	
	LOG("Realizing directory: " << parallel_dir);
	RealizeDirectory(parallel_dir);
	if (!DirectoryExists(parallel_dir)) {LOG("error: could not create directory " << parallel_dir); return false;}
	
	
	String title = GetTitle();
	String abbr = GetAbbreviation();
	String abbrup = ToUpper(abbr);
	char abbrl = GetAbbreviationLetter();
	
	String pkgname = "I" + title;
	String pkgdir = AppendFileName(parallel_dir, pkgname);
	
	LOG("Realizing directory: " << pkgdir);
	RealizeDirectory(pkgdir);
	
	String main_h = pkgname + ".h";
	
	Vector<String> file_list;
	file_list.Add(main_h);
	file_list.Add("Enums.h");
	file_list.Add("Vendors.h");
	file_list.Add("IfaceFuncs.inl");
	file_list.Add("BaseClasses.h");
	file_list.Add("TmplClasses.h");
	
	// Write .upp file
	if (1) {
		String upp_path = AppendFileName(pkgdir, pkgname + ".upp");
		FileOut fout(upp_path);
		ASSERT(fout.IsOpen());
		fout	<< "description \"\\377B"
				<< IntStr(clr.r) << ","
				<< IntStr(clr.g) << ","
				<< IntStr(clr.b) << "\";;\n\n";
		
		fout << "uses\n\tLocal";
		for (String dep : deps) {
			fout << ",\n\t" << dep;
		}
		fout << ";\n\n";
		
		fout << "file";
		for(int i = 0; i < file_list.GetCount(); i++) {
			if (i) fout << ",";
			String f = file_list[i];
			fout << "\n\t" << f;
			if (GetFileExt(f) == ".inl")
				fout << " highlight cpp";
		}
		fout << ";\n\n";
		
		fout << "mainconfig\n";
		fout <<	"\t\"\" = \"";
		for(int i = 0; i < main_flags.GetCount(); i++) {
			if (i) fout << " ";
			fout << main_flags[i];
		}
		fout << "\"\n\n";
	}
	
	// Write main .h file
	if (1) {
		String path = AppendFileName(pkgdir, main_h);
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n\n";
		fout << "#ifndef _" + pkgname + "_" + pkgname + "_h_\n";
		fout << "#define _" + pkgname + "_" + pkgname + "_h\n\n";
		fout << "NAMESPACE_TOPSIDE_BEGIN\n\n";

		for (String dep : deps)
			fout << "#include <" << dep << "/" << dep << ".h>\n";
		fout << "\n";
		
		for(int i = 1; i < file_list.GetCount(); i++)
			fout << "#include \"" << file_list[i] << "\"\n";
		fout << "\n";
		
		fout << "NAMESPACE_TOPSIDE_END\n";
		fout << "\n#endif\n\n";
	}
	
	// Base classes file
	if (1) {
		String path = AppendFileName(pkgdir, "BaseClasses.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n\n";
		fout << "#ifndef _" + pkgname + "_BaseClasses_h_\n";
		fout << "#define _" + pkgname + "_BaseClasses_h\n\n";
		fout << "NAMESPACE_TOPSIDE_BEGIN\n\n";
		
		for (Class& c : ns.classes.GetValues()) {
			c.cpp_name = abbr + c.name;
			c.t_name = c.name + "T";
			
			if (c.inherits.IsEmpty())
				c.inherits = "RTTIBase";
			
			fout << "struct " << c.cpp_name << " : " << c.inherits << " {\n";
			fout << "\tRTTI_DECL" << (c.inherits == "RTTIBase" ? String("0(") << c.cpp_name : String("1(") << c.cpp_name << ", " << c.inherits) << ")\n";
			fout << "\t\n";
			fout << "\tvirtual ~" << c.cpp_name << "() {}\n\n";
			
			
			fout << "};\n\n";
		}
		
		fout << "NAMESPACE_TOPSIDE_END\n\n";
		fout << "\n\n#endif\n\n";
	}
	
	// Template classes file
	if (1) {
		String path = AppendFileName(pkgdir, "TmplClasses.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n\n";
		fout << "#ifndef _" + pkgname + "_TmplClasses_h_\n";
		fout << "#define _" + pkgname + "_TmplClasses_h\n\n";
		fout << "NAMESPACE_TOPSIDE_BEGIN\n\n";
		
		for (Class& c : ns.classes.GetValues()) {
			fout << "template <class " << abbr << "> struct " << c.t_name << ";\n";
		}
		fout << "\n\n";
		
		for (Class& c : ns.classes.GetValues()) {
			fout << "template <class " << abbr << ">\nstruct " << c.t_name << " : " << c.cpp_name << " {\n";
			fout << "\t\n";
			
			fout << "};\n\n";
		}
		
		
		
		fout << "NAMESPACE_TOPSIDE_END\n\n";
		fout << "\n\n#endif\n\n";
	}
	
	// Function declarations file
	if (1) {
		String path = AppendFileName(pkgdir, "IfaceFuncs.inl");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n\n";
		
		for (Function& f : iface.funcs.GetValues()) {
			fout << f.GetDeclarationString() << "\n";
		}
	}
	
	// Vendors file
	if (1) {
		String path = AppendFileName(pkgdir, "Vendors.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n\n";
		fout << "#ifndef _" + pkgname + "_Vendors_h_\n";
		fout << "#define _" + pkgname + "_Vendors_h\n\n";
		fout << "NAMESPACE_TOPSIDE_BEGIN\n\n";
		
		fout << "#define " << abbrup << "_CLS_LIST(x) \\\n";
		for (Class& c : ns.classes.GetValues()) {
			fout << "\t" << abbrup << "_CLS(" << c.name << ", x) \\\n";
		}
		fout << "\n\n\n";
		
		
		fout << "#define " << abbrup << "_VNDR_LIST \\\n";
		for (Vendor& v : vendors.GetValues()) {
			fout << "\t" << abbrup << "_VNDR(" << abbr << v.name << ") \\\n";
		}
		fout << "\n\n\n";
		
		
		fout << "#define " << abbrup << "_CLS(x, v) struct v##x;\n";
		fout << "#define " << abbrup << "_VNDR(x) " << abbrup << "_CLS_LIST(x)\n";
		fout << abbrup << "_VNDR_LIST\n";
		fout << "#undef " << abbrup << "_VNDR\n";
		fout << "#undef " << abbrup << "_CLS\n";
		
		fout << "\n\n\n";
		
		fout << "VENDORSSZZ\n";
		
		for (Vendor& v : vendors.GetValues()) {
			fout << "struct " << abbr << v.name << " {\n";
			fout << "\tstruct Thread {\n";
			
			fout << "\t};\n";
			fout << "\tstatic Thread& Local() {thread_local static Thread t; return t;}\n";
			
			
			fout << "\t\n";
			fout << "\t#include \"IfaceFuncs.inl\"\n";
			
			fout << "\t\n";
			
			fout << "};\n\n";
		}
		
		
		fout << "\n\n";
		fout << "NAMESPACE_TOPSIDE_END\n";
		fout << "\n\n#endif\n\n";
	}
	
	// Enums file
	if (1) {
		String path = AppendFileName(pkgdir, "Enums.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n\n";
		fout << "#ifndef _" + pkgname + "_Enums_h_\n";
		fout << "#define _" + pkgname + "_Enums_h\n\n";
		fout << "NAMESPACE_TOPSIDE_BEGIN\n\n";
		
		
		
		fout << "\n\n";
		fout << "NAMESPACE_TOPSIDE_END\n";
		fout << "\n\n#endif\n\n";
	}
	
	
	
	if (0) {
		String path = AppendFileName(pkgdir, "BaseClasses.cpp");
		FileOut fout(path);
		fout << "#include \"" << pkgname << ".h\"\n\n";
	}
		
	return true;
}


NAMESPACE_PLAN_END
