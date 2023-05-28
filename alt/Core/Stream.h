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
	
protected:
	bool err = false;
	bool storing = false;
	bool eof = false;
	size_t cursor = 0;
	
protected:
	virtual   void  _Put(int w) {char c = w; Put(&c, 1);}
	virtual   int   _Term() {return 0;} //if (IsEof()) return 0; byte b; Get(&b, 1); SeekCur(-1); return b;}
	virtual   int   _Get() { char c; _Get(&c, 1); return c; }
	virtual   void  _Put(const void *data, dword size) {}
	virtual   dword _Get(void *data, dword size) { return 0; }
	
public:
	virtual   void  Seek(int64 pos) {}
	virtual   int64 GetSize() const {return 0;}
	virtual   void  SetSize(int64 size);
	virtual   void  Flush() {}
	virtual   void  Close() {}
	virtual   bool  IsOpen() const = 0;
	
public:

	String Get(int size);

	bool IsLoading() const { return !storing; }
	bool IsStoring() const { return storing; }
	bool IsEof() const { return eof; }

	void Put(const void* mem, dword size) { _Put(mem, size); }
	void Put(int c) {_Put(c);}
	void Put(const String& s) { _Put(s.Begin(), s.GetCount()); }
	dword Get(void* mem, dword size) { return _Get(mem, size); }
	
	int64 GetCursor() { return cursor; }
	int Peek() {return _Term();}
	
	void SetError(bool b=true) {err = b;}
	bool IsError() const {return err;}
	
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
	
	void Put(char chr, int count) {
		String s; s.Cat(chr, count); Put(s);
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
	FILE* GetHandle() const {return s;}
	
	bool Open(String path, int mode) {
		Close();
		this->mode = mode;
		storing = mode == CREATE || mode == APPEND;
		cursor = 0;
		if (mode == READ) {
			if (s) fclose(s);
			fopen_s(&s, path.Begin(), "rb");
			eof = s ? feof(s) : true;
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
			eof = s ? feof(s) : true;
			if (mode == APPEND)
				Seek(GetSize());
			return s != NULL;
		}
		return false;
	}
	void Close() override {
		if (s) { fflush(s); fclose(s); s = NULL; eof = true;}
	}
	void Clear() {Close();}
	
	/*String Get(int size) override {
		if (!s || !size) return String();
		ASSERT(size > 0);
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
		eof = feof(s);
		return out;
	}*/
	
	/*String GetText(int size) {
		if (!s) return "";
		Vector<char> v;
		v.SetCount(size+1);
		v[size] = 0;
		fread(v.Begin(), 1, size, s);
		return v.GetData();
	}*/

	dword _Get(void* mem, dword size) override {
		if (!s) return 0;
		int64 ret = fread(mem, size, 1, s) * size;
		ASSERT(ret < INT_MAX);
		eof = feof(s);
		cursor = ftell(s);
		return (int)ret;
	}
	
	//int Get() {byte b=0; Get(&b, 1); return b;}
	
	//int64 GetCursor() override { if (!s) return 0; return ftell(s); }

	int64 GetSize() const override {
		if (!s) return 0;
		long pos = ftell(s);
		fseek(s, 0, SEEK_END);
		int size = ftell(s);
		fseek(s, pos, SEEK_SET);
		return size;
	}

	void Seek(int64 pos) override { fseek(s, (long)pos, SEEK_SET); cursor = pos; }

	int _Term() override {
		if (feof(s))
			return 0;
		long cur = ftell(s);
		byte b;
		fread(&b, 1, 1, s);
		fseek(s, cur, SEEK_SET);
		return b;
	}
	/*Stream& operator << (String str) {
		Put(str.Begin(), str.GetCount());
		return *this;
	}
	Stream& operator << (int i) {
		String str = IntStr(i);
		Put(str.Begin(), str.GetCount());
		return *this;
	}*/

	void _Put(const void* mem, dword size) override {
		if (!s) return;
		int64 ret = fwrite(mem, size, 1, s) * size;
		ASSERT(ret < INT_MAX);
		cursor += size;
	}
	//int Put(char c) override { return Put(&c, 1); }
	//int Put(String s) { if (s.GetCount()) return Put(s.Begin(), s.GetCount()); return 0;}

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
	
public:
	StringStream() {storing = true;}
	StringStream(String s) {this->s.SetCount(s.GetCount()); memcpy(this->s.Begin(), s.Begin(), this->s.GetCount());}
	
	void Clear() {s.Clear(); cursor = 0; storing = true;}
	
	bool IsOpen() const override {return true;}
	
	void Swap(StringStream& ss) {
		::UPP::Swap(ss.s, s);
		::UPP::Swap(ss.cursor, cursor);
		::UPP::Swap(ss.storing, storing);
	}
	
	void SetStoring() {storing = true;}
	void SetLoading() {storing = false;}
	
	/*Stream& operator << (String str) override {
		Put(str.Begin(), str.GetCount());
		return *this;
	}
	Stream& operator << (int i) override {
		String str = IntStr(i);
		Put(str.Begin(), str.GetCount());
		return *this;
	}*/
	void _Put(const void* mem, dword size) override {
		int64 end = cursor + size;
		ASSERT(end < INT_MAX);
		if (end > s.GetCount())
			s.SetCount((int)end);
		char* dst = (char*)s.Begin() + cursor;
		const char* src = (const char*)mem;
		MemoryCopy(dst, src, size);
		cursor += size;
		eof = cursor >= s.GetCount();
	}
	
	dword _Get(void* mem, dword size) override {
		int64 sz = min((int64)size, (int64)s.GetCount() - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		char* b = (char*)mem;
		MemoryCopy(b, s.Begin() + cursor, (int)sz);
		cursor += sz;
		eof = cursor >= s.GetCount();
		return (int)sz;
	}
	
	int64 GetSize() const override {return s.GetCount();}
	
	StringStream& Cat(char c) {Put(c); return *this;}
	
	void Reserve(int i) {s.Reserve(i);}
	void Seek(int64 i) override { cursor = i; eof = cursor >= s.GetCount();}
	String GetResult() const { String s; s.SetData(this->s.Begin(), this->s.GetCount()); return s;}
	
	operator String() const {return GetResult();}
	
};

#if 0
class WStringStream : public Stream {
	Vector<wchar_t> s;
	int64 cursor = 0;
	
public:
	WStringStream() {storing = true;}
	WStringStream(WString s) {storing = true; this->s.SetCount(s.GetCount()); memcpy(this->s.Begin(), s.Begin(), this->s.GetCount());}

	Stream& Cat(wchar_t w) {
		s.Add(w);
		return *this;
	}
	Stream& operator << (String str) {
		WString wstr = ToWString(str);
		Put(wstr.Begin(), wstr.GetCount());
		return *this;
	}
	Stream& operator << (int i) {
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
		eof = cursor >= s.GetCount();
		return size;
	}
	
	int _Put(const void* mem, int size) override {
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
		eof = cursor >= s.GetCount();
		return size;
	}
	
	int _Put(char c) override { wchar_t w = c; return Put(&w, 1); }
	
	int Put(const String& str) {
		WString wstr = ToWString(str);
		return Put(wstr.Begin(), wstr.GetCount());
	}
	int Get(void* mem, int size) {
		int frame = size;
		int mod = frame % sizeof(wchar_t);
		if (mod) frame += sizeof(wchar_t) - mod;
		int64 sz = min((int64)size, (int64)s.GetCount() - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		char* b = (char*)mem;
		MemoryCopy(b, s.Begin() + cursor, (int)sz);
		cursor += frame;
		eof = cursor >= s.GetCount();
		return (int)sz;
	}
	int Get(wchar_t* mem, int size) {
		int64 sz = min((int64)size, (int64)s.GetCount() - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		char* b = (char*)mem;
		MemoryCopy(b, s.Begin() + cursor, (int)sz);
		cursor += sz;
		eof = cursor >= s.GetCount();
		return (int)sz;
	}
	int64 GetCursor() override { return cursor; }
	int64 GetSize() const override {return s.GetCount();}

	void Seek(int64 i) override { cursor = i; }
	WString GetResult() const { WString s; s.SetData(this->s.Begin(), this->s.GetCount()); return s;}
	
	operator WString() const {return GetResult();}
	
};
#endif

class MemReadStream : public Stream {
	const byte* buf;
	int64 size = 0;
	int64 cursor = 0;
	
public:
	MemReadStream(const void* buf, int64 size) : buf((const byte*)buf), size(size) {}
	
	dword _Get(void* mem, dword size) override {
		int64 sz = min((int64)size, this->size - cursor);
		if (sz <= 0) return 0;
		ASSERT(sz < INT_MAX);
		byte* b = (byte*)mem;
		MemoryCopy(b, buf + cursor, (int)sz);
		cursor += sz;
		eof = cursor >= size;
		return (dword)sz;
	}
	void Seek(int64 i) override { cursor = i; }
	int64 GetSize() const override {return size;}
	bool IsOpen() const override {return true;}
	
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
	
	Stream& operator << (String str) override {Put(str.Begin(), str.GetCount()); return *this;}
	Stream& operator << (int i) override {String str = IntStr(i); Put(str.Begin(), str.GetCount()); return *this;}
	void _Put(const void* mem, dword size) override {
		for (Stream* s : streams)
			s->Put(mem, size);
		cursor += size;
	}
	dword _Get(void* mem, dword size) override {
		dword read = size;
		for (Stream* s : streams)
			read = min(read, s->Get(mem, size));
		return read;
	}
	int64 GetSize() const override {return cursor;}
	void Flush() override {for (Stream* s : streams) s->Flush();};

	void Seek(int64 i) override {}
	String GetResult() const {return String();}
	
	operator String() const {return GetResult();}
	
	bool IsOpen() const override {MULTI_BOOL(IsOpen)}
	
	
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
