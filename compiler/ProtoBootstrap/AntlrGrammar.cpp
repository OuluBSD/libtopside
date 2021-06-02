#include "Bootstrap.h"

#ifdef flagMAIN

NAMESPACE_TOPSIDE_BEGIN


int Uncapitalize(String& s, int begin, int end) {
	String repl;
	bool to_lower = true;
	
	bool all_upper = true;
	for(int i = begin; i < end; i++) {
		int chr = s[i];
		if (IsAlpha(chr) && IsUpper(chr))
			;
		else
			all_upper = false;
	}
	if (all_upper)
		return 0;
	
	for(int i = begin; i < end; i++) {
		int chr = s[i];
		
		if (to_lower) {
			if (IsAlNum(chr)) {
				repl.Cat(ToLower(chr));
				to_lower = false;
			}
		}
		else {
			if (IsAlpha(chr) && IsUpper(chr)) {
				repl.Cat('_');
				repl.Cat(ToLower(chr));
			}
			else if (IsAlNum(chr) || chr == '_')
				repl.Cat(chr);
			else
				to_lower = true;
		}
	}
	
	int len = end - begin;
	int diff = repl.GetCount() - len;
	
	s = s.Left(begin) + repl + s.Mid(end);
	
	return diff;
}

String Uncapitalize(String s) {
	enum {SEARCH_BEGIN, SEARCH_END};
	int mode = SEARCH_BEGIN;
	int begin, end;
	
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		
		if (chr == '\"') {
			s = s.Left(i) + "\'" + s.Mid(i+1);
		}
		else if (mode == SEARCH_BEGIN) {
			
			if (IsAlpha(chr) && IsUpper(chr)) {
				begin = i;
				mode = SEARCH_END;
			}
		}
		else {
			if (IsAlpha(chr) || chr == '_') {
				
			}
			else {
				end = i;
				mode = SEARCH_BEGIN;
				i += Uncapitalize(s, begin, end);
			}
		}
	}
	
	if (mode == SEARCH_END) {
		end = s.GetCount();
		mode = SEARCH_BEGIN;
		Uncapitalize(s, begin, end);
	}
	
	return s;
}



hash_t Element::GetHashValue() {
	CombineHash h;
	h << blocks.GetCount() << 1;
	for(int i = 0; i < blocks.GetCount(); i++)
		h << blocks[i].GetHashValue() << 1;
	h << key.GetHashValue() << 1
		<< (int)is_opt << 1
		<< (int)is_many << 1
		<< (int)is_term << 1
		<< (int)is_set << 1
		<< (int)is_neg << 1
		<< (int)is_char << 1;
	return h;
}


bool RemovePrePost(String& s) {
	int a, b;
	
	while ((a = s.Find("(<")) >= 0) {
		b = s.Find(")", a);
		if (b < 0) return false;
		b++;
		
		s = s.Left(a) + s.Mid(b);
	}
	
	while ((a = s.Find("(>")) >= 0) {
		b = s.Find(")", a);
		if (b < 0) return false;
		b++;
		
		s = s.Left(a) + s.Mid(b);
	}
	
	return true;
}



bool AntlrGrammar::Load(String g4_path) {
	RemoteParser rem;
	String g = LoadFile(g4_path);
	
	{
		int i = g.Find("// BEGIN RULES");
		if (i < 0) {
			LOG("Not found in grammar: '// BEGIN RULES'");
			return false;
		}
		i = g.Find("\n", i) + 1;
		ASSERT(i > 0);
		g = g.Mid(i);
	}
	
	{
		int a = g.Find("/* BEGIN BOOTSTRAP EXTRA");
		if (a < 0) {
			LOG("Not found in grammar: '/* BEGIN BOOTSTRAP EXTRA'");
			return false;
		}
		int b = g.Find("\n", a) + 1;
		ASSERT(b > 0);
		g = g.Left(a) + g.Mid(b);
	}
	
	{
		int a = g.Find("*/");
		if (a < 0) {
			LOG("Not found in grammar: '/* BEGIN BOOTSTRAP EXTRA'");
			return false;
		}
		int b = g.Find("\n", a) + 1;
		ASSERT(b > 0);
		g = g.Left(a) + g.Mid(b);
	}
	

	if (!RemovePrePost(g)) {
		LOG("Removing pre & post failed");
		return false;
	}
	
	String g4 = Uncapitalize(g);
	g4 = "grammar " + GetFileTitle(g4_path) + ";\n\n" + g4;
	
	LOG(g4);
	
	
	String parsed = rem.ParseG4(g4);
	//LOG(parsed);
	CParser p(parsed);
	root.Clear();
	
	rem.ReadNode(p, root);
	LOG(NodeTreeString(root));
	
	VisitGrammarSpec(root);
	
	return true;
}

String AntlrGrammar::GetCppParserHeader() {
	return header;
}

String AntlrGrammar::GetCppParserEnum() {
	return enumstr;
}

String AntlrGrammar::GetCppParserEnumType() {
	return enumtypestr;
}


String AntlrGrammar::GetPython3ParserHeader() {
	return header;
}

String AntlrGrammar::GetPython3ParserEnum() {
	return enumstr;
}

String AntlrGrammar::GetPython3ParserEnumType() {
	return enumtypestr;
}


bool IsId(String s) {
	//if (s.Left(3) == "TK_") return false;
	String mid = s.Mid(1, s.GetCount()-2);
	if (mid.GetCount() >= 2) {
		bool alphadigit = true;
		for(int i = 0; i < mid.GetCount(); i++) {
			int chr = mid[i];
			if (IsAlpha(chr) || IsDigit(chr) || chr == '_')
				;
			else
				alphadigit = false;
		}
		return alphadigit;
	}
	
	return false;
}

