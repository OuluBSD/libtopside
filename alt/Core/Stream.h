#ifndef _CoreAlt_Stream_h_
#define _CoreAlt_Stream_h_

#ifdef flagPOSIX
inline int fopen_s(FILE **f, const char *name, const char *mode) {
    int ret = 0;
    ASSERT(f);
    *f = fopen(name, mode);
    /* Can't be sure about 1-to-1 mapping of errno and MS' errno_t */
    if (!*f)
        ret = errno;
    return ret;
}
#endif

NAMESPACE_UPP_BEGIN

class Stream {
	bool err = false;
	
public:

	virtual String Get(int size) { return ""; }
	virtual bool IsOpen() const { return false; }

	virtual bool IsLoading() { return false; }
	virtual bool IsStoring() { return false; }
	virtual bool IsEof() { return false; }

	virtual int Put(const void* mem, int size) { return 0; }
	virtual int Put(char c) {return Put(&c, 1);}
	virtual int Put(const String& s) { return Put(s.Begin(), s.GetCount()); }
	virtual int Get(void* mem, int size) { return 0; }
	virtual int64 GetCursor() { return 0; }
	virtual void Seek(int64 pos) {}
	virtual int64 GetSize() const {return 0;}
	virtual int Peek() {if (IsEof()) return 0; byte b; Get(&b, 1); SeekCur(-1); return b;}
	
	virtual void SetSize(int64 len);
	void SetError(bool b=true) {err = b;}
	bool IsError() const {return err;}
	
	virtual void Flush() {};
	
	int Get();
	void PutEol();
	void PutLine(String s) {Put(s); PutEol();}
	void SeekCur(int64 pos) {Seek(GetCursor() + pos);}
	int64 GetLength() const {return GetSize();}
	int64 GetLeft() {return GetSize() - GetCursor();}
	
	String GetLine(int max = UINT16_MAX) {
		String out;
		while (!IsEof() && out.GetCount() < max) {
			char chr;
			if (!Get(&chr, 1))
				break;
			if (chr == '\n')
				break;
			out.Cat(chr);
		}
		return out;
	}
	
	template <class T>
	Stream& operator%(T& o) {o.Serialize(*this); return *this;}
	
	Stream& operator << (char c) {Put(&c, 1); return *this;}
	Stream& operator << (unsigned char i) {Put(&i, 1); return *this;}
	Stream& operator << (double d) {return *this << DblStr(d);}
	Stream& operator << (const char* c) {int len = (int)strnlen(c, 10000000); if (len > 0) Put(c, len); return *this;}
	Stream& operator << (unsigned long l) {return *this << IntStr64(l);}
	Stream& operator << (unsigned int l) {return *this << IntStr64(l);}
	#ifdef flagMSC
	Stream& operator << (size_t l) {return *this << IntStr64(l);}
	#endif
	virtual Stream& operator << (int i) {return *this << IntStr(i);}
	virtual Stream& operator << (String s) {if (s.GetCount()) Put(s.Begin(), s.GetCount()); return *this;}
	
	operator  bool() const { return IsOpen(); }
	
	int Put(char chr, int count) {
		if (count <= 4) {int wrote = 0; for(int i = 0; i < count; i++) wrote += Put(&chr, 1); return wrote;}
		else {String s; s.Cat(chr, count); return Put(s);}
	}
	int Get(Huge& huge, int size);
	
};

#define DEFAULT_SERIALIZER(type) template <> inline Stream& Stream::operator%(type& o) {\
	if (IsLoading()) Get(&o, sizeof(type)); \
	else Put(&o, sizeof(type)); \
	return *this; \
}

DEFAULT_SERIALIZER(bool)
DEFAULT_SERIALIZER(int8)
DEFAULT_SERIALIZER(uint8)
DEFAULT_SERIALIZER(int16)
DEFAULT_SERIALIZER(uint16)
DEFAULT_SERIALIZER(int32)
DEFAULT_SERIALIZER(uint32)
DEFAULT_SERIALIZER(int64)
DEFAULT_SERIALIZER(uint64)
DEFAULT_SERIALIZER(float)
DEFAULT_SERIALIZER(double)
#if CPU_32
DEFAULT_SERIALIZER(unsigned long)
#endif

class FileStream : public Stream {
	
protected:
	mutable FILE* s = NULL;
	int mode = -1;
	
public:
	enum {
		READ,
		CREATE,
		APPEND
	};
	
	FileStream() {}
	FileStream(FILE* s) : s(s) {}
	~FileStream() {Close();}
	
	bool IsOpen() const override { return s != NULL; }
	bool IsEof() override { if (!s) return true; return feof(s); }
	bool IsLoading() override { return mode == READ; }
	bool IsStoring() override { return mode == CREATE || mode == APPEND; }
	FILE* GetHandle() const {return s;}
	
