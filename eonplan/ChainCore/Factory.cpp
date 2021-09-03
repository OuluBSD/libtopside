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

bool Factory::Export(CompilationUnit& cu, Package& pkg) {
	auto& vals = Vals();
	auto& devs = Devs();
	auto& valdevs = ValDevs();
	auto& bases = Bases();
	auto& headers = Headers();
	
	Namespace& ns_ts = cu.GetAddNamespace("TS");
	Namespace& ns_serial = ns_ts.GetAddNamespace("Serial");
	
	ClassDecl& fcls_atomtype = ns_serial.GetAddClassDecl("AtomTypeCls");
	
	TypeExpr te_atombase;
	te_atombase.SetMove(fcls_atomtype);
	cu.Activate(te_atombase);
	
	
	for (Header& h : Headers().GetValues()) {
		if (h.pkg == &pkg)
			continue;
		
		String h_name = h.name;
		LOG("\tExporting " << h_name);
		
		Class& cls_h = ns_serial.GetAddClass(h_name);
		
		String tmpl_name = "Atom<" + h_name + ">";
		Class& cls_atombase = ns_serial.GetAddClass(tmpl_name);
		cls_atombase.tmpl.is = true;
		
		
		
		if (!cls_h.Inherit(cls_atombase)) {
			OnError("class " + h_name + " could not inherit " + tmpl_name);
			return false;
		}
		
		{
			MStmt& ms_rtti = cls_h.AddMetaStatement();
			ms_rtti.SetPublic();
			MExpr& ms_rtti_expr = ms_rtti;
			ms_rtti_expr.SetCall("RTTI_DECL1");
			ms_rtti_expr.AddSub().SetId(h_name);
			ms_rtti_expr.AddSub().SetId("BaseT");
		}
		
		{
			MStmt& ms_copypanic = cls_h.AddMetaStatement();
			ms_copypanic.SetPublic();
			MExpr& ms_copypanic_expr = ms_copypanic;
			ms_copypanic_expr.SetCall("COPY_PANIC");
			ms_copypanic_expr.AddSub().SetId(h_name);
		}
		
		{
			FunctionIdScope& fis_atype = cls_h.GetAddFunctionIdScope("GetAtomType");
			Function& fn_atype = fis_atype.AddFunction();
			fn_atype.SetStatic();
			fn_atype.SetReturn(te_atombase);
			
		}
		
	}
	
	/*
	Class& cls_binary_sample = ns_serial.GetAddClass("BinarySample");
	cls_binary_sample.Hint(HINT_HIDDEN, "true");
	
	{
		String sample_name = "SoundSample";
		
		Class& sample_type = ns_serial.GetAddClass(sample_name);
		sample_type.Hint(HINT_PKG, "SerialMach");
		sample_type.Hint(HINT_FILE, "GenSamples");
		sample_type.Hint(HINT_FWD_DECL_PKG, "SerialMach");
		sample_type.Hint(HINT_FWD_DECL_FILE, "GenDefs");
		sample_type.Inherit(cls_binary_sample);
		
		
	}
	
	
	{
		Class& cls_format = ns_serial.GetAddClass("Format");
		cls_format.Hint(HINT_PKG, "SerialMach");
		cls_format.Hint(HINT_FILE, "GenFormats");
		
		
	}
	*/
	
	
	return true;
}

NAMESPACE_PLAN_END