void TestPartToken(String& out, String key, bool is_opt) {
	if (key.Find("Identifier") == 0) {
		out << "\t\tTEST_PART(" << key << ");\n";
	}
	else {
		out << "\t\tTEST_PART_TOKEN";
		
		if (key.Left(3) == "TK_")
			;
		else if (IsId(key))
			out << "_ID";
		else if (key.GetCount() > 3)
			out << (key.GetCount()-2);
		
		if (is_opt)
			out << "_OPT";
		if (key.GetCount() > 3)
			key.Replace("'", "\"");
		key.Replace("\\", "\\\\");
		out << "(" << key << ");\n";
	}
}

String AntlrGrammar::GetCppParserImplementation() {
	String out, first, second;
	
	may_fail_parts.Clear();
	new_scope.Clear();
	act.Clear();
	pre_act.Clear();
	iter_act.Clear();
	
	new_scope.Add("FileInput");
	new_scope.Add("EmptyStmt");
	new_scope.Add("KeyValueStmt");
	new_scope.Add("CharRuleStmt");
	new_scope.Add("TokenRuleStmt");
	new_scope.Add("RuleExprStmt");
	
	//may_fail_parts.Add("");
	//act.Add("", "ACT_");
	//pre_act.Add("", "ACT_");
	//iter_act.Add("", "ACT_");
	
	return GetGenericParserImplementation();
}

String AntlrGrammar::GetPython3ParserImplementation() {
	may_fail_parts.Clear();
	new_scope.Clear();
	act.Clear();
	pre_act.Clear();
	iter_act.Clear();
	
	new_scope.Add("FileInput");
	new_scope.Add("ModuleSuiteStmt");
	new_scope.Add("PkgSuiteStmt");
	new_scope.Add("VersionSuiteStmt");
	new_scope.Add("DepSuiteStmt");
	new_scope.Add("ClassSuiteStmt");
	new_scope.Add("KeyValueStmt");
	new_scope.Add("PassStmt");
	
	// Those, which are between TK_INDENT and TK_DEDENT and have sub-rules with END_STMT ending
	// TODO: recognize automatically
	may_fail_parts.Add("ScopeModuleSuiteStmt");
	may_fail_parts.Add("ScopePkgSuiteStmt");
	may_fail_parts.Add("ScopeVersionSuiteStmt");
	may_fail_parts.Add("ScopeDepSuiteStmt");
	may_fail_parts.Add("ScopeClassSuiteStmt");
	
	return GetGenericParserImplementation();
}

