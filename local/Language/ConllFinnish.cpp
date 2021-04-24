#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN


extern Node* roooot;

String GetSentenceLines(const String& s) {
	Vector<WString> sentences;
	WString txt = s.ToWString();
	
	WString sent;
	WString w;
	bool is_abbr = false;
	bool check_late_sent = false;
	for(int i = 0; i < txt.GetCount(); i++) {
		int chr = txt[i];
		
		if (is_abbr) {
			if (chr == '\n') {
				w.Cat(' ');
			}
			else if (IsSpace(chr)) {
				is_abbr = false;
				sent.Cat(w);
				sent.Cat(chr);
				w.Clear();
			}
			else {
				w.Cat(chr);
			}
		}
		else {
			if (chr == '\n') {
				w.Cat(' ');
			}
			else if (IsSpace(chr)) {
				sent.Cat(w);
				sent.Cat(chr);
				w.Clear();
			}
			else if (chr == ';') {
				sent.Cat(w);
				sent.Cat(chr);
				w.Clear();
				sentences.Add(TrimBoth(sent));
				sent.Clear();
			}
			else if (chr == '?' || chr == '!') {
				sent.Cat(w);
				sent.Cat(chr);
				w.Clear();
				sentences.Add(TrimBoth(sent));
				sent.Clear();
			}
			else if (chr == '.') {
				if (w.GetCount() && IsNumberStr(w)) {
					w.Cat(chr);
				}
				else if (w.GetCount() == 1) {
					is_abbr = true;
					w.Cat(chr);
				}
				else if (w.IsEmpty() || w.GetCount() >= 4) {
					sent.Cat(w);
					sent.Cat(chr);
					w.Clear();
					sentences.Add(TrimBoth(sent));
					sent.Clear();
				}
				else {
					if (IsUpper(w[0]))
						check_late_sent = true;
					w.Cat(chr);
				}
			}
			else if (IsLetter(chr)) {
				if (check_late_sent) {
					if (IsUpper(chr)) {
						sent.Cat(w);
						sentences.Add(TrimBoth(sent));
						sent.Clear();
						w.Clear();
					}
					check_late_sent = false;
				}
				w.Cat(chr);
			}
			else if (IsDigit(chr)) {
				w.Cat(chr);
			}
			else {
				sent.Cat(w);
				sent.Cat(chr);
				w.Clear();
			}
		}
		
	}
	
	sent.Cat(w);
	if (sent.GetCount())
		sentences.Add(TrimBoth(sent));
	
	//DUMPC(sentences);
	return Join(sentences, "\n").ToString();
}


String GetConllEnglish(String txt, int turku_npp_port) {
	/*
	txt = GetSentenceLines(txt);
	
	static StaticMutex lock;
	lock.Enter();
	
	String input_file = ConfigFile("spacy.in");
	String output_file = ConfigFile("spacy.out");
	FileOut fout(input_file);
	fout << txt;
	fout.Close();
	
	String cmd = "python3 -m spacy_conll --disable_sbd --input_file \"" + input_file + "\" --output_file \"" + output_file + "\"";
	LOG(cmd);
	String out;
	Sys(cmd, out);
	
	lock.Leave();
	
	out = LoadFile(output_file);
	return out;*/
	
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(txt);
	h.Url("http://localhost:" + IntStr(turku_npp_port));
	//h.Trace();
	return h.Execute();
}

String GetConllFinnish(String txt, int turku_npp_port) {
	HttpRequest h;
	h.POST();
	h.ContentType("text/plain; charset=utf-8");
	h.PostData(txt);
	h.Url("http://localhost:" + IntStr(turku_npp_port));
	//h.Trace();
	return h.Execute();
}

bool dbg_break;

