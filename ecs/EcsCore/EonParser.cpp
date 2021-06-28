#include "EcsCore.h"


NAMESPACE_ECS_BEGIN

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
	for (Statement& arg : args)
		s << arg.GetTreeString(indent+1);
	return s;
}

String Statement::ToString() const {
	String s;
	s << id.ToString();
	if (!value.IsEmpty())
		s << ": " << value->ToString();
	return s;
}

String LoopDefinition::ToString() const {
	return "loop " + id.ToString();
}

String LoopDefinition::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << "loop " << id.ToString() << ":\n";
	for (const Statement& stmt : stmts) {
		s << stmt.GetTreeString(indent+1) << "\n";
	}
	for (const Statement& stmt : ret_list) {
		s.Cat('\t', indent+1);
		s << "return " << stmt.ToString() << "\n";
	}
	return s;
}

String Value::ToString() const {
	String s;
	if (type == VAL_INVALID) {
		return "invalid";
	}
	else if (type == VAL_CUSTOMER) {
		return customer.ToString();
	}
	else if (type == VAL_STRING) {
		s << "\"" << str << "\"";
	}
	else if (type == VAL_BOOLEAN) {
		s << (b ? "true" : "false");
	}
	else if (type == VAL_ID) {
		return id.ToString();
	}
	else s << "<internal error>";
	return s;
}

String Value::GetValue() const {
	String s;
	if (type == VAL_CUSTOMER) {
		return customer.ToString();
	}
	else if (type == VAL_STRING) {
		s << str;
	}
	else if (type == VAL_BOOLEAN) {
		s << (b ? "true" : "false");
	}
	else if (type == VAL_ID) {
		return id.ToString();
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

String SidechainDefinition::GetTypeString() const {
	switch (type) {
		case CENTER: return "sidechain";
		case NET: return "net_sidechain";
		default: return "invalid";
	}
}

String SidechainDefinition::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << GetTypeString() << " " << id.ToString() << ":\n";
	for (SidechainDefinition& def : chains) {
		s << def.GetTreeString(indent+1) << "\n";
	}
	for (LoopDefinition& def : loops) {
		s << def.GetTreeString(indent+1) << "\n";
	}
	for (const Statement& stmt : ret_list) {
		s.Cat('\t', indent+1);
		s << "return " << stmt.ToString() << "\n";
	}
	return s;
}

String CompilationUnit::GetTreeString(int indent) const {
	return main.GetTreeString(indent);
}







#define PASS_ID(x) if (!Id(x)) {/*LOG(__LINE__);*/ String s = "Expected '"; s.Cat(x); s.Cat('\''); AddError(s); return false;}
#define PASS_CHAR(x) if (!Char(x)) {/*LOG(__LINE__);*/ String s = "Expected '"; s.Cat(x); s.Cat('\''); AddError(s); return false;}

bool Parser::Parse(String content, String filepath) {
	Set(content, filepath);
	DoSpaces();
	return Parse(cunit);
}

bool Parser::Parse(Eon::CompilationUnit& cunit) {
	
	cunit.main.id.Set("main");
	cunit.main.type = SidechainDefinition::CENTER;
	if (!SidechainStmtList(cunit.main))
		return false;
	
	return true;
}

bool Parser::ParseLoop(Eon::LoopDefinition& def) {
	PASS_ID("loop")
	
	if (!ParseId(def.id))
		return false;
	
	PASS_CHAR(':')
	if (!LoopScope(def))
		return false;
	
	PASS_CHAR(';')
	return true;
}

bool Parser::ParseSidechain(Eon::SidechainDefinition& def, Eon::SidechainDefinition::Type t) {
	if (t == Eon::SidechainDefinition::CENTER) {
		PASS_ID("sidechain")
	}
	else if (t == Eon::SidechainDefinition::NET) {
		PASS_ID("net_sidechain")
	}
	
	def.type = t;
	
	if (!ParseId(def.id))
		return false;
	
	PASS_CHAR(':')
	if (!SidechainScope(def))
		return false;
	
	PASS_CHAR(';')
	return true;
}

bool Parser::SidechainStmtList(Eon::SidechainDefinition& def) {
	while (!IsEof() && !IsChar('}')) {
		
		if (EmptyStatement())
			continue;
		else if (IsId("loop")) {
			if (!ParseLoop(def.loops.Add()))
				return false;
		}
		else if (IsId("sidechain")) {
			if (!ParseSidechain(def.chains.Add(), Eon::SidechainDefinition::CENTER))
				return false;
		}
		else if (IsId("net_sidechain")) {
			if (!ParseSidechain(def.chains.Add(), Eon::SidechainDefinition::NET))
				return false;
		}
		else if (IsId("return")) {
			if (!ParseReturnStmt(def.ret_list.Add()))
				return false;
		}
		else {
			AddError("Expected scope specifier");
			return false;
		}
		
	}
	
	return true;
}
bool Parser::SidechainScope(Eon::SidechainDefinition& def) {
	PASS_CHAR('{')
	
	SidechainStmtList(def);
	
	PASS_CHAR('}')
	return true;
}

bool Parser::LoopScope(Eon::LoopDefinition& def) {
	PASS_CHAR('{')
	
	while (!IsChar('}')) {
		if (EmptyStatement())
			continue;
		else if (IsId("return")) {
			if (!ParseReturnStmt(def.ret_list.Add()))
				return false;
		}
		else {
			if (!ParseStmt(def.stmts.Add()))
				return false;
		}
	}
	
	PASS_CHAR('}')
	return true;
}

bool Parser::ParseStmt(Eon::Statement& stmt) {
	if (!ParseId(stmt.id))
		return false;
	
	PASS_CHAR(':')
	stmt.value.Create();
	if (!ParseValue(*stmt.value))
		return false;
	
	if (IsChar('{')) {
		if (!ParseStmtArguments(stmt))
			return false;
	}
	
	PASS_CHAR(';')
	return true;
}

bool Parser::ParseStmtArguments(Eon::Statement& stmt) {
	PASS_CHAR('{')
	
	while (!IsChar('}')) {
		if (EmptyStatement())
			continue;
		
		if (!ParseStmt(stmt.args.Add()))
			return false;
	}
	
	PASS_CHAR('}')
	return true;
}

bool Parser::ParseValue(Eon::Value& v) {
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
		if (!ParseId(v.id))
			return false;
		return true;
	}
	else if (IsString()) {
		v.type = Eon::Value::VAL_STRING;
		v.str = ReadString();
		return true;
	}
	else if (IsChar('{')) {
		v.type = Eon::Value::VAL_CUSTOMER;
		MemSwap(v.id, v.customer.id);
		return LoopScope(v.customer);
	}
	else {
		AddError("Unexpected token");
		return false;
	}
}

bool Parser::ParseId(Eon::Id& id) {
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

bool Parser::ParseReturnStmt(Eon::Statement& stmt) {
	PASS_ID("return")
	if (!ParseId(stmt.id))
		return false;
	if (Char(':')) {
		stmt.value.Create();
		if (!ParseValue(*stmt.value))
			return false;
	}
	PASS_CHAR(';')
	return true;
}

void Parser::AddError(String msg) {
	String s;
	s << GetFileName() << ":" << GetLine() << ":" << GetColumn() << ": error: " << msg;
	LOG(s);
}


#undef PASS_CHAR
#undef PASS_ID

}
NAMESPACE_ECS_END