	bool Open(String path, int mode) {
		Close();
		this->mode = mode;
		if (mode == READ) {
			if (s) fclose(s);
			fopen_s(&s, path.Begin(), "rb");
			return s != NULL;
		}
		else if (mode == CREATE || mode == APPEND) {
			const char* mode_str = mode == CREATE ? "w+b" : "a+b";
			if (s) fclose(s);
			#ifdef flagMSC
			s = _fsopen(path.Begin(), mode_str, _SH_DENYWR);
			#else
			s = fopen(path.Begin(), mode_str);
			#endif
			return s != NULL;
		}
		return false;
	}
	void Close() {
		if (s) { fflush(s); fclose(s); s = NULL; }
	}
	void Clear() {Close();}
	
	String Get(int size) override {
		if (!s || !size) return String();
		ASSERT(size > 0);
		int pos = ftell(s);
		Vector<char> v;
		v.SetCount(size, 0);
		char* it = v.Begin();
		int left = size;
		int total_read = 0;
		while (left > 0) {
			int read_size = (int)fread(it, 1, left, s);
			left -= read_size;
			it += read_size;
			total_read += read_size;
			if (!read_size)
				break;
		}
		String out;
		out.SetData(v.Begin(), total_read);
		return out;
	}
	
	String GetText(int size) {
		if (!s) return "";
		Vector<char> v;
		v.SetCount(size+1);
		v[size] = 0;
		size_t read_size = fread(v.Begin(), 1, size, s);
		return v.GetData();
	}

	int Get(void* mem, int size) override {
		if (!s) return 0;
		int64 ret = fread(mem, size, 1, s) * size;
		ASSERT(ret < INT_MAX);
		return (int)ret;
	}
	
	int Get() {byte b=0; Get(&b, 1); return b;}
	
	int64 GetCursor() override { if (!s) return 0; return ftell(s); }

	int64 GetSize() const override {
		if (!s) return 0;
		long pos = ftell(s);
		fseek(s, 0, SEEK_END);
		int size = ftell(s);
		fseek(s, pos, SEEK_SET);
		return size;
	}

	void Seek(int64 pos) override { fseek(s, (long)pos, SEEK_SET); }

	
	Stream& operator << (String str) override {
		Put(str.Begin(), str.GetCount());
		return *this;
	}
	Stream& operator << (int i) override {
		String str = IntStr(i);
		Put(str.Begin(), str.GetCount());
		return *this;
	}

	int Put(const void* mem, int size) override {
		if (!s) return 0;
		int64 ret = fwrite(mem, size, 1, s) * size;
		ASSERT(ret < INT_MAX);
		return (int)ret;
	}
	int Put(char c) override { return Put(&c, 1); }
	int Put(String s) { if (s.GetCount()) return Put(s.Begin(), s.GetCount()); return 0;}

	void Flush() override { if (s) fflush(s); }
	
};

class FileIn : public FileStream {

public:
	FileIn() {}
	FileIn(FILE* s) : FileStream(s) {}
	FileIn(String path) {Open(path);}
	
	bool Open(String path) {return FileStream::Open(path, READ);}
	
};

class FileOut : public FileStream {

public:
	FileOut() {}
	FileOut(FILE* s) : FileStream(s) {}
	FileOut(String path) {Open(path);}
	
	bool Open(String path) {return FileStream::Open(path, CREATE);}
	
};

class FileAppend : public FileStream {

public:
	FileAppend() {}
	FileAppend(FILE* s) : FileStream(s) {}
	FileAppend(String path) {Open(path);}
	
	bool Open(String path) {return FileStream::Open(path, APPEND);}
	
};

extern FileIn cin;
extern FileOut cout, cerr;

String LoadFile(String path);


class StringStream : public Stream {
	Vector<char> s;
	int64 cursor = 0;
	bool is_storing = true;
	
public:
	StringStream() {}
	StringStream(String s) {this->s.SetCount(s.GetCount()); memcpy(this->s.Begin(), s.Begin(), this->s.GetCount());}
	
	void Clear() {s.Clear(); cursor = 0; is_storing = true;}
	
	void Swap(StringStream& ss) {
		::UPP::Swap(ss.s, s);
		::UPP::Swap(ss.cursor, cursor);
		::UPP::Swap(ss.is_storing, is_storing);
	}
	bool IsLoading() override { return !is_storing; }
	bool IsStoring() override { return is_storing; }
	bool IsEof() override { return cursor >= s.GetCount(); }
	
	void SetStoring() {is_storing = true;}
	void SetLoading() {is_storing = false;}
	
