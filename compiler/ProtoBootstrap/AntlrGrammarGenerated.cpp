#include "Bootstrap.h"

#ifdef flagMAIN

NAMESPACE_TOPSIDE_BEGIN


void AntlrGrammar::VisitGrammarSpec(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "grammarDecl") {
			VisitGrammarDecl(n0);
		}
		else if (n0.key == "rules") {
			VisitRules(n0);
		}
		else {
			// useless
		}
	}
}

void AntlrGrammar::VisitGrammarDecl(const GrammarNode& n) {
	String type, id;
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "grammarType") {
			type = n0.sub[0].key;
		}
		else if (n0.key == "identifier") {
			id = n0.sub[0].key;
		}
		else {
			// useless
		}
	}
	
	if (!type.IsEmpty() && !id.IsEmpty()) {
		ASSERT(type == "grammar" || type == "lexer" || type == "parser");
		grammar_name = id;
	}
}

void AntlrGrammar::VisitIdentifier(const GrammarNode& n) {
	/*for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];


		// Terminals
		if (n0.key == "CPP14") {
			
		}
		else if (n0.key == "val") {
			
		}
		else if (n0.key == "channel") {
			
		}
		else if (n0.key == "HIDDEN") {
			
		}
		else if (n0.key == "skip") {
			
		}
	}*/
	Panic("ID should be handled in caller");
}

void AntlrGrammar::VisitRules(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];
		
		// Non-terminals
		if (n0.key == "ruleSpec") {
			cur_rule = &rules.Add();
			
			VisitRuleSpec(n0);
			
			cur_rule = NULL;
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitRuleSpec(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "parserRuleSpec") {
			VisitParserRuleSpec(n0);
		}
		else if (n0.key == "lexerRuleSpec") {
			VisitLexerRuleSpec(n0);
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitParserRuleSpec(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "ruleBlock") {
			VisitRuleBlock(n0);
		}


		// Terminals
		else if (cur_rule->key.IsEmpty()) {
			cur_rule->key = n0.key;
		}
		else {
			// useless
		}
	}
}

void AntlrGrammar::VisitRuleBlock(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "ruleAltList") {
			cur_rule_block = &cur_rule->blocks.Add();
			
			VisitRuleAltList(n0);
			
			cur_rule_block = NULL;
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitRuleAltList(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "labeledAlt") {
			VisitLabeledAlt(n0);
		}


		// Terminals
		else if (n0.key == "|") {
			cur_rule_block = &cur_rule->blocks.Add();
		}
		
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitLabeledAlt(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "alternative") {
			VisitAlternative(n0);
		}
		else if (n0.key == "#")
			break;
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitElement(const GrammarNode& n) {
	Element* prev_element = cur_element;
	cur_element = &cur_rule_block->el.Add();
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "atom") {
			VisitAtom(n0);
		}
		else if (n0.key == "ebnfSuffix") {
			VisitEbnfSuffix(n0);
		}
		else if (n0.key == "labeledElement") {
			VisitLabeledElement(n0);
		}
		else if (n0.key == "ebnf") {
			VisitEBNF(n0);
		}
		else if (n0.key == "actionBlock") {
			VisitActionBlock(n0);
		}
		else if (n0.key == "?") {
			cur_element->is_opt = true;
		}
		else Panic("Unexpected key " + n0.key);
	}
	
	cur_element = prev_element;
}

void AntlrGrammar::VisitActionBlock(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];
		cur_element->key += n0.key;
	}
}

void AntlrGrammar::VisitEBNF(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "block") {
			VisitBlock(n0);
		}
		else if (n0.key == "blockSuffix") {
			VisitBlockSuffix(n0);
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitBlock(const GrammarNode& n) {
	Block* prev_rule_block = cur_rule_block;
	cur_rule_block = &cur_element->blocks.Add();
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "altList") {
			VisitAltList(n0);
		}
		else if (n0.key == "(") {
			
		}
		else if (n0.key == ")") {
			
		}
		else Panic("Unexpected key " + n0.key);
	}
	
	cur_rule_block = prev_rule_block;
}

