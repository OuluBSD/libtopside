#if 0

#include "Meta.h"

NAMESPACE_TOPSIDE_BEGIN

String EscapeString(String s) {
	s.Replace("\\", "\\\\");
	s.Replace("\n", "\\n");
	s.Replace("\t", "\\t");
	s.Replace("\r", "\\r");
	s.Replace("\"", "\\\"");
	
	return s;
}

String EscapeSpecial(String s) {
	s.Replace("\n", "\\n");
	s.Replace("\t", "\\t");
	s.Replace("\r", "\\r");
	
	return s;
}

void ErrorSource::Info(String msg, int file, int line, int col) {
	Message m;
	m.source = src;
	m.file = file;
	m.line = line;
	m.col = col;
	m.severity = LVL_INFO;
	m.what = msg;
	WhenMessage(&m);
}

void ErrorSource::Warning(String msg, int file, int line, int col) {
	Message m;
	m.source = src;
	m.file = file;
	m.line = line;
	m.col = col;
	m.severity = LVL_WARNING;
	m.what = msg;
	WhenMessage(&m);
}

void ErrorSource::Error(String msg, int file, int line, int col) {
	succ = false;
	Message m;
	m.source = src;
	m.file = file;
	m.line = line;
	m.col = col;
	m.severity = LVL_ERROR;
	m.what = msg;
	WhenMessage(&m);
}

NAMESPACE_TOPSIDE_END

#endif