String AntlrGrammar::GetGenericParserImplementation() {
	String out, first, second;
	
	
	for(int i = 0; i < rules.GetCount(); i++) {
		Rule& rule = rules[i];
		
		if (rule.key.Find("UserDefined") == 0) {
			rule.is_lex = false;
		}
		
		LOG("EntityTemplate& et_" << ToVarName(rule.key) << " = AddEntityTemplate(NODE_" << ToCaps(rule.key) << ");");
		
		
		bool has_scope = new_scope.Find(rule.key) >= 0;
		String scope_act;
		if (has_scope) scope_act = new_scope.Get(rule.key);
		bool may_fail_part = may_fail_parts.Find(rule.key) >= 0;
		
		bool has_act = act.Find(rule.key) >= 0;
		bool has_pre_act = pre_act.Find(rule.key) >= 0;
		bool has_iter_act = iter_act.Find(rule.key) >= 0;
		String act_str, pre_act_str, iter_act_str;
		if (has_act) act_str = act.Get(rule.key);
		if (has_pre_act) pre_act_str = pre_act.Get(rule.key);
		if (has_iter_act) iter_act_str = iter_act.Get(rule.key);
		
		bool is_optmany = rule.key.Right(7) == "OptMany";
		
		header << "\tbool " << rule.key << "();\n";
		enumstr << "NODE_" << ToCaps(rule.key) << ",\n";
		enumtypestr << "case NODE_" << ToCaps(rule.key) << ": return \"" << rule.key << "\";\n";
		
		if (rule.is_lex) {
			if (rule.blocks.GetCount() == 1 && rule.blocks[0].el.GetCount() == 1 && IsId(rule.blocks[0].el[0].key)) {
				ASSERT(!has_scope);
				ASSERT(!has_act);
				ASSERT(!has_pre_act);
				
				Element& el = rule.blocks[0].el[0];
				
				String s = el.key;
				s.Replace("'", "\"");
				
				out << "bool Parser::" << rule.key << "() {\n";
				if (FindRule(s) || s.Find("Identifier") == 0)
					out << "\treturn " << s << "();\n";
				else
					out << "\treturn PassTokenId(" << s << ");\n";
				out << "}\n\n";
			}
			continue;
		}
		
		
		out << "bool Parser::" << rule.key << "() {\n";
		out << "\tRET(" << ToCaps(rule.key) << ")\n";
		bool has_saved = false;
		
		if (has_pre_act) {
			out << "\tSAVE;\n";
			out << "\tSINGLE_PRE_ACT(" << pre_act_str << ");\n";
			has_saved = true;
		}
		
		bool has_lrec = false, has_rrec = false;
		for(int j = 0; j < rule.blocks.GetCount(); j++) {
			Block& b = rule.blocks[j];
			
			if (b.el.GetCount() > 1) {
				Element& first = b.el[0];
				Element& last = b.el[b.el.GetCount()-1];
				
				if (first.key == rule.key) {
					has_lrec = true;
				}
				else if (last.key == rule.key) {
					has_rrec = true;
				}
			}
		}
		ASSERT(!(has_lrec && has_rrec));
		
		if (!has_lrec && !has_rrec) {
			if (has_scope) {
				if (!has_saved) {
					out << "\tSAVE;\n";
					has_saved = true;
				}
				if (scope_act.GetCount())
					out << "\tSINGLE_ACT(" << scope_act << ");\n";
			}
			for(int j = 0; j < rule.blocks.GetCount(); j++) {
				Block& b = rule.blocks[j];
				out << "\tBLOCK_BEGIN(" << j << ");\n";
				if (b.el.GetCount() == 0) {
					out << "\tTEST_PASS;\n";
				}
				else if (b.el.GetCount() == 1 && !may_fail_part) {
					Element& e = b.el[0];
					Rule* r = FindRule(e.key);
					
					if ((e.is_char || !r) && e.key.Find("Identifier") != 0) {
						out << "\t";
						if (IsId(e.key))
							out << "TEST_TOKEN_ID";
						else if (e.key.GetCount() > 3)
							out << "TEST_TOKEN" << (e.key.GetCount()-2);
						else
							out << "TEST_TOKEN";
						if (has_saved)
							out << "_DISCARDSAVED";
						String s = e.key;
						if (e.key.GetCount() > 3) s.Replace("'", "\"");
						out << "(" << s << ", " << (has_act ? act_str : "ACT_INVALID") << ")\n";
					}
					else {
						if (!has_saved)
							out << "\tTEST(" << e.key << ", " << (has_act ? act_str : "ACT_INVALID") << ")\n";
						else
							out << "\tTEST_DISCARDSAVED(" << e.key << ", " << (has_act ? act_str : "ACT_INVALID") << ")\n";
					}
				}
				else {
					if (!has_saved) {
						out << "\tSAVE;\n";
						has_saved = true;
					}
					if (may_fail_part)
						out << "\tPRE_MAY_FAIL\n";
					out << "\twhile (true) {\n";
					
					Element& first = b.el[0];
					Element& last = b.el[b.el.GetCount()-1];
					
					if (first.key == rule.key) {
						Panic("Didn't expect left recursive here");
					}
					else if (last.key == rule.key) {
						Panic("Didn't expect right recursive here");
					}
					else {
						for(int k = 0; k < b.el.GetCount(); k++) {
							Element& e = b.el[k];
							
							Rule* r = FindRule(e.key);
							if (e.is_char || !r) {
								TestPartToken(out, e.key, e.is_opt);
							}
							else {
								if (!e.is_opt) {
									out << "\t\tTEST_PART(" << e.key << ");\n";
								}
								else {
									out << "\t\tTEST_PART_OPT(" << e.key << ");\n";
								}
							}
						}
					}
					if (has_act)
						out << "\t\tSINGLE_ACT(" << act_str << ");\n";
					out << "\t\tDISCARD; SET_RETURNED;";
					out << " return true;\n";
					out << "\t}\n";
					if (may_fail_part)
						out << "\tPOST_MAY_FAIL;\n";
					out << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";
				}
			}
		}
		else if (is_optmany) {
			String orig_rule = rule.key.Left(rule.key.GetCount()-4-3);
			
			if (!has_saved) {
				out << "\tSAVE;\n";
				has_saved = true;
			}
			out << "\t{\n";
			out << "\t\twhile (true) {\n";
			out << "\t\t\tTEST_PART_OPT_BREAK(" << orig_rule << ");\n";
			out << "\t\t}\n";
			out << "\t\tDISCARD; SET_RETURNED; return true;\n";
			out << "\t}\n";
		}
		else if (has_lrec) {
			header << "\tbool " << rule.key << "First();\n";
			header << "\tbool " << rule.key << "Second();\n";
			enumstr << "NODE_" << ToCaps(rule.key) << "_ITEM,\n";
			enumtypestr << "case NODE_" << ToCaps(rule.key) << "_ITEM: return \"" << rule.key << "Item\";\n";
			
			LOG("EntityTemplate& et_" << ToVarName(rule.key) << "_item = AddEntityTemplate(NODE_" << ToCaps(rule.key) << "_ITEM);");
			
			if (has_scope) {
				if (!has_saved) {
					out << "\tSAVE;\n";
					has_saved = true;
				}
				if (scope_act.GetCount())
					out << "\tSINGLE_ACT(" << scope_act << ");\n";
			}
			if (may_fail_part)
				out << "\tPRE_MAY_FAIL\n";
			if (!has_saved)
				out << "\tbool is_fail = false;\n";
			out << "\twhile (!IsEof() && !IsToken(" << tk_dedent << ")) {\n";
			if (has_iter_act) {
				out << "\t\tif (ret->IsEmpty()) {TEST_PART_ITER_ACT(" << rule.key << "First, " << iter_act_str << ");}\n";
				out << "\t\telse {TEST_PART_ITER_ACT(" << rule.key << "Second, " << iter_act_str << ");}\n";
			}
			else {
				out << "\t\tif (ret->IsEmpty()) {TEST_PART(" << rule.key << "First);}\n";
				out << "\t\telse {TEST_PART(" << rule.key << "Second);}\n";
			}
			if (may_fail_part)
				out << "\t\tUPDATE_SUCC_POINT;\n";
			out << "\t}\n";
			if (may_fail_part)
				out << "\tPOST_MAY_FAIL;\n";
			if (has_act)
				out << "\tSINGLE_ACT(" << act_str << ");\n";
			if (has_saved)
				out << "\tDISCARD;\n";
			out << "\tif (!ret->IsEmpty()) {SET_RETURNED; return true;}\n";
			
			/*has_saved = true;
			out << "\tSAVE;\n";
			if (has_scope) {
				if (scope_act.GetCount())
					out << "\tSINGLE_ACT(" << scope_act << ");\n";
			}
			if (may_fail_part)
				out << "\tPRE_MAY_FAIL\n";
			out << "\twhile (!IsEof() && !IsToken(" << tk_dedent << ")) {\n";
			out << "\t\tif (ret->IsEmpty()) {TEST_PART(" << rule.key << "First);}\n";
			out << "\t\telse {TEST_PART(" << rule.key << "Second);}\n";
			out << "\t}\n";
			if (may_fail_part)
				out << "\tPOST_MAY_FAIL\n";
			out << "\tif (ret->GetCount()) {DISCARD; SET_RETURNED; return true;}\n";
			out << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";*/
			
			first << "bool Parser::" << rule.key << "First() {\n";
			first << "\tRET(" << ToCaps(rule.key) << "_ITEM)\n";
			bool has_first_saved = false;
			for(int j = 0; j < rule.blocks.GetCount(); j++) {
				Block& b = rule.blocks[j];
				
				if (b.el.GetCount() == 1) {
					first << "\tBLOCK_BEGIN(" << j << ");\n";
					
					Element& e = b.el[0];
					Rule* r = FindRule(e.key);
					
					if ((e.is_char || !r) && e.key.Find("Identifier") != 0) {
						first << "\t";
						if (IsId(e.key))
							first << "TEST_TOKEN_ID";
						else if (e.key.GetCount() > 3)
							first << "TEST_TOKEN" << (e.key.GetCount()-2);
						else
							first << "TEST_TOKEN";
						if (has_first_saved)
							first << "_DISCARDSAVED";
						String s = e.key;
						if (e.key.GetCount() > 3) s.Replace("'", "\"");
						first << "(" << s << ", ACT_INVALID)\n";
					}
					else {
						if (!has_first_saved)
							first << "\tTEST(" << e.key << ", ACT_INVALID)\n";
						else
							first << "\tTEST_DISCARDSAVED(" << e.key << ", ACT_INVALID)\n";
					}
				}
				else {
					Element& f = b.el[0];
					Element& l = b.el[b.el.GetCount()-1];
					
					if (f.key == rule.key) {
						continue;
					}
					else if (l.key == rule.key) {
						Panic("Didn't expect right recursive here");
					}
					
					first << "\tBLOCK_BEGIN(" << j << ");\n";
					
					if (!has_first_saved) {
						first << "\tSAVE;\n";
						has_first_saved = true;
					}
					
					first << "\twhile (true) {\n";
					
					for(int k = 0; k < b.el.GetCount(); k++) {
						Element& e = b.el[k];
						
						Rule* r = FindRule(e.key);
						if (e.is_char || !r) {
							TestPartToken(first, e.key, e.is_opt);
						}
						else {
							if (!e.is_opt) {
								first << "\t\tTEST_PART(" << e.key << ");\n";
							}
							else {
								first << "\t\tTEST_PART_OPT(" << e.key << ");\n";
							}
						}
					}
					first << "\t\tDISCARD; SET_RETURNED; return true;\n";
					first << "\t}\n";
					first << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";
				}
			}
			
			if (has_first_saved) {
				first << "\tDISCARD;\n";
			}
			first << "\treturn false;\n";
			first << "}\n\n";
			
			
			
			second << "bool Parser::" << rule.key << "Second() {\n";
			second << "\tRET(" << ToCaps(rule.key) << "_ITEM)\n";
			bool has_second_saved = false;
			for(int j = 0; j < rule.blocks.GetCount(); j++) {
				Block& b = rule.blocks[j];
				
				if (b.el.GetCount() == 1) {
					; // skip
				}
				else {
					Element& f = b.el[0];
					Element& l = b.el[b.el.GetCount()-1];
					
					if (f.key != rule.key) {
						continue;
					}
					
					second << "\tBLOCK_BEGIN(" << j << ");\n";
					
					if (b.el.GetCount() == 2) {
						Element& e = b.el[1];
						Rule* r = FindRule(e.key);
						
						if ((e.is_char || !r) && e.key.Find("Identifier") != 0) {
							second << "\t";
							if (IsId(e.key))
								second << "TEST_TOKEN_ID";
							else if (e.key.GetCount() > 3)
								second << "TEST_TOKEN" << (e.key.GetCount()-2);
							else
								second << "TEST_TOKEN";
							if (has_second_saved)
								second << "_DISCARDSAVED";
							String s = e.key;
							if (e.key.GetCount() > 3) s.Replace("'", "\"");
							second << "(" << s << ", ACT_INVALID)\n";
						}
						else {
							if (!has_second_saved)
								second << "\tTEST(" << e.key << ", ACT_INVALID)\n";
							else
								second << "\tTEST_DISCARDSAVED(" << e.key << ", ACT_INVALID)\n";
						}
					}
					else {
							
						if (!has_second_saved) {
							second << "\tSAVE;\n";
							has_second_saved = true;
						}
						
						second << "\twhile (true) {\n";
						
						for(int k = 1; k < b.el.GetCount(); k++) {
							Element& e = b.el[k];
							
							Rule* r = FindRule(e.key);
							if (e.is_char || !r) {
								TestPartToken(second, e.key, e.is_opt);
							}
							else {
								if (!e.is_opt) {
									second << "\t\tTEST_PART(" << e.key << ");\n";
								}
								else {
									second << "\t\tTEST_PART_OPT(" << e.key << ");\n";
								}
							}
						}
						second << "\t\tDISCARD; SET_RETURNED; return true;\n";
						second << "\t}\n";
						second << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";
					}
				}
			}
			
			if (has_second_saved) {
				second << "\tDISCARD;\n";
			}
			second << "\treturn false;\n";
			second << "}\n\n";
			
			
			
		}
		
		// Right recursive
		else {
			header << "\tbool " << rule.key << "First();\n";
			header << "\tbool " << rule.key << "Second();\n";
			enumstr << "NODE_" << ToCaps(rule.key) << "_ITEM,\n";
			enumtypestr << "case NODE_" << ToCaps(rule.key) << "_ITEM: return \"" << rule.key << "Item\";\n";
			
			LOG("EntityTemplate& et_" << ToVarName(rule.key) << "_item = AddEntityTemplate(NODE_" << ToCaps(rule.key) << "_ITEM);");
			
			has_saved = true;
			out << "\tSAVE;\n";
			if (has_scope) {
				if (scope_act.GetCount())
					out << "\tSINGLE_ACT(" << scope_act << ");\n";
			}
			out << "\twhile (true) {\n";
			out << "\t\tTEST_PART(" << rule.key << "First)\n";
			out << "\t\tTEST_PART(" << rule.key << ")\n";
			if (has_act)
				out << "\t\tSINGLE_ACT(" << act_str << ");\n";
			out << "\t\tDISCARD; SET_RETURNED; return true;\n";
			out << "\t}\n";
			out << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";
			if (has_scope) {
				if (scope_act.GetCount())
					out << "\tSINGLE_ACT(" << scope_act << ");\n";
			}
			out << "\twhile (true) {\n";
			out << "\t\tTEST_PART(" << rule.key << "Second)\n";
			if (has_act)
				out << "\t\tSINGLE_ACT(" << act_str << ");\n";
			out << "\t\tDISCARD; SET_RETURNED; return true;\n";
			out << "\t}\n";
			out << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";
			
			first << "bool Parser::" << rule.key << "First() {\n";
			first << "\tRET(" << ToCaps(rule.key) << "_ITEM)\n";
			bool has_first_saved = false;
			for(int j = 0; j < rule.blocks.GetCount(); j++) {
				Block& b = rule.blocks[j];
				
				if (b.el.GetCount() <= 1) {
					continue;
				}
				else {
					Element& f = b.el[0];
					Element& l = b.el[b.el.GetCount()-1];
					
					if (l.key != rule.key) {
						continue;
					}
					
					first << "\tBLOCK_BEGIN(" << j << ");\n";
				
					if (!has_first_saved) {
						first << "\tSAVE;\n";
						has_first_saved = true;
					}
					
					first << "\twhile (true) {\n";
					
					for(int k = 0; k < b.el.GetCount()-1; k++) {
						Element& e = b.el[k];
						
						Rule* r = FindRule(e.key);
						if (e.is_char || !r) {
							TestPartToken(first, e.key, e.is_opt);
						}
						else {
							if (!e.is_opt) {
								first << "\t\tTEST_PART(" << e.key << ");\n";
							}
							else {
								first << "\t\tTEST_PART_OPT(" << e.key << ");\n";
							}
						}
					}
					first << "\t\tDISCARD; SET_RETURNED; return true;\n";
					first << "\t}\n";
					first << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";
				}
			}
			
			if (has_first_saved) {
				first << "\tDISCARD;\n";
			}
			first << "\treturn false;\n";
			first << "}\n\n";
			
			
			
			second << "bool Parser::" << rule.key << "Second() {\n";
			second << "\tRET(" << ToCaps(rule.key) << "_ITEM)\n";
			bool has_second_saved = false;
			for(int j = 0; j < rule.blocks.GetCount(); j++) {
				Block& b = rule.blocks[j];
				
				if (b.el.GetCount() == 0) {
					// pass
				}
				else if (b.el.GetCount() == 1) {
					second << "\tBLOCK_BEGIN(" << j << ");\n";
					
					Element& e = b.el[0];
					Rule* r = FindRule(e.key);
					
					if ((e.is_char || !r) && e.key.Find("Identifier") != 0) {
						second << "\t";
						if (IsId(e.key))
							second << "TEST_TOKEN_ID";
						else if (e.key.GetCount() > 3)
							second << "TEST_TOKEN" << (e.key.GetCount()-2);
						else
							second << "TEST_TOKEN";
						if (has_second_saved)
							second << "_DISCARDSAVED";
						String s = e.key;
						if (e.key.GetCount() > 3) s.Replace("'", "\"");
						second << "(" << s << ", ACT_INVALID)\n";
					}
					else {
						if (!has_second_saved)
							second << "\tTEST(" << e.key << ", ACT_INVALID)\n";
						else
							second << "\tTEST_DISCARDSAVED(" << e.key << ", ACT_INVALID)\n";
					}
				}
				else {
					Element& f = b.el[0];
					Element& l = b.el[b.el.GetCount()-1];
					
					if (f.key == rule.key) {
						Panic("Didn't expect left recursive here");
					}
					else if (l.key == rule.key) {
						continue;
					}
					
					second << "\tBLOCK_BEGIN(" << j << ");\n";
					
					if (!has_second_saved) {
						second << "\tSAVE;\n";
						has_second_saved = true;
					}
					
					second << "\twhile (true) {\n";
					
					for(int k = 0; k < b.el.GetCount(); k++) {
						Element& e = b.el[k];
						
						Rule* r = FindRule(e.key);
						if (e.is_char || !r) {
							TestPartToken(second, e.key, e.is_opt);
						}
						else {
							if (!e.is_opt) {
								second << "\t\tTEST_PART(" << e.key << ");\n";
							}
							else {
								second << "\t\tTEST_PART_OPT(" << e.key << ");\n";
							}
						}
					}
					second << "\t\tDISCARD; SET_RETURNED; return true;\n";
					second << "\t}\n";
					second << "\tLOAD_NO_DISCARD; CLEAR_RET;\n";
				}
			}
			
			if (has_second_saved) {
				second << "\tDISCARD;\n";
			}
			second << "\treturn false;\n";
			second << "}\n\n";
			
			
		}
		if (has_saved) {
			out << "\tDISCARD;\n";
		}
		out << "\treturn false;\n";
		out << "}\n\n";
		
		if (first.GetCount()) {
			out << first;
			first.Clear();
		}
		
		if (second.GetCount()) {
			out << second;
			second.Clear();
		}
	}
	
	return out;
}

