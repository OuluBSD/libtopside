#ifndef _ProtoGrammar_AntlrGrammar_h_
#define _ProtoGrammar_AntlrGrammar_h_

#ifdef flagMAIN

NAMESPACE_OULU_BEGIN


struct Block;
struct Rule;

struct Element {
	Array<Block> blocks;
	String key, id;
	int unique = 0;
	bool is_opt = false;
	bool is_many = false;
	bool is_term = false;
	bool is_set = false;
	bool is_neg = false;
	bool is_char = false;
	
	
	Element() {
		
	}
	Element(const Element& e) {
		*this = e;
	}
	
	hash_t GetHashValue();
	//void Xmlize(XmlIO& xml);
	void CopyContrib(const Element& e) {
		is_opt = e.is_opt;
		is_many = e.is_many;
	}
	void operator=(const Element& e) {
		blocks <<= e.blocks;
		key = e.key;
		id = e.id;
		unique = e.unique;
		is_opt = e.is_opt;
		is_many = e.is_many;
		is_term = e.is_term;
		is_set = e.is_set;
		is_neg = e.is_neg;
		is_char = e.is_char;
	}
	bool operator==(const Element& e) const;
	bool operator!=(const Element& e) const {return !(*this == e);}
};

struct Block {
	Rule* orig_rule = NULL;
	int orig_block = 0;
	
	Array<Element> el;
	bool is_editable = false;
	bool is_skip = false;
	int unique = 0;
	
	Block() {
		
	}
	Block(const Block& b) {
		*this = b;
	}
	hash_t GetHashValue() {
		CombineHash h;
		h << el.GetCount() << 1;
		for(int i = 0; i < el.GetCount(); i++)
			h << el[i].GetHashValue() << 1;
		return h;
	}
	void operator=(const Block& b) {
		el <<= b.el;
		is_editable = b.is_editable;
		is_skip = b.is_skip;
		unique = b.unique;
	}
	bool operator==(const Block& b) const {
		if (el.GetCount() != b.el.GetCount()) return false;
		for(int i = 0; i < el.GetCount(); i++)
			if (el[i] != b.el[i])
				return false;
		return
			is_editable == b.is_editable &&
			is_skip == b.is_skip &&
			unique == b.unique;
	}
	bool operator!=(const Block& b) const {return !(*this == b);}
	/*void Xmlize(XmlIO& xml) {
		for(int i = 0; i < el.GetCount(); i++)
			xml
				(IntStr(i), el[i]);
	}*/
};

struct Rule {
	Array<Block> blocks;
	String key;
	int phase = 0;
	bool is_lex = false;
	bool is_editable = false;
	
	int uses_count = 0;
	int recursive_used_by_count = 0;
	
	bool is_set = false;
	
	Rule() {}
	Rule(const Rule& r) {*this = r;}
	bool operator()(const Rule& a, const Rule& b) const {
		if (a.recursive_used_by_count > b.recursive_used_by_count)
			return true;
		else
			return a.uses_count < b.uses_count;
	}
	void operator=(const Rule& r) {
		blocks <<= r.blocks;
		key = r.key;
		is_lex = r.is_lex;
		is_editable = r.is_editable;
		is_set = r.is_set;
	}
	hash_t GetHashValue() {
		CombineHash c;
		c << blocks.GetCount() << 1;
		for(int i = 0; i < blocks.GetCount(); i++)
			c << blocks[i].GetHashValue() << 1;
		return c;
	}
	/*void Xmlize(XmlIO& xml) {
		Index<unsigned> idx;
		if (xml.IsStoring()) {
			for(int i = 0; i < blocks.GetCount(); i++)
				idx.Add(blocks[i].GetHashValue());
			xml
				("idx", idx);
			for(int i = 0; i < blocks.GetCount(); i++)
				xml (IntStr64(blocks[i].GetHashValue()), blocks[i]);
		}
		else {
			xml
				("idx", idx);
			for(int i = 0; i < blocks.GetCount(); i++) {
				unsigned hash = blocks[i].GetHashValue();
				String key = IntStr64(hash);
				int j = idx.Find(hash);
				if (j >= 0)
					xml(key, blocks[i]);
			}
		}
	}*/
	
