#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

Node* GetBacktrace(Backpointer& back, DictMap<int, int, WString, Backpointer>& bp) {
	// Extract the tree from the backpointers
	if (back.len == 6) {
		Node* n = new Node();
		n->SetType(NODE_NL);
		Node* l = GetBacktrace(bp.Get(back.i, back.s, back.Y), bp);
		Node* r = GetBacktrace(bp.Get(back.s+1, back.j, back.Z), bp);
		n->Add(NODE_NL).SetText(back.X);
		if (l) n->Add(l);
		if (r) n->Add(r);
		return n;
	}
	else if (back.len == 4) {
		Node* n = new Node();
		n->SetType(NODE_NL);
		n->Add(NODE_NL).SetText(back.X);
		n->Add(NODE_NL).SetText(back.Y);
		return n;
	}
	else return NULL;
}

Node* CKY(PCFG& pcfg, Vector<NormWord>& norm_words) {
	int n = norm_words.GetCount();
	norm_words.Insert(0);
	
	DictMap<int, int, WString, double> pi;
	DictMap<int, int, WString, Backpointer> bp;
	
	for(int i = 1; i < n+1; i++) {
		NormWord& nw = norm_words[i];
		for(int j = 0; j < pcfg.N.GetCount(); j++) {
			const WString& X = pcfg.N[j];
			NormWord nw2;
			nw2.norm = X;
			nw2.word_ = nw.norm;
			int k = pcfg.q1.Find(nw2);
			if (k >= 0) {
				double d = pcfg.q1[k];
				pi.GetAdd(i, i, X) = d;
				bp.GetAdd(i, i, X).Set(X, nw.word_, i, i);
			}
		}
	}
	for(int l = 1; l < n; l++) {
		for(int i = 1; i < n-l+1; i++) {
			int j = i+l;
			for(int k = 0; k < pcfg.N.GetCount(); k++) {
				const WString& X = pcfg.N[k];
				
				double max_score = -DBL_MAX;
				Backpointer back;
				
				int brc = pcfg.binary_rules.GetCount();
				const Vector<Y2>& br = pcfg.binary_rules.GetAdd(X);
				int brc2 = br.GetCount();
				
				for(int t = 0; t < br.GetCount(); t++) {
					const WString& Y = br[t].y1;
					const WString& Z = br[t].y2;
					for(int s = i; s < j; s++) {
						if (pi.GetDefault(i, s, Y, 0) > 0 && pi.GetDefault(s+1, j, Z, 0) > 0) {
							double score =
								pcfg.q2.Get(XY2(X, Y, Z)) *
								pi.Get(i, s, Y) *
								pi.Get(s+1, j, Z);
							if (score > max_score) {
								max_score = score;
								back.X = X;
								back.Y = Y;
								back.Z = Z;
								back.i = i;
								back.s = s;
								back.j = j;
								back.len = 6;
							}
						}
					}
				}
				
				//if (max_score > 0.0) {
					bp.GetAdd(i, j, X) = back;
					pi.GetAdd(i, j, X) = max_score;
				//}
			}
		}
	}
	
	double max_a = -DBL_MAX;
	Backpointer* top = NULL;
	for(int i = 0; i < pcfg.N.GetCount(); i++) {
		const WString& X = pcfg.N[i];
		double a = pi.GetDefault(1, n, X, -DBL_MAX);
		if (a > max_a) {
			max_a = a;
			top = &bp.Get(1, n, X);
		}
	}
	
	if (!top) return NULL;
	return GetBacktrace(*top, bp);
}






StatParser::StatParser() {
	
}

void StatParser::LoadModel() {
	if (pcfg.IsEmpty())
		BuildModel(pcfg);
}

void StatParser::NormParse(WString sentence) {
	tokenizer.Tokenize(sentence);
	if (tokenizer.GetCount() == 0) return;
	
	WString first = tokenizer.Get(0).GetString();
	if (IsCapWord(first))
		tokenizer.ForceGet(0).str_value = ToLower(first);
	
	Vector<NormWord> norm_words;
	for(int i = 0; i < tokenizer.GetCount(); i++) {
		WString w = tokenizer.Get(i).str_value;
		//TODO: if isinstance(word, tuple):
		
		NormWord& nw = norm_words.Add();
		nw.norm = pcfg.GetNormWord(w);
		nw.word_ = w;
		
		LOG(i << ": " << nw.word_ << " (" << nw.norm << ")");
	}
	
	root = CKY(pcfg, norm_words);
}

bool StatParser::Parse(WString sentence) {
	NormParse(sentence);
	if (root.IsEmpty())
		return false;
	UnChomskyNormalForm(*root);
	return true;
}

void StatParser::Dump() {
	if (!root.IsEmpty()) {
		LOG(NodeTreeString(*root));
	}
}



bool IsCapWord(const WString& w) {
	if (w.IsEmpty())
		return false;
	if (IsUpper(w[0])) {
		bool all_lower = true;
		for(int i = 1; i < w.GetCount(); i++) {
			if (!IsLower(w[i])) {
				all_lower = false;
				break;
			}
		}
		return all_lower;
	}
	return false;
}



void StatParseEnglish(String text, Node& n) {
	Vector<String> sents = Split(GetSentenceLines(text), "\n");
	
	n.Clear();
	n.SetType(NODE_ROOT);
	
	for(int i = 0; i < sents.GetCount(); i++) {
		String& sent = sents[i];
		
		StatParser p;
		p.Parse(sent.ToWString());
		
		if (!p.root.IsEmpty()) {
			n.Add(NODE_SENTENCE).Add(p.root.Detach());
		}
	}
	
}


NAMESPACE_LANGUAGE_END
