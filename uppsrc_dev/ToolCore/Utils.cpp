#include "ToolCore.h"
#include <TextLib/TextLib.h>


BEGIN_TEXTLIB_NAMESPACE




SolverBaseIndicator::SolverBaseIndicator() {
	ProgressIndicator::Set(0,1);
	
}

void SolverBaseIndicator::Attach(SolverBase& sb) {
	sb.WhenProgress << [this](int a, int t) {PostCallback(THISBACK2(SetProgress, a,t));};
}

void SolverBaseIndicator::SetProgress(int a, int t) {
	ProgressIndicator::Set(a, t);
}




String Capitalize(String s) {
	return ToUpper(s.Left(1)) + s.Mid(1);
}

void RemoveSinger(String& s) {
	int a = s.Find(" by the singer");
	if (a >= 0)
		s = s.Left(a);
}

String JoinMap(const VectorMap<String,String>& m, String delim0, String delim1) {
	String o;
	for(int i = 0; i < m.GetCount(); i++)
		o << m.GetKey(i) << delim0 << m[i] << delim1;
	return o;
}

String FixStructIndent(const String& s) {
	Vector<String> lines = Split(s, "\n");
	int indent = 0;
	for (String& l : lines) {
		l = TrimBoth(l);
		if (l.IsEmpty()) continue;
		int diff = 0;;
		if (l[0] == '[') {
			int a = 1;
			int b0 = l.Find("]");
			int b1 = l.Find(":");
			int b = -1;
			if (b0 >= 0 && b1 >= 0) b = min(b0,b1);
			else if (b0 >= 0) b = b0;
			else b = b1;
			
			if (b >= 0) {
				indent = Split(l.Mid(a,b-a),".").GetCount();
				diff = -1;
			}
		}
		String new_l;
		new_l.Cat('\t', indent + diff);
		new_l.Cat(l);
		l = new_l;
	}
	return Join(lines, "\n");
}

void GetDirectoryFiles(String dir, Index<String>& files) {
	files.Clear();
	FindFile ff;
	if (ff.Search(AppendFileName(dir, "*"))) {
		do {
			String name = ff.GetName();
			if (name == "." || name == "..") continue;
			files.Add(name);
		}
		while (ff.Next());
	}
}

END_TEXTLIB_NAMESPACE
