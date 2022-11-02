#ifndef _Language_ConllParser_h_
#define _Language_ConllParser_h_

#include "ConllMacros.h"


NAMESPACE_LANGUAGE_BEGIN


struct ResolverError {
	String e;
	
	ResolverError(String e) : e(e) {}
};

String GetConllEnglish(String txt, int turku_npp_port=7690);
String GetConllFinnish(String txt, int turku_npp_port=7689);


struct ConllRule {
	int type = 0;
	Vector<WString> first_match, second_match;
	WString first_arg_match, second_arg_match;
	WString new_node_name;
	
	
	bool operator==(const ConllRule& r) {
		if (first_match.GetCount() != r.first_match.GetCount()) return false;
		if (second_match.GetCount() != r.second_match.GetCount()) return false;
		for(int i = 0; i < first_match.GetCount(); i++)
			if (r.first_match[i] != first_match[i])
				return false;
		for(int i = 0; i < second_match.GetCount(); i++)
			if (r.second_match[i] != second_match[i])
				return false;
		return type == r.type && first_arg_match == r.first_arg_match &&
			second_arg_match == r.second_arg_match && new_node_name == r.new_node_name;
	}
	void Serialize(Stream& s) {s % type % first_match % second_match % first_arg_match % second_arg_match % new_node_name;}
	
	bool operator()(const ConllRule& a, const ConllRule& b) const {
		if (b.first_arg_match.GetCount() || b.second_arg_match.GetCount())
			return true;
		if (a.first_arg_match.GetCount() || a.second_arg_match.GetCount())
			return false;
		if (a.type == b.type) {
			if (a.first_match.GetCount() && b.first_match.GetCount())
				return a.first_match[0] < b.first_match[0];
			else
				return a.new_node_name < b.new_node_name;
		}
		return a.type < b.type;
	}
};


class ConllRuleParser {
	
	Array<ConllRule>* rules;
	void ApplyRules(Node& n, bool& changes);
	
public:
	
	virtual bool Parse(Array<ConllRule>& rules, Node& n);
	
	
	One<Node> root;
	
};

class ConllParser : public Parser {
	
	//Node* ParseConllEnglish(Vector<Vector<WString> >& line_tokens);
	Node* ParseConll(Vector<Vector<WString> >& line_tokens);
public:
	
	virtual bool Parse(WString txt) {return ParseEnglish(txt);}
	virtual bool ParseEnglish(WString txt);
	virtual bool ParseFinnish(WString txt);
	
	void Dump() {if (!root.IsEmpty()) {LOG(NodeTreeString(*root));}}
	
	One<Node> root;
	
};


void RemoveRecursiveDuplicatesEnglish(Node& n);
void RemoveRecursiveDuplicatesFinnish(Node& n);
void RemoveRecursiveDuplicates(Node& n);
void FixWeirdUnknowns(Node& n);
void FixRootUnknown(Node& n);
void FixFinnishPronouns(Node& n, Node& root);
bool InsertAtId(Node& n, Node* to_insert, int id);
String GetSentenceLines(const String& s);

Node* FindFailedSentenceStructure(Node& n);
bool IsRecursiveError(Node& n, Index<Node*>& nodes);
bool IsBeginningWithComma(Node& n);
bool IsEndingWithComma(Node& n);
void ClearTexts(Node& n);
void GetIds(Node& n, Vector<int>& ids);
int FindOutlier(Vector<int>& ids, Index<int>& skip_ids);
bool IsVectorEqual(Vector<int>& a, Vector<int>& b);
int FindWrongOrderId(Node&n, int& counter);
Node* PopWrongOrder(Node& n, int match_id);
Node* FindNodeId(Node& n, int match_id);
bool InsertToCorrectOrder(Node* to_insert, Node& n, int max_id);
void ClearTextIds(Node& n);
void ClearEmptyNodes(Node& n);
bool ContainsTextId(Node& n, int id);
bool ContainsTextIdOrGreater(Node& n, int id);
bool ContainsTextIdOrLess(Node& n, int id);
bool ContainsUnknowns(Node& n);

void FixText(Node& n);

void ProcessConllNode(Array<ConllRule>& rules, Node& node);


NAMESPACE_LANGUAGE_END

#endif
