#include "ChainCore.h"

NAMESPACE_PLAN_BEGIN

String Factory::Val::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Dev::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::ValDev::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Base::ToString() const {
	String s;
	s << name;
	if (flags.GetCount()) {
		s << "(";
		for(int i = 0; i < flags.GetCount(); i++) {
			if (i) s << ",";
			s << flags[i];
		}
		s << ")";
	}
	return s;
}

String Factory::Header::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Loop::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Link::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Chain::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Scope::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Machine::ToString() const {
	String s;
	s << name;
	return s;
}

void Factory::Dump() {
	
	auto& vals = Vals();
	DUMPC(vals);
	
	auto& devs = Devs();
	DUMPC(devs);
	
	auto& valdevs = ValDevs();
	DUMPC(valdevs);
	
	auto& bases = Bases();
	DUMPC(bases);
	
	auto& headers = Headers();
	DUMPC(headers);
	
	auto& loops = Loops();
	DUMPC(loops);
	
	auto& links = Links();
	DUMPC(links);
	
	auto& chains = Chains();
	DUMPC(chains);
	
	auto& scopes = Scopes();
	DUMPC(scopes);
	
	auto& machines = Machines();
	DUMPC(machines);
	
}

bool Factory::Export(CompilationUnit& cu) {
	auto& pkgs = Packages();
	DUMPC(pkgs);

	for(Package& pkg: pkgs.GetValues()) {
		LOG("Exporting project: " << pkg.name);
		if (!Export(cu, pkg))
			return false;
	}

	return true;
}

void Factory::OnError(String msg) {
	LOG("Factory: error: " << msg);
}

void InitPre(Namespace& ns_serial, String pre, Vector<MExpr*>& deflists, Vector<MExpr*>& clslists) {
	MStmt& ms_deflist = ns_serial.GetAddMetaStatement("$" + pre + "ATOM_TYPE_LIST");
	MExpr& ms_deflist_expr = ms_deflist;
	ms_deflist.Hint(HINT_ASSEMBLY, "parallel");
	ms_deflist.Hint(HINT_PKG, "ParallelMach");
	ms_deflist.Hint(HINT_FILE, "Generated");
	ms_deflist.HideStatement();
	ms_deflist_expr.SetDefine(pre + "ATOM_TYPE_LIST");
	deflists.Add(&ms_deflist_expr);
	
	MStmt& ms_clslist = ns_serial.GetAddMetaStatement("$" + pre + "ATOM_CLASS_LIST");
	MExpr& ms_clslist_expr = ms_clslist;
	ms_clslist.Hint(HINT_ASSEMBLY, "parallel");
	ms_clslist.Hint(HINT_PKG, "ParallelMach");
	ms_clslist.Hint(HINT_FILE, "Generated");
	ms_clslist.HideStatement();
	ms_clslist_expr.SetDefine(pre + "ATOM_CLASS_LIST");
	clslists.Add(&ms_clslist_expr);
}

