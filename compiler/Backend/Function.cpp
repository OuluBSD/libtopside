#include "Backend.h"


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
	s << name << ": Function";
	return s;
}

String Function::GetCodeString(const CodeArgs& args) const {
	if (!IsContained(args))
		return String();
	
	String s;
	
	if (args.have_header) {
		
		TODO
		
	}
	
	if (args.have_impl) {
		
		TODO
		
	}
	
	return s;
}










Function& FunctionIdScope::AddFunction() {
	Function& f = funcs.Add();
	f.SetParent(this);
	return f;
}

String FunctionIdScope::GetTreeString(int indent) const {
	TODO
}

String FunctionIdScope::GetCodeString(const CodeArgs& args) const {
	TODO
}

String FunctionIdScope::ToString() const {
	TODO
}



NAMESPACE_TOPSIDE_END