Rule* AntlrGrammar::FindRule(Array<Rule>& rules, String key) {
	for(int i = 0; i < rules.GetCount(); i++) {
		Rule& r = rules[i];
		if (r.key == key)
			return &r;
	}
	return NULL;
}

String GoldEscapeString(String s) {
	s.Replace("\n", "\\n");
	s.Replace("\t", "\\t");
	s.Replace("\r", "\\r");
	if (s.GetCount() > 2 && s.Left(1) == "'" && s.Right(1) == "'")
		;
	else s.Replace("'", "''");
	
	return s;
}

bool IsIdTerminal(Rule& rule) {
	if (rule.blocks.GetCount() == 1 && rule.blocks[0].el.GetCount() == 1) {
		Element& e = rule.blocks[0].el[0];
		
		if (e.is_term)
			return true;
	}
	return false;
}

void RenameBlock(Block& b, const VectorMap<String, String>& renames) {
	
	for(int i = 0; i < b.el.GetCount(); i++) {
		Element& el = b.el[i];
		
		int j = renames.Find(el.key);
		if (j >= 0)
			el.key = renames[j];
		
		for(int j = 0; j < el.blocks.GetCount(); j++) {
			RenameBlock(el.blocks[j], renames);
		}
	}
	
}

void AntlrGrammar::FixNames() {
	VectorMap<String, String> renames;
	
	for(int i = 0; i < rules.GetCount(); i++) {
		Rule& r = rules[i];
		
		bool all_caps = true;
		for(int j = 0; j < r.key.GetCount(); j++)
			if (!IsUpper(r.key[j]) && r.key[j] != '_' && !IsDigit(r.key[j]))
				all_caps = false;
		
		if (all_caps) {
			r.phase = 0;
			
			/*if (r.key == "WHITESPACE" ||
				r.key == "DIGIT") {
				String new_name = r.key + "_";
				renames.Add(r.key, new_name);
				r.key = new_name;
			}*/
		}
		else {
			if (IsUpper(r.key[0])) {
				r.phase = 1;
			}
			else {
				r.phase = 2;
			}
			
			String new_name = CamelToName(r.key);
			renames.Add(r.key, new_name);
			r.key = new_name;
		}
	}
	
	RenameAll(renames);
}