bool Factory::Export(CompilationUnit& cu, Package& pkg) {
	auto& vals = Vals();
	auto& devs = Devs();
	auto& valdevs = ValDevs();
	auto& bases = Bases();
	auto& headers = Headers();
	
	Namespace& ns_ts = cu.GetAddNamespace("TS");
	Namespace& ns_parallel = ns_ts.GetAddNamespace("Parallel");
	
	ClassDecl& fcls_atomtype = ns_parallel.GetAddClassDecl("AtomTypeCls");
	ClassDecl& fcls_linktype = ns_parallel.GetAddClassDecl("LinkTypeCls");
	ClassDecl& fcls_rtvis = ns_parallel.GetAddClassDecl("RuntimeVisitor");
	ClassDecl& fcls_packet = ns_parallel.GetAddClassDecl("Packet");
	ClassDecl& fcls_fwdscope = ns_parallel.GetAddClassDecl("FwdScope");
	
	
	TypeExpr te_atomtype;
	te_atomtype.SetMove(fcls_atomtype);
	cu.Activate(te_atomtype);
	
	TypeExpr te_linktype;
	te_linktype.SetMove(fcls_linktype);
	cu.Activate(te_linktype);
	
	TypeExpr te_void;
	te_void.SetVoid();
	cu.Activate(te_void);
	
	TypeExpr te_ref_rtvis;
	te_ref_rtvis.SetReference(fcls_rtvis);
	cu.Activate(te_ref_rtvis);
	
	TypeExpr te_packet;
	te_packet.SetReference(fcls_packet);
	cu.Activate(te_packet);
	
	TypeExpr te_fwdscope;
	te_fwdscope.SetReference(fcls_fwdscope);
	cu.Activate(te_fwdscope);
	
	Index<String> atom_types;
	Vector<MExpr*> deflists, clslists;
	
	atom_types.Add("");
	InitPre(ns_parallel, "", deflists, clslists);
	
	
	
	for (Header& h : Headers().GetValues()) {
		if (h.pkg == &pkg)
			continue;
		
		String h_name = h.name;
		String base_name = h.base;
		LOG("\tExporting " << h_name);
		LOG("\t\tBase: " << base_name);
		
		int i = bases.Find(base_name);
		if (i < 0) {
			OnError("Base '" + base_name + "' not found");
			return false;
		}
		Base& base = bases[i];
		
		Class& cls_h = ns_parallel.GetAddClass(h_name);
		
		Index<String> req_def;
		String pkg_def;
		int list_i = 0;
		for(int i = 0; i < h.args.GetCount(); i++) {
			String key = h.args.GetKey(i);
			if (key.Left(7) == "reqdef_") {
				String def = key.Mid(7);
				String pre = def + "_";
				cls_h.RequireMetaDefinition(def);
				req_def.FindAdd(def);
				
				list_i = atom_types.Find(pre);
				if (list_i < 0) {
					InitPre(ns_parallel, pre, deflists, clslists);
					list_i = atom_types.GetCount();
					atom_types.Add(pre);
				}
			}
			else if (key == "HINT_PKG") {
				pkg_def = h.args[i];
				ASSERT(pkg_def.GetCount() > 2);
				if (pkg_def.GetCount() > 2)
					pkg_def = pkg_def.Mid(1, pkg_def.GetCount()-2);
				cls_h.WeakHint(HINT_PKG, pkg_def);
			}
		}
		
		Index<String> inherits;
		/*inherits.Add("Atom<" + h_name + ">");
		if (0)
			inherits.Add(base_name + "<" + h_name + ">");
		else*/
		inherits.Add(base_name);
		inherits.Append(h.inherits);
		
		{
			MetaExpression& e = deflists[list_i]->AddSub();
			e.SetCall("ATOM_TYPE");
			e.AddSub().SetId(h.key);
		}
		
		{
			MetaExpression& e = clslists[list_i]->AddSub();
			e.SetCall("ATOM_CLASS");
			e.AddSub().SetId(h_name);
		}
		
		for(int i = 0; i < inherits.GetCount(); i++) {
			String cls_name = inherits[i];
			Class& cls = ns_parallel.GetAddClass(cls_name);
			if (cls_name.Find("<") >= 0)
				cls.tmpl.is = true;
			else
				cls.Hint(HINT_HIDDEN, "true");
			
			if (!cls_h.Inherit(cls)) {
				OnError("class " + h_name + " could not inherit " + cls_name);
				return false;
			}
		}
		
		if (1) {
			MStmt& ms_rtti = cls_h.GetAddMetaStatement("$RTTI_DECL");
			ms_rtti.HideStatement().SetPublic();
			MExpr& ms_rtti_expr = ms_rtti;
			ms_rtti_expr.SetCall("RTTI_DECL" + IntStr(inherits.GetCount()));
			ms_rtti_expr.AddSub().SetId(h_name);
			//ms_rtti_expr.AddSub().SetId("AtomT");
			for(int i = 0; i < inherits.GetCount(); i++)
				ms_rtti_expr.AddSub().SetId(inherits[i]);
		}
		
		{
			MStmt& ms_copypanic = cls_h.GetAddMetaStatement("$COPY");
			ms_copypanic.HideStatement().SetPublic();
			MExpr& ms_copypanic_expr = ms_copypanic;
			ms_copypanic_expr.SetCall("COPY_PANIC");
			ms_copypanic_expr.AddSub().SetId(h_name);
		}
		
		// static AtomTypeCls GetAtomType()
		{
			FunctionIdScope& fis_atype = cls_h.GetAddFunctionIdScope("GetAtomType");
			Function& fn_atype = fis_atype.AddFunction();
			fn_atype.SetStatic();
			fn_atype.SetReturn(te_atomtype);
			
			// return ATOM0(CENTER_CUSTOMER, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);
			Statement& stmt = fn_atype;
			Statement& ret = stmt.Add();
			Expression& ret_expr = ret;
			Expression& ret_val = ret_expr.SetReturn().First();
			ASSERT(h.src_count > 0 && h.sink_count > 0);
			
			String call = "ATOM"
				+ IntStr(h.sink_count - h.sink_user_side_count)
				+ IntStr(h.src_count - h.src_user_side_count);
			if (h.sink_user_side_count > 0 || h.src_user_side_count > 0)
				call << "_U" << h.sink_user_side_count << h.src_user_side_count;
			ret_val.SetMetaCall(call);
			ret_val.Add().SetId(h.key);
			ret_val.Add().SetId(h.role);
			String dev, val;
			
			GetKeyValDevUpper(h.content, dev, val);
			ret_val.Add().SetId(dev);
			ret_val.Add().SetId(val);
			
			for(int i = 0; i < h.sink_count; i++) {
				GetKeyValDevUpper(h.sink[i], dev, val);
				ret_val.Add().SetId(dev);
				ret_val.Add().SetId(val);
			}
			
			for(int i = 0; i < h.src_count; i++) {
				GetKeyValDevUpper(h.src[i], dev, val);
				ret_val.Add().SetId(dev);
				ret_val.Add().SetId(val);
			}
		}
		
		// static LinkTypeCls GetLinkType()
		{
			FunctionIdScope& fis_atype = cls_h.GetAddFunctionIdScope("GetLinkType");
			Function& fn_atype = fis_atype.AddFunction();
			fn_atype.SetStatic();
			fn_atype.SetReturn(te_linktype);
			
			// return ATOM0(CENTER_CUSTOMER, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);
			Statement& stmt = fn_atype;
			Statement& ret = stmt.Add();
			Expression& ret_expr = ret;
			Expression& ret_val = ret_expr.SetReturn().First();
			ASSERT(h.src_count > 0 && h.sink_count > 0);
			
			String call = "LINKTYPE";
			ret_val.SetMetaCall(call);
			ret_val.Add().SetId(h.link_key);
			ret_val.Add().SetId(h.link_role);
		}
		
		// void Visit(RuntimeVisitor& vis) override
		{
			FunctionIdScope& fis_visit = cls_h.GetAddFunctionIdScope("Visit");
			Function& fn_visit = fis_visit.AddFunction();
			fn_visit.SetReturn(te_void).SetOverrideAnonymous();
			fn_visit.AddParam("vis", te_ref_rtvis);
			
			// vis.VisitThis<...>(this);
			for (String s : inherits) {
				Statement& stmt = fn_visit;
				Statement& ret = stmt.Add();
				Expression& ret_expr = ret;
				ret_expr.SetParentExpr();
				ret_expr.Add().SetId("vis");
				Expression& call = ret_expr.Add().SetObjMethodTemplate("VisitThis");
				Expression& tmpl_args = call.First();
				Expression& call_params = call.Second();
				tmpl_args.Add().SetId(s);
				call_params.Add().SetId("this");
			}
		}
		
		// AtomTypeCls GetType() const override
		{
			FunctionIdScope& fis = cls_h.GetAddFunctionIdScope("GetType");
			Function& fn = fis.AddFunction();
			fn.SetReturn(te_atomtype).SetConst().SetOverrideAnonymous();
			
			// return GetAtomType();
			Statement& stmt = fn;
			Statement& ret = stmt.Add();
			Expression& ret_expr = ret;
			Expression& ret_val = ret_expr.SetReturn().First();
			ret_val.SetCall("GetAtomType");
		}
		
		// ATOM_MAKE_ACTION_BEGIN
		{
			MStmt& ms_begin = cls_h.GetAddMetaStatement("ATOM_BEGIN");
			ms_begin.HideStatement().SetPublic();
			MExpr& ms_begin_expr = ms_begin;
			ms_begin_expr.SetId("ATOM_MAKE_ACTION_BEGIN");
			
			int a = base.actions.GetCount();
			int b = h.actions.GetCount();
			int act_total = a + b;
			for(int i = 0; i < act_total; i++) {
				String flag_str = i < a ? base.actions[i] : h.actions[i-a];
				MStmt& ms_flag = cls_h.GetAddMetaStatement("ATOM_FLAG_" + IntStr(i));
				ms_flag.HideStatement().SetPublic();
				MExpr& ms_flag_expr = ms_flag;
				ms_flag_expr.SetCall("ATOM_MAKE_ACTION_UNDEF_TO_TRUE");
				ms_flag_expr.AddSub().SetString(flag_str);
			}
			
			MStmt& ms_end = cls_h.GetAddMetaStatement("ATOM_END");
			ms_end.HideStatement().SetPublic();
			MExpr& ms_end_expr = ms_end;
			ms_end_expr.SetId("ATOM_MAKE_ACTION_END");
		}
		
		// using CenterCustomerRef = Ref<CenterCustomer, AtomParent>;
		{
			UsingStatement& using_ref = ns_parallel.GetAddUsing(h_name + "Ref");
			Expression& using_expr = using_ref;
			using_expr.SetIdTemplate("Ref");
			using_expr.Add().SetId(h_name);
			//using_expr.Add().SetIdTemplate("RefParent1").Add().SetId("Loop");
			using_expr.Add().SetId("AtomParent");
			
			for (String req : req_def)
				using_ref.RequireMetaDefinition(req);
			
			if (pkg_def.GetCount())
				using_ref.WeakHint(HINT_PKG, pkg_def);
		}
		
		
		if (0) {
			// void Forward(FwdScope& fwd) override;
			if (base.flags.Find("forward") >= 0) {
				FunctionIdScope& fis = cls_h.GetAddFunctionIdScope("Forward");
				Function& fn = fis.AddFunction();
				fn.SetReturn(te_void).SetOverrideAnonymous();
				fn.AddParam("fwd", te_fwdscope);
				if (h.args.Find("ALT_LINK") >= 0)
					fn.SetAltImpl();
				else
					fn.SetExternalImpl();
			}
			
			// void StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) override;
			if (base.flags.Find("store_packet") >= 0) {
				FunctionIdScope& fis = cls_h.GetAddFunctionIdScope("StorePacket");
				Function& fn = fis.AddFunction();
				fn.SetReturn(te_void).SetOverrideAnonymous();
				fn.AddParam("p", te_packet);
				if (h.args.Find("ALT_LINK") >= 0)
					fn.SetAltImpl();
				else
					fn.SetExternalImpl();
			}
			
			// void IntervalSinkProcess() override;
			if (base.flags.Find("ival_sink_proc") >= 0) {
				FunctionIdScope& fis = cls_h.GetAddFunctionIdScope("IntervalSinkProcess");
				Function& fn = fis.AddFunction();
				fn.SetReturn(te_void).SetOverrideAnonymous();
				if (h.args.Find("ALT_LINK") >= 0)
					fn.SetAltImpl();
				else
					fn.SetExternalImpl();
			}
		}
	}
	
	/*
	Class& cls_binary_sample = ns_parallel.GetAddClass("BinarySample");
	cls_binary_sample.Hint(HINT_HIDDEN, "true");
	
	{
		String sample_name = "SoundSample";
		
		Class& sample_type = ns_parallel.GetAddClass(sample_name);
		sample_type.Hint(HINT_PKG, "ParallelMach");
		sample_type.Hint(HINT_FILE, "GenSamples");
		sample_type.Hint(HINT_FWD_DECL_PKG, "ParallelMach");
		sample_type.Hint(HINT_FWD_DECL_FILE, "GenDefs");
		sample_type.Inherit(cls_binary_sample);
		
		
	}
	
	
	{
		Class& cls_format = ns_parallel.GetAddClass("Format");
		cls_format.Hint(HINT_PKG, "ParallelMach");
		cls_format.Hint(HINT_FILE, "GenFormats");
		
		
	}
	*/
	
	
	return true;
}

NAMESPACE_PLAN_END
