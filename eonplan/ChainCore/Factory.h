#ifndef _ChainCore_Factory_h_
#define _ChainCore_Factory_h_

NAMESPACE_PLAN_BEGIN


class ValSpec;
class DevSpec;
class ValDevSpec;


class Factory {
public:
	
	struct Package {
		String name;
		Index<String> deps;
		
		void Set(String s) {name = s; deps.Clear();}
		String ToString() const {return name;}
	};
	
public:
	struct Generic {
		Package* pkg = 0;
		const char* name;
		
	};
public:
	struct Val : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,Val>& Vals() {static ArrayMap<String,Val> a; return a;}
	
	
public:
	struct Dev : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,Dev>& Devs() {static ArrayMap<String,Dev> a; return a;}
	
	
public:
	struct ValDev : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,ValDev>& ValDevs() {static ArrayMap<String,ValDev> a; return a;}
	
	
public:
	struct Base : Generic {
		Index<String>	flags;
		Index<String>	actions;
		
		String ToString() const;
	};
	
	static ArrayMap<String,Base>& Bases() {static ArrayMap<String,Base> a; return a;}
	
	
public:
	struct Header : Generic {
		static const int MAX_VDS = MAX_VDTUPLE_SIZE;
		const char*		base = 0;
		const char*		content = 0;
		const char*		sink[MAX_VDS] = {0};
		const char*		src[MAX_VDS] = {0};
		int				sink_count = 0;
		int				src_count = 0;
		int				sink_user_side_count = 0;
		int				src_user_side_count = 0;
		String			role, key;
		Index<String>				actions, inherits;
		VectorMap<String,String>	args;
		
		String ToString() const;
	};
	
	static ArrayMap<String,Header>& Headers() {static ArrayMap<String,Header> a; return a;}
	
	
public:
	struct Loop : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,Loop>& Loops() {static ArrayMap<String,Loop> a; return a;}
	
	
public:
	struct Link : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,Link>& Links() {static ArrayMap<String,Link> a; return a;}
	
public:
	struct Chain : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,Chain>& Chains() {static ArrayMap<String,Chain> a; return a;}
	
public:
	struct Scope : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,Scope>& Scopes() {static ArrayMap<String,Scope> a; return a;}
	
public:
	struct Machine : Generic {
		
		String ToString() const;
	};
	
	static ArrayMap<String,Machine>& Machines() {static ArrayMap<String,Machine> a; return a;}
	
	
public:
	typedef Factory CLASSNAME;
	Factory() = delete;
	
	
	template <class T> static
	void RegVal(const char* name) {
		Val& v = Vals().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class T> static
	void RegDev(const char* name) {
		Dev& v = Devs().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class T> static
	void RegValDev(const char* name) {
		ValDev& v = ValDevs().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class T> static
	void RegBase(const char* name) {
		Base& v = Bases().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class T> static
	void BaseFlag(const char* name, const char* flag) {
		Base& v = Bases().GetAdd(name);
		v.flags.FindAdd(flag);
	}
	
	template <class T> static
	void BaseAction(const char* name, const char* action) {
		Base& v = Bases().GetAdd(name);
		v.actions.FindAdd(action);
	}
	
	template <class T> static
	void HeaderAction(const char* name, const char* action) {
		Header& v = Headers().GetAdd(name);
		v.actions.FindAdd(action);
	}
	
	template <class T> static
	void HeaderInherits(const char* name, const char* cls) {
		Header& v = Headers().GetAdd(name);
		v.inherits.FindAdd(cls);
	}
	
	template <class T> static
	void HeaderArg(const char* name, const char* key, const char* value) {
		Header& v = Headers().GetAdd(name);
		v.args.GetAdd(key) = value;
	}
	
	template <class T> static
	void RegHeader(
		const char* name,
		const char* base,
		const char* role,
		const char* content,
		int sink_user_count,
		int src_user_count,
		const char* sink0,
		const char* sink1,
		const char* sink2,
		const char* sink3,
		const char* sink4,
		const char* src0,
		const char* src1,
		const char* src2,
		const char* src3,
		const char* src4) {
		Header& v = Headers().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		v.base = base;
		v.content = content;
		
		v.sink_user_side_count = sink_user_count;
		v.sink_count = (sink0 != 0) + (sink1 != 0) + (sink2 != 0) + (sink3 != 0) + (sink4 != 0);
		v.sink[0] = sink0;
		v.sink[1] = sink1;
		v.sink[2] = sink2;
		v.sink[3] = sink3;
		v.sink[4] = sink4;
		
		v.src_user_side_count = src_user_count;
		v.src_count = (src0 != 0) + (src1 != 0) + (src2 != 0) + (src3 != 0) + (src4 != 0);
		v.src[0] = src0;
		v.src[1] = src1;
		v.src[2] = src2;
		v.src[3] = src3;
		v.src[4] = src4;
		
		v.key = ToCaps(name);
		v.role = ToUpper(role);
	}
	
	template <class T> static
	void RegLoop(const char* name, const char* headers) {
		Loop& v = Loops().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class F, class T> static
	void RegLink(const char* name, const char* from, const char* to) {
		Link& v = Links().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class T> static
	void RegChain(const char* name, const char* loops, const char* links) {
		T::LinkString() = links;
		Chain& v = Chains().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class T> static
	void RegScope(const char* name, const char* chains, const char* links) {
		T::LinkString() = links;
		Scope& v = Scopes().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	template <class T> static
	void RegMachine(const char* name, const char* scopes, const char* links) {
		T::LinkString() = links;
		Machine& v = Machines().Add(name);
		v.pkg = ActivePackage();
		v.name = name;
		
	}
	
	static ArrayMap<String,Package>& Packages() {static ArrayMap<String,Package> a; return a;}
	static Package*& ActivePackage() {static Package* p; return p;}
	static void SetActivePackage(String pkg) {auto p = &Packages().Add(pkg); p->name = pkg; ActivePackage() = p;}
	static void AddDep(String pkg) {ActivePackage()->deps.FindAdd(pkg);}
	static void Dump();
	static bool Export(CompilationUnit& cu);
	static bool Export(CompilationUnit& cu, Package& pkg);
	
	static void OnError(String msg);
	
};


NAMESPACE_PLAN_END

#endif
