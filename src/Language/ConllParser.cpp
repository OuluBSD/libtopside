#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN


bool ConllRuleParser::Parse(Array<ConllRule>& rules, Node& n) {
	this->rules = &rules;
	
	for (int iter = 0; iter < 1000; iter++) {
		bool changes = false;
		
		ApplyRules(n, changes);
		
		if (!changes) break;
	}
	
	
	return true;
}

void ConllRuleParser::ApplyRules(Node& n, bool& changes) {
	
	if (n.IsType(NODE_NL)) {
		for(int i = rules->GetCount()-1; i >= 0; i--) {
			const ConllRule& rule = (*rules)[i];
			
			bool check =
				((rule.type == 0 || rule.type == 1) && n.GetCount() > 2) ||
				(rule.type == 2 && n.GetCount() == 2 && IsConstChar(n.GetText(), "UNKNOWN", 7));
			
			if (check) {
				Node& n0 = n.At(0);
				Node& n1 = n.At(1);
				if (n0.IsType(NODE_NL) && n1.IsType(NODE_NL)) {
					int j;
					WString s0 = n0.GetText();
					WString s1 = n1.GetText();
					WString arg0, arg1;
					j = s0.ReverseFind(",");
					if (j >= 0) arg0 = s0.Mid(j+1);
					j = s1.ReverseFind(",");
					if (j >= 0) arg1 = s1.Mid(j+1);
					j = s0.Find(",");
					if (j >= 0) s0 = s0.Left(j);
					j = s1.Find(",");
					if (j >= 0) s1 = s1.Left(j);
					
					bool match0 = false;
					for(int j = 0; j < rule.first_match.GetCount(); j++) {
						if (rule.first_match[j] == s0) {
							match0 = true;
							break;
						}
					}
					
					bool match1 = false;
					for(int j = 0; j < rule.second_match.GetCount(); j++) {
						if (rule.second_match[j] == s1) {
							match1 = true;
							break;
						}
					}
					
					bool arg_match0 = true;
					if (rule.first_arg_match.GetCount())
						arg_match0 = arg0 == rule.first_arg_match;
					
					bool arg_match1 = true;
					if (rule.second_arg_match.GetCount())
						arg_match1 = arg1 == rule.second_arg_match;
					
					if (match0 && match1 && arg_match0 && arg_match1) {
						
						if (rule.type == 0) {
							Node* n2 = new Node(NODE_NL, rule.new_node_name);
							n2->Add(n.Detach(0));
							n2->Add(n.Detach(0));
							n.Insert(0, n2);
							changes = true;
						}
						else if (rule.type == 1) {
							Node* n2 = new Node(NODE_NL, rule.new_node_name);
							while (n.GetCount() >= 2)
								n2->Add(n.Detach(1));
							n.Add(n2);
							changes = true;
						}
						else if (rule.type == 2) {
							n.SetText(rule.new_node_name);
							changes = true;
						}
						
						break;
					}
				}
			}
		}
	}
	
	for(int i = 0; i < n.GetCount(); i++) {
		ApplyRules(n.At(i), changes);
	}
}

void ProcessConllNode(Array<ConllRule>& rules, Node& n) {
	ConllRuleParser p;
	p.Parse(rules, n);
}


NAMESPACE_LANGUAGE_END
