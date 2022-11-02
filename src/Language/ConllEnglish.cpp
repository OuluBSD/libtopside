#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

Node* roooot;


bool ConllParser::ParseEnglish(WString txt) {
	root.Create();
	root->SetType(NODE_ROOT);
	Vector<Vector<WString> > line_tokens;
	
	Vector<WString> lines = Split(txt, WString("\n"), false);
	
	for(int i = 0; i < lines.GetCount(); i++) {
		const WString& line = lines[i];
		
		//LOG(line);
		if (IsSpaceString(line)) {
			if (!line_tokens.IsEmpty()) {
				//LOG(root->GetCount());
				if (root->GetCount() < 0)
					root->Add(0);
				else {
					Node* nn = ParseConll(line_tokens);
					if (nn) {
						Node& n = root->Add(nn);
						
						if (n.GetCount() == 1 && n.At(0).GetCount() >= 2)
							n.At(0).SetText("UNKNOWN");
						
					}
				}
			}
			line_tokens.Clear();
			continue;
		}
		
		if (line[0] == '#')
			continue;
		
		Vector<WString>& cur_line = line_tokens.Add();
		cur_line.Add();
		bool read_empty = false;
		for(int j = 0; j < line.GetCount(); j++) {
			int chr = line[j];
			if (!read_empty) {
				if (IsSpace(chr)) {
					read_empty = true;
					cur_line.Add();
				}
				else {
					cur_line.Top().Cat(chr);
				}
			} else {
				if (!IsSpace(chr)) {
					cur_line.Top().Cat(chr);
					read_empty = false;
				}
			}
		}
		
		if (cur_line.GetCount() < 7) {
			DUMPC(cur_line);
			Panic("Invalid line");
		}
		
		
	}
	
	return true;
}


Node* FindFailedSentenceStructure(Node& n) {
	bool has_text = false, has_nl = false;
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		
		Node* n1 = FindFailedSentenceStructure(n0);
		if (n1)
			return n1;
		
		if (n0.IsType(NODE_TEXT))
			has_text = true;
		else if (n0.IsType(NODE_NL))
			has_nl = true;
	}
	
	if (has_text && has_nl)
		return &n;
	
	return NULL;
}

void RemoveRecursiveDuplicatesEnglish(Node& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		RemoveRecursiveDuplicatesEnglish(n.At(i));
	}
	
	if (n.IsType(NODE_NL) && n.GetCount() == 1) {
		Node& n0 = n.At(0);
		if (n0.IsType(NODE_NL)) {
			auto& tags = GetTags().tags;
			int lev0 = tags.Find(n.GetText());
			int lev1 = tags.Find(n0.GetText());
			if (lev0 == -1) lev0 = tags.GetCount();
			if (lev1 == -1) lev1 = tags.GetCount();
			if (lev1 < lev0)
				//n.SetText(n0.GetText());
				n.SetText(n0.GetText() + "," + n.GetText());
			else
				n.SetText(n.GetText() + "," + n0.GetText());
			for(int i = 0; i < n0.GetCount();)
				n.Add(n0.Detach(i));
			n.Remove(0);
		}
	}
}

bool IsRecursiveError(Node& n, Index<Node*>& nodes) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		
		int j = nodes.Find(&n0);
		if (j >= 0)
			return true;
		
		nodes.Add(&n0);
		if (IsRecursiveError(n0, nodes))
			return true;
		nodes.Pop();
	}
	return false;
}

bool IsBeginningWithComma(Node& n) {
	if (n.IsType(NODE_TEXT)) {
		WString txt = n.GetText();
		int count = txt.GetCount();
		return count && txt[0] == ',';
	}
	
	if (!n.GetCount()) {
		return false;
	}
	else {
		return IsBeginningWithComma(n.At(0));
	}
}

bool IsEndingWithComma(Node& n) {
	if (n.IsType(NODE_TEXT)) {
		WString txt = n.GetText();
		int count = txt.GetCount();
		return count && txt[count-1] == ',';
	}
	
	if (!n.GetCount()) {
		return false;
	}
	else {
		return IsEndingWithComma(n.Top());
	}
}

void ClearTexts(Node& n) {
	if (n.IsType(NODE_TEXT))
		n.ClearText();
	else
		for(int i = 0; i < n.GetCount(); i++)
			ClearTexts(n.At(i));
}


NAMESPACE_LANGUAGE_END
