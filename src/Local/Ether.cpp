#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

void Object::Etherize(Ether& e) {
	if (e.IsLoading()) {
		obj.Clear();
		dword type = 0;
		e.GetT(type);
		if (type != VOID_O) {
			bool b = CreateType(type);
			ASSERT_(b && obj, "Could not create type " + HexStr(type));
			if (obj) obj->Etherize(e);
			else e.SetError();
		}
	}
	else {
		dword type = obj ? obj->GetType() : VOID_O;
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
	dword len = s.GetCount();
	Put(&len, sizeof(len));
	Put(s.Begin(), len);
}

String Ether::GetString() {
	dword len = 0;
	Get(&len, sizeof(len));
	thread_local static Vector<char> buf;
	buf.SetCount(len);
	Get(buf.Begin(), len);
	return String(buf.Begin(), len);
}




WriteEther::WriteEther() {
	SetStoring();
}

void WriteEther::_Put(const void *data, dword size) {
	/*if (this->cursor >= 146) {
		LOG("");
	}*/
	ss.Put(data, size);
	cursor = ss.GetPos();
}

dword WriteEther::_Get(void *data, dword size) {
	dword ret = ss.Get(data, size);
	cursor = ss.GetPos();
	return ret;
}

dword WriteEther::_Peek() {
	return 0;
}

void WriteEther::Seek(int64 pos) {
	ss.Seek(pos);
	cursor = ss.GetPos();
}

int64 WriteEther::GetSize() const {
	return ss.GetSize();
}

void WriteEther::SetSize(int64 size) {
	ss.SetSize(size);
	cursor = ss.GetPos();
}




void ReadEther::_Put(const void *data, dword size) {
	ss.Put(data, size);
	cursor = ss.GetPos();
}

dword ReadEther::_Get(void *data, dword size) {
	dword ret = ss.Get(data, size);
	eof = ss.IsEof();
	cursor = ss.GetPos();
	return ret;
}

dword ReadEther::_Peek() {
	if (ss.IsEof())
		return 0;
	int64 pos = ss.GetPos();
	dword d = 0;
	ss.Get(&d, sizeof(d));
	ss.Seek(pos);
	return d;
}

bool ReadEther::IsEof() const {
	ReadEther* e = const_cast<ReadEther*>(this);
	e->eof = e->ss.IsEof();
	return eof;
}

void ReadEther::Seek(int64 pos) {
	ss.Seek(0);
	eof = ss.IsEof();
	cursor = ss.GetPos();
}

int64 ReadEther::GetSize() const {
	return ss.GetSize();
}

void ReadEther::SetSize(int64 size) {
	ss.SetSize(size);
}

bool ReadEther::TypeKey(dword chk_type, bool ref, const char* chk_key) {
	// Fastest peek (1 byte)
	int first_byte = ss.Peek();
	if (!first_byte)
		return false;
	
	// Slower peek (4 bytes)
	int64 begin = GetCursor();
	dword obj_type = 0;
	ss.Get(&obj_type, sizeof(obj_type));
	ASSERT(chk_type != 0);
	
	if (ref)
		chk_type |= 0x80000000;
	
	if (obj_type == chk_type && chk_type != 0) {
		// Peek key
		byte len = 0;
		ss.Get(&len, sizeof(len));
		char key_chars[256];
		ss.Get(key_chars, len);
		byte chk_key_len = strnlen(chk_key, 256);
		if (len == chk_key_len && strncmp(key_chars, chk_key, len) == 0) {
			// If the key matches, don't revert peek and cursor change
			return true;
		}
	}
	ss.Seek(begin);
	return false;
}



NAMESPACE_TOPSIDE_END
