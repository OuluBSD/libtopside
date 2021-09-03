#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


TypeExpr& TypeExpr::operator=(const TypeExpr& o) {
	Clear();
	sub <<= o.sub;
	global_ptr = o.global_ptr;
	clsdecl = o.clsdecl;
	return *this;
}

void TypeExpr::Clear() {
	sub.Clear();
	global_ptr = 0;
	clsdecl = 0;
	type = EMPTY;
}

TypeExpr& TypeExpr::SetMove(ClassDecl& clsdecl) {
	Clear();
	this->clsdecl = &clsdecl;
	type = MOVE;
	return *this;
}

String TypeExpr::ToString() const {
	String s;
	
	if (global_ptr && global_ptr != this)
		return global_ptr->ToString();
	
	if (type == EMPTY || !clsdecl)
		;
	else if (type == MOVE) {
		s = clsdecl->GetName();
	}
	else if (type == REFERENCE) {
		s = clsdecl->GetName() + "&";
	}
	else if (type == PTR) {
		s = clsdecl->GetName() + "*";
	}
	else if (type == STATIC_CALL) {
		int i = 0;
		for (TypeExpr& te : sub) {
			if (i == 0) {
				s << te.ToString();
				s << "(*)(";
			}
			else {
				if (i > 1)
					s << ",";
				s << te.ToString();
			}
			s << ")";
			++i;
		}
		s << ")";
	}
	else if (type == OBJECT_CALL) {
		int i = 0;
		Class* cls = clsdecl->GetClass();
		for (TypeExpr& te : sub) {
			if (i == 0) {
				s << te.ToString();
				s << "(" << (cls ? cls->GetPath() : "") << "::*)(";
			}
			else {
				if (i > 1)
					s << ",";
				s << te.ToString();
			}
			s << ")";
			++i;
		}
		s << ")";
	}
	else
		s = "<invalid>";
	
	return s;
}


NAMESPACE_TOPSIDE_END
