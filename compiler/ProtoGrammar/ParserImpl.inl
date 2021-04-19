
namespace GRAMMAR_NAME {


Parser::Parser() : ErrorSource("Parser") {
    keywords.Add("asm");
    keywords.Add("else");
    keywords.Add("new");
    keywords.Add("this");
    keywords.Add("auto");
    keywords.Add("enum");
    keywords.Add("operator");
    keywords.Add("throw");
    keywords.Add("bool");
    keywords.Add("explicit");
    keywords.Add("private");
    keywords.Add("true");
    keywords.Add("break");
    keywords.Add("export");
    keywords.Add("protected");
    keywords.Add("try");
    keywords.Add("case");
    keywords.Add("extern");
    keywords.Add("public");
    keywords.Add("typedef");
    keywords.Add("catch");
    keywords.Add("false");
    keywords.Add("register");
    keywords.Add("typeid");
    keywords.Add("char");
    keywords.Add("float");
    keywords.Add("reinterpret_cast");
    keywords.Add("typename");
    keywords.Add("class");
    keywords.Add("for");
    keywords.Add("return");
    keywords.Add("union");
    keywords.Add("const");
    keywords.Add("friend");
    keywords.Add("short");
    keywords.Add("unsigned");
    keywords.Add("const_cast");
    keywords.Add("goto");
    keywords.Add("signed");
    keywords.Add("using");
    keywords.Add("continue");
    keywords.Add("if");
    keywords.Add("sizeof");
    keywords.Add("virtual");
    keywords.Add("default");
    keywords.Add("inline");
    keywords.Add("static");
    keywords.Add("void");
    keywords.Add("delete");
    keywords.Add("int");
    keywords.Add("static_cast");
    keywords.Add("volatile");
    keywords.Add("do");
    keywords.Add("long");
    keywords.Add("struct");
    keywords.Add("wchar_t");
    keywords.Add("double");
    keywords.Add("mutable");
    keywords.Add("switch");
    keywords.Add("while");
    keywords.Add("dynamic_cast");
    keywords.Add("namespace");
    keywords.Add("template");
    keywords.Add("And");
    keywords.Add("bitor");
    keywords.Add("not_eq");
    keywords.Add("xor");
    keywords.Add("and_eq");
    keywords.Add("compl");
    keywords.Add("or");
    keywords.Add("xor_eq");
    keywords.Add("bitand");
    keywords.Add("not");
    keywords.Add("or_eq");
}

void Parser::Error(String msg, Node& token) {
	ErrorSource::AddError(token.GetToken().loc, "Unexpected token");
}

int Parser::Save() {
	int id = counter++;
	SaveState& st = states.Add(id);
	st.cursor = cursor;
	st.act_count = actions.GetCount();
	return id;
}

void Parser::Next() {
	cursor++;
	if (!err_thrds.IsEmpty()) {
		ErrorThread& t = err_thrds.Top();
		if (cursor == t.err_cursor)
			t.pending_err.Clear();
	}
}

void Parser::Discard(int save_id) {
	states.RemoveKey(save_id);
}

void Parser::LoadNoDiscard(int save_id) {
	SaveState& st = states.Get(save_id);
	cursor = st.cursor;
	actions.SetCount(st.act_count);
}

bool Parser::PassTokenId(String id) {
	if (IsEof()) return false;
	
	Node& n = Get();
	int type = n.GetTokenType();
	String txt = n.GetTokenString();
	
	if (type == TK_ID && txt == id) {
		SetReturned(new Node(n));
		Next();
		return true;
	}
	
	String msg;
	if (1) {
		if (type == TK_ID) {
			msg = "Unexpected identifier";
			if (txt.GetCount())
				msg << " '" << txt << "'";
		}
		else {
			msg = "Unexpected token";
			String ntype = GetNodeTypeString(n);
			if (ntype.IsEmpty())
				ntype = n.GetTypeString();
			if (ntype.GetCount())
				msg << " '" << ntype << "'";
			
			if (id.GetCount())
				msg << " (expected '" << id << "')";
		}
	}
	
	SetError(ERR_PARSER, msg);
	
	return false;
}

bool Parser::PassToken(int token) {
	if (token == -1) {
		if (IsEof()) {
			SetReturned(new Node(NODE_EOF));
			return true;
		}
		return false;
	}
	if (IsEof()) return false;
	
	Node& n = Get();
	int type = n.GetTokenType();
	if (token == type) {
		SetReturned(new Node(n));
		Next();
		return true;
	}
	
	String msg;
	if (1) {
		msg = "Unexpected token";
		
		String ntype;
		if (token < TK_NONCHAR_BEGIN)
			ntype.Cat(token);
		else {
			ntype = GetNodeTypeString(n);
			if (ntype.IsEmpty())
				ntype = n.GetTypeString();
			if (ntype.GetCount())
				msg << " '" << ntype << "'";
		}
		
		if (1)
			msg << " (expected '" << Token::GetTypeStringStatic(token) << "')";
	}
	else {
		msg << "Expected token '";
		if (token < TK_NONCHAR_BEGIN) msg.Cat(token);
		else msg << Token::GetTypeStringStatic(token);
		msg << "'";
	}
	
	if (token == end_token)
		SetError(ERR_PARSER_PROBABLE, msg);
	else
		SetError(ERR_PARSER, msg);
	
	return false;
}

bool Parser::PassToken(const char* tks, int count) {
	int save_id = Save();
	for(int i = 0; i < count; i++) {
		if (!PassToken(tks[i])) {
			Load(save_id);
			return false;
		}
	}
	return true;
}

void Parser::SetReturned(Node* n) {
	returned = n;
}

Node* Parser::DetachReturned() {
	return returned.Detach();
}

void Parser::Act(ActionType type, String str, Node* ptr) {
	Action& a = actions.Add();
	a.type = type;
	a.str_data = str;
	a.node_data = ptr;
}

bool Parser::Process() {
	/*InputStage* stage = GetUnit().GetPreviousStage();
	src = stage->GetOutput();
	if (!src) {
		AddError(FileLocation(), t_("Couldn't get output from previous stage"));
		return false;
	}*/
	ASSERT(src);
	
	//LOG(NodeTreeString(*src));
	
	PushErrScope();
	
	bool rules_succeeded = false;
	try {
		rules_succeeded = FileInput();
		
		ProcessErrorThreads(!rules_succeeded);
	}
	catch (Exc e) {
		struct ProcMsg err;
		err.severity = PROCMSG_ERROR;
		err.msg = e;
		err.line = 0;
		err.col = 0;
		WhenMessage(err);
		return false;
	}
	
	if (!returned.IsEmpty())
		this->root = returned.Detach();
	else
		this->root.Clear();
	
	bool has_errors = false;

	if (!rules_succeeded && actions.IsEmpty()) {
		ErrorThread& t = err_thrds.Top();
		struct ProcMsg e;
		if (t.err_cursor >= 0 && t.pending_err.GetCount()) {
			StringStream ss(t.pending_err);
			ss % e;
		}
		else {
			e.severity = PROCMSG_ERROR;
			e.src = "Parser";
			e.msg = "Parsing failed (without specific errors)";
		}
		WhenMessage(e);
		has_errors = true;
	}
	else {
		for(int i = 0; i < actions.GetCount(); i++) {
			Action& a = actions[i];
			
			if (a.type == ACT_ADD_ERROR) {
				struct ProcMsg e;
				StringStream ss(a.str_data);
				ss.SetLoading();
				ss % e;
				WhenMessage(e);
				has_errors = true;
			}
		}
	}
	
	return !has_errors;
}


bool Parser::CanTryAgain() {
	if (err_thrds.IsEmpty())
		return false;
	ErrorThread& t = err_thrds.Top();
	
	// This is actually wrong! The point of this function is to bang over and the cursor might be reseted with fail flag.
	//		if (t.succ_cursor == cursor) return false;
	
	String str = t.pending_err;
	int depth = 0;
	while (!IsEof()) {
		if (cursor == t.err_cursor && str.GetCount()) {
			Act(ACT_ADD_ERROR, str);
			t.pending_err.Clear();
		}
		Node& n = Get();
		int type = n.GetTokenType();
		if (type == end_token) {
			if (depth == 0) {
				Next();
				return true;
			}
		}
		else if (type == end_scope) {
			if (depth > 0)
				depth--;
			else
				return false;
		}
		else if (type == begin_scope) {
			depth++;
		}
		Next();
	}
	return false;
}

void Parser::SetError(ErrorType e, String msg) {
	ErrorThread& t = err_thrds.Top();
	
	if (cursor > t.max_cursor || (cursor == t.max_cursor && e > t.type)) {
		t.max_cursor = cursor;
		t.max_msg = msg;
		t.type = e;
	}
}

void Parser::ProcessErrorThreads(bool is_failed) {
	if (err_thrds.GetCount() == 0 || (err_thrds.GetCount() == 1 && err_thrds[0].max_cursor == -1)) {
		return;
	}
	
	if (is_failed) {
		ErrorType e = ERR_INVALID;
		ErrorThread& t = err_thrds.Top();
		if (t.max_cursor >= 0) {
			Node& token = src->At(t.max_cursor);
			
			if (0) {
				String summary;
				summary
					<< token.GetTokenFile() << ":"
					<< token.GetTokenLine() << ":"
					<< token.GetTokenCol() << ": "
					<< "error: " << t.max_msg;
				LOG(summary);
			}
			
			struct ProcMsg err;
			err.severity = PROCMSG_ERROR;
			err.src = ErrorSource::GetSource();
			err.file = token.GetTokenFile();
			err.line = token.GetTokenLine();
			err.col = token.GetTokenCol();
			err.msg = t.max_msg;
			
			t.err_cursor = t.max_cursor;
			
			StringStream ss;
			ss.SetStoring();
			ss % err;
			t.pending_err = ss.GetResult();
		}
	}
		
}

void Parser::PushErrScope() {
	ErrorThread& t = err_thrds.Add();
	t.succ_cursor = cursor;
}

void Parser::PopErrScope() {
	ASSERT(err_thrds.GetCount());
	err_thrds.Remove(err_thrds.GetCount() - 1);
}

void Parser::UpdateErrScopeSuccess() {
	ASSERT(err_thrds.GetCount());
	ErrorThread& t = err_thrds.Top();
	t.succ_cursor = cursor;
}

String Parser::GetTypeString(Node& n) {
	String s;
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_TOKEN)) {
			int t = n0.GetTokenType();
			switch (t) {
				case TK_ID:	s << n0.GetTokenString(); break;
				case TK_LESS: s << "<"; break;
				case TK_GREATER: s << ">"; break;
				default: throw Exc("Not implemented");
			}
		}
		else s << GetTypeString(n0);
	}
	return s;
}

