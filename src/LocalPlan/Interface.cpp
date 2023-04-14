#include "LocalPlan.h"

NAMESPACE_TOPSIDE_BEGIN


InterfaceBuilder::Header& InterfaceBuilder::AddHeader(String name, String base, String role) {
	ASSERT(HasBase(base));
	Header& h = headers.Add();
	h.name = name;
	h.base = base;
	h.role = role;
	return h;
}

void InterfaceBuilder::Package(String s, String a) {
	cur = &packages.Add();
	cur->name = s;
	cur->abbr = a;
}

void InterfaceBuilder::SetColor(byte r, byte g, byte b) {
	cur->clr = UPP::Color(r,g,b);
}

void InterfaceBuilder::Dependency(String lib, String conditional, bool have_header) {
	struct Dependency& d = cur->deps.Add(lib);
	d.conditional = conditional;
	d.have_header = have_header;
}

void InterfaceBuilder::Library(String lib, String conditional) {
	cur->libs.Add(lib,conditional);
}

void InterfaceBuilder::HaveRecvFinalize() {
	cur->have_recv_finalize = true;
}

void InterfaceBuilder::HaveUpdate() {
	cur->have_update = true;
}

void InterfaceBuilder::HaveIsReady() {
	cur->have_is_ready = true;
}

void InterfaceBuilder::HaveNegotiateFormat() {
	cur->have_negotiate_format = true;
}

void InterfaceBuilder::HaveContextFunctions() {
	cur->have_context_fns = true;
}

void InterfaceBuilder::EnableIf(String conditional) {
	cur->enable_if.Add(conditional);
}

void InterfaceBuilder::EnableAlways() {
	cur->enable_always = true;
}

void InterfaceBuilder::Interface(String name, String conditional) {
	cur->ifaces.Add(name, conditional);
}

void InterfaceBuilder::Vendor(String name, String conditional) {
	cur->vendors.Add(name, conditional);
}





InterfaceBuilder::Header& InterfaceBuilder::Header::In(String vd) {
	ins.Add(vd, false);
	return *this;
}

InterfaceBuilder::Header& InterfaceBuilder::Header::InOpt(String vd) {
	ins.Add(vd, true);
	return *this;
}


InterfaceBuilder::Header& InterfaceBuilder::Header::InOpt(int count, String vd) {
	for(int i = 0; i < count; i++)
		ins.Add(vd, true);
	return *this;
}

InterfaceBuilder::Header& InterfaceBuilder::Header::Out(String vd) {
	outs.Add(vd, false);
	return *this;
}

InterfaceBuilder::Header& InterfaceBuilder::Header::OutOpt(String vd) {
	outs.Add(vd, true);
	return *this;
}

InterfaceBuilder::Header& InterfaceBuilder::Header::OutOpt(int count, String vd) {
	for(int i = 0; i < count; i++)
		outs.Add(vd, true);
	return *this;
}

InterfaceBuilder::Header& InterfaceBuilder::Header::Action(String act) {
	ASSERT(action.IsEmpty());
	action = act;
	return *this;
}

InterfaceBuilder::Header& InterfaceBuilder::Header::Arg(String key, String value) {
	args.Add(key, value);
	return *this;
}

InterfaceBuilder::Header& InterfaceBuilder::Header::Link(String type, String role) {
	link_type = type;
	link_role = role;
	return *this;
}



