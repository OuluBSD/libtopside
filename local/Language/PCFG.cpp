#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

PCFG::PCFG() {
	
}

WString PCFG::GetNormWord(WString word_) {
	if (well_known_words.Find(word_) >= 0)
		return word_;
	else
		return WordClass(word_);
}

void PCFG::BuildCaches() {
	N.Clear();
	binary_rules.Clear();
	
	for(int i = 0; i < q1.GetCount(); i++) {
		N.FindAdd(q1.GetKey(i).norm);
	}
	
	for(int i = 0; i < q2.GetCount(); i++) {
		const XY2& xy2 = q2.GetKey(i);
		N.FindAdd(xy2.x);
		N.FindAdd(xy2.y1);
		N.FindAdd(xy2.y2);
		Y2& br = binary_rules.GetAdd(xy2.x).Add();
		br.y1 = xy2.y1;
		br.y2 = xy2.y2;
	}
}

WString PCFG::WordClass(WString word_) {
	
	if (IsCapWord(word_))
		return "_CAP_";
	
	if (IsEnding("ly", 2, word_))
		return "_LY_";
	
	if (IsEnding("ed", 2, word_))
		return "_ED_";
	
	if (IsEnding("ing", 3, word_))
		return "_ING_";
	
	if (IsNumberStr(word_))
		return "_NUM_";
	
	int i = word_type_count.Find(word_);
	if (i >= 0) {
		auto& map = word_type_count[i];
		if (map.GetCount() == 1)
			return "_RARE_" + map.GetKey(0) + "_";
	}
	
	return "_RARE_";
}

void PCFG::LearnFromTreebanks(Vector<String>& treebanks) {
	sym_count.Clear();
	unary_count.Clear();
	binary_count.Clear();
	words_count.Clear();
	
	for(int i = 0; i < treebanks.GetCount(); i++) {
		FileIn fin(treebanks[i]);
		while (!fin.IsEof()) {
			String line = fin.GetLine();
			Node n;
			LoadFromJson(n, line);
			Count(n);
		}
	}
	
	
	// Words
	for(int i = 0; i < word_type_count.GetCount(); i++)
		SortByValue(word_type_count[i], StdGreater<int>());
	for(int i = 0; i < words_count.GetCount(); i++)
		if (words_count[i] >= RARE_WORD_COUNT)
			well_known_words.FindAdd(words_count.GetKey(i));
	
	
	// Normalise the unary rules count
	VectorMap<NormWord, int> norm;
	for(int i = 0; i < unary_count.GetCount(); i++) {
		const NormWord& key = unary_count.GetKey(i);
		NormWord nw;
		nw.word_ = GetNormWord(key.word_);
		nw.norm = key.norm;
		norm.GetAdd(nw, 0) += unary_count[i];
	}
	Swap(unary_count, norm);
	
	// Q1
	for(int i = 0; i < unary_count.GetCount(); i++) {
		const NormWord& key = unary_count.GetKey(i);
		q1.GetAdd(key) = (double)unary_count[i] / (double)sym_count.Get(key.norm);
	}
	
	// Q2
	for(int i = 0; i < binary_count.GetCount(); i++) {
		const XY2& key = binary_count.GetKey(i);
		q2.GetAdd(key) = (double)binary_count[i] / (double)sym_count.Get(key.x);
	}
	
	BuildCaches();
}

void PCFG::Count(Node& tree) {
	
	// Count the non-terminal symbols
	Node& sym = tree.At(0);
	sym_count.GetAdd(sym.GetText(), 0)++;
	
	if (tree.GetCount() == 3) {
		// Binary Rule
		XY2 key;
		key.x = sym.GetText();
		key.y1 = tree.At(1).At(0).GetText();
		key.y2 = tree.At(2).At(0).GetText();
		binary_count.GetAdd(key, 0)++;
		
		// Recursively count the children
		Count(tree.At(1));
		Count(tree.At(2));
	}
	else if (tree.GetCount() == 2) {
		// Unary Rule
		NormWord nw;
		nw.word_ = tree.At(1).GetText();
		nw.norm = sym.GetText();
		unary_count.GetAdd(nw, 0)++;
		words_count.GetAdd(nw.word_, 0)++;
		word_type_count.GetAdd(nw.word_).GetAdd(nw.norm, 0)++;
	}
}

void PCFG::SaveModel(String path) {
	FileOut fout(path);
	
	fout % q1
		 % q2
		 % well_known_words
		 % word_type_count;
	
	/*for(int i = 0; i < q1.GetCount(); i++) {
		const NormWord& nw = q1.GetKey(i);
		ValueArray va;
		va.Add("Q1");
		va.Add(nw.word_);
		va.Add(nw.norm);
		va.Add(q1[i]);
		fout << AsJSON(va) << "\n";
	}
	
	for(int i = 0; i < q2.GetCount(); i++) {
		const XY2& xy = q2.GetKey(i);
		ValueArray va;
		va.Add("Q2");
		va.Add(xy.x);
		va.Add(xy.y1);
		va.Add(xy.y2);
		va.Add(q2[i]);
		fout << AsJSON(va) << "\n";
	}
	
	ValueArray va;
	va.Add("WORDS");
	ValueArray words;
	for(int i = 0; i < well_known_words.GetCount(); i++)
		words.Add(well_known_words[i]);
	va.Add(words);
	fout << AsJSON(va) << "\n";*/
}

void PCFG::LoadModel(String path) {
	FileIn fin(path);
	
	fin  % q1
		 % q2
		 % well_known_words
		 % word_type_count;
		
	/*while (!fin.IsEof()) {
		String line = fin.GetLine();
		ValueArray va = ParseJSON(line);
		String s0 = va[0];
		if (s0 == "Q1") {
			NormWord nw;
			nw.word_ = va[1];
			nw.norm = va[2];
			double count = va[3];
			q1.GetAdd(nw) = count;
		}
		else if (s0 == "Q2") {
			XY2 xy;
			xy.x = va[1];
			xy.y1 = va[2];
			xy.y2 = va[3];
			double count = va[4];
			q2.GetAdd(xy) = count;
		}
		else if (s0 == "WORDS") {
			well_known_words.Clear();
			ValueArray list = va[1];
			for(int i = 0; i < list.GetCount(); i++)
				well_known_words.Add(list[i]);
		}
	}*/
	
	BuildCaches();
}

bool PCFG::IsEmpty() {
	return !binary_rules.GetCount();
}


NAMESPACE_LANGUAGE_END
