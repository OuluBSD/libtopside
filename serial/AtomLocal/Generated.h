#ifndef _AtomLocal_Generated_h_
#define _AtomLocal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Serial {

class CustomerAtom : public Atom<CustomerAtom> {

public:
	RTTI_DECL1(CustomerAtom, BaseT);
	COPY_PANIC(CustomerAtom);

};

class TestRealtimeSrc : public Atom<TestRealtimeSrc> {

public:
	RTTI_DECL1(TestRealtimeSrc, BaseT);
	COPY_PANIC(TestRealtimeSrc);

};

class TestRealtimeSink : public Atom<TestRealtimeSink> {

public:
	RTTI_DECL1(TestRealtimeSink, BaseT);
	COPY_PANIC(TestRealtimeSink);

};

}

}



#endif
