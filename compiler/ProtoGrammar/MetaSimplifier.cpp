#include "Grammar.h"

#ifndef flagBOOTSTRAP

NAMESPACE_OULU_BEGIN


MetaSimplifier::MetaSimplifier(AstResolver& ar) : ErrorSource("MetaSimplifier"), ar(ar) {
	
}

bool MetaSimplifier::Process() {
	tmp.Clear();
	
	if (!src) {
		PushError("No source set");
		return false;
	}
	
	if (!FileInput(*src)) {
		return false;
	}
	
	
	return true;
}

String MetaSimplifier::NodeTreeString(const Node& n, int depth, String tab) {
	TODO
}

void MetaSimplifier::Dump() {
	if (root) {
		LOG("Dumping post-parser:"); LOG(NodeTreeString(*root));
	}
	else {
		LOG("No root to dump");
	}
}

void MetaSimplifier::PushError(String msg) {
	ErrorSource::AddError(FileLocation(), msg);
}

bool MetaSimplifier::Visit(const Node& in, NodeVec& out, int* pos, int* type, int count) {
	if (!count) {
		Ast::Node* n = VisitNode(in);
		if (n) {
			out.Add(n);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		ASSERT(count > 0);
		
		int p = *pos;
		if (p < 0) {
			int t = *type;
			// Visit all
			if (t == -2) {
				for (const Node& n : in.Sub())
					if (!Visit(n, out, pos + 1, type + 1, count - 1))
						return false;
				return true;
			}
			// Get type name of the node
			else if (t == -3) {
				Token tk;
				tk.type = TK_ID;
				tk.str_value = Meta::StaticParser().GetNodeTypeString(in);
				Node n;
				n.FromToken(tk);
				out.Add(AstLiteral(n));
				return true;
			}
			else if (t < 0) {
				PushError("Unknown type value");
				return false;
			}
			// Visit specific node type
			else {
				int found = 0;
				for (const Node& n : in.Sub()) {
					if (n.GetType() == t) {
						found++;
						if (!Visit(n, out, pos + 1, type + 1, count - 1))
							return false;
					}
				}
				/*Not error until optionals are handled: if (!found) {
					PushError("Couldn't find type");
					return true;
				}*/
				return true;
			}
		}
		// Visit specific position
		else {
			return Visit(in[p], out, pos + 1, type + 1, count - 1);
		}
	}
	
	throw Exc("Never");
}

void MetaSimplifier::AstBeginStmt() {
	ar.BeginStmt();
}

Ast::Node* MetaSimplifier::AstCompilationUnit(NodeVec& cont) {
	TODO
}

Ast::Node* MetaSimplifier::AstCall(NodeVec& cont) {
	TODO
}

Ast::Node* MetaSimplifier::AstCall(NodeVec& id, NodeVec& cont) {
	TODO
}

Ast::Node* MetaSimplifier::AstCallArg(NodeVec& pre, NodeVec& pos, NodeVec& cont) {
	TODO
}

Ast::Node* MetaSimplifier::AstExpressionStatement(NodeVec& cont) {
	TODO
}

Ast::Node* MetaSimplifier::AstIdentifier(NodeVec& cont) {
	if (cont.GetCount() == 1) {
		Ast::Literal* lit = dynamic_cast<Ast::Literal*>(&cont[0]);
		if (lit)  {
			if (lit->str.IsEmpty()) {
				PushError("Expected string value for identifier");
				return 0;
			}
				
			return ar.NewExprId(lit->str);
		}
		else {
			PushError("Unexpected argument for AstIdentifier");
			return 0;
		}
	}
	else {
		PushError("Invalid size of arguments for AstIdentifier");
		return 0;
	}
}

Ast::Node* MetaSimplifier::AstToken(const Node& n) {
	if (n.IsType(NODE_TOKEN)) {
		int type = n.GetTokenType();
		
		if (type == TK_ID) {
			String s = n.GetTokenString();
			if (s.IsEmpty()) {
				PushError("Empty token string for AstToken");
				return 0;
			}
			return ar.NewExprId(s);
		}
		else {
			PushError("Unimplemented argument for AstToken");
			return 0;
		}
	}
	else {
		//LOG(Meta::StaticParser().NodeTreeString(n));
		//TODO;
		PushError("Unexpected argument for AstToken");
		return 0;
	}
}

Ast::Node* MetaSimplifier::AstLiteral(const Node& n) {
	if (n.IsType(NODE_TOKEN)) {
		int type = n.GetTokenType();
		
		if (type == TK_ID) {
			String s = n.GetTokenString();
			if (s.IsEmpty()) {
				PushError("Empty token string for AstLiteral");
				return 0;
			}
			return new Ast::Literal(s);
		}
		else {
			PushError("Unimplemented argument for AstLiteral");
			return 0;
		}
	}
	else {
		//LOG(Meta::StaticParser().NodeTreeString(n));
		//TODO;
		PushError("Unexpected argument for AstLiteral");
		return 0;
	}
}


}

#endif

