#include "Adventure.h"

namespace Adventure {


Sentence& Dialog::Add() {
	Sentence& s = sentences.Add();
	s.num = sentences.GetCount() - 1;
	return s;
}

void Dialog::Clear() {
	sentences.Clear();
	col = 0;
	hlcol = 0;
	visible = 0;
}

void Program::DialogSet(StrVec& msg_table) {
	for (const String& msg : msg_table) {
		DialogAdd(msg);
	}
}

void Program::DialogAdd(const String& msg) {
	Sentence& s = dialog_curr.Add();
	s.msg = msg;
	
	// break msg into lines (if (necc.)
	CreateTextLines(msg, 32, s.lines);
	
	// find longest line
	s.char_width = GetLongestLineSize(s.lines);
	
}

void Program::DialogStart(int col, int hlcol) {
	dialog_curr.col = col;
	dialog_curr.hlcol = hlcol;
	dialog_curr.visible = true;
	selected_sentence = NULL;
}

void Program::DialogHide() {
	dialog_curr.visible = false;
}

void Program::DialogClear() {
	dialog_curr.sentences = {};
	selected_sentence = NULL;
}

void Program::DialogEnd() {
	dialog_curr.Clear();
}


}