void AntlrGrammar::RenameAll(VectorMap<String, String>& renames) {
	for(int i = 0; i < rules.GetCount(); i++) {
		Rule& r = rules[i];
		for(int j = 0; j < r.blocks.GetCount(); j++) {
			RenameBlock(r.blocks[j], renames);
		}
	}
}

int AntlrGrammar::GetMaximumPhase(Block& b) {
	int max_phase = 0;
	for(int i = 0; i < b.el.GetCount(); i++) {
		Element& e = b.el[i];
		Rule* r = FindRule(e.key);
		if (r)
			max_phase = max(max_phase, r->phase);
		
		for(int j = 0; j < e.blocks.GetCount(); j++) {
			max_phase = max(max_phase, GetMaximumPhase(e.blocks[j]));
		}
	}
	return max_phase;
}

void AntlrGrammar::Sort() {
	UPP::Sort(rules, Rule());
}

void AntlrGrammar::CountUses() {
	
	for(int i = 0; i < rules.GetCount(); i++) {
		Rule& r = rules[i];
		r.recursive_used_by_count = 0;
		r.uses_count = 0;
	}
	
	for(int i = 0; i < rules.GetCount(); i++) {
		Rule& r = rules[i];
		
		for(int j = 0; j < r.blocks.GetCount(); j++) {
			Block& b = r.blocks[j];
			
			Index<String> added_uses, added_used_by;
			IncreaseUses(b, added_uses);
			IncreaseRecusiveUsedBy(b, added_used_by);
		}
	}
	
}

