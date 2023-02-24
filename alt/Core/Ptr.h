#ifndef _CoreAlt_Ptr_h_
#define _CoreAlt_Ptr_h_

NAMESPACE_UPP_BEGIN


template<class T> void PteAttach(T* o, void* ptr);
template<class T> void PteRelease(T* o, void* ptr);

template <class T>
class Ptr : Moveable<Ptr<T>> {
	T* o = 0;
	
public:
	Ptr() {}
	Ptr(T* o) {Set(o);}
	~Ptr() {Clear();}
	
	void Clear() {if (o) {PteRelease(o, this); o = 0;}}
	void ForcedRelease() {o = 0;}
	void Set(T* o) {if (this->o == o) return; Clear(); this->o = o; PteAttach(o, this);}
	
	Ptr& operator=(T* o) {Set(o); return *this;}
	
	operator T*() const {return o;}
	T* operator->() {return o;}
	T* operator~() {return o;}
	const T* operator->() const {return o;}
	
};

template <class T>
class Pte {
	Vector<Ptr<T>*> ptrs;
	
	
	void Clear() {
		for(auto& o : ptrs)
			o->ForcedRelease();
		ptrs.Clear();
	}
public:
	Pte() {}
	~Pte() {Clear();}
	
	void Attach(Ptr<T>* o) {ptrs.Add(o);}
	void Release(Ptr<T>* o) {
		for(int i = 0; i < ptrs.GetCount(); i++)
			if (ptrs[i] == o)
				ptrs.Remove(i--);
	}
	
};

template<class T> inline void PteAttach(T* o, void* ptr) {static_cast<Pte<T>&>(*o).Attach((Ptr<T>*)ptr);}
template<class T> inline void PteRelease(T* o, void* ptr) {static_cast<Pte<T>&>(*o).Release((Ptr<T>*)ptr);}


#if 0

template <class T> class Ptr;

class PteBase {
protected:
	struct Prec {
		PteBase *ptr;
		Atomic   n;
	};

	volatile Prec  *prec;

	Prec           *PtrAdd();
	static void     PtrRelease(Prec *prec);
	static Prec    *PtrAdd(const Uuid& uuid);

	PteBase();
	~PteBase();

	friend class PtrBase;
};

class PtrBase {
protected:
	PteBase::Prec *prec;
	void Set(PteBase *p);
	void Release();
	void Assign(PteBase *p);

public:
	~PtrBase();
};

template <class T>
class Pte : public PteBase {
	friend class Ptr<T>;
};

template <class T>
class Ptr : public PtrBase, Moveable< Ptr<T> > {
	T   *Get() const                          { return prec ? static_cast<T *>(prec->ptr) : NULL; }

public:
	T       *operator->() const               { return Get(); }
	T       *operator~() const                { return Get(); }
	operator T*() const                       { return Get(); }

	Ptr& operator=(T *ptr)                    { Assign(ptr); return *this; }
	Ptr& operator=(const Ptr& ptr)            { Assign(ptr.Get()); return *this; }

	Ptr()                                     { prec = NULL; }
	Ptr(T *ptr)                               { Set(ptr); }
	Ptr(const Ptr& ptr)                       { Set(ptr.Get()); }

	String ToString() const;

	friend bool operator==(const Ptr& a, const T *b)   { return a.Get() == b; }
	friend bool operator==(const T *a, const Ptr& b)   { return a == b.Get(); }
	friend bool operator==(const Ptr& a, const Ptr& b) { return a.prec == b.prec; }

	friend bool operator==(const Ptr& a, T *b)         { return a.Get() == b; }
	friend bool operator==(T *a, const Ptr& b)         { return a == b.Get(); }

	friend bool operator!=(const Ptr& a, const T *b)   { return a.Get() != b; }
	friend bool operator!=(const T *a, const Ptr& b)   { return a != b.Get(); }
	friend bool operator!=(const Ptr& a, const Ptr& b) { return a.prec != b.prec; }

	friend bool operator!=(const Ptr& a, T *b)         { return a.Get() != b; }
	friend bool operator!=(T *a, const Ptr& b)         { return a != b.Get(); }
};

template <class T>
String Ptr<T>::ToString() const
{
	return prec ? FormatPtr(Get()) : String("0x0");
}

#endif

NAMESPACE_UPP_END

#endif
