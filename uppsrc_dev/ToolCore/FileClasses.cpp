#include "ToolCore.h"


BEGIN_TEXTLIB_NAMESPACE


void IntVectorFile::Load(const String& path) {
	idx.Clear();
	this->path = path;
	String content = LoadFile(path);
	content.Replace("\r","");
	if (!content.IsEmpty()) {
		Vector<String> lines = Split(content, "\n", false);
		for (String& l : lines)
			idx.Add(ScanInt(l));
	}
}

void IntVectorFile::Store() {
	String content;
	for (int i : idx) {
		if (!content.IsEmpty()) content << "\n";
		content << IntStr(i);
	}
	String old_content = LoadFile(path);
	if (content.GetHashValue() != old_content.GetHashValue()) {
		//LOG(path);
		FileOut fout(path);
		fout << content;
		fout.Close();
	}
}



void IntIndexFile::Load(const String& path) {
	idx.Clear();
	this->path = path;
	String content = LoadFile(path);
	content.Replace("\r","");
	if (!content.IsEmpty()) {
		Vector<String> lines = Split(content, "\n", false);
		for (String& l : lines)
			idx.Add(ScanInt(l));
	}
}

void IntIndexFile::Store() {
	String content;
	for (int i : idx.GetKeys()) {
		if (!content.IsEmpty()) content << "\n";
		content << IntStr(i);
	}
	String old_content = LoadFile(path);
	if (content.GetHashValue() != old_content.GetHashValue()) {
		//LOG(path);
		FileOut fout(path);
		fout << content;
		fout.Close();
	}
}



void IndexFile::Load(const String& path) {
	idx.Clear();
	this->path = path;
	String content = LoadFile(path);
	content.Replace("\r","");
	if (!content.IsEmpty()) {
		Vector<String> lines = Split(content, "\n", false);
		for (String& l : lines)
			idx.Add(l);
	}
}

void IndexFile::Store() {
	String content = Join(idx.GetKeys(), "\n", false);
	String old_content = LoadFile(path);
	if (content.GetHashValue() != old_content.GetHashValue()) {
		FileOut fout(path);
		fout << content;
		fout.Close();
	}
}


END_TEXTLIB_NAMESPACE

