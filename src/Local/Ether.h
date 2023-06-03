#ifndef _Local_Ether_h_
#define _Local_Ether_h_

NAMESPACE_TOPSIDE_BEGIN


#define ETH_KEYOBJ(var) e.PutAsKeyObject(#var, var);
#define ETH_KEYOBJCONT(var) e.PutAsKeyObjectContainer(#var, var);
#define ETH_KEYREF(var) this->PutAsKeyRef(e, #var, var);
#define ETH_KEYREFCONT(var) this->PutAsKeyRefContainer(e, #var, var);

class Ether;
template <class T> void EtherizeContainer(Ether& e, T& o);
template <class T> void EtherizeMapContainer(Ether& e, T& o);
template <class T> void Etherize(Ether& e, T& o) {o.Etherize(e);}
template <class T> void Etherize(Ether& e, Vector<T>& o) {EtherizeContainer(e, o);}
template <class T> void Etherize(Ether& e, Array<T>& o) {EtherizeContainer(e, o);}
template <class T> void Etherize(Ether& e, LinkedList<T>& o) {EtherizeContainer(e, o);}
template <class K, class V> void Etherize(Ether& e, VectorMap<K,V>& o) {EtherizeMapContainer(e, o);}
template <class K, class V> void Etherize(Ether& e, ArrayMap<K,V>& o)  {EtherizeMapContainer(e, o);}
template <class K, class V> void Etherize(Ether& e, LinkedMap<K,V>& o) {EtherizeMapContainer(e, o);}


class Ether {
	
protected:
	bool err = false;
	bool storing = false;
	bool eof = false;
	size_t cursor = 0;
	
protected:
	virtual   void  _Put(const void *data, dword size) {}
	virtual   dword _Get(void *data, dword size) { return 0; }
	
public:
	virtual   void  Seek(int64 pos) {}
	virtual   int64 GetSize() const {return 0;}
	virtual   void  SetSize(int64 size) {}
	
public:
	
	bool IsLoading() const { return !storing; }
	bool IsStoring() const { return storing; }
	bool IsEof() const { return eof; }
	bool IsError() const {return err; }
	int64 GetCursor() { return cursor; }
	int64 GetLeft() {return GetSize() - GetCursor();}
	
	void SetStoring() {storing = true;}
	void SetLoading() {storing = false;}
	void SetError(bool b=true) {err = b;}
	void SeekCur(int64 pos) {Seek(GetCursor() + pos);}
	
	void Put(const String& s);
	void Put(const void* mem, dword size) { _Put(mem, size); }
	dword Get(void* mem, dword size) { return _Get(mem, size); }
	String GetString();
	
	template <class T> Ether& operator%(T& o);
	
	template <class T> void PutType(bool ref) {
		dword obj_type = (ref ? 0x80000000 : 0) | ObjectTypeNo<T>(0);
		PutT(obj_type);
	}
	inline void PutKey(const char* key) {
		byte key_len = (byte)strnlen(key, 255);
		PutT(key_len);
		Put(key, key_len);
	}
	template <class T> void PutKeyType(const char* key, bool ref) {
		PutType<T>(ref);
		PutKey(key);
	}
	template <class T> void PutAsObject(T& o, bool ref) {
		PutType<T>(ref);
		Etherize(*this, o);
	}
	
	
	template <class T> void PutAsKeyObject(const char* key, T& o) {
		PutKeyType<T>(key, false);
		Etherize(*this, o);
		byte chk = 0xFF; PutT(chk);
	}
	
	template <class T> void PutAsKeyObjectContainer(const char* key, Vector<T>& v) {
		PutKeyType<T>(key, false);
		dword c = v.GetCount();
		PutT(c);
		for (T& o : v)
			Etherize(*this, o);
		byte chk = 0xFF; PutT(chk);
	}
	
	
	template <class T> void GetT(T& o) {Get(&o, sizeof(o));}
	template <class T> void PutT(T& o) {Put(&o, sizeof(o));}
	
};