void InterfaceBuilder::Generate(bool write_actually) {
	VectorMap<String, String> outputs;
	
	#ifdef flagWIN32
	String prj_dir = "C:\\git\\libtopside";
	#else
	String prj_dir = AppendFileName(GetHomeDirectory(), "libtopside");
	#endif
	String par_dir = AppendFileName(prj_dir, "src");
	
	String pm_file = AppendFileName(par_dir, "ParallelMach" DIR_SEPS "Generated.h");
	String ga_file = AppendFileName(par_dir, "ParallelMach" DIR_SEPS "GenAtom.inl");
	LOG("\tParallelMach generated: " << pm_file);
	LOG("\tParallelMach generated inline: " << ga_file);
	
	
	VectorMap<String, Vector<int>> flag_headers;
	int i = 0;
	for (Header& h : headers) {
		String s;
		/*for(int j = 0; j < h.args.GetCount(); j++) {
			String k = h.args.GetKey(j);
			if (k.Left(7) == "reqdef_") {
				String flag = k.Mid(7);
				if (!s.IsEmpty()) s.Cat('_');
				if (flag.Left(4) == "flag") flag = flag.Mid(4);
				s << flag;
			}
		}*/
		String cond = GetBaseConds(h.base);
		if (cond.GetCount()) {
			cond.Replace("|","_");
			cond.Replace("&","v");
		}
		flag_headers.GetAdd(s).Add(i);
		++i;
	}
	


	for (const Pkg& pkg : packages) {
		String a = pkg.abbr;
		String n = pkg.name;
		String iname = "I" + pkg.name;
		String dir = AppendFileName(par_dir, iname);
		LOG("Package directory: " << dir);
		RealizeDirectory(dir);
		
		String upp_file = AppendFileName(dir, iname + ".upp");
		LOG("\tProject file: " << upp_file);
		String h_file = AppendFileName(dir, iname + ".h");
		LOG("\tHeader file: " << h_file);
		String iface_file = AppendFileName(dir, "IfaceFuncs.inl");
		LOG("\tIface file: " << iface_file);
		String impl_inl_file = AppendFileName(dir, "Impl.inl");
		LOG("\tImpl file: " << impl_inl_file);
		
		String cabbr = ToUpper(pkg.abbr);
		
		// .upp file
		{
			String s;
			int r = pkg.clr.GetR();
			int g = pkg.clr.GetG();
			int b = pkg.clr.GetB();
			
			s	<< "description \"\\377B" << IntStr(r) << "," << IntStr(g) << "," << IntStr(b) << "\";\n"
				<< "\n";
				
			for(int i = 0; i < pkg.deps.GetCount(); i++) {
				String k = pkg.deps.GetKey(i);
				const struct Dependency& dep = pkg.deps[i];
				
				if (dep.conditional.IsEmpty())
					s << "\tuses " << k << ";\n";
				else
					s << "\tuses(" << dep.conditional << ") " << k << ";\n";
			}
			
			s	<< "\n";
			
			for(int i = 0; i < pkg.libs.GetCount(); i++) {
				String k = pkg.libs.GetKey(i);
				String v = pkg.libs[i];
				if (v.IsEmpty())
					s << "\tlibrary \"" << k << "\";\n";
				else
					s << "\tlibrary(" << v << ") \"" << k << "\";\n";
			}
			
			s	<< "\n"
				<< "file\n"
				<< "\t" << iname << ".h,\n"
				;
			
			for(int i = 0; i < pkg.vendors.GetCount(); i++) {
				String k = pkg.vendors.GetKey(i);
				s << "\t" << k << ".cpp,\n";
			}
			
			if (FileExists(impl_inl_file)) {
				s << "\tImpl.inl highlight cpp,\n";
			}
			
			s	<< "\tIfaceFuncs.inl highlight cpp;\n"
				<< "\n"
				<< "mainconfig\n"
				<< "        \"\" = \"\";\n";
			
			//LOG(s);
			outputs.Add(upp_file, s);
		}
		
		// Main header
		{
			String s;
			s	<< "// This file have been generated automatically.\n"
				<< "// DO NOT MODIFY THIS FILE!\n"
				<< "\n"
				<< "#ifndef _" << iname << "_" << iname << "_h_\n"
				<< "#define _" << iname << "_" << iname << "_h_\n"
				<< "\n";
			
			for(int i = 0; i < pkg.deps.GetCount(); i++) {
				String k = pkg.deps.GetKey(i);
				const struct Dependency& dep = pkg.deps[i];
				if (dep.have_header) {
					String title = GetFileTitle(k);
					int j = title.ReverseFind("/");
					if (j >= 0)
						title = title.Mid(j+1);
					s << "#include <" << k << "/" << title << ".h>\n";
				}
			}
			
			s	<< "\n"
				<< "NAMESPACE_PARALLEL_BEGIN\n"
				<< "\n"
				<< "#define " << cabbr << "_CLS_LIST(x) \\\n";
			
			for(int i = 0; i < pkg.ifaces.GetCount(); i++) {
				String k = pkg.ifaces.GetKey(i);
				s << "\t" << cabbr << "_CLS(" << k << ", x) \\\n";
			}
			
			s	<< "\n"
				<< "#define " << cabbr << "_VNDR_LIST \\\n";
			
			for(int i = 0; i < pkg.vendors.GetCount(); i++) {
				String k = pkg.vendors.GetKey(i);
				s << "\t" << cabbr << "_VNDR(" << pkg.abbr << k << ") \\\n";
			}
			
			s	<< "\n"
				<< "#define " << cabbr << "_CLS(x, v) struct v##x;\n"
				<< "#define " << cabbr << "_VNDR(x) " << cabbr << "_CLS_LIST(x)\n"
				<< "" << cabbr << "_VNDR_LIST\n"
				<< "#undef " << cabbr << "_VNDR\n"
				<< "#undef " << cabbr << "_CLS\n"
				<< "\n";
			
			ASSERT(!pkg.enable_always || pkg.enable_if.IsEmpty());
			
			for(int i = 0; i < pkg.vendors.GetCount(); i++) {
				String k = pkg.vendors.GetKey(i);
				String v = pkg.vendors[i];
				
				if (v.GetCount())
					s << "#if " << GetMacroConditionals(v) << "\n";
				
				
				s	<< "struct " << pkg.abbr << k << " {\n";
				
				for (int j = 0; j < pkg.ifaces.GetCount(); j++) {
					String k = pkg.ifaces.GetKey(j);
					String v = pkg.ifaces[j];
					
					if (v.GetCount())
						s << "\t#if " << GetMacroConditionals(v) << "\n";
					
					s << "\tstruct Native" << k << ";\n";
					
					if (v.GetCount())
						s << "\t#endif\n";
				}
				
				s	<< "\t\n"
					<< "\tstruct Thread {\n"
					<< "\t\t\n"
					<< "\t};\n"
					<< "\t\n"
					<< "\tstatic Thread& Local() {thread_local static Thread t; return t;}\n"
					<< "\t\n"
					<< "\t#include \"IfaceFuncs.inl\"\n"
					<< "\t\n"
					<< "};\n";
				
				if (v.GetCount())
					s << "#endif\n";
				
				
			}
			
			s	<< "\n";
			
			for(int i = 0; i < pkg.ifaces.GetCount(); i++) {
				String k = pkg.ifaces.GetKey(i);
				String v = pkg.ifaces[i];
				
				if (v.GetCount())
					s << "#if " << GetMacroConditionals(v) << "\n";
				
				s	<< "struct " << pkg.abbr << k << " : public Atom {\n"
					<< "\tRTTI_DECL1(" << pkg.abbr << k << ", Atom)\n"
					<< "\tvoid Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}\n"
					<< "\t\n"
					<< "\tvirtual ~" << pkg.abbr << k << "() {}\n"
					<< "};\n";
				
				if (v.GetCount())
					s << "#endif\n";
				
				s << "\n";
			}
			
			s	<< "\n";
			
			
			for(int i = 0; i < pkg.ifaces.GetCount(); i++) {
				String k = pkg.ifaces.GetKey(i);
				String v = pkg.ifaces[i];
				
				if (v.GetCount())
					s << "#if " << GetMacroConditionals(v) << "\n";
				
				s	<< "template <class " << a << "> struct " << n << k << "T : "<<a<<k<<" {\n"
				
					<< "\tusing CLASSNAME = "<<n<<k<<"T<"<<a<<">;\n"
					<< "\tRTTI_DECL1(CLASSNAME, "<<a<<k<<")\n"
					<< "\tvoid Visit(RuntimeVisitor& vis) override {\n"
					   "\t\tif (dev) "<<a<<"::"<<k<<"_Visit(*dev, *this, vis);\n"
					   "\t\tvis.VisitThis<"<<a<<k<<">(this);\n"
					   "\t}\n"
					
					<< "\ttypename "<<a<<"::Native"<<k<<"* dev = 0;\n"
					
					<< "\tbool Initialize(const Script::WorldState& ws) override {\n"
				    << "\t\tif (!"<<a<<"::"<<k<<"_Create(dev))\n"
				    << "\t\t\treturn false;\n"
				    << "\t\tif (!"<<a<<"::"<<k<<"_Initialize(*dev, *this, ws))\n"
				    << "\t\t\treturn false;\n"
				    << "\t\treturn true;\n"
					<< "\t}\n"
					
					<< "\tbool PostInitialize() override {\n"
				    << "\t\tif (!"<<a<<"::"<<k<<"_PostInitialize(*dev, *this))\n"
				    << "\t\t\treturn false;\n"
				    << "\t\treturn true;\n"
					<< "\t}\n"
					
					<< "\tbool Start() override {\n"
				    << "\t\treturn "<<a<<"::"<<k<<"_Start(*dev, *this);\n"
					<< "\t}\n"
					
					<< "\tvoid Stop() override {\n"
				    << "\t\t"<<a<<"::"<<k<<"_Stop(*dev, *this);\n"
					<< "\t}\n"
					
					<< "\tvoid Uninitialize() override {\n"
				    << "\t\tASSERT(this->GetDependencyCount() == 0);\n"
				    << "\t\t"<<a<<"::"<<k<<"_Uninitialize(*dev, *this);\n"
				    << "\t\t"<<a<<"::"<<k<<"_Destroy(dev);\n"
					<< "\t}\n"
					
					<< "\tbool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {\n"
				    << "\t\tif (!"<<a<<"::"<<k<<"_Send(*dev, *this, cfg, out, src_ch))\n"
				    << "\t\t\treturn false;\n"
				    << "\t\treturn true;\n"
					<< "\t}\n";
				
				if (pkg.have_recv_finalize)
					s	<< "\tbool Recv(int sink_ch, const Packet& in) override {\n"
					    << "\t\treturn "<<a<<"::"<<k<<"_Recv(*dev, *this, sink_ch, in);\n"
						<< "\t}\n"
					
						<< "\tvoid Finalize(RealtimeSourceConfig& cfg) override {\n"
					    << "\t\treturn "<<a<<"::"<<k<<"_Finalize(*dev, *this, cfg);\n"
						<< "\t}\n";
				
				if (pkg.have_update)
					s	<< "\tvoid Update(double dt) override {\n"
					    << "\t\treturn "<<a<<"::"<<k<<"_Update(*dev, *this, dt);\n"
						<< "\t}\n";
				
				if (pkg.have_is_ready)
					s	<< "\tbool IsReady(PacketIO& io) override {\n"
					    << "\t\treturn "<<a<<"::"<<k<<"_IsReady(*dev, *this, io);\n"
						<< "\t}\n";
				
				if (pkg.have_negotiate_format)
					s	<< "\tbool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override {\n"
						<< "\t\treturn "<<a<<"::"<<k<<"_NegotiateSinkFormat(*dev, *this, link, sink_ch, new_fmt);\n"
						<< "\t}\n";
				
				if (pkg.have_context_fns) {
					s	<< "\tbool AttachContext(AtomBase& a) override {\n"
						<< "\t\treturn "<<a<<"::"<<k<<"_AttachContext(*dev, *this, a);\n"
						<< "\t}\n";
						
					s	<< "\tvoid DetachContext(AtomBase& a) override {\n"
						<< "\t\t"<<a<<"::"<<k<<"_DetachContext(*dev, *this, a);\n"
						<< "\t}\n";
				}
				s	<< "};\n";
				
				if (v.GetCount())
					s << "#endif\n";
				
			}
			
			s << "\n";
			
			for(int i = 0; i < pkg.vendors.GetCount(); i++) {
				String vk = pkg.vendors.GetKey(i);
				String vv = pkg.vendors[i];
				
				if (vv.GetCount())
					s << "#if " << GetMacroConditionals(vv) << "\n";
				
				for (int j = 0; j < pkg.ifaces.GetCount(); j++) {
					String ik = pkg.ifaces.GetKey(j);
					String iv = pkg.ifaces[j];
					
					if (iv.GetCount())
						s << "#if " << GetMacroConditionals(iv) << "\n";
					
					s << "using " << vk << ik << " = " << n << ik << "T<" << a << vk << ">;\n";
					
					if (iv.GetCount())
						s << "#endif\n";
				}
				
				if (vv.GetCount())
					s << "#endif\n";
				
			}
			
			
			s	<< "\n"
				<< "NAMESPACE_PARALLEL_END\n"
				<< "\n"
			
				<< "#endif\n";
			
			//LOG(s);
			outputs.Add(h_file, s);
		}
		
		
		
		{
			String s;
			
			s	<< "// This file have been generated automatically.\n"
				<< "// DO NOT MODIFY THIS FILE!\n\n";
				
			for(int i = 0; i < pkg.ifaces.GetCount(); i++) {
				String k = pkg.ifaces.GetKey(i);
				String v = pkg.ifaces[i];
				
				if (v.GetCount())
					s << "#if " << GetMacroConditionals(v) << "\n";
				
				String nat_this_ = "Native" + k + "&, ";
				
				s	<< "static bool " << k << "_Create(Native" + k + "*& dev);\n"
					<< "static void " << k << "_Destroy(Native" + k + "*& dev);\n"
					<< "static bool " << k << "_Initialize(" << nat_this_ << "AtomBase&, const Script::WorldState&);\n"
					<< "static bool " << k << "_PostInitialize(" << nat_this_ << "AtomBase&);\n"
					<< "static bool " << k << "_Start(" << nat_this_ << "AtomBase&);\n"
					<< "static void " << k << "_Stop(" << nat_this_ << "AtomBase&);\n"
					<< "static void " << k << "_Uninitialize(" << nat_this_ << "AtomBase&);\n"
					<< "static bool " << k << "_Send(" << nat_this_ << "AtomBase&, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch);\n"
					<< "static void " << k << "_Visit(" << nat_this_ << "AtomBase&, RuntimeVisitor& vis);\n"
					;
				
				if (pkg.have_recv_finalize) {
					s	<< "static bool " << k << "_Recv(" << nat_this_ << "AtomBase&, int, const Packet&);\n"
						<< "static void " << k << "_Finalize(" << nat_this_ << "AtomBase&, RealtimeSourceConfig&);\n";
				}
				if (pkg.have_update) {
					s	<< "static void " << k << "_Update(" << nat_this_ << "AtomBase&, double dt);\n";
				}
				
				if (pkg.have_negotiate_format) {
					s	<< "static bool " << k << "_NegotiateSinkFormat(" << nat_this_ << "AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt);\n";
				}
				
				if (pkg.have_is_ready) {
					s	<< "static bool " << k << "_IsReady(" << nat_this_ << "AtomBase&, PacketIO& io);\n";
				}
				
				if (pkg.have_context_fns) {
					s	<< "static bool " << k << "_AttachContext(" << nat_this_ << "AtomBase& a, AtomBase& other);\n";
					s	<< "static void " << k << "_DetachContext(" << nat_this_ << "AtomBase& a, AtomBase& other);\n";
				}
				
				if (v.GetCount())
					s << "#endif\n";
				
				s << "\n";
				
			}
			
			//LOG(s);
			outputs.Add(iface_file, s);
		}
	}
	
	
		
	// ParallerMach/Generated.h
	{
		String s;
		
		s	<< "#ifndef _ParallelMach_Generated_h_\n"
			<< "#define _ParallelMach_Generated_h_\n"
			<< "\n"
			<< "// This file is generated. Do not modify this file.\n"
			<< "\n"
			<< "namespace TS {\n"
			<< "\n"
			<< "namespace Parallel {\n";
		for(int i = 0; i < flag_headers.GetCount(); i++) {
			String k = flag_headers.GetKey(i);
			const Vector<int>& hi = flag_headers[i];
			
			String pre = k.IsEmpty() ? String() : k + "_";
			
			s	<< "#define " << pre << "ATOM_TYPE_LIST \\\n";
			for(int i = 0; i < hi.GetCount(); i++) {
				const Header& h = headers[hi[i]];
				s << "\tATOM_TYPE(" << h.GetMacro() << ") \\\n";
			}
			s	<< "\n";
			
			s	<< "#define " << pre << "ATOM_CLASS_LIST \\\n";
			for(int i = 0; i < hi.GetCount(); i++) {
				const Header& h = headers[hi[i]];
				s << "\tATOM_CLASS(" << h.name << ") \\\n";
			}
			s	<< "\n";
		}
		
		s	<< "}}\n\n";
		s	<< "#endif\n";
		
		//LOG(s);
		outputs.Add(pm_file, s);
	}
	
	// ParallerMach/GenAtom.inl
	{
		String s;
		
		s	<< "#ifdef GEN_ATOM_TYPE_LIST\n\n";
		for(int i = 0; i < flag_headers.GetCount(); i++) {
			String k = flag_headers.GetKey(i);
			const Vector<int>& hi = flag_headers[i];
			String pre = k.IsEmpty() ? String() : k + "_";
			
			if (k.IsEmpty())
				s	<< pre << "ATOM_TYPE_LIST\n";
			else
				s	<< "#if " << GetMacroFlags(k) << "\n"
					<< pre << "ATOM_TYPE_LIST\n"
					<< "#endif\n\n";
			
		}
		s	<< "\n#endif\n\n\n";
		
		s	<< "#ifdef GEN_ATOM_CLASS_LIST\n\n";
		for(int i = 0; i < flag_headers.GetCount(); i++) {
			String k = flag_headers.GetKey(i);
			const Vector<int>& hi = flag_headers[i];
			String pre = k.IsEmpty() ? String() : k + "_";
			
			if (k.IsEmpty())
				s	<< pre << "ATOM_CLASS_LIST\n";
			else
			s	<< "#if " << GetMacroFlags(k) << "\n"
				<< pre << "ATOM_CLASS_LIST\n"
				<< "#endif\n\n";
			
		}
		s	<< "\n#endif\n";
		
		//LOG(s);
		outputs.Add(ga_file, s);
	}
	
	// Atoms
	{
		String def_atom = "AtomLocal";
		VectorMap<String, Vector<int>> atom_list;
		int i = 0;
		for (Header& h : headers) {
			String atom = h.args.Get("HINT_PKG", def_atom);
			atom_list.GetAdd(atom).Add(i);
			i++;
		}
		
		for(int i = 0; i < atom_list.GetCount(); i++) {
			String k = atom_list.GetKey(i);
			const Vector<int>& ai = atom_list[i];
			String atom_dir = AppendFileName(par_dir, k);
			String genh_path = AppendFileName(atom_dir, "Generated.h");
			String genc_path = AppendFileName(atom_dir, "Generated.cpp");
			String icpp_path = AppendFileName(atom_dir, "Init.cpp");
			
			{
				String s;
				
				s	<< "#ifndef _" << k << "_Generated_h_\n"
					<< "#define _" << k << "_Generated_h_\n"
					<< "\n"
					<< "// This file is generated. Do not modify this file.\n"
					<< "\n"
					<< "namespace TS {\n"
					<< "\n"
					<< "namespace Parallel {\n\n";
				
				for(int j = 0; j < ai.GetCount(); j++) {
					const Header& h = headers[ai[j]];
					
					String cond = GetBaseConds(h.base);
					
					if (cond.GetCount())
						s << "#if " << GetMacroConditionals(cond) << "\n";
					
					s	<< "class " << h.name << " : public " << h.base << " {\n"
						<< "\n"
						<< "public:\n"
						<< "\tRTTI_DECL1(" << h.name << ", " << h.base << ")\n"
						<< "\tCOPY_PANIC(" << h.name << ")\n"
						<< "\tstatic String GetAction();\n"
						<< "\tstatic AtomTypeCls GetAtomType();\n"
						<< "\tstatic LinkTypeCls GetLinkType();\n"
						<< "\tvoid Visit(RuntimeVisitor& vis) override;\n"
						<< "\tAtomTypeCls GetType() const override;\n"
						<< "\t\n"
						<< "};\n";
					
					if (cond.GetCount())
						s << "#endif\n";
					
					s	<< "\n";
				}
				
				s << "}\n\n";
				s << "}\n";
				s << "#endif\n";
				
				outputs.Add(genh_path, s);
			}
			
			{
				String s;
				
				s	<< "#include \"" << k << ".h\"\n"
					<< "\n"
					<< "// This file is generated. Do not modify this file.\n"
					<< "\n"
					<< "namespace TS {\n"
					<< "\n"
					<< "namespace Parallel {\n"
					<< "\n";
				
				for(int j = 0; j < ai.GetCount(); j++) {
					const Header& h = headers[ai[j]];
					
					// Some error handling (possibly in bad place)
					if (h.link_type == "PIPE") {
						for(int i = 0; i < h.ins.GetCount(); i++) {
							ASSERT(!h.ins[i]);
						}
						for(int i = 0; i < h.outs.GetCount(); i++) {
							ASSERT(!h.outs[i]);
						}
					}
					
					
					String cond = GetBaseConds(h.base);
					
					if (cond.GetCount())
						s << "#if " << GetMacroConditionals(cond) << "\n";
					
					s	<< "String " << h.name << "::GetAction() {\n"
						<< "\treturn \"" << h. action << "\";\n"
						<< "}\n\n"
						<< "AtomTypeCls " << h.name << "::GetAtomType() {\n"
						<< "\tAtomTypeCls t;\n"
						<< "\tt.sub = SubAtomCls::" << GetMacroName(h.name) << ";\n"
						<< "\tt.role = AtomRole::" << ToUpper(h.role) << ";\n";
						
					for(int i = 0; i < h.ins.GetCount(); i++) {
						String k = h.ins.GetKey(i);
						bool opt = h.ins[i];
						s << "\tt.AddIn(" << GetVD(k) << "," << (int)opt << ");\n";
					}
						
					for(int i = 0; i < h.outs.GetCount(); i++) {
						String k = h.outs.GetKey(i);
						bool opt = h.outs[i];
						s << "\tt.AddOut(" << GetVD(k) << "," << (int)opt << ");\n";
					}
					
					s	<< "\treturn t;\n"
						<< "}\n\n"
						<< "LinkTypeCls " << h.name << "::GetLinkType() {\n"
						<< "\treturn LINKTYPE(" << ToUpper(h.link_type) << ", " << ToUpper(h.link_role) << ");\n"
						<< "}\n\n"
						<< "void " << h.name << "::Visit(RuntimeVisitor& vis) {\n"
						<< "\tvis.VisitThis<" << h.base << ">(this);\n"
						<< "}\n\n"
						<< "AtomTypeCls " << h.name << "::GetType() const {\n"
						<< "\treturn GetAtomType();\n"
						<< "}\n";
					
					if (cond.GetCount())
						s << "#endif\n";
					
					s	<< "\n\n";
				}
				
				
				s	<< "}\n\n}\n\n";
				
				
				//LOG(s);
				
				outputs.Add(genc_path, s);
			}
			
			{
				String s;
				
				s	<< "#include \"" << k << ".h\"\n"
					<< "\n"
					<< "// This file is generated. Do not modify this file.\n"
					<< "\n"
				
					<< "INITBLOCK_(" << k << ") {\n"
					<< "\tusing namespace TS::Parallel;\n"
					<< "\tusing namespace TS::Serial;\n"
					<< "\tusing namespace TS;\n";
				
				for(int j = 0; j < ai.GetCount(); j++) {
					const Header& h = headers[ai[j]];
					
					String cond = GetBaseConds(h.base);
					
					if (cond.GetCount())
						s << "\t#if " << GetMacroConditionals(cond) << "\n";
					
					s << "\tFactory::RegisterAtom<" << h.name << ">();\n";
					
					if (cond.GetCount())
						s << "\t#endif\n";
					
				}
				
				s << "}\n\n";
				
				outputs.Add(icpp_path, s);
			}
		}
		//DUMPC(atom_list.GetKeys());
	}
	
	
	if (write_actually) {
		for(int i = 0; i < outputs.GetCount(); i++) {
			String file = outputs.GetKey(i);
			String content = outputs[i];
			LOG("Writing " << file);
			
			FileOut fout(file);
			fout << content;
			fout.Close();
		}
	}
	
	
}

