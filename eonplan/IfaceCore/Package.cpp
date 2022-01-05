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

void Package::Export(CompilationUnit& cu) {
	
	
	
	TODO
	
}


NAMESPACE_PLAN_END
