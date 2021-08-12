#ifndef _ChainCore_Factory_h_
#define _ChainCore_Factory_h_

NAMESPACE_PLAN_BEGIN


class ValSpec;
class DevSpec;
class ValDevSpec;


class Factory {
	
public:
	struct Val {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Val>& Vals() {static ArrayMap<String,Val> a; return a;}
	
	
public:
	struct Dev {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Dev>& Devs() {static ArrayMap<String,Dev> a; return a;}
	
	
public:
	struct ValDev {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,ValDev>& ValDevs() {static ArrayMap<String,ValDev> a; return a;}
	
	
public:
	struct Base {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Base>& Bases() {static ArrayMap<String,Base> a; return a;}
	
	
public:
	struct Header {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Header>& Headers() {static ArrayMap<String,Header> a; return a;}
	
	
public:
	struct Loop {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Loop>& Loops() {static ArrayMap<String,Loop> a; return a;}
	
	
public:
	struct Link {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Link>& Links() {static ArrayMap<String,Link> a; return a;}
	
public:
	struct Chain {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Chain>& Chains() {static ArrayMap<String,Chain> a; return a;}
	
public:
	struct Scope {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Scope>& Scopes() {static ArrayMap<String,Scope> a; return a;}
	
public:
	struct Machine {
		const char* name;
		
		
		String ToString() const;
	};
	
	static ArrayMap<String,Machine>& Machines() {static ArrayMap<String,Machine> a; return a;}
	
	
public:
	typedef Factory CLASSNAME;
	Factory() {}
	
	
	template <class T> static
	void RegVal(const char* name) {
		Val& v = Vals().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegDev(const char* name) {
		Dev& v = Devs().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegValDev(const char* name) {
		ValDev& v = ValDevs().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegBase(const char* name, const char* sink, const char* side, const char* src) {
		Base& v = Bases().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegHeader(const char* name, const char* base) {
		Header& v = Headers().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegLoop(const char* name, const char* headers) {
		Loop& v = Loops().Add(name);
		v.name = name;
		
	}
	
	template <class F, class T> static
	void RegLink(const char* name, const char* from, const char* to) {
		Link& v = Links().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegChain(const char* name, const char* loops, const char* links) {
		T::LinkString() = links;
		Chain& v = Chains().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegScope(const char* name, const char* chains, const char* links) {
		T::LinkString() = links;
		Scope& v = Scopes().Add(name);
		v.name = name;
		
	}
	
	template <class T> static
	void RegMachine(const char* name, const char* scopes, const char* links) {
		T::LinkString() = links;
		Machine& v = Machines().Add(name);
		v.name = name;
		
	}
	
	static void Dump();
	
};


NAMESPACE_PLAN_END

#endif
