#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

void Object::Etherize(Ether& e) {
	if (e.IsLoading()) {
		obj.Clear();
		dword type = 0;
		e.GetT(type);
		if (type != VOID_V) {
			bool b = CreateType(type);
			ASSERT_(b && obj, "Could not create type " + HexStr(type));
			if (obj) obj->Etherize(e);
			else e.SetError();
		}
	}
	else {
		dword type = obj ? obj->GetType() : VOID_V;
		e.PutT(type);
		if (obj) obj->Etherize(e);
	}
}

void ObjectArray::Etherize(Ether& e) {
	if (e.IsLoading()) {
		Clear();
		dword count = 0;
		e.GetT(count);
		SetCount(count);
		for (Object& o : values) {
			e % o;
		}
	}
	else {
		dword count = values.GetCount();
		e.PutT(count);
		for (Object& o : values) {
			e % o;
		}
	}
}

void ObjectMap::Etherize(Ether& e) {
	if (e.IsLoading()) {
		Clear();
		dword count = 0;
		e.GetT(count);
		keys.SetCount(count);
		values.SetCount(count);
		for (String& s : keys) {
			e % s;
		}
		for (Object& o : values) {
			e % o;
		}
	}
	else {
		dword count = values.GetCount();
		e.PutT(count);
		for (String& s : keys) {
			e % s;
		}
		for (Object& o : values) {
			e % o;
		}
	}
}


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