String InterfaceBuilder::Header::GetMacro() const {
	String s;
	bool prev_lower = false;
	for(int i = 0; i < name.GetCount(); i++) {
		int chr = name[i];
		bool lower = !IsUpper(chr);
		
		if (prev_lower && !lower)
			s.Cat('_');
		
		s.Cat(ToUpper(chr));
		
		prev_lower = lower;
	}
	return s;
}

String InterfaceBuilder::GetMacroConditionals(String cond_str) {
	String s;
	ASSERT(!cond_str.IsEmpty());
	Vector<String> ors = Split(cond_str, "|");
	int i = 0;
	int parts = 0;
	for (String o : ors) {
		if (i++) s << " || ";
		s << "(";
		Vector<String> ands = Split(o, "&");
		int j = 0;
		for (String a : ands) {
			if (j++) s << " && ";
			if (a.Left(1) == "!")
				s << "!defined flag" << a.Mid(1);
			else
				s << "defined flag" << a;
			parts++;
		}
		s << ")";
	}
	
	if (parts == 1) {
		if (cond_str.Left(1) == "!")
			return "!defined flag" + cond_str.Mid(1);
		else
			return "defined flag" + cond_str;
	}
	
	return s;
}

String InterfaceBuilder::GetVD(String vd_name) {
	int b = 0;
	for(int i = 1; i < vd_name.GetCount(); i++) {
		if (IsUpper(vd_name[i])) {
			b = i;
			break;
		}
	}
	String dev = vd_name.Left(b);
	String val = vd_name.Mid(b);
	
	return "VD(" + ToUpper(dev) + "," + ToUpper(val) + ")";
}