	Stream& operator << (String str) override {
		Put(str.Begin(), str.GetCount());
		return *this;
	}
	Stream& operator << (int i) override {
		String str = IntStr(i);
		Put(str.Begin(), str.GetCount());
		return *this;
	}
	int Put(const void* mem, int size) override {
		int64 end = cursor + size;
		ASSERT(end < INT_MAX);
		if (end > s.GetCount())
			s.SetCount((int)end);
		char* dst = (char*)s.Begin() + cursor;
		const char* src = (const char*)mem;
		MemoryCopy(dst, src, size);
		cursor += size;
		return size;
	}
	int Put(char c) override { return Put(&c, 1); }
	int Put(const String& s) override { return Put(s.Begin(), s.GetCount()); }
	int Get(void* mem, int size) override {
		int64 sz = min((int64)size, (int64)s.GetCount() - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		char* b = (char*)mem;
		MemoryCopy(b, s.Begin() + cursor, (int)sz);
		cursor += sz;
		return (int)sz;
	}
	int64 GetCursor() override { return cursor; }
	int64 GetSize() const override {return s.GetCount();}
	
	StringStream& Cat(char c) {Put(c); return *this;}
	
	void Reserve(int i) {s.Reserve(i);}
	void Seek(int64 i) override { cursor = i; }
	String GetResult() const { String s; s.SetData(this->s.Begin(), this->s.GetCount()); return s;}
	
	operator String() const {return GetResult();}
	
};

class WStringStream : public Stream {
	Vector<wchar_t> s;
	int64 cursor = 0;
	bool is_storing = true;
	
public:
	WStringStream() {}
	WStringStream(WString s) {this->s.SetCount(s.GetCount()); memcpy(this->s.Begin(), s.Begin(), this->s.GetCount());}

	bool IsLoading() override { return !is_storing; }
	bool IsStoring() override { return is_storing; }
	bool IsEof() override { return cursor >= s.GetCount(); }
	
	void SetStoring() {is_storing = true;}
	void SetLoading() {is_storing = false;}
	
