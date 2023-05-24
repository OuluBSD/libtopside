#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

void Ether::Put(const String& s) {
	dword len = s.GetCount() + 1;
	Put(&len, sizeof(len));
	Put(s.Begin(), len);
}

String Ether::GetString() {
	dword len;
	Get(&len, sizeof(len));
	thread_local static Vector<char> buf;
	buf.SetCount(len);
	Get(buf.Begin(), len);
	return String(buf.Begin());
}




WriteEther::WriteEther() {
	SetStoring();
}

void WriteEther::_Put(const void *data, dword size) {
	ss.Put(data, size);
}

dword WriteEther::_Get(void *data, dword size) {
	return ss.Get(data, size);
}

void WriteEther::Seek(int64 pos) {
	ss.Seek(pos);
}

int64 WriteEther::GetSize() const {
	return ss.GetSize();
}

void WriteEther::SetSize(int64 size) {
	ss.SetSize(size);
}




void ReadEther::_Put(const void *data, dword size) {
	ss.Put(data, size);
}

dword ReadEther::_Get(void *data, dword size) {
	return ss.Get(data, size);
}

void ReadEther::Seek(int64 pos) {
	ss.Seek(0);
}

int64 ReadEther::GetSize() const {
	return ss.GetSize();
}

void ReadEther::SetSize(int64 size) {
	ss.SetSize(size);
}




NAMESPACE_TOPSIDE_END