void AntlrGrammar::VisitBlockSuffix(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "ebnfSuffix") {
			VisitEbnfSuffix(n0);
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitAltList(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "alternative") {
			VisitAlternative(n0);
		}
		else if (n0.key == "|") {
			
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitAlternative(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "element") {
			VisitElement(n0);
		}
		else if (n0.key == "elementOptions") {
			LOG("warning: todo elementOptions");
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitAtom(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "ruleref") {
			VisitRuleref(n0);
		}
		else if (n0.key == "terminal") {
			VisitTerminal(n0);
		}
		else if (n0.key == "~") {
			cur_element->is_neg = true;
		}
		else if (n0.key == "notSet") {
			VisitNotSet(n0);
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitRuleref(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];
		
		ASSERT(cur_element->key.IsEmpty());
		
		cur_element->key = n0.key;
		
	}
}

void AntlrGrammar::VisitEbnfSuffix(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];


		// Terminals
		if (n0.key == "?") {
			cur_element->is_opt = true;
		}
		else if (n0.key == "*") {
			cur_element->is_opt = true;
			cur_element->is_many = true;
		}
		else if (n0.key == "+") {
			cur_element->is_many = true;
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitTerminal(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];
		
		cur_element->is_term = true;
		
		ASSERT(cur_element->key.IsEmpty());
		cur_element->key = n0.key;
	}
}

void AntlrGrammar::VisitLabeledElement(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "identifier") {
			cur_element->id = n0.sub[0].key;
		}
		else if (n0.key == "atom") {
			VisitAtom(n0);
		}
		else if (n0.key == "block") {
			VisitBlock(n0);
		}


		// Terminals
		else if (n0.key == "=") {
			
		}
		else if (n0.key == "+=") {
			
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitLexerRuleSpec(const GrammarNode& n) {
	cur_rule->is_lex = true;
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerRuleBlock") {
			VisitLexerRuleBlock(n0);
		}


		// Terminals
		else if (cur_rule->key.IsEmpty()) {
			cur_rule->key = n0.key;
			
			if (cur_rule->key == "fragment")
				cur_rule->key.Clear();
		}
		else {
			// useless
		}
	}
}

void AntlrGrammar::VisitLexerRuleBlock(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerAltList") {
			VisitLexerAltList(n0);
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitLexerAltList(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerAlt") {
			VisitLexerAlt(n0);
		}


		// Terminals
		else if (n0.key == "|") {
			
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitLexerAlt(const GrammarNode& n) {
	Block* prev_rule_block = cur_rule_block;
	if (!cur_element)
		cur_rule_block = &cur_rule->blocks.Add();
	else
		cur_rule_block = &cur_element->blocks.Add();
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerElements") {
			VisitLexerElements(n0);
		}
		else if (n0.key == "lexerCommands") {
			VisitLexerCommands(n0);
		}
		else Panic("Unexpected key " + n0.key);
	}
	
	cur_rule_block = prev_rule_block;
}

void AntlrGrammar::VisitLexerElements(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerElement") {
			VisitLexerElement(n0);
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitLexerElement(const GrammarNode& n) {
	Element* prev_element = cur_element;
	cur_element = &cur_rule_block->el.Add();
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerAtom") {
			VisitLexerAtom(n0);
		}
		else if (n0.key == "lexerBlock") {
			VisitLexerBlock(n0);
		}
		else if (n0.key == "ebnfSuffix") {
			VisitEbnfSuffix(n0);
		}
		else if (n0.key == "actionBlock") {
			VisitActionBlock(n0);
		}
		else if (n0.key == "?") {
			cur_element->is_opt = true;
		}
		else Panic("Unexpected key " + n0.key);
	}
	
	cur_element = prev_element;
}