#define DEFAULT_ETHERIZER(type) template <> inline void Etherize(Ether& e, type& o) {\
	if (e.IsLoading()) e.Get(&o, sizeof(type)); \
	else e.Put(&o, sizeof(type)); \
}

DEFAULT_ETHERIZER(bool)
DEFAULT_ETHERIZER(char)
DEFAULT_ETHERIZER(unsigned char)
DEFAULT_ETHERIZER(short)
DEFAULT_ETHERIZER(unsigned short)
DEFAULT_ETHERIZER(int)
DEFAULT_ETHERIZER(unsigned int)
DEFAULT_ETHERIZER(int64)
DEFAULT_ETHERIZER(uint64)
DEFAULT_ETHERIZER(float)
DEFAULT_ETHERIZER(double)
#if CPU_32 || (defined WIN32 && defined flagCLANG)
DEFAULT_ETHERIZER(unsigned long)
#endif
DEFAULT_ETHERIZER(Date)
DEFAULT_ETHERIZER(Time)
DEFAULT_ETHERIZER(Point)
DEFAULT_ETHERIZER(Size)
DEFAULT_ETHERIZER(Rect)
DEFAULT_ETHERIZER(RGBA)
DEFAULT_ETHERIZER(Color)
DEFAULT_ETHERIZER(ByteArray256)
#if IS_UPP_CORE && defined flagMSC
DEFAULT_ETHERIZER(dword)
#endif
#if IS_UPP_CORE
DEFAULT_ETHERIZER(signed char)
DEFAULT_ETHERIZER(long)
#endif

template <> inline void Etherize(Ether& e, Image& i) {
	TODO
}

template <> inline void Etherize(Ether& e, Exc& s) {
	if (e.IsLoading()) s = e.GetString();
	else e.Put(s);
}

template <> inline void Etherize(Ether& e, String& s) {
	if (e.IsLoading()) s = e.GetString();
	else e.Put(s);
}

template <> inline void Etherize(Ether& e, WString& s) {
	if (e.IsLoading()) s = e.GetString().ToWString();
	else e.Put(s.ToString());
}

template <class T> Ether& Ether::operator%(T& o) {Etherize(*this, o); return *this;}
	

template <class T> void EtherizeContainer(Ether& e, T& v) {
	if (e.IsLoading()) {
		v.Clear();
		dword c = 0;
		e.GetT(c);
		v.SetCount(c);
		for (auto& o : v)
			Etherize(e, o);
	}
	else {
		dword c = v.GetCount();
		e.PutT(c);
		for (auto& o : v)
			Etherize(e, o);
	}
}

template <class T> void EtherizeMapContainer(Ether& e, T& v) {
	using K = typename T::KeyType;
	if (e.IsLoading()) {
		v.Clear();
		dword c;
		e.Get(&c, sizeof(c));
		K k;
		for(int i = 0; i < c; i++) {
			Etherize(e, k);
			v.Add(k);
		}
		for (auto& o : v.GetValues())
			Etherize(e, o);
	}
	else {
		dword c = v.GetCount();
		e.Put(&c, sizeof(c));
		for (auto& k : v.GetKeys())
			Etherize(e, const_cast<K&>(k));
		for (auto& o : v.GetValues())
			Etherize(e, o);
	}
}


class WriteEther : public Ether {
	StringStream ss;
	
protected:
	void  _Put(const void *data, dword size) override;
	dword _Get(void *data, dword size) override;
	
public:
	void  Seek(int64 pos) override;
	int64 GetSize() const override;
	void  SetSize(int64 size) override;
	
public:
	WriteEther();
	
	String GetResult() {return ss.GetResult();}
	
};

class ReadEther : public Ether {
	MemReadStream ss;
	
protected:
	void  _Put(const void *data, dword size) override;
	dword _Get(void *data, dword size) override;
	
public:
	void  Seek(int64 pos) override;
	int64 GetSize() const override;
	void  SetSize(int64 size) override;
	
public:
	ReadEther(const void* data, int len) : ss(data, len) {}
	
};


NAMESPACE_TOPSIDE_END

#endif