String InterfaceBuilder::GetMacroName(String name) {
	String s;
	bool prev_lower = false;
	for(int i = 0; i < name.GetCount(); i++) {
		int chr = name[i];
		bool lower = !IsUpper(chr);
		
		if (prev_lower && !lower)
			s.Cat('_');
		
		s.Cat(ToUpper(chr));
		
		prev_lower = lower;
	}
	return s;
}

String InterfaceBuilder::GetMacroFlags(String flags) {
	Vector<String> v = Split(flags, "_");
	String s;
	for (String vs : v) {
		if (!s.IsEmpty())
			s << " && ";
		
		if (vs.Left(1) == "!")
			s << "!defined flag" << vs.Mid(1);
		else
			s << "defined flag" << vs;
	}
	return s;
}

bool InterfaceBuilder::HasBase(String s) const {
	//DUMP(s);
	for(const Pkg& p : packages) {
		for(int i = 0; i < p.vendors.GetCount(); i++) {
			String vendor = p.vendors.GetKey(i);
			for(int j = 0; j < p.ifaces.GetCount(); j++) {
				String iface = p.ifaces.GetKey(j);
				String base = vendor + iface;
				//DUMP(base);
				if (base == s) {
					ASSERT(custom_atom_bases.Find(s) < 0);
					return true;
				}
			}
		}
	}
	
	if (custom_atom_bases.Find(s) >= 0)
		return true;
	
	DUMP(s);
	return false;
}

