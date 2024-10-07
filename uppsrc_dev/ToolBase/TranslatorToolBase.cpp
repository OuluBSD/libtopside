#include "ToolBase.h"


BEGIN_TEXTLIB_NAMESPACE



TranslatorToolCtrl::TranslatorToolCtrl() {
	Add(hsplit.HSizePos().VSizePos());
	
	hsplit.Horz() << orig << trans;
	InitEditor(orig);
	InitEditor(trans);
	
	orig.SetFont(Monospace(15));
	trans.SetFont(Monospace(15));
	
	#if 0
	orig.WhenAction << THISBACK(OnOriginalChange);
	trans.WhenAction << THISBACK(OnTranslatedChange);
	#endif
	
}

void TranslatorToolCtrl::InitEditor(CodeEditor& codeedit) {
	int editortabsize, indent_spaces, indent_amount, show_tabs, no_parenthesis_indent, hilite_scope, hilite_bracket;
	int hilite_ifdef, barline, hilite_if_endif, thousands_separator, hline, line_numbers, auto_enclose;
	int mark_lines, bordercolumn, bordercolor, persistent_find_replace, find_replace_restore_pos;
	int font_height;
	
	editortabsize = 4;
	indent_spaces = 0;
	indent_amount = 4;
	show_tabs = 0;
	no_parenthesis_indent = 0;
	hilite_scope = 2;
	hilite_bracket = 1;
	hilite_ifdef = 1;
	barline = 1;
	hilite_if_endif = 1;
	thousands_separator = 1;
	hline = 1;
	line_numbers = 1;
	auto_enclose = 1;
	mark_lines = 0;
	bordercolumn = 1;
	bordercolor = 1;
	persistent_find_replace = 1;
	find_replace_restore_pos = 0;
	font_height = 15;
	
	
	String highlight = "cpp";
	codeedit.DefaultHlStyles();
	codeedit.Highlight(highlight);
	
	codeedit.TabSize(editortabsize);
	codeedit.IndentSpaces(indent_spaces);
	codeedit.IndentAmount(indent_amount);
	codeedit.ShowTabs(show_tabs);
	codeedit.ShowLineEndings(show_tabs);
	codeedit.NoParenthesisIndent(no_parenthesis_indent);
	codeedit.HiliteScope(hilite_scope);
	codeedit.HiliteBracket(hilite_bracket);
	codeedit.HiliteIfDef(hilite_ifdef);
	codeedit.BarLine(barline);
	codeedit.HiliteIfEndif(hilite_if_endif);
	codeedit.ThousandsSeparator(thousands_separator);
	codeedit.ShowCurrentLine(hline ? HighlightSetup::GetHlStyle(HighlightSetup::SHOW_LINE).color : (Color)Null);
	codeedit.LineNumbers(line_numbers);
	codeedit.AutoEnclose(auto_enclose);
	codeedit.MarkLines(mark_lines);
	//codeedit.BorderColumn(bordercolumn, bordercolor);
	codeedit.PersistentFindReplace(persistent_find_replace);
	codeedit.FindReplaceRestorePos(find_replace_restore_pos);
	
	codeedit.SetFont(Monospace(font_height));
	
}

void TranslatorToolCtrl::Data() {
	EditorPtrs& p = GetPointers();
	
	#if 0
	orig.SetData(GetOriginalText());
	trans.SetData(GetTranslatedText());
	#endif
}

void TranslatorToolCtrl::ToolMenu(Bar& bar) {
	bar.Add(t_("Translate"), AppImg::Part(), THISBACK(Translate)).Key(K_F5);
	
}

String TranslatorToolCtrl::GetStatusText() {
	return t_("Left: native; Right: english");
}

void TranslatorToolCtrl::Translate() {
	using namespace TextLib;
	EditorPtrs& p = GetPointers();
	if(!p.component || !p.entity || key.IsEmpty() || trans_key.IsEmpty())
		return;
	
	
	/*if (fn == FN_TRANSLATE_NL) {
		String orig_lng = GetCurrentLanguageString().Left(5);
		String trans_lng = "EN-US";
		
		TaskMgr& m = TaskMgr::Single();
		m.TranslateSongData(orig_lng, key, trans_lng, trans_key, THISBACK(OnTranslatedRecv));
	}*/
}
/*
String TranslatorToolCtrl::GetOriginalText() const {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	if (key.GetCount()) {
		if (artist && p.entity) {
			return p.entity->data.GetAdd(key);
		}
		else if (release && p.release) {
			return p.release->data.GetAdd(key);
		}
		else if (song && p.component) {
			return p.component->data.GetAdd(key);
		}
	}
	return String();
}

String TranslatorToolCtrl::GetTranslatedText() const {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	if (trans_key.GetCount()) {
		if (artist && p.entity) {
			return p.entity->data.GetAdd(trans_key);
		}
		else if (release && p.release) {
			return p.release->data.GetAdd(trans_key);
		}
		else if (song && p.component) {
			return p.component->data.GetAdd(trans_key);
		}
	}
	return String();
}

void TranslatorToolCtrl::OnOriginalChange() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	String txt = orig.GetData();
	if (key.GetCount()) {
		if (artist && p.entity) {
			p.entity->data.GetAdd(key) = txt;
		}
		else if (release && p.release) {
			p.release->data.GetAdd(key) = txt;
		}
		else if (song && p.component) {
			p.component->data.GetAdd(key) = txt;
		}
	}
}

void TranslatorToolCtrl::OnTranslatedChange() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	String txt = trans.GetData();
	if (trans_key.GetCount()) {
		if (artist && p.entity) {
			p.entity->data.GetAdd(trans_key) = txt;
		}
		else if (release && p.release) {
			p.release->data.GetAdd(trans_key) = txt;
		}
		else if (song && p.component) {
			p.component->data.GetAdd(trans_key) = txt;
		}
	}
}*/

void TranslatorToolCtrl::OnTranslatedRecv() {
	#if 0
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	trans.SetData(GetTranslatedText());
	#endif
}







END_TEXTLIB_NAMESPACE