String Parser::NodeTreeString(const Node& n, int depth, String tab) {
	if (depth >= 100) return "";
	
	String s;
	for(int i = 0; i < depth; i++)
		s.Cat(tab);
	
	String ntype = GetNodeTypeString(n);
	if (ntype.IsEmpty())
		ntype = n.GetTypeString();
	
	s << ntype;
	
	int block = n.GetBlock();
	if (block >= 0)
		s << "(b" << block << ")";
	
	s << "(" << GetFileName(n.GetTokenFile()) << ":" << n.GetTokenLine() << ":" << n.GetTokenCol() << "):";
	if (n.GetTokenType())
		s << " (" << n.GetTokenType() << ")";
	
	String tk_str = n.GetTokenString();
	if (tk_str.GetCount())
		s << " " << tk_str;
	
	const NodeData* d = n.GetData();
	if (d) {
		for(int i = 0; i < d->GetAttrCount(); i++)
			s << " " <<d->GetAttrKey(i) << "=\"" << d->GetAttr(i) << "\"";
	}
	s << "\n";
	
	for(int i = 0; i < n.GetCount(); i++)
		s << NodeTreeString(n.At(i), depth+1, tab);
	
	return s;
}

String Parser::GetNodeTypeString(const Node& n) {
	switch (n.GetType()) {
		#include GRAMMAR_ENUMTYPE_FILE
	}
	return String();
}








#define TOKENFN1(name, token) \
	bool Parser:: name () { \
		if (IsEof()) return false; \
		Node& n = Get(); \
		int t = n.GetTokenType(); \
		if (t == token) { \
			SetReturned(new Node(n)); \
			Next(); \
			return true; \
		} \
		return false; \
	}


TOKENFN1(STRING, TK_STRING)
TOKENFN1(CHAR, TK_CHAR)
TOKENFN1(IDENTIFIER, TK_ID)

#undef TOKENFN1


bool Parser::CHARLIST() {
	if (IsEof()) return false;
	Node& n0 = Get();
	if (!n0.IsTokenType('[')) return false;
	Next();
	Index<int> chars;
	while (!IsEof()) {
		Node& n = Get();
		if (n.IsTokenType(']')) {
			Next();
			Node* n = new Node(n0);
			String& out = n->GetToken().str_value;
			for(int chr : chars)
				out.Cat(chr);
			SetReturned(n);
			return true;
		}
		String str = n.GetTokenTextValue();
		for(int i = 0; i < str.GetCount(); i++) {
			int chr = str[i];
			if (chars.Find(chr) >= 0)
				return false;
			chars.Add(chr);
		}
		Next();
	}
	return false;
}

}
