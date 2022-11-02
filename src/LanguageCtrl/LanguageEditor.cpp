#include "LanguageCtrl.h"


NAMESPACE_LANGUAGE_BEGIN

void CollectSentences(Node& orig, const Node& nl) {
	if (nl.IsType(NODE_SENTENCE))
		orig.Add(new Node(nl));
	else {
		for(int i = 0; i < nl.GetCount(); i++)
			CollectSentences(orig, nl.At(i));
	}
}


void LENode::SetNode(Node& n) {
	this->n = &n;
	sub.Clear();
	max_depth = 0;
	
	int w = 0;
	if (n.IsType(NODE_NL) || n.IsType(NODE_SENTENCE)) {
		for(int i = 0; i < n.GetCount(); i++) {
			if (i) w += HDIV;
			LENode& l = sub.Add();
			l.SetNode(n.At(i));
			w += l.width;
			max_depth = max(max_depth, l.max_depth + 1);
		}
	}
	
	txt = n.GetText().ToString();
	//int i = txt.Find(",");
	//if (i >= 0) txt = txt.Left(i);
	
	Font fnt(Arial(FONTH));
	Size txt_sz = GetTextSize(txt, fnt);
	
	width = max(txt_sz.cx + 2, w);
}

void LENode::Paint(Draw& d, int x, int y) {
	if (IsAnyA(*n))
		d.DrawRect(x, y, width, ROWH, Color(255, 255, 200));
	else if (IsAnyN(*n))
		d.DrawRect(x, y, width, ROWH, Color(255, 200, 196));
	else if (IsAnyV(*n))
		d.DrawRect(x, y, width, ROWH, Color(180, 221, 255));
	else if (IsPP(*n))
		d.DrawRect(x, y, width, ROWH, Color(168, 255, 208));
	else if (IsS(*n))
		d.DrawRect(x, y, width, ROWH, Color(255, 197, 162));
	else if (IsUnknown(*n))
		d.DrawRect(x, y, width, ROWH, Color(249, 185, 255));
	else
		d.DrawRect(x, y, width, ROWH, Color(209, 209, 209));
	
	d.DrawText(x+1, y+2, txt, Arial(FONTH), Black());
	
	
	int x_delta = 0;
	for(int i = 0; i < sub.GetCount(); i++) {
		if (i) x_delta += HDIV;
		LENode& l = sub.At(i);
		
		l.Paint(d, x + x_delta, y + ROWH);
		x_delta += l.width;
	}
	
}

LENode* LENode::FindByCursor(int x, int y) {
	if (x < 0 || y < 0 || x >= width)
		return NULL;
	if (y < ROWH)
		return this;
	int x_delta = 0;
	for(int i = 0; i < sub.GetCount(); i++) {
		if (i) x_delta += HDIV;
		LENode& l = sub.At(i);
		LENode* n = l.FindByCursor(x - x_delta, y - ROWH);
		if (n) return n;
		x_delta += l.width;
	}
	return NULL;
}





LanguageEditor::LanguageEditor() {
	
}

void LanguageEditor::Clear() {
	lock.Enter();
	loff = 0;
	toff = 0;
	graph.Clear();
	root.sub.Clear();
	root.width = 0;
	lock.Leave();
}

void LanguageEditor::SetNode(Node& n) {
	lock.Enter();
	
	//LOG(NodeTreeString(n));
	root.SetNode(n);
	
	int depth = root.max_depth + 1;
	int h = depth * LENode::ROWH;
	int w = root.width;
	ImageDraw graph(w, h);
	graph.DrawRect(0, 0, w, h, White());
	root.Paint(graph, 0, 0);
	this->graph = graph;
	
	lock.Leave();
	
	
	Size sz(GetSize());
	Size graph_sz = this->graph.GetSize();
	loff = (sz.cx - graph_sz.cx) / 2;
	toff = (sz.cy - graph_sz.cy) / 2;
}

void LanguageEditor::Paint(Draw& d) {
	Size sz(GetSize());
	
	d.DrawRect(sz, White());
	
	if (!graph.IsEmpty())
		d.DrawImage(loff, toff, graph);
}

void LanguageEditor::Layout() {
	
	Size sz(GetSize());
	Size graph_sz = this->graph.GetSize();
	loff = (sz.cx - graph_sz.cx) / 2;
	toff = (sz.cy - graph_sz.cy) / 2;
	
	Refresh();
}

String AppendPhrases(String s) {
	if (s == "V") s += ";VP";
	if (s == "N") s += ";NP";
	if (s == "A") s += ";AP";
	if (s == "Adv") s += ";PP";
	return s;
}

void LanguageEditor::LeftDown(Point p, dword keyflags) {
	int x = p.x - loff;
	int y = p.y - toff;
	LENode* n = root.FindByCursor(x, y);
	if (n) {
		
	}
}











LanguageEditorCtrl::LanguageEditorCtrl() {
	Add(vsplit.SizePos());
	vsplit << edit << hsplit;
	vsplit.SetPos(7000);
	vsplit.Vert();
	
	sentlist.AddColumn("Sentence");
	sentlist <<= THISBACK(SelectSentence);
	
	hsplit.Horz();
	hsplit << sentlist;
	hsplit.SetPos(3000);
}

void LanguageEditorCtrl::SelectSentence() {
	edit.Clear();
	node_id = sentlist.GetCursor();
	if (node_id < 0 || node_id >= orig.GetCount())
		return;
	
	lock.Enter();
	n = orig.At(node_id);
	lock.Leave();
	
	Thread::Start(THISBACK(Process));
}

void LanguageEditorCtrl::RuleMenu(Bar& bar) {
	bar.Add("Dummy action", Callback());
}

void LanguageEditorCtrl::SetData(const Value& data) {
	edit.Clear();
	
	Node nl;
	String s = data;
	MemStream mem((void*)s.Begin(), s.GetCount());
	mem % nl;
	
	SetNode(nl);
}

void LanguageEditorCtrl::SetNode(const Node& n) {
	
	orig.Clear();
	CollectSentences(orig, n);
	
	sent_ok.SetCount(orig.GetCount());
	for(auto& v : sent_ok) v = false;
	
	for(int i = 0; i < orig.GetCount(); i++) {
		WString sentence = GetSentence(orig.At(i));
		AttrText txt;
		txt.Set(sentence);
		if (!sent_ok[i]) {
			txt.NormalPaper(Color(255, 195, 191));
			txt.Ink(Black());
		}
		sentlist.Set(i, 0, txt);
	}
	sentlist.SetCount(orig.GetCount());
	
	if (orig.GetCount() && !sentlist.IsCursor()) {
		sentlist.SetCursor(0);
	}
	
	SelectSentence();
	Data();
	
}

void LanguageEditorCtrl::Process() {
	lock.Enter();
	
	// do something...
	
	// mark as ok
	sent_ok[node_id] = true;
	
	lock.Leave();
	
	PostCallback(THISBACK(ProcessReady));
}

void LanguageEditorCtrl::ProcessReady() {
	edit.SetNode(n);
	edit.Layout();
	Data();
}

void LanguageEditorCtrl::Data() {
	
	
	edit.Refresh();
	
}

NAMESPACE_LANGUAGE_END