void AntlrGrammar::IncreaseRecusiveUsedBy(Block& b, Index<String>& added) {
	for(int i = 0; i < b.el.GetCount(); i++) {
		Element& e = b.el[i];
		
		for(int j = 0; j < e.blocks.GetCount(); j++) {
			IncreaseRecusiveUsedBy(e.blocks[j], added);
		}
		
		if (added.Find(e.key) == -1) {
			Rule* r = FindRule(e.key);
			if (r) {
				added.Add(e.key);
				r->recursive_used_by_count++;
				
				for(int j = 0; j < r->blocks.GetCount(); j++) {
					IncreaseRecusiveUsedBy(r->blocks[j], added);
				}
			}
		}
	}
}

void AntlrGrammar::IncreaseUses(Block& b, Index<String>& added) {
	for(int i = 0; i < b.el.GetCount(); i++) {
		Element& e = b.el[i];
		
		for(int j = 0; j < e.blocks.GetCount(); j++) {
			IncreaseUses(e.blocks[j], added);
		}
		
		if (added.Find(e.key) == -1) {
			Rule* r = FindRule(e.key);
			if (r) {
				added.Add(e.key);
				r->uses_count++;
			}
		}
	}
}

Rule* AntlrGrammar::FindStartRule() {
	Rule* start = &rules[0];
	for(int i = 0; i < rules.GetCount(); i++) {
		Rule& r = rules[i];
		
		/*if (r.uses_count > 0 && r.uses_count < start->uses_count &&
			r.recursive_used_by_count > start->recursive_used_by_count)
			start = & r;*/
			
		for(int j = 0; j < r.blocks.GetCount(); j++) {
			Block& b = r.blocks[j];
			
			for(int k = 0; k < b.el.GetCount(); k++) {
				
				if (b.el[k].key == "EOF")
					start = &r;
			}
		}
	}
	
	return start;
}

