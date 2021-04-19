
## Different class instances in a vector
This is very basic stuff, which should be obvious for programmers. Unfortunately, your big brand software tends to still use the very insane and wrong way.

### Wrong
```c++
struct Base {
	virtual void Destroy() {} // #1 not pure virtual function
	// #2 no virtual destructor (for deleting the Derived while deleting Base)
};
struct Derived : public Base {
	// #3 doesn't override
	// #4 deleting this is sane for garbage collected objects (only?)
	virtual void Destroy() {delete this;}
};
struct Manager {
	Vector<Base*> v;

	~Manager() {
		// #5 deleted pointers remains in vector while function finishes (possible race condition)
		// #6 manually writing this is very insane, because the unit tested container class could handle the destruction
		for(Base* b : v)
			delete b;
		v.Clear();
	}

	void Add() {
		Add(new Derived()); // #7 manual memory handling outside of unit tested containers is very prone to small errors
	}
	// #8 Accepting pointers while using it as a contructor argument is very problematic in any convention.
	//    Memory pointers allows more error-prone usage than references, and you should always use the least error-prone way.
	//    The memory pointer should tell for the developer, that the ownership of the object is at risk.
	void Add(Derived* d) {
		v.Add(new Derived(*d));
	}
};

```

### Right
```c++
struct Base {
	virtual void Dummy() = 0; // #1 functions, which are strictly required, are marked with "= 0" as "pure"
	virtual ~Base() {} // #2 destroys Derived when Base is deleted
};
struct Derived : public Base {
	void Dummy() override {} // #3 while not using "override" might work, using it catches problems early
};
struct Manager {
	Array<Base> a;
	// #5 Array function *should* invalidate interface before starting to clear/destruct content
	// #6 Array is essentially "Vector<Base*>" and it when it deletes Base, it deleted Derived via virtual destructor

	void Add() {
		a.Add(new Derived()); // #7 transfering ownership to sub-object **in a single function** with pointers is sensible
	}

	// #8 const references tells that something is added while the original stays same
	void Add(const Derived& d) {
		a.Add(new Derived(d)); // #8 using reference as constructor argument, not pointer	
	}
	void Add(Derived* d) {
		a.Add(d); // #8 the ownership is changed and it's the responsibility of the caller to have the ownership released before that
	}
};
```