	Stream& Cat(wchar_t w) {
		s.Add(w);
		return *this;
	}
	Stream& operator << (String str) override {
		WString wstr = ToWString(str);
		Put(wstr.Begin(), wstr.GetCount());
		return *this;
	}
	Stream& operator << (int i) override {
		String str = IntStr(i);
		WString wstr = ToWString(str);
		Put(wstr.Begin(), wstr.GetCount());
		return *this;
	}
	int Put(const wchar_t* mem, int size) {
		int64 end = cursor + size;
		ASSERT(end < INT_MAX);
		if (end > s.GetCount())
			s.SetCount((int)end);
		wchar_t* dst = s.Begin() + cursor;
		MemoryCopy(dst, mem, size);
		cursor += size / sizeof(wchar_t);
		return size;
	}
	int Put(const void* mem, int size) override {
		int frame = size;
		int mod = frame % sizeof(wchar_t);
		if (mod) frame += sizeof(wchar_t) - mod;
		int64 end = cursor + frame;
		ASSERT(end < INT_MAX);
		if (end > s.GetCount())
			s.SetCount((int)end);
		wchar_t* dst = s.Begin() + cursor;
		const wchar_t* src = (const wchar_t*)mem;
		MemoryCopy(dst, src, size);
		cursor += frame / sizeof(wchar_t);
		return size;
	}
	int Put(char c) override { wchar_t w = c; return Put(&w, 1); }
	int Put(const String& str) override {
		WString wstr = ToWString(str);
		return Put(wstr.Begin(), wstr.GetCount());
	}
	int Get(void* mem, int size) override {
		int frame = size;
		int mod = frame % sizeof(wchar_t);
		if (mod) frame += sizeof(wchar_t) - mod;
		int64 sz = min((int64)size, (int64)s.GetCount() - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		char* b = (char*)mem;
		MemoryCopy(b, s.Begin() + cursor, (int)sz);
		cursor += frame;
		return (int)sz;
	}
	int Get(wchar_t* mem, int size) {
		int64 sz = min((int64)size, (int64)s.GetCount() - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		char* b = (char*)mem;
		MemoryCopy(b, s.Begin() + cursor, (int)sz);
		cursor += sz;
		return (int)sz;
	}
	int64 GetCursor() override { return cursor; }
	int64 GetSize() const override {return s.GetCount();}

	void Seek(int64 i) override { cursor = i; }
	WString GetResult() const { WString s; s.SetData(this->s.Begin(), this->s.GetCount()); return s;}
	
	operator WString() const {return GetResult();}
	
};

class MemReadStream : public Stream {
	const byte* buf;
	int64 size = 0;
	int64 cursor = 0;
	
public:
	MemReadStream(const void* buf, int64 size) : buf((const byte*)buf), size(size) {}

	bool IsLoading() override { return true; }
	bool IsStoring() override { return false; }
	bool IsEof() override { return cursor >= size; }
	
	int Get(void* mem, int size) override {
		int64 sz = min((int64)size, this->size - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		byte* b = (byte*)mem;
		MemoryCopy(b, buf + cursor, (int)sz);
		cursor += sz;
		return (int)sz;
	}
	int64 GetCursor() override { return cursor; }
	void Seek(int64 i) override { cursor = i; }
	int64 GetSize() const override {return size;}
};

class MultiStream : public Stream {
	Vector<Stream*> streams;
	int64 cursor = 0;
	
public:
	MultiStream() {}
	
	void Add(Stream& s) {streams.Add(&s);}
	void Clear() {streams.Clear();}
	
	#define MULTI_BOOL(fn) \
		bool b = streams.GetCount(); \
		for (Stream* s : streams) b = b && s->fn(); \
		return b;
	
	bool IsLoading() override {MULTI_BOOL(IsLoading)}
	bool IsStoring() override {MULTI_BOOL(IsStoring)}
	bool IsEof() override {MULTI_BOOL(IsEof)}
	
	Stream& operator << (String str) override {Put(str.Begin(), str.GetCount()); return *this;}
	Stream& operator << (int i) override {String str = IntStr(i); Put(str.Begin(), str.GetCount()); return *this;}
	int Put(const void* mem, int size) override {
		int wrote = size;
		for (Stream* s : streams)
			wrote = min(wrote, s->Put(mem, size));
		cursor += wrote;
		return wrote;
	}
	int Put(char c) override { return Put(&c, 1); }
	int Put(const String& s) override { return Put(s.Begin(), s.GetCount()); }
	int Get(void* mem, int size) override {
		int read = size;
		for (Stream* s : streams)
			read = min(read, s->Put(mem, size));
		return read;
	}
	int64 GetCursor() override { return cursor; }
	int64 GetSize() const override {return cursor;}
	void Flush() override {for (Stream* s : streams) s->Flush();};

	void Seek(int64 i) override {}
	String GetResult() const {return String();}
	
	operator String() const {return GetResult();}
	
};



template <class T>
void StringT<T>::Serialize(Stream& str) {
	uint32 len = 0;
	if (str.IsLoading()) {
		Clear();
		str.Get(&len, sizeof(len));
		count = len;
		if (count < buf_size) {
			str.Get(buf, len*sizeof(T));
			buf[count] = 0;
		}
		else {
			T* buf = (T*)malloc(sizeof(T) * (count + 1));
			str.Get(buf, len*sizeof(T));
			buf[count] = 0;
			BIG = new String0T(buf, count + 1);
			is_big = true;
		}
	}
	else {
		len = GetCount();
		str.Put(&len, sizeof(len));
		str.Put(Begin(), len*sizeof(T));
	}
}

template <class T>
void Vector<T>::Serialize(Stream& str) {
	uint32 len = 0;
	if (str.IsLoading()) {
		str.Get(&len, sizeof(len));
		SetCount(len);
	}
	else {
		len = GetCount();
		str.Put(&len, sizeof(len));
	}
	for(T& o : *this)
		str % o;
}

template <class T>
void Array<T>::Serialize(Stream& s) {
	T** data = l.GetData();
	if (s.IsLoading()) {
		int count = 0;
		s % count;
		SetCount(count);
		for(T **it = data, **end = data + count; it != end; ++it)
			s % **it;
	}
	else if (s.IsStoring()) {
		int count = GetCount();
		s % count;
		for(T **it = data, **end = data + count; it != end; ++it)
			s % **it;
	}
}

template <class T>
void LoadFromFile(T& o, String path) {
	FileIn fin(path);
	if (!fin.IsOpen()) return;
	fin % o;
}

template <class T>
void StoreToFile(T& o, String path) {
	FileOut fout(path);
	if (!fout.IsOpen()) return;
	fout % o;
}




enum {
	LOG_COUT = (1 << 0),
	LOG_FILE = (1 << 1),
};

void StdLogSetup(dword flags);




class XmlIO : public Stream {
	
};

class JsonIO : public Stream {
	
	
public:
	
	
	template <class T> JsonIO& operator()(String key, T& o) {TODO_}
	
};


MultiStream& LogMulti();
Stream& VppLog();
Stream& LogFile();
Stream& Cout();
Stream& Cerr();
Stream& Cin();

inline String ReadStdIn() {return Cin().GetLine();}


NAMESPACE_UPP_END

#endif
