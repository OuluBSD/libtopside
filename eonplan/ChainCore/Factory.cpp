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

bool Factory::Export(CompilationUnit& cu, Package& pkg) {
	auto& vals = Vals();
	auto& devs = Devs();
	auto& valdevs = ValDevs();
	auto& bases = Bases();
	auto& headers = Headers();
	
	Namespace& ns_ts = cu.GetAddNamespace("TS");
	Namespace& ns_serial = ns_ts.GetAddNamespace("Serial");
	
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
