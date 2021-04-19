namespace GRAMMAR_NAME {


PostParser::PostParser() : ErrorSource("PostParser") {
	
}

bool PostParser::Process() {
	ASSERT(src);
	
	//LOG(NodeTreeString(*src));
	
	tokens.Reserve(1 << 13);
	tokens.SetCount(0);
	cmds.SetCount(0);
	cursor = 0;
	
	
	bool rules_succeeded = false;
	try {
		rules_succeeded = FileInput(*src);
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
	
	/*if (!ProcessActions())
		return false;*/
	
	
	
	bool has_errors = false;

	/*if (!rules_succeeded && actions.IsEmpty()) {
		ErrorThread& t = err_thrds.Top();
		struct ProcMsg e;
		if (t.err_cursor >= 0 && t.pending_err.GetCount()) {
			StringStream ss(t.pending_err);
			ss % e;
		}
		else {
			e.severity = PROCMSG_ERROR;
			e.src = "PostParser";
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
	}*/
	
	/*if (1) {
		Dump();
	}*/
	
	return !has_errors;
}

bool PostParser::TestCharLiteral(const Node& n, const char* str) {
	ASSERT(str && str[0] != 0);
	if (str[1] == 0) {
		char chr = str[0];
		int tk_type = n.GetTokenType();
		if (tk_type == chr) {
			return true;
		}
	}
	if (n.GetCount() == 1) {
		const Node& n0 = n[0];
		if (n0.IsType(NODE_CHAR_LITERAL)) {
			String value = n0.GetTokenString();
			if (value.Compare(str) == 0)
				return true;
		}
	}
	return false;
}

bool PostParser::TestStringLiteral(const Node& n, const char* str) {
	ASSERT(str && str[0] != 0);
	if (str[1] == 0) {
		char chr = str[0];
		int tk_type = n.GetTokenType();
		if (tk_type == chr) {
			return true;
		}
	}
	if (n.GetCount() == 1) {
		const Node& n0 = n[0];
		if (n0.IsType(NODE_STRING_LITERAL)) {
			String value = n0.GetTokenString();
			if (value.Compare(str) == 0)
				return true;
		}
	}
	return false;
}

void PostParser::PushCommand(const char* str, int str_len) {
	Command& cmd = cmds.Add();
	cmd.indent = indent;
	cmd.raw = String(str, str_len);
	
	
	int a = 0;
	for(int i = 0; i < str_len; i++) {
		char c = str[i];
		
		if (c == ' ') {
			int b = i;
			FileLocation fl;
			fl.cursor = cursor + indent + a;
			fl.line = cmds.GetCount() - 1;
			fl.col = indent + a;
			
			Token& tk = tokens.Add();
			if (a + 1 == b) {
				tk.type = str[a];
				
				if (tk.type == 'b')
					indent++;
				else if (tk.type == 'e')
					indent--;
			}
			else {
				tk.type = TK_ID;
				tk.str_value = String(str + a, b - a);
			}
			tk.loc = fl;
			
			fl.cursor = cursor + indent + b;
			fl.col = indent + b;
			tk.end = fl;
			
			a = b + 1;
		}
	}
	
	if (a < str_len) {
		int b = str_len;
		FileLocation fl;
		fl.cursor = cursor + indent + a;
		fl.line = cmds.GetCount() - 1;
		fl.col = indent + a;
		
		Token& tk = tokens.Add();
		if (a + 1 == b) {
			tk.type = str[a];
			
			if (tk.type == 'b')
				indent++;
			else if (tk.type == 'e')
				indent--;
		}
		else {
			tk.type = TK_ID;
			tk.str_value = String(str + a, b - a);
		}
		tk.str_value = String(str + a, b - a);
		tk.loc = fl;
		
		fl.cursor = cursor + indent + b;
		fl.col = indent + b;
		tk.end = fl;
	}
	
	
	cursor += indent + str_len + 1;
}

String PostParser::NodeTreeString(const Node& n, int depth, String tab) {
	TODO
}

void PostParser::Dump() {
	LOG("Dumping post-parser:");
	for(int i = 0; i < cmds.GetCount(); i++) {
		const Command& cmd = cmds[i];
		String line;
		line.Cat('\t', std::max(cmd.indent, 0));
		line.Cat(cmd.raw);
		LOG(line);
	}
}


#define NODE_CHECK(rule, value) void PostParser:: rule (const Node& n) {\
	IS_TYPE(n, value); \
}


NODE_CHECK(Eof, NODE_EOF);
NODE_CHECK(CharLiteral, NODE_CHAR_LITERAL);
NODE_CHECK(StringLiteral, NODE_STRING_LITERAL);
NODE_CHECK(Identifier, NODE_IDENTIFIER);
NODE_CHECK(CharList, NODE_CHAR_LIST);


}
