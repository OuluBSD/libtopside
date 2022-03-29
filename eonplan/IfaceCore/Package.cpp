#include "IfaceCore.h"

NAMESPACE_PLAN_BEGIN

String Class::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Class " << name << "\n";
	return s;
}

void Class::AddNativeInherit(String cls, String name) {
	nat_inherited.GetAdd(cls) = name;
}

Function& Class::AddFunction(String name) {
	ASSERT(funcs.Find(name) < 0);
	return funcs.Add(name).SetName(name);
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
	
	String type, name;
	int i = param.Find(" ");
	if (i >= 0) {
		type = param.Left(i);
		name = param.Mid(i+1);
	}
	else {
		type = param;
		name = "a" + IntStr(args.GetCount());
	}
	args.Add(name, type);
	
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

String Function::GetDeclarationString(bool argnames, String prefix, bool have_this_arg) const {
	String s;
	if (ret_str.IsEmpty())
		s << "void";
	else
		s << ret_str;
	s << " " << prefix << name << "(";
	for(int i = 0, j = 0; i < args.GetCount(); i++) {
		String type = args[i];
		String line = type;
		if (argnames) {
			String name = args.GetKey(i);
			if (name == "this") {
				name = "o";
				if (!have_this_arg)
					continue;
			}
			line << " " << name;
		}
		if (j) s << ", ";
		s << line;
		j++;
	}
	s << ")";
	return s;
}

String Function::GetProxyString(const Class& c, String prefix) const {
	String s;
	if (!ret_str.IsEmpty())
		s << "return ";
	
	s << prefix << name << "(";
	for(int i = 0; i < args.GetCount(); i++) {
		String name = args.GetKey(i);
		if (name == "this") {
			name.Clear();
			String type = args[i];
			
			if (type.Left(6) == "Native")
				type = type.Mid(6);
			if (type.Right(1) == "&")
				type = type.Left(type.GetCount()-1);
			
			for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
				String a = c.nat_inherited.GetKey(i);
				//LOG(a << " == " << type);
				if (a == type)
					name = c.nat_inherited[i];
			}
			if (name.GetCount())
				name = "this->" + name;
			else
				Panic("invalid this argument: " + type);
		}
		if (i) s << ", ";
		s << name;
	}
	s << ")";
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
	for (Vendor& v : vendors.GetValues())
		file_list.Add(v.name + ".cpp");
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
		
		fout << "uses\n\tParallelLib";
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
			fout << ToUpper(main_flags[i]);
		}
		fout << "\"\n\n";
	}
	
	// Write main .h file
	if (1) {
		String path = AppendFileName(pkgdir, main_h);
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n";
		fout << "// Last export: " << GetSysTime().ToString() << "\n\n";
		fout << "#ifndef _" + pkgname + "_" + pkgname + "_h_\n";
		fout << "#define _" + pkgname + "_" + pkgname + "_h_\n\n";

		for (String dep : deps)
			fout << "#include <" << dep << "/" << dep << ".h>\n";
		fout << "\n";
		
		for(int i = 1; i < file_list.GetCount(); i++) {
			String f = file_list[i];
			if (GetFileExt(f) == ".inl")
				;
			else if (GetFileExt(f) == ".cpp")
				;
			else
				fout << "#include \"" << f << "\"\n";
		}
		fout << "\n";
		
		fout << "\n#endif\n\n";
	}
	
	// Base classes file
	if (1) {
		String path = AppendFileName(pkgdir, "BaseClasses.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n";
		fout << "// Last export: " << GetSysTime().ToString() << "\n\n";
		fout << "#ifndef _" + pkgname + "_BaseClasses_h_\n";
		fout << "#define _" + pkgname + "_BaseClasses_h_\n\n";
		fout << "NAMESPACE_PARALLEL_BEGIN\n\n";
		
		for (Class& c : ns.classes.GetValues()) {
			c.cpp_name = abbr + c.name;
			c.t_name = title + c.name + "T";
			
			if (c.inherits.IsEmpty())
				c.inherits = "Atom";
			
			fout << "struct " << c.cpp_name << " : public " << c.inherits << " {\n";
			fout << "\tRTTI_DECL" << (c.inherits == "RTTIBase" ? String("0(") << c.cpp_name : String("1(") << c.cpp_name << ", " << c.inherits) << ")\n";
			fout << "\t\n";
			fout << "\tvirtual ~" << c.cpp_name << "() {}\n\n";
			
			
			fout << "};\n\n";
		}
		
		fout << "NAMESPACE_PARALLEL_END\n\n";
		fout << "\n\n#endif\n\n";
	}
	
	// Template classes file
	if (1) {
		String path = AppendFileName(pkgdir, "TmplClasses.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n";
		fout << "// Last export: " << GetSysTime().ToString() << "\n\n";
		fout << "#ifndef _" + pkgname + "_TmplClasses_h_\n";
		fout << "#define _" + pkgname + "_TmplClasses_h_\n\n";
		fout << "NAMESPACE_PARALLEL_BEGIN\n\n";
		
		for (Class& c : ns.classes.GetValues()) {
			fout << "template <class " << abbr << "> struct " << c.t_name << ";\n";
		}
		fout << "\n\n";
		
		for (Class& c : ns.classes.GetValues()) {
			fout << "template <class " << abbr << ">\nstruct " << c.t_name << " : " << c.cpp_name << " {\n";
			
			for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
				String cls = c.nat_inherited.GetKey(i);
				String name = c.nat_inherited[i];
				fout << "\ttypename " << abbr << "::Native" << cls << " " << name << ";\n";
			}
			fout << "\t\n";
			
			fout << "\tbool Initialize(const Script::WorldState& ws) override {\n";
			for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
				String cls = c.nat_inherited.GetKey(i);
				String name = c.nat_inherited[i];
				fout << "\t\tif (!" << abbr << "::" << cls << "_Initialize(" << name << ", *this, ws))\n";
				fout << "\t\t\treturn false;\n";
			}
			/*fout << "\t\tconst int sink_ch_i = 0;\n";
			fout << "\t\tobj.Create();\n";
			fout << "\t\tobj->WhenAction << THISBACK(SinkCallback);\n";
			fout << "\t\tif (!obj->Initialize(*this, ws))\n";
			fout << "\t\t\treturn false;\n";
			fout << "\t\tobj->OpenDefault();\n";
			fout << "\t\tValue& sink_val = GetSink()->GetValue(sink_ch_i);\n";
			fout << "\t\tfmt = ConvertPortaudioFormat(obj->GetFormat());\n";
			fout << "\t\tASSERT(fmt.IsValid());\n";
			fout << "\t\tsink_val.SetFormat(fmt);\n";
			fout << "\t\tobj->Start();\n";
			fout << "\t\tSetPrimarySinkQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);\n";
			fout << "\t\tobj->Start();\n";*/
			fout << "\t\treturn true;\n";
			fout << "\t}\n\n";
			
			fout << "\tvoid Uninitialize() override {\n";
			for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
				String cls = c.nat_inherited.GetKey(i);
				String name = c.nat_inherited[i];
				fout << "\t\t" << abbr << "::" << cls << "_Uninitialize(" << name << ");\n";
			}
			/*fout << "\t\tobj->Stop();\n";
			fout << "\t\tobj.Clear();\n";*/
			fout << "\t}\n\n";
			
			fout << "\tbool ProcessPacket(PacketValue& v) override {\n";
			for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
				String cls = c.nat_inherited.GetKey(i);
				String name = c.nat_inherited[i];
				fout << "\t\tif (!" << abbr << "::" << cls << "_ProcessPacket(" << name << ", v))\n";
				fout << "\t\t\treturn false;\n";
			}
			fout << "\t\treturn true;\n";
			fout << "\t}\n\n";
			
			
			// Proxy functions
			/*String nat_this;
			for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
				String type = c.nat_inherited.GetKey(i);
				String name = c.nat_inherited[i];
				if (i)
					nat_this << ", ";
				nat_this << "Native" << type << "& " << name;
			}
			String nat_this_ = (nat_this.GetCount() ? (nat_this + ", ") : String());*/
			
			String prefix0 = "";
			String prefix1 = abbr + "::" + c.name + "_";
			for (Function& f : c.funcs.GetValues()) {
				fout << "\t" << f.GetDeclarationString(true, prefix0, false) << " {\n";
				fout << "\t\t" << f.GetProxyString(c, prefix1) << ";\n";
				fout << "\t}\n";
				fout << "\t\n";
			}
			
			fout << "\t\n";
			
			
			
			fout << "};\n\n";
		}
		
		for (Vendor& v : vendors.GetValues()) {
			for (Class& c : ns.classes.GetValues()) {
				String to = v.name + c.name;
				String from = c.t_name + "<" + abbr + v.name + ">";
				fout << "using " << to << " = " << from << ";\n";
				//using PortAudioSinkDevice = AudioSinkDeviceT<AudPortaudio>;
			}
		}
		fout << "\n\n";
		
		fout << "NAMESPACE_PARALLEL_END\n\n";
		fout << "\n\n#endif\n\n";
	}
	
	// Function declarations file
	if (1) {
		String path = AppendFileName(pkgdir, "IfaceFuncs.inl");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n";
		fout << "// Last export: " << GetSysTime().ToString() << "\n\n";
		
		for (Class& c : ns.classes.GetValues()) {
			String nat_this;
			for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
				String type = c.nat_inherited.GetKey(i);
				String name = c.nat_inherited[i];
				if (i)
					nat_this << ", ";
				nat_this << "Native" << type << "& " << name;
			}
			String nat_this_ = (nat_this.GetCount() ? (nat_this + ", ") : String());
			fout << "static bool " << c.name << "_Initialize(" << nat_this_ << "AtomBase&, const Script::WorldState&);\n";
			fout << "static void " << c.name << "_Start(" << nat_this << ");\n";
			fout << "static void " << c.name << "_Stop(" << nat_this << ");\n";
			fout << "static void " << c.name << "_Uninitialize(" << nat_this << ");\n";
			fout << "static bool " << c.name << "_ProcessPacket(" << nat_this_ << "PacketValue& v);\n";
			fout << "\n";
			
			String prefix = c.name + "_";
			for (Function& f : c.funcs.GetValues()) {
				fout << "static " << f.GetDeclarationString(true, prefix) << ";\n";
			}
			fout << "\t\n";
		}
		
		for (Function& f : iface.funcs.GetValues()) {
			fout << f.GetDeclarationString(true) << ";\n";
		}
	}
	
	// Vendors header file
	if (1) {
		String path = AppendFileName(pkgdir, "Vendors.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n";
		fout << "// Last export: " << GetSysTime().ToString() << "\n\n";
		fout << "#ifndef _" + pkgname + "_Vendors_h_\n";
		fout << "#define _" + pkgname + "_Vendors_h_\n\n";
		fout << "NAMESPACE_PARALLEL_BEGIN\n\n";
		
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
		
		for (Vendor& v : vendors.GetValues()) {
			fout << "struct " << abbr << v.name << " {\n";
			for (Class& c : iface.nat_cls.GetValues()) {
				fout << "\tusing Native" << c.name << " = uint32;\n";
			}
			//fout << "\ttypedef void (*DataCallbackFn)(void*, char* data, int size);\n";
			fout << "\t\n";
			
			
			fout << "\tstruct Thread {\n";
			fout << "\t\t\n";
			fout << "\t};\n";
			fout << "\tstatic Thread& Local() {thread_local static Thread t; return t;}\n";
			
			
			fout << "\t\n";
			fout << "\t#include \"IfaceFuncs.inl\"\n";
			
			fout << "\t\n";
			
			fout << "};\n\n";
		}
		
		
		fout << "\n\n";
		fout << "NAMESPACE_PARALLEL_END\n";
		fout << "\n\n#endif\n\n";
	}
	
	if (1) {
		for (Vendor& v : vendors.GetValues()) {
			String path = AppendFileName(pkgdir, v.name + ".cpp");
			
			// Protect user-made changes
			if (FileExists(path)) {
				LOG("Protecting file: " << path);
				continue;
			}
			
			FileOut fout(path);
			
			fout << "#include \"" << pkgname << ".h\"\n\n";
			fout << "NAMESPACE_PARALLEL_BEGIN\n\n";
			
			for (Class& c : ns.classes.GetValues()) {
				String cls = abbr + v.name;
				String nat_this;
				for(int i = 0; i < c.nat_inherited.GetCount(); i++) {
					String type = c.nat_inherited.GetKey(i);
					String name = c.nat_inherited[i];
					if (i)
						nat_this << ", ";
					nat_this << "Native" << type << "& " << name;
				}
				String nat_this_ = (nat_this.GetCount() ? (nat_this + ", ") : String());
				
				fout << "bool " << cls << "::" << c.name << "_Initialize(" << nat_this_ << "AtomBase& a, const Script::WorldState& ws) {\n";
				fout << "\tTODO\n";
				fout << "}\n\n";
				
				fout << "void " << cls << "::" << c.name << "_Start(" << nat_this << ") {\n";
				fout << "\tTODO\n";
				fout << "}\n\n";
				
				fout << "void " << cls << "::" << c.name << "_Stop(" << nat_this << ") {\n";
				fout << "\tTODO\n";
				fout << "}\n\n";
				
				fout << "void " << cls << "::" << c.name << "_Uninitialize(" << nat_this << ") {\n";
				fout << "\tTODO\n";
				fout << "}\n\n";
				
				fout << "bool " << cls << "::" << c.name << "_ProcessPacket(" << nat_this_ << "PacketValue& v) {\n";
				fout << "\tTODO\n";
				fout << "}\n\n";
				
				for (Function& f : c.funcs.GetValues()) {
					String prefix = cls + "::" + c.name + "_";
					fout << f.GetDeclarationString(true, prefix) << " {\n";
					fout << "\tTODO\n";
					fout << "}\n\n";
				}
			}
			
			fout << "\n\n\n";
			fout << "\nNAMESPACE_PARALLEL_END\n\n";
		}
		
		
		
	}
	
	
	// Enums file
	if (1) {
		String path = AppendFileName(pkgdir, "Enums.h");
		FileOut fout(path);
		
		fout << "// This file have been generated automatically.\n";
		fout << "// DO NOT MODIFY THIS FILE!\n";
		fout << "// Last export: " << GetSysTime().ToString() << "\n\n";
		fout << "#ifndef _" + pkgname + "_Enums_h_\n";
		fout << "#define _" + pkgname + "_Enums_h_\n\n";
		fout << "NAMESPACE_PARALLEL_BEGIN\n\n";
		
		
		
		fout << "\n\n";
		fout << "NAMESPACE_PARALLEL_END\n";
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
