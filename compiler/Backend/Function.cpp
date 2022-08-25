#include "Backend.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN



Function& Function::SetStatic(bool b) {
	is_static = b;
	return *this;
}

Function& Function::SetReturn(const TypeExpr& te) {
	ASSERT(te.global_ptr);
	ASSERT(!te.IsEmpty());
	ret = te;
	return *this;
}

Function& Function::SetOverrideAnonymous() {
	is_override_anon = true;
	return *this;
}

Function& Function::SetConst() {
	is_const = true;
	return *this;
}

Function& Function::SetExternalImpl() {
	is_ext_impl = true;
	return *this;
}

Function& Function::SetAltImpl() {
	is_alt_impl = true;
	return *this;
}

Function& Function::AddParam(String key, const TypeExpr& te) {
	ASSERT(te.IsActivated());
	ASSERT(params.Find(key) < 0);
	params.Add(key, te);
	return *this;
}

Statement& Function::RealizeStatement() {
	if (impl.IsEmpty()) {
		impl.Create();
		impl->SetOwner(this);
		impl->SetBlock();
	}
	return *impl;
}

String Function::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	if (impl)
		s << impl->GetTreeString(indent+1);
	return s;
}

String Function::ToString() const {
	String s;
	s << "Function: " << ret.ToString();
	return s;
}

String Function::GetCodeString(const CodeArgs& args) const {
	if (!IsContained(args))
		return String();
	
	FunctionIdScope* scope = GetOwner();
	ASSERT(scope);
	if (!scope) return String();
	
	String s;
	
	if (args.have_header) {
		s.Cat('\t', args.indent);
		if (is_static) s << "static ";
		s << ret.ToString() << " ";
		s << scope->GetName() << "(";
		for(int i = 0; i < params.GetCount(); i++) {
			if (i) s << ", ";
			String name = params.GetKey(i);
			const TypeExpr& type = params[i];
			s << type.ToString() << " " << name;
		}
		s << ")";
		if (is_const) s << " const";
		if (is_override_anon) s << " override";
		s << ";\n";
	}
	
	if (args.have_impl && !is_ext_impl) {
		CodeArgs subargs = args;
		
		ASSERT(GetOwner() && !GetSubOwner());
		FunctionIdScope& id_scope = *GetOwner();
		s << ret.ToString() << " ";
		s << id_scope.GetClassPath() << "(";
		for(int i = 0; i < params.GetCount(); i++) {
			if (i) s << ", ";
			String name = params.GetKey(i);
			const TypeExpr& type = params[i];
			s << type.ToString() << " " << name;
		}
		s << ")";
		if (is_const) s << " const";
		s << "\n";
		if (impl)
			s << impl->GetCodeString(subargs) << "\n";
		else if (is_alt_impl) {
			s <<	"{\n"
					"\tAlt" << scope->GetName() << "(";
			for(int i = 0; i < params.GetCount(); i++) {
				if (i) s << ", ";
				s << params.GetKey(i);
			}
			s <<	");\n"
					"}\n\n";
		}
		else {
			s.Cat('\t', args.indent); s << "{\n";
			s.Cat('\t', args.indent+1); s << "\n";
			s.Cat('\t', args.indent); s << "}\n";
			s << "\n";
		}
	}
	
	return s;
}










Function& FunctionIdScope::AddFunction() {
	Function& f = funcs.Add();
	f.SetOwner(this);
	return f;
}

String FunctionIdScope::GetTreeString(int indent) const {
	String s;
	for (const Function& o : funcs) {
		s << o.GetTreeString(indent);
	}
	return s;
}

String FunctionIdScope::GetCodeString(const CodeArgs& args, CodeAccess& acc) const {
	String s;
	
	if (args.have_header) {
		for (const Function& o : funcs) {
			CHK_ACCESS
			s << o.GetCodeString(args);
		}
	}
	
	return s;
}

String FunctionIdScope::GetCodeString(const CodeArgs& args) const {
	String s;
	
	if (args.have_header) {
		CodeAccess acc = CodeAccess::ACC_PRIVATE;
		s << GetCodeString(args, acc);
	}
	
	if (args.have_impl) {
		for (const Function& o : funcs) {
			s << o.GetCodeString(args);
		}
	}
	
	return s;
}

String FunctionIdScope::ToString() const {
	String s;
	s << name << ": FunctionIdScope";
	return s;
}



NAMESPACE_TOPSIDE_END

#endif
