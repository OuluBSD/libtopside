#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

void ChomskyNormalForm(Node& tree) {
	int n = tree.GetCount();
	
	if (n < 2) {
		throw Exc("Rule should have at least two items");
	}
	
	if (tree.At(0).GetText().GetCount() == 0)
		throw Exc("Root should be a string");
	
	if (n == 2) {
		// X -> word
		if (tree.At(1).GetCount()) {
			// (1) Normalise single non-terminal on the right
			Node& t0 = tree.At(0);
			Node& t1 = tree.At(1);
			WString ws = t0.GetText() + "+" + t1.At(0).GetText();
			t0.ClearNodes();
			t0.SetText(ws);
			for(int i = 1; i < t1.GetCount();)
				tree.Add(t1.Detach(i));
			tree.Remove(1);
			ChomskyNormalForm(tree);
		}
		else {
			if (tree.At(1).GetText().IsEmpty())
				throw Exc("Terminal should be a string");
		}
	}
	else if (n == 3) {
		// X -> Y1, Y2
		for(int i = 1; i < 3; i++) {
			Node& t = tree.At(i);
			if (t.GetText().GetCount()) {
				// (2) Normalise rule that mixes terminal with non-terminal
				WString ws = t.GetText();
				t.SetText("");
				t.Add(NODE_NL).SetText(ToUpper(ws));
				t.Add(NODE_NL).SetText(ws);
			} else {
				if (!t.GetCount())
					throw Exc("Non-terminal should be a list");
				ChomskyNormalForm(t);
			}
		}
	}
	else {
		// (3) Normalise illegal n-ary rule
		Node& n = tree.Insert(2);
		n.SetType(NODE_NL);
		n.Add(NODE_NL).SetText(tree.At(0).GetText());
		for(int i = 3; i < tree.GetCount();)
			n.Add(tree.Detach(i));
		ChomskyNormalForm(tree);
	}
}

void UnChomskyNormalForm(Node& tree) {
	Node& sym = tree.At(0);
	WString t = sym.GetText();
	
	if (tree.GetCount() == 2) {
		int i = t.Find("+");
		if (i >= 0) {
			// Undo (1)
			WString a = t.Left(i);
			WString b = t.Mid(i+1);
			sym.SetText(a);
			Node& t1 = tree.Insert(1).SetType(NODE_NL);
			t1.Add(NODE_NL).SetText(b);
			t1.Add(tree.Detach(2));
		}
	}
	else {
		bool transformed = false;
		int count = tree.GetCount();
		for(int i = 2; i < count; i++) {
			Node& n0 = tree.At(i);
			if (n0.At(0).GetText() == t) {
				// Undo (3)
				for(int j = 1, k = 1; j < n0.GetCount(); k++)
					tree.Insert(i+k, n0.Detach(j));
				tree.Remove(i);
				transformed = true;
			}
		}
		if (transformed)
			UnChomskyNormalForm(tree);
		else {
			for(int i = 1; i < tree.GetCount(); i++) {
				UnChomskyNormalForm(tree.At(i));
			}
		}
	}
}

bool IsNullElementsFilter(Node& tree) {
	if (tree.GetText().GetCount() && tree.GetCount() == 0)
		;
	else {
		if (tree.GetCount() < 2)
			return false;
		else if (tree.GetCount() == 2) {
			Node& n0 = tree.At(0);
			if (n0.GetText().Find("-NONE-") >= 0)
				return false;
		}
	}
	return true;
}

void PruneNullElements(Node& tree, VectorMap<Node*, Node*>& parents) {
	for(int i = 0; i < tree.GetCount(); i++) {
		if (!IsNullElementsFilter(tree.At(i))) {
			tree.Remove(i);
			i--;
		}
	}
	
	if (tree.GetCount() >= 2) {
		Node& root = tree.At(0);
		
		if (root.GetText().IsEmpty()) {
			throw Exc("Root should be a string");
		}
		
		if (root.GetText() == WString("X"))
			throw UncertainParsing();
		
		for(int i = 1; i < tree.GetCount(); i++) {
			Node& n = tree.At(i);
			if (n.GetCount()) {
				parents.GetAdd(&n) = &tree;
				PruneNullElements(n, parents);
			}
		}
	}
	
	for(int i = 0; i < tree.GetCount(); i++) {
		if (!IsNullElementsFilter(tree.At(i))) {
			tree.Remove(i);
			i--;
		}
	}
}

void LowerFirstWord(Node& tree) {
	if (tree.GetCount() == 2) {
		if (IsCapWord(tree.At(1).GetText()))
			tree.At(1).SetText(ToLower(tree.At(1).GetText()));
	}
	else
		LowerFirstWord(tree.At(1));
}

bool HasNoneTag(Node& n) {
	if (n.GetCount() && n.At(0).GetText() == WString("-NONE-"))
		return true;
	for(int i = 1; i < n.GetCount(); i++)
		if (HasNoneTag(n.At(i)))
			return true;
	return false;
}

void FixSingleTags(Node& n) {
	if (n.GetCount() == 1) {
		String tag = n.At(0).GetText().ToString();
		if (tag == "-LRB-")
			n.Add(NODE_NL).SetText("-LRB-");
		else if (tag == "-RRB-")
			n.Add(NODE_NL).SetText("-RRB-");
	}
	for(int i = 0; i < n.GetCount(); i++) {
		FixSingleTags(n.At(i));
	}
}

void GenerateNormal(String path, const Vector<String>& input_treebanks) {
	FileOut fout(path);
	for(int i = 0; i < input_treebanks.GetCount(); i++) {
		const String& path = input_treebanks[i];
		Node tb;
		ParseTreebank(path, tb);
		for(int j = 0; j < tb.GetCount(); j++) {
			Node& t = tb.At(j);
			try {
				VectorMap<Node*, Node*> parents;
				PruneNullElements(t, parents);
				FixSingleTags(t);
				ChomskyNormalForm(t);
				LowerFirstWord(t);
				fout.PutLine(StoreAsJson(t, false));
				fout.Flush();
			}
			catch (UncertainParsing e) {
				continue;
			}
			catch (Exc e) {
				int words = 0;
				LOG(GetSentence(t, words));
				LOG(e);
				//LOG("Discarding tree:");
				//LOG(NodeTreeString(t));
			}
		}
	}
}


NAMESPACE_LANGUAGE_END
