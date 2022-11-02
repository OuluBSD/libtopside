#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN

TokenNode::TokenNode() {
	
}

TokenNode& TokenNode::Add() {
	TokenNode& s = sub.Add();
	s.SetOwner(this);
	return s;
}

String TokenNode::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const TokenNode& n : sub) {
		s << n.GetTreeString(indent+1);
	}
	return s;
}

String TokenNode::GetCodeString(const CodeArgs& args) const {
	TODO
}

String TokenNode::ToString() const {
	if (begin) {
		String s;
		int i = 0;
		const Token* iter = begin;
		while (iter != end) {
			if (i++ > 0) s.Cat(' ');
			s.Cat(iter->GetTextValue());
			iter++;
		}
		return s;
	}
	else return "<no token>";
}











TokenStructure::TokenStructure() :
	ErrorSource("TokenStructure")
{
	root.SetOwner(this);
}

bool TokenStructure::ProcessEon(const Tokenizer& t) {
	root.Clear();
	
	const Vector<Token>& tokens = t.GetTokens();
	
	iter = tokens.Begin();
	end = tokens.End();
	
	return ParseBlock(root);
}

bool TokenStructure::ParseBlock(TokenNode& n) {
	while (!IsEnd()) {
		if (Current().IsType(TK_DEDENT))
			break;
		
		if (Current().IsType(TK_INDENT)) {
			if (!PassType(TK_INDENT))
				return false;
			
			ParseBlock(n);
			
			if (!PassType(TK_DEDENT))
				return false;
		}
		else {
			TokenNode& s = n.Add();
			if (!ParseStatement(s, false))
				return false;
		}
	}
	return true;
}

bool TokenStructure::ParseStatement(TokenNode& n, bool break_comma) {
	ASSERT(!IsEnd());
	n.begin = &Current();
	ASSERT(!n.begin->IsType(':'));
	ASSERT(!n.begin->IsType(TK_INDENT));
	bool has_block = false;
	
	while (!IsEnd()) {
		const Token& t = Current();
		n.end = &t;
		
		if (t.IsType(':')) {
			Next();
			has_block = true;
			break;
		}
		else if (t.IsType(TK_END_STMT)) {
			Next();
			break;
		}
		else if (t.IsType(TK_EOF)) {
			Next();
			break;
		}
		else if (t.IsType(TK_DEDENT))
			break;
		
		Next();
		
		if (break_comma && Current().IsType(','))
			break;
	}
	
	if (has_block) {
		if (Current().IsType(TK_INDENT)) {
			if (!PassType(TK_INDENT))
				return false;
			
			ParseBlock(n);
			
			if (!PassType(TK_DEDENT))
				return false;
		}
		else {
			TokenNode& s = n.Add();
			if (!ParseStatement(s, true))
				return false;
			
			while (Current().IsType(',')) {
				Next();
				if (!ParseStatement(s, true))
					return false;
			}
			
		}
	}
	
	return true;
}

bool TokenStructure::PassType(int tk) {
	const Token& t = Current();
	if (t.IsType(tk)) {
		Next();
		return true;
	}
	AddError(t.loc, "expected '" + Token::GetTypeStringStatic(tk) + "', but got '" + t.GetTypeString() + "'");
	return false;
}

String TokenStructure::GetTreeString(int indent) const {
	return root.GetTreeString();
}

String TokenStructure::GetCodeString(const CodeArgs& args) const {
	return root.GetCodeString(args);
}

String TokenStructure::ToString() const {
	return root.ToString();
}



NAMESPACE_TOPSIDE_END