void AntlrGrammar::VisitLexerAtom(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "terminal") {
			VisitTerminal(n0);
		}
		else if (n0.key == "notSet") {
			VisitNotSet(n0);
		}
		
		else if (n0.key.Left(1) == "[") {
			Element& el = *cur_element;
			el.is_char = true;
			String char_rule = n0.key.Mid(1, n0.key.GetCount()-2);
			for(int i = 0; i < char_rule.GetCount(); i++) {
				int chr0 = char_rule[i];
				int chr1 = i+1 < char_rule.GetCount() ? char_rule[i+1] : 0;
				if (chr1 == '-') {
					int chr2 = i+2 < char_rule.GetCount() ? char_rule[i+2] : 0;
					if (chr2 == 0) {
						Block& b0 = el.blocks.Add();
						Element& e0 = b0.el.Add();
						e0.key.Cat(chr0);
						
						Block& b1 = el.blocks.Add();
						Element& e1 = b1.el.Add();
						e1.key.Cat(chr1);
						
						i += 1;
					}
					else {
						Block& b = el.blocks.Add();
						Element& e = b.el.Add();
						e.key.Cat(chr0);
						e.key.Cat(chr1);
						e.key.Cat(chr2);
						
						i += 2;
					}
				}
				else if (chr0 == '\\') {
					Block& b = el.blocks.Add();
					Element& e = b.el.Add();
					e.key.Cat(chr0);
					e.key.Cat(chr1);
					i++;
				}
				else {
					Block& b = el.blocks.Add();
					Element& e = b.el.Add();
					e.key.Cat(chr0);
				}
			}
		}
		else if (n0.key == ".") {
			Element& el = *cur_element;
			el.key = n0.key;
			el.is_char = true;
		}
		else if (n0.key == "characterRange") {
			Element& el = *cur_element;
			el.key = n0.sub[0].key + "-" + n0.sub[2].key;
			el.is_char = true;
		}
		else {
			ASSERT(!n0.sub.GetCount());
			// useless
		}
	}
}

void AntlrGrammar::VisitLexerBlock(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerAltList") {
			VisitLexerAltList(n0);
		}


		// Terminals
		else if (n0.key == "(") {
			
		}
		else if (n0.key == ")") {
			
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitNotSet(const GrammarNode& n) {
	cur_element->is_neg = true;
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "setElement") {
			VisitSetElement(n0);
		}
		else if (n0.key == "blockSet") {
			VisitBlockSet(n0);
		}

		// Terminals
		else if (n0.key == "~") {
			
		}
		else Panic("Unexpected key " + n0.key);
	}
}

void AntlrGrammar::VisitBlockSet(const GrammarNode& n) {
	bool has_many = false;
	
	Element* prev = cur_element;
	cur_element = &prev->blocks.Add().el.Add();
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];
		
		if (n0.key == "|") {
			cur_element = &prev->blocks.Add().el.Add();
		}
		else if (n0.key == "setElement") {
			VisitSetElement(n0);
		}
		else if (n0.key == "(") {
			
		}
		else if (n0.key == ")") {
			
		}
		else Panic("Unexpected key " + n0.key);
	}
	cur_element = prev;
}

void AntlrGrammar::VisitSetElement(const GrammarNode& n) {
	cur_element->is_set = true;
	
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		ASSERT(cur_element->key.IsEmpty());
		if (n0.key.Left(1) == "[") {
			cur_element->key = n0.key.Mid(1, n0.key.GetCount()-2);
			cur_element->is_char = true;
		}
		else {
			cur_element->key = n0.key;
		}
	}
}

void AntlrGrammar::VisitLexerCommands(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerCommand") {
			VisitLexerCommand(n0);
		}


		// Terminals
		else if (n0.key == "->") {
			
		}
	}
}

void AntlrGrammar::VisitLexerCommand(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "lexerCommandName") {
			VisitLexerCommandName(n0);
		}
		else if (n0.key == "lexerCommandExpr") {
			VisitLexerCommandExpr(n0);
		}


		// Terminals
		else if (n0.key == "(") {
			
		}
		else if (n0.key == ")") {
			
		}
	}
}

void AntlrGrammar::VisitLexerCommandName(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "identifier") {
			//VisitIdentifier(n0);
			String key = n0.sub[0].key;
			
			if (key == "skip") {
				cur_rule_block->is_skip = true;
			}
		}
	}
}

void AntlrGrammar::VisitLexerCommandExpr(const GrammarNode& n) {
	for (int i = 0; i < n.sub.GetCount(); i++) {
		const GrammarNode& n0 = n.sub[i];

		// Non-terminals
		if (n0.key == "identifier") {
			//VisitIdentifier(n0);
		}
	}
}


NAMESPACE_TOPSIDE_END

#endif
