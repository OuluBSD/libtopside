#ifndef _IfaceCore_Package_h_
#define _IfaceCore_Package_h_

NAMESPACE_PLAN_BEGIN

struct Class;

struct Function {
	Vector<String> arg_str;
	VectorMap<String,String> args;
	String ret_str;
	String name;
	
	
	Function& SetName(String s) {name = s; return *this;}
	Function& Arg(String param);
	Function& Ret(String type);
	String GetTreeString(int indent);
	String GetDeclarationString(bool argnames, String prefix="", bool have_this_arg=true) const;
	String GetProxyString(const Class& c, String prefix) const;
	String GetWrapDeclarationString(String cls) const;
	
};

struct EnabledFlag : Moveable<EnabledFlag> {
	Vector<String> flags;
	
	
	EnabledFlag& AddFlag(String f) {flags.Add(f); return *this;}
	
};

struct Class {
	String name;
	String type;
	String cpp_name;
	String t_name;
	String inherits;
	VectorMap<String, String> nat_inherited;
	VectorMap<String, String> nat_field;
	ArrayMap<String, Function> funcs;
	bool have_context_fns = false;
	Vector<EnabledFlag> enabled;
	
	Class& SetName(String s) {name = s; return *this;}
	Class& SetType(String s) {type = s; return *this;}
	Class& Inherit(String s) {ASSERT(inherits.IsEmpty()); inherits = s; return *this;}
	String GetTreeString(int indent);
	Function& AddFunction(String name);
	void AddNativeInherit(String cls, String name);
	void AddNativeField(String cls, String name);
	EnabledFlag& AddEnabled() {return enabled.Add();}
	String GetPreprocessorEnabler() const;
};

struct EnumValue {
	String name, value;
	
	EnumValue& SetName(String s) {name = s; return *this;}
	EnumValue& Set(String value) {this->value = value; return *this;}
	String GetTreeString(int indent);
	
};

struct Enum {
	ArrayMap<String, EnumValue> keys;
	String name;
	
	
	Enum& SetName(String s) {name = s; return *this;}
	EnumValue& AddKey(String key, String value);
	String GetTreeString(int indent);
	
};

struct Namespace {
	ArrayMap<String, Enum> enums;
	ArrayMap<String, Class> classes;
	
	
	Enum& AddEnum(String name);
	Class& AddClass(String name);
	String GetTreeString(int indent);
	
};

struct Interface {
	ArrayMap<String, Class> nat_cls, util_cls;
	ArrayMap<String, Function> funcs;
	
	Class& AddNativeClass(String name, String type="void*");
	Class& AddUtilClass(String name);
	Function& AddFunction(String name);
	String GetTreeString(int indent);
};

struct Vendor {
	struct Struct {
		VectorMap<String,String> fields;
		Vector<EnabledFlag> enabled;
		
		Struct& Add(String name, String type) {fields.Add(name, type); return *this;}
		String GetPreprocessorEnabler() const;
		void RequireFlag(const String& f) {enabled.Add().flags.Add(f);}
	};
	
	String name;
	VectorMap<String, String> nat_typedef;
	VectorMap<String, Vector<String>> includes;
	Vector<EnabledFlag> enabled;
	ArrayMap<String, Struct> structs;
	bool includes_in_header = false;
	
	Vendor& SetName(String s) {name = s; return *this;}
	Vendor& AddNativeTypedef(String iface_cls, String nat_cls) {nat_typedef.Add(iface_cls, nat_cls); return *this;}
	Vendor& AddInclude(String macro_if_str, String filepath) {includes.GetAdd(macro_if_str).Add(filepath); return *this;}
	Vendor& SetIncludeInHeader(bool b=true) {includes_in_header = b; return *this;}
	Struct& AddStruct(String type) {return structs.Add(type);}
	EnabledFlag& AddEnabled() {return enabled.Add();}
	String GetTreeString(int indent);
	String GetPreprocessorEnabler() const;
	String GetIncludes(int indent=0) const;
};

struct Package {
	
protected:
	Namespace ns;
	Interface iface;
	ArrayMap<String, Vendor> vendors;
	Index<String> deps;
	Index<String> main_flags;
	VectorMap<String, Vector<String>> libraries;
	VectorMap<String, Vector<String>> cond_deps;
	RGBA clr;
	bool have_recv_finalize = false;
	bool have_update = false;
	bool have_negotiate_fmt = false;
	bool have_is_ready = false;
	
	void SetColor(int r, int g, int b) {clr.r = r; clr.b = b; clr.g = g;}
	void AddDependency(String s) {deps.FindAdd(s);}
	void AddDependency(String upp_if_str, String s) {cond_deps.GetAdd(upp_if_str).Add(s);}
	void AddMainFlag(String s) {main_flags.FindAdd(s);}
	
public:
	Package();
	
	Vendor& AddVendor(String name);
	Package& AddLibrary(String upp_cond_str, String library_str) {libraries.GetAdd(upp_cond_str).Add(library_str); return *this;}
	void HaveRecvFinalize() {have_recv_finalize = true;}
	void HaveUpdate() {have_update = true;}
	void HaveNegotiateFormat() {have_negotiate_fmt = true;}
	void HaveIsReady() {have_is_ready = true;}
	
	virtual const char* GetTitle() const = 0;
	virtual const char* GetAbbreviation() const = 0;
	virtual char GetAbbreviationLetter() const = 0;
	
	String GetTreeString(int indent);
	void Dump();
	bool Export(CompilationUnit& cu);
	bool Export();
	
	
};

NAMESPACE_PLAN_END

#endif