String AntlrGrammar::GetGoldElementString(Element& el) {
	StringStream fout;
	
	Rule* rr = FindRule(el.key);
	
	String s = el.key;
	
	if (!rr) {
		if (s.IsEmpty()) {
			fout << "(";
			for (int i = 0; i < el.blocks.GetCount(); i++) {
				Block& b = el.blocks[i];
				if (i) fout << " | ";
				for(int j = 0; j < b.el.GetCount(); j++) {
					if (j) fout << " ";
					Element& e = el.blocks[i].el[j];
					fout << GetGoldElementString(e);
				}
			}
			fout << ")";
		}
		else {
			s = GoldEscapeString(el.key);
			
			if (s == "EOF")
				return "";
			
			else if (s == ".")
				s = "{Printable}";
			
			else if (s == "'''")
				s = "''";
			
			else if (s.Left(1) != "'")
				s = "'" + s + "'";
			
			fout << s;
		}
	}
	else {
		if (rr->phase == 1)
			fout << s;
		else if (rr->phase == 2)
			fout << "<" << s << ">";
		else
			fout << "{" << s << "}";
	}
	
	if (el.is_opt && el.is_many)
		fout << "*";
	else if (el.is_many)
		fout << "+";
	else if (el.is_opt)
		fout << "?";
						
	return fout.GetResult();
}

String AntlrGrammar::GetGoldGrammarText() {
	StringStream fout;
	
	for (int phase = 0; phase < 3; phase++) {
		fout << "\n\n! ===================================================================\n";
		if (phase == 0) {
			fout << "! Character sets\n";
		}
		else if (phase == 1) {
			fout << "! Literal sets\n";
		}
		else if (phase == 2) {
			fout << "! Terminal\n";
		}
		fout << "! ===================================================================\n\n";
		
		for(int i = 0; i < rules.GetCount(); i++) {
			Rule& rule = rules[i];
			
			bool all_caps = true;
			for(int j = 0; j < rule.key.GetCount(); j++)
				if (!IsUpper(rule.key[j]) && rule.key[j] != '_')
					all_caps = false;
			
			if (phase == 0 && rule.phase == 0) {
				fout << "{" << rule.key << "} = ";
				
				Block& b = rule.blocks[0];
				
				for(int j = 0; j < b.el.GetCount(); j++) {
					Element& el = b.el[j];
					
					if (el.blocks.GetCount() && el.key.IsEmpty()) {
						for(int k = 0; k < el.blocks.GetCount(); k++) {
							Block& b = el.blocks[k];
							Element& e = b.el[0];
							
							if (k) fout << " + ";
							fout << "[";
							
							if (e.key.GetCount() == 3 && e.key[1] == '-') {
								int begin = e.key[0];
								int end = e.key[2];
								for (int chr = begin; chr <= end; chr++) {
									fout.Put(chr);
								}
							}
							else {
								String s = e.key;
								s = GoldEscapeString(s);
								fout << s;
							}
							
							fout << "]";
						}
					}
					else {
						if (j) fout << " + ";
						
						if (el.is_neg)
							fout << "{Printable} - ";
						
						Rule* rr = FindRule(el.key);
						
						String s = el.key;
						s = GoldEscapeString(s);
						
						if (!rr)
							fout << "[" << s << "]";
						else
							fout << "{" << s << "}";
						
						if (el.is_opt && el.is_many)
							fout << "*";
						else if (el.is_many)
							fout << "+";
						else if (el.is_opt)
							fout << "?";
					}
				}
				fout << "\n";
			}
			else if (phase == 1 && rule.phase == 1) {
				/*
				if (IsIdTerminal(rule))
					continue;
				*/
				String name = rule.key;
				fout << name << " = ";
				
				for(int j = 0; j < rule.blocks.GetCount(); j++) {
					Block& b = rule.blocks[j];
					
					if (j) {
						fout.Put(' ', name.GetCount() + 1);
						fout << "| ";
					}
					
					for(int k = 0; k < b.el.GetCount(); k++) {
						Element& el = b.el[k];
						if (k) fout << " ";
						fout << GetGoldElementString(el);
					}
					fout << "\n";
				}
				
				fout << "\n";
			}
			else if (phase == 2 && rule.phase == 2) {
				
				fout << "<" << rule.key << "> ::= ";
				
				for (int bi = 0; bi < rule.blocks.GetCount(); bi++) {
					Block& b = rule.blocks[bi];
					
					if (bi) fout << "        | ";
					
					for(int j = 0; j < b.el.GetCount(); j++) {
						Element& el = b.el[j];
						
						if (j) fout << " ";
						
						fout << GetGoldElementString(el);
						/*if (el.is_neg) {
							LOG("ERROR: is_neg in key " << rule.key);
						}
						
						Rule* rr = FindRule(el.key);
						
						if (!rr)
							fout << el.key;
						else
							fout << "{" << el.key << "}";
						
						if (el.is_opt && el.is_many)
							fout << "*";
						else if (el.is_many)
							fout << "+";
						else if (el.is_opt)
							fout << "?";
						*/
					}
					
					fout << "\n";
				}
				fout << "\n";
			}
		}
	}
	
	String ret = fout.GetResult();
	
	ret.Replace(" EOF\n", "\n");
	ret.Replace("'\\''", "''");
	
	return ret;
}

String HighEscapeCharString(String s) {
	s.Replace("\\", "\\\\");
	s.Replace("\n", "\\n");
	s.Replace("\t", "\\t");
	s.Replace("\r", "\\r");
	s.Replace("\"", "\\\"");
	s.Replace("?", "\\?");
	s.Replace("+", "\\+");
	s.Replace("*", "\\*");
	s.Replace("^", "\\^");
	s.Replace("<", "\\<");
	s.Replace(">", "\\>");
	s.Replace("$", "\\$");
	s.Replace("{", "\\{");
	s.Replace("}", "\\}");
	s.Replace("|", "\\|");
	s.Replace("(", "\\(");
	s.Replace(")", "\\)");
	s.Replace("/", "\\/");
	s.Replace("]", "\\]");
	s.Replace("[", "\\[");
	s.Replace(".", "\\.");
	/*if (s.GetCount() > 2 && s.Left(1) == "'" && s.Right(1) == "'")
		;
	else s.Replace("'", "''");*/
	
	return s;
}

