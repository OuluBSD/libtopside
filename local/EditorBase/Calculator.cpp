#include "EditorBase.h"

NAMESPACE_TOPSIDE_BEGIN



ArrayMap<String, EscValue>& UscGlobal()
{
	static ArrayMap<String, EscValue> global;
	return global;
}



TheCalc::TheCalc()
{
	Highlight("calc");
	NoHorzScrollbar();
	HideBar();
}

int LfToSpaceFilter(int c)
{
	return c == '\n' ? ' ' : c;
}

void TheCalc::Execute()
{
	int li = GetLineCount() - 1;
	if(IsSelection()) {
		String s = GetSelection();
		if(s.GetLength() < 80) {
			SetCursor(GetLength());
			Paste(Filter(s, LfToSpaceFilter).ToWString());
		}
		return;
	}
	if(GetLine(GetCursor()) != li) {
		WString s = GetWLine(GetLine(GetCursor()));
		if(s[0] == '$') s = s.Mid(1);
		SetCursor(GetLength());
		Paste(s);
		return;
	}
	String txt;
	try {
		ArrayMap<String, EscValue>& g = UscGlobal();
		for(int i = 0; i < g.GetCount(); i++)
			vars.GetAdd(g.GetKey(i)) = g[i];
		String s = GetUtf8Line(li);
		if(IsNull(s))
			return;
		EscValue v = Evaluatex(s, vars);
		txt = v.ToString(GetSize().cx / max(1, GetFont().Info()['x']), 4, true);
		vars.GetAdd("_") = v;
	}
	catch(CParser::Error e) {
		const char *x = strchr(e, ':');
		txt << "ERROR: " << (x ? x + 1 : ~e);
	}
	SetCursor(GetPos(li));
	Paste("$");
	SetCursor(GetLength());
	Paste("\n");
	Paste(FromUtf8(txt));
	Paste("\n");
}

void TheCalc::LeftDouble(Point p, dword flags)
{
	CodeEditor::LeftDouble(p, flags);
	if(IsSelection())
		Execute();
}

bool TheCalc::Key(dword key, int count)
{
	switch(key) {
	case K_ENTER:
		Execute();
		break;
	default:
		return CodeEditor::Key(key, count);
	}
	return true;
}


NAMESPACE_TOPSIDE_END