String InterfaceBuilder::GetBaseConds(String s) const {
	int i = custom_atom_bases.Find(s);
	if (i >= 0)
		return custom_atom_bases[i];
	
	for(const Pkg& p : packages) {
		for(int i = 0; i < p.vendors.GetCount(); i++) {
			String vendor = p.vendors.GetKey(i);
			for(int j = 0; j < p.ifaces.GetCount(); j++) {
				String iface = p.ifaces.GetKey(j);
				String base = vendor + iface;
				//DUMP(base);
				if (base == s) {
					String vcond = p.vendors[i];
					String icond = p.ifaces[j];
					Index<String> ors;
					if (vcond.GetCount() && icond.GetCount()) {
						for (String a : Split(vcond, "|"))
							for (String b : Split(icond, "|"))
								ors.FindAdd(a + "&" + b);
					}
					else if (vcond.GetCount()) {
						for (String cond : Split(vcond, "|"))
							ors.FindAdd(cond);
					}
					else if (icond.GetCount()) {
						for (String cond : Split(icond, "|"))
							ors.FindAdd(cond);
					}
					
					SortIndex(ors, StdLess<String>());
					
					String s;
					for(int i = 0; i < ors.GetCount(); i++) {
						if (i) s.Cat('|');
						s.Cat(ors[i]);
					}
					return s;
				}
			}
		}
	}
	
	NEVER();
	Panic("error");
	return String();
}

NAMESPACE_TOPSIDE_END