	void SetEditable() {
		is_editable = true;
		for(int i = 0; i < blocks.GetCount(); i++)
			blocks[i].is_editable = true;
	}
};



class AntlrGrammar {
	Rule* cur_rule = NULL;
	Block* cur_rule_block = NULL;
	Element* cur_element = NULL;
	
	Index<String> may_fail_parts;
	VectorMap<String, String> new_scope, act, pre_act, iter_act;
	
	int GetMaximumPhase(Block& b);
	void IncreaseRecusiveUsedBy(Block& b, Index<String>& added);
	void IncreaseUses(Block& b, Index<String>& added);
	
public:
	
	
	bool Load(String g4_path);
	String GetGoldGrammarText();
	String GetHighGrammarText();
	String GetGoldElementString(Element& el);
	String GetHighElementString(Element& el);
	void FixNames();
	void Sort();
	void CountUses();
	Rule* FindStartRule();
	Rule* FindRule(String key) {return FindRule(rules, key);}
	Rule* FindRule(Array<Rule>& rules, String key);
	void RenameAll(VectorMap<String, String>& renames);
	
	String header, enumstr, enumtypestr;
	String GetCppParserHeader();
	String GetCppParserImplementation();
	String GetCppParserEnum();
	String GetCppParserEnumType();
	
	String GetPython3ParserHeader();
	String GetPython3ParserImplementation();
	String GetPython3ParserEnum();
	String GetPython3ParserEnumType();
	
	String GetGenericParserImplementation();
	
	String tk_dedent, tk_indent;
	
	String grammar_name;
	GrammarNode root;
	
	Array<Rule> rules;
	
	// Generated. Do not edit.
	void VisitGrammarSpec(const GrammarNode& n);
	void VisitGrammarDecl(const GrammarNode& n);
	void VisitIdentifier(const GrammarNode& n);
	void VisitRules(const GrammarNode& n);
	void VisitRuleSpec(const GrammarNode& n);
	void VisitParserRuleSpec(const GrammarNode& n);
	void VisitRuleBlock(const GrammarNode& n);
	void VisitRuleAltList(const GrammarNode& n);
	void VisitLabeledAlt(const GrammarNode& n);
	void VisitAlternative(const GrammarNode& n);
	void VisitElement(const GrammarNode& n);
	void VisitActionBlock(const GrammarNode& n);
	void VisitEBNF(const GrammarNode& n);
	void VisitBlock(const GrammarNode& n);
	void VisitBlockSuffix(const GrammarNode& n);
	void VisitAltList(const GrammarNode& n);
	void VisitAtom(const GrammarNode& n);
	void VisitRuleref(const GrammarNode& n);
	void VisitEbnfSuffix(const GrammarNode& n);
	void VisitTerminal(const GrammarNode& n);
	void VisitLabeledElement(const GrammarNode& n);
	void VisitLexerRuleSpec(const GrammarNode& n);
	void VisitLexerBlock(const GrammarNode& n);
	void VisitLexerAltList(const GrammarNode& n);
	void VisitLexerAlt(const GrammarNode& n);
	void VisitLexerElements(const GrammarNode& n);
	void VisitLexerElement(const GrammarNode& n);
	void VisitLexerAtom(const GrammarNode& n);
	void VisitLexerRuleBlock(const GrammarNode& n);
	void VisitNotSet(const GrammarNode& n);
	void VisitBlockSet(const GrammarNode& n);
	void VisitSetElement(const GrammarNode& n);
	void VisitLexerCommands(const GrammarNode& n);
	void VisitLexerCommand(const GrammarNode& n);
	void VisitLexerCommandName(const GrammarNode& n);
	void VisitLexerCommandExpr(const GrammarNode& n);
	
};


String HighEscapeString(String s);
String HighEscapeCharString(String s);


NAMESPACE_OULU_END

#endif
#endif