bool ConllParser::ParseFinnish(WString txt) {
	root.Create();
	root->SetType(NODE_ROOT);
	Vector<Vector<WString> > line_tokens;
	
	Vector<WString> lines = Split(txt, WString("\n"), false);
	
	for(int i = 0; i < lines.GetCount(); i++) {
		const WString& line = lines[i];
		
		//LOG(line);
		if (IsSpaceString(line)) {
			if (!line_tokens.IsEmpty()) {
				dbg_break = root->GetCount() == 161;
				
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

void FixText(Node& n) {
	if (n.GetCount() == 1) {
		Node& n0 = n.At(0);
		FixText(n0);
		//if (n0.GetText() == WString("UNKNOWN") && !n.GetText().IsEmpty())
		//	n.SetText(n0.GetText());
		if (n.IsType(NODE_NL) && n0.IsType(NODE_NL)) {
			n.SetText(n0.GetText());
			while (n0.GetCount())
				n.Add(n0.Detach(0));
			n.Remove(0);
		}
	}
	else
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		
		if (n0.IsType(NODE_TEXT)) {
			Node* n1 = new Node(NODE_NL, n.GetText());
			n1->Add(n.Detach(i));
			n.Insert(i, n1);
			n.SetText("UNKNOWN");
		}
		else FixText(n0);
	}
	
}

bool IsVectorEqual(Vector<int>& a, Vector<int>& b) {
	if (a.GetCount() != b.GetCount()) return false;
	for(int i = 0; i < a.GetCount(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

Node* ConllParser::ParseConll(Vector<Vector<WString> >& line_tokens) {
	ArrayMap<int, Node> nodes;
	VectorMap<int, Node*> node_links;
	
	int max_id = line_tokens.GetCount();
	for(int i = 0; i <= line_tokens.GetCount(); i++)
		node_links.Add(i, &nodes.Add(i));
	
	WString commapunct(",,punct");
	
	for(int i = 0; i < line_tokens.GetCount(); i++) {
		Vector<WString>& cur_line = line_tokens[i];
		int id = StrInt(cur_line[0].ToString());
		int parent = StrInt(cur_line[6].ToString());
		
		int j = nodes.Find(id);
		if (j < 0)
			return NULL;
		
		Node& n = nodes[j];
		n.SetType(NODE_NL);
		n.SetText(cur_line[4] + (7 < cur_line.GetCount() ? "," + cur_line[7] : ""));
		if (n.GetText() == commapunct)
			n.SetText("Comma,punct");
		
		Node& txt = n.Add(NODE_TEXT);
		txt.SetText(cur_line[1]);
		txt.SetInt(id);
		
		if (cur_line[2].GetCount() != 1 || cur_line[2][0] != '_') {
			Node& lemma = txt.Add(NODE_LEMMA);
			lemma.SetText(cur_line[2]);
		}
		
		String attr = cur_line[5].ToString();
		Vector<String> attrs = Split(attr, "|");
		for(int i = 0; i < attrs.GetCount(); i++) {
			String& keyvalue = attrs[i];
			int j = keyvalue.Find("=");
			if (j == -1) continue;
			String key = keyvalue.Left(j).ToString();
			String value = keyvalue.Mid(j+1).ToString();
			n.SetAttr(key, value);
		}
		
		int k = node_links.Find(parent);
		if (k < 0)
			return NULL;
		Node& p = *node_links[k];
		p.Add(nodes.Detach(j));
	}
	
	Node* n = nodes.Detach(0);
	n->SetType(NODE_SENTENCE);
	
	FixText(*n);
	
	Index<int> skip_ids;
	Vector<int> prev_ids;
	while (true) {
		Vector<int> ids;
		GetIds(*n, ids);
		
		if (!IsVectorEqual(prev_ids, ids))
			skip_ids.Clear();
		
		int match_id = FindOutlier(ids, skip_ids);
		if (match_id == -1)
			break;
		Swap(ids, prev_ids);
		
		Node* wrong = PopWrongOrder(*n, match_id);
		ASSERT(wrong);
		
		ClearEmptyNodes(*n);
		
		if (!InsertToCorrectOrder(wrong, *n, max_id))
			return NULL;
		else
			skip_ids.Add(match_id);
	}
	ClearEmptyNodes(*n);
	RemoveRecursiveDuplicates(*n);
	FixWeirdUnknowns(*n);
	FixRootUnknown(*n);
	
	ClearTextIds(*n);
	
	return n;
}


void RemoveRecursiveDuplicatesFinnish(Node& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		RemoveRecursiveDuplicatesFinnish(n.At(i));
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

void RemoveRecursiveDuplicates(Node& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		RemoveRecursiveDuplicates(n.At(i));
	}
	
	if (n.IsType(NODE_NL) && n.GetCount() == 1) {
		Node& n0 = n.At(0);
		if (n0.IsType(NODE_NL) && n0.GetText() == n.GetText()) {
			for(int i = 0; i < n0.GetCount();)
				n.Add(n0.Detach(i));
			n.Remove(0);
		}
	}
}

void GetIds(Node& n, Vector<int>& ids) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_TEXT)) {
			int id = n0.GetInt();
			ids.Add(id);
		}
		else {
			GetIds(n.At(i), ids);
		}
	}
}


int FindOutlier(Vector<int>& ids, Index<int>& skip_ids) {
	int match_id = -1, match_dist = 0;
	for(int i = 0; i < ids.GetCount(); i++) {
		int id = ids[i];
		int dist_l = 0, dist_r = 0;
		if (i > 0) {
			int l = id - 1;
			int real_l = ids[i-1];
			dist_l = abs(l - real_l);
		}
		if (i < ids.GetCount()-1) {
			int r = id + 1;
			int real_r = ids[i+1];
			dist_r = abs(r - real_r);
		}
		int dist = dist_l + dist_r;
		if (dist > match_dist) {
			if (skip_ids.Find(id) >= 0)
				continue;
			match_dist = dist;
			match_id = id;
		}
	}
	
	return -1;
}

Node* PopWrongOrder(Node& n, int match_id) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_TEXT)) {
			int id = n0.GetInt();
			
			if (match_id == id) {
				Node* n2 = new Node(NODE_NL, n.GetText());
				n2->Add(n.Detach(i));
				return n2;
			}
		}
		else {
			Node* n2 = PopWrongOrder(n.At(i), match_id);
			if (n2) return n2;
		}
	}
	
	return NULL;
}