String HighEscapeString(String s) {
	s.Replace("\\", "\\\\");
	s.Replace("\n", "\\n");
	s.Replace("\t", "\\t");
	s.Replace("\r", "\\r");
	if (s.GetCount() >= 3 && s.Left(1) == "'" && s.Right(1) == "'") {
		String mid = s.Mid(1, s.GetCount()-2);
		mid.Replace("'", "\\'");
		s = "'" + mid + "'";
	}
	else {
		s.Replace("'", "\\'");
	}
	s.Replace("\"", "\\\"");
	/*if (s.GetCount() > 2 && s.Left(1) == "'" && s.Right(1) == "'")
		;
	else s.Replace("'", "''");*/
	
	return s;
}

String AntlrGrammar::GetHighElementString(Element& el) {
	StringStream fout;
	
	Rule* rr = FindRule(el.key);
	
	String s = el.key;
	
	if (!rr) {
		if (s.IsEmpty()) {
			fout << "(";
			for (int i = 0; i < el.blocks.GetCount(); i++) {
				Block& b = el.blocks[i];
				if (i) fout << " | ";
				if (b.el.GetCount() > 1) fout << "(";
				for(int j = 0; j < b.el.GetCount(); j++) {
					if (j) fout << " ";
					Element& e = el.blocks[i].el[j];
					fout << GetHighElementString(e);
				}
				if (b.el.GetCount() > 1) fout << ")";
			}
			fout << ")";
		}
		else {
			s = HighEscapeString(el.key);
			
			if (s == "EOF")
				return "EOF";
			
			else if (s == ".")
				s = "{Printable}";
			
			else if (s == "'''")
				s = "'\\''";
			
			else if (s.Left(1) != "'")
				s = "'" + s + "'";
			
			fout << s;
		}
	}
	else {
		if (rr->phase == 0)
			fout << "{" << s << "}";
		else if (rr->phase == 1)
			fout << s;
		else if (rr->phase == 2)
			fout << s;
	}
	
	if (el.is_opt && el.is_many)
		fout << "*";
	else if (el.is_many)
		fout << "+";
	else if (el.is_opt)
		fout << "?";
						
	return fout.GetResult();
}

String AntlrGrammar::GetHighGrammarText() {
	StringStream fout;
	
	for (int phase = 0; phase < 3; phase++) {
		fout << "\n\n// ===================================================================\n";
		if (phase == 0) {
			fout << "// Character sets\n";
		}
		else if (phase == 1) {
			fout << "// Literal sets\n";
		}
		else if (phase == 2) {
			fout << "// Terminal\n";
		}
		fout << "// ===================================================================\n\n";
		if (phase == 0) {
			fout << "character:\n\n";
		}
		else if (phase == 1) {
			fout << "literal:\n\n";
		}
		else if (phase == 2) {
			fout << "terminal:\n\n";
		}
		for(int i = 0; i < rules.GetCount(); i++) {
			Rule& rule = rules[i];
			
			bool all_caps = true;
			for(int j = 0; j < rule.key.GetCount(); j++)
				if (!IsUpper(rule.key[j]) && rule.key[j] != '_')
					all_caps = false;
			
			if (phase == 0 && rule.phase == 0) {
				fout << rule.key << "\n\t";
				
				Block& b = rule.blocks[0];
				
				for(int j = 0; j < b.el.GetCount(); j++) {
					Element& el = b.el[j];
					
					if (el.blocks.GetCount() && el.key.IsEmpty()) {
						fout << "[";
						for(int k = 0; k < el.blocks.GetCount(); k++) {
							Block& b = el.blocks[k];
							if (b.el.GetCount() == 0) {
								LOG("warning: no elements");
								continue;
							}
							Element& e = b.el[0];
							
							if (e.key.GetCount() == 3 && e.key[1] == '-') {
								fout << "(" << e.key << ")";
							}
							else {
								String s = e.key;
								s = HighEscapeCharString(s);
								fout << s;
							}
						}
						fout << "]";
					}
					else {
						if (el.is_neg)
							fout << "[^";
						
						Rule* rr = FindRule(el.key);
						
						String s = el.key;
						s = HighEscapeCharString(s);
						
						if (!rr)
							fout << s;
						else
							fout << "<" << s << ">";
						
						if (el.is_opt && el.is_many)
							fout << "*";
						else if (el.is_many)
							fout << "+";
						else if (el.is_opt)
							fout << "?";
						
						if (el.is_neg)
							fout << "]";
					}
				}
				fout << "\n";
			}
			else if (phase == 1 && rule.phase == 1) {
				String name = rule.key;
				fout << name << "\n";
				
				for(int j = 0; j < rule.blocks.GetCount(); j++) {
					Block& b = rule.blocks[j];
					
					fout.Put('\t');
					
					for(int k = 0; k < b.el.GetCount(); k++) {
						Element& el = b.el[k];
						if (k) fout << " ";
						fout << GetHighElementString(el);
					}
					fout << "\n";
					
					if (b.is_skip)
						fout << "\t\tskip\n";
				}
				
				fout << "\n";
			}
			else if (phase == 2 && rule.phase == 2) {
				
				fout << rule.key << "\n";
				
				for (int bi = 0; bi < rule.blocks.GetCount(); bi++) {
					Block& b = rule.blocks[bi];
					
					fout << "\t";
					
					if (b.el.GetCount()) {
						for(int j = 0; j < b.el.GetCount(); j++) {
							Element& el = b.el[j];
							
							if (j) fout << " ";
							
							fout << GetHighElementString(el);
						}
					}
					else {
						fout << "|";
					}
					
					fout << "\n";
				}
				fout << "\n";
			}
		}
	}
	
	String ret = fout.GetResult();
	
	
	ret.Replace(" EOF\n", "\n");
	
	
	return ret;
}


NAMESPACE_TOPSIDE_END

#endif
