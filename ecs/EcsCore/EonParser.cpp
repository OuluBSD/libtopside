#include "EcsCore.h"


NAMESPACE_TOPSIDE_BEGIN

namespace Eon {

void Statement::operator=(const Statement& v) {
	id = v.id;
	if (v.value.IsEmpty())
		value.Clear();
	else {
		value.Create();
		*value = *v.value;
	}
}




String Id::ToString() const {
	String s;
	for(String& part : parts) {
		if (!s.IsEmpty())
			s << ".";
		s << part;
	}
	return s;
}

String Id::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString();
	return s;
}

String Statement::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << id.ToString();
	if (value.IsEmpty())
		s << ": <no value>";
	else
		s << ":\n" << value->GetTreeString(indent+1);
	return s;
}

String CustomerDefinition::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << id.ToString() << ":\n";
	for (Statement& stmt : stmts) {
		s << stmt.GetTreeString(indent+1) << "\n";
	}
	return s;
}

String Value::GetTreeString(int indent) const {
	String s;
	if (type == VAL_INVALID) {
		s.Cat('\t', indent);
		s << "invalid";
	}
	else if (type == VAL_CUSTOMER) {
		return customer.GetTreeString(indent);
	}
	else if (type == VAL_STRING) {
		s.Cat('\t', indent);
		s << "\"" << str << "\"";
	}
	else if (type == VAL_BOOLEAN) {
		s.Cat('\t', indent);
		s << (b ? "true" : "false");
	}
	else if (type == VAL_ID) {
		return id.GetTreeString(indent);
	}
	else s << "<internal error>";
	return s;
}

String CompilationUnit::GetTreeString(int indent) const {
	String s;
	for (CustomerDefinition& def : customers) {
		s << def.GetTreeString(indent) << "\n";
	}
	return s;
}





#define PASS_CHAR(x) if (!Char(x)) {String s = "Expected '"; s.Cat(x); s.Cat('\''); AddError(s); return false;}

bool Parser::Parse(String content, String filepath) {
	Set(content, filepath);
	DoSpaces();
	return Parse(cunit);
}

bool Parser::Parse(Eon::CompilationUnit& cunit) {
	while (!IsEof()) {
		if (!Parse(cunit.customers.Add()))
			return false;
	}
	return true;
}

bool Parser::Parse(Eon::CustomerDefinition& def) {
	if (!Parse(def.id))
		return false;
	
	return CustomerScope(def);
}

bool Parser::CustomerScope(Eon::CustomerDefinition& def) {
	PASS_CHAR(':')
	PASS_CHAR('{')
	
	while (!IsChar('}')) {
		if (EmptyStatement())
			continue;
		if (!Parse(def.stmts.Add()))
			return false;
	}
	
	PASS_CHAR('}')
	return true;
}

bool Parser::Parse(Eon::Statement& stmt) {
	if (!Parse(stmt.id))
		return false;
	
	PASS_CHAR(':')
	stmt.value.Create();
	if (!Parse(*stmt.value))
		return false;
	
	PASS_CHAR(';')
	return true;
}

bool Parser::Parse(Eon::Value& v) {
	if (Id("true")) {
		v.type = Eon::Value::VAL_BOOLEAN;
		v.b = true;
		return true;
	}
	else if (Id("false")) {
		v.type = Eon::Value::VAL_BOOLEAN;
		v.b = false;
		return true;
	}
	else if (IsId()) {
		v.type = Eon::Value::VAL_ID;
		if (!Parse(v.id))
			return false;
		if (IsChar(':')) {
			v.type = Eon::Value::VAL_CUSTOMER;
			MemSwap(v.id, v.customer.id);
			return CustomerScope(v.customer);
		}
		return true;
	}
	else if (IsString()) {
		v.type = Eon::Value::VAL_STRING;
		v.str = ReadString();
		return true;
	}
	else {
		AddError("Unexpected token");
		return false;
	}
}

bool Parser::Parse(Eon::Id& id) {
	if (!IsId()) {
		AddError("Expected id");
		return false;
	}
	id.parts.Add(ReadId());
	
	while (Char('.')) {
		if (!IsId()) {
			AddError("Expected id");
			return false;
		}
		id.parts.Add(ReadId());
	}
	return true;
}

void Parser::AddError(String msg) {
	String s;
	s << GetFileName() << ":" << GetLine() << ":" << GetColumn() << ": error: " << msg;
	LOG(s);
}




}
NAMESPACE_TOPSIDE_END