void ClearEmptyNodes(Node& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_NL) && n0.GetCount() == 0) {
			n.Remove(i);
			i--;
		}
		else
			ClearEmptyNodes(n0);
	}
}

bool InsertToCorrectOrder(Node* to_insert, Node& n, int max_id) {
	if (to_insert->GetCount() == 0) return false;
	Node& n0 = to_insert->At(0);
	int id = n0.GetInt();
	
	if (id <= 1) {
		int right = id+1;
		for(int i = 0; i < n.GetCount(); i++) {
			Node& r = n.At(i);
			if (ContainsTextIdOrGreater(r, right)) {
				n.Insert(i, to_insert);
				return true;
			}
		}
	}
	else if (id == max_id) {
		int left = id-1;
		for(int i = 0; i < n.GetCount(); i++) {
			Node& l = n.At(i);
			if (ContainsTextId(l, left)) {
				n.Insert(i+1, to_insert);
				return true;
			}
		}
	}
	else {
		ASSERT(id < max_id);
		int left = id-1;
		int right = id+1;
		for(int i = 1; i < n.GetCount(); i++) {
			Node& l = n.At(i-1);
			Node& r = n.At(i);
			if (
				(ContainsTextId(l, left) && ContainsTextIdOrGreater(r, right)) ||
				(ContainsTextIdOrLess(l, left) && ContainsTextId(r, right)) ) {
				n.Insert(i, to_insert);
				return true;
			}
		}
	}
	
	for(int i = 0; i < n.GetCount(); i++) {
		if (InsertToCorrectOrder(to_insert, n.At(i), max_id))
			return true;
	}
	return false;
}

void FixWeirdUnknowns(Node& n) {
	for(int i = 0; i < n.GetCount(); i++) {
		FixWeirdUnknowns(n.At(i));
	}
	
	if (n.IsType(NODE_NL)) {
		WString type = n.GetText();
		while (true) {
			if (IsConstChar(type, "UNKNOWN", 7) && type.Find(",") == 7) {
				type = type.Mid(8);
				n.SetText(type);
			}
			else break;
		}
	}
}

void FixRootUnknown(Node& n) {
	if (n.IsType(NODE_ROOT)) {
		for(int i = 0; i < n.GetCount(); i++) {
			FixWeirdUnknowns(n.At(i));
		}
	}
	else if (n.IsType(NODE_SENTENCE)) {
		if (n.GetCount() > 1) {
			Node* unk = new Node(NODE_NL, "UNKNOWN");
			while (n.GetCount())
				unk->Add(n.Detach(0));
			n.Add(unk);
		}
	}
}

void ClearTextIds(Node& n) {
	if (n.IsType(NODE_TEXT))
		n.SetInt(0);
	else
		for(int i = 0; i < n.GetCount(); i++)
			ClearTextIds(n.At(i));
}

int FindWrongOrderId(Node&n, int& counter) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_TEXT)) {
			int id = n0.GetInt();
			if (id != counter)
				return counter;
			counter++;
		}
		else {
			int j = FindWrongOrderId(n.At(i), counter);
			if (j >= 0) return j;
		}
	}
	
	return -1;
}


bool InsertAtId(Node& n, Node* to_insert, int id) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_NL) && n0.GetCount() == 1 && n0.At(0).IsType(NODE_TEXT) && id == n0.At(0).GetInt()) {
			n.Insert(i, to_insert);
			return true;
		}
		else {
			if (InsertAtId(n0, to_insert, id))
				return true;
		}
	}
	
	return false;
}

Node* FindNodeId(Node& n, int match_id) {
	for(int i = 0; i < n.GetCount(); i++) {
		Node& n0 = n.At(i);
		if (n0.IsType(NODE_TEXT)) {
			int id = n0.GetInt();
			if (match_id == id)
				return &n;
		}
		else {
			Node* n2 = PopWrongOrder(n.At(i), match_id);
			if (n2) return n2;
		}
	}
	
	return NULL;
}

bool ContainsTextId(Node& n, int id) {
	if (n.IsType(NODE_TEXT))
		return n.GetInt() == id;
	for(int i = 0; i < n.GetCount(); i++)
		if (ContainsTextId(n.At(i), id))
			return true;
	return false;
}

bool ContainsTextIdOrGreater(Node& n, int id) {
	if (n.IsType(NODE_TEXT))
		return n.GetInt() >= id;
	for(int i = 0; i < n.GetCount(); i++)
		if (ContainsTextIdOrGreater(n.At(i), id))
			return true;
	return false;
}

bool ContainsTextIdOrLess(Node& n, int id) {
	if (n.IsType(NODE_TEXT))
		return n.GetInt() <= id;
	for(int i = 0; i < n.GetCount(); i++)
		if (ContainsTextIdOrLess(n.At(i), id))
			return true;
	return false;
}

bool ContainsUnknowns(Node& n) {
	if (n.IsType(NODE_NL) && IsConstChar(n.GetText(), "UNKNOWN", 7))
		return true;
	for(int i = 0; i < n.GetCount(); i++)
		if (ContainsUnknowns(n.At(i)))
			return true;
	return false;
}


NAMESPACE_LANGUAGE_END
