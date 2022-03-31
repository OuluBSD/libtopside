#ifndef _IfaceCore_Defs_h_
#define _IfaceCore_Defs_h_

#define PKG(title, abbr, letter) \
	struct Pkg##abbr : public Package {\
		void Setup(); \
		static Pkg##abbr& Local() {static Pkg##abbr o; return o;} \
		static void Init() {Local().Setup();} \
		const char* GetTitle() const override {return #title;} \
		const char* GetAbbreviation() const override {return #abbr;} \
		char GetAbbreviationLetter() const override {return #letter [0];} \
	}; \
	static TS::Callinit init_Pkg##abbr(Pkg##abbr::Init); \
	void Pkg##abbr::Setup()
#define NAMESPACE for (Namespace* n = &this->ns; n; n = 0)
#define ENUM(name) for (Enum* e = &n->AddEnum(#name); e; e = 0)
#define ENUMVAL(name, value) e->AddKey(#name, #value);
#define CLASS(name) for (Class* c = &n->AddClass(#name); c; c = 0)
#define PKG_IFACE for (Interface* i = &this->iface; i; i = 0)
#define NATIVE_CLASS(name) i->AddNativeClass(#name);
#define NATIVE_CLASS_(name, nat_type) i->AddNativeClass(#name, #nat_type);
#define VENDOR_CLASS(iface_type, nat_type) v->AddNativeTypedef(#iface_type, #nat_type);
#define NATIVE_FIELD(cls, name) c->AddNativeField(#cls, #name);
#define NATIVE_INHERIT(cls, name) c->AddNativeInherit(#cls, #name);
#define UTIL_CLASS(name) i->AddUtilClass(#name);
#define VENDOR(name) for (Vendor* v = &AddVendor(#name); v; v = 0)
#define VENDOR_ENABLED_FLAG(flag) v->AddEnabled().AddFlag(#flag);
#define VENDOR_INCLUDE(macro_if_str, filepath) v->AddInclude(macro_if_str, #filepath);
#define VENDOR_HEADER_REQUIRES_INCLUDES v->SetIncludeInHeader(true);
#define LIBRARY(upp_if_str, lib) this->AddLibrary(upp_if_str, #lib);
#define DEPENDENCY_(upp_if_str, lib) this->AddDependency(upp_if_str, #lib);
#define DEPENDENCY(x) this->AddDependency(#x);
#define MAINFLAG(x) this->AddMainFlag(#x);
#define COLOR(r,g,b) this->SetColor(r,g,b);
#define INHERIT(x) c->Inherit(#x);
#define METHOD0V(name) c->AddFunction(#name);
#define METHOD1V(name, a0) c->AddFunction(#name).Arg(#a0);
#define METHOD2V(name, a0, a1) c->AddFunction(#name).Arg(#a0).Arg(#a1);
#define METHOD3V(name, a0, a1, a2) c->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2);
#define METHOD4V(name, a0, a1, a2, a3) c->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3);
#define METHOD5V(name, a0, a1, a2, a3, a4) c->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4);
#define METHOD6V(name, a0, a1, a2, a3, a4, a5) c->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5);
#define METHOD7V(name, a0, a1, a2, a3, a4, a5, a6) c->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5).Arg(#a6);
#define METHOD0R(name, r) c->AddFunction(#name).Ret(#r);
#define METHOD1R(name, r, a0) c->AddFunction(#name).Ret(#r).Arg(#a0);
#define METHOD2R(name, r, a0, a1) c->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1);
#define METHOD3R(name, r, a0, a1, a2) c->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2);
#define METHOD4R(name, r, a0, a1, a2, a3) c->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3);
#define METHOD5R(name, r, a0, a1, a2, a3, a4) c->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4);
#define METHOD6R(name, r, a0, a1, a2, a3, a4, a5) c->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5);
#define METHOD7R(name, r, a0, a1, a2, a3, a4, a5, a6) c->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5).Arg(#a6);

/*#define METHOD0V(name) c->AddFunction(#name);
#define METHOD1V(name, a0, n0) c->AddFunction(#name).Arg(#a0, #n0);
#define METHOD2V(name, a0, n0, a1, n1) c->AddFunction(#name).Arg(#a0, #n0).Arg(#a1, #n1);
#define METHOD3V(name, a0, n0, a1, n1, a2, n2) c->AddFunction(#name).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2);
#define METHOD4V(name, a0, n0, a1, n1, a2, n2, a3, n3) c->AddFunction(#name).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3);
#define METHOD5V(name, a0, n0, a1, n1, a2, n2, a3, n3, a4, n4) c->AddFunction(#name).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3).Arg(#a4, #n4);
#define METHOD6V(name, a0, n0, a1, n1, a2, n2, a3, n3, a4, n4, a5, n5) c->AddFunction(#name).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3).Arg(#a4, #n4).Arg(#a5, #n5);
#define METHOD7V(name, a0, n0, a1, n1, a2, n2, a3, n3, a4, n4, a5, n5, a6, n6) c->AddFunction(#name).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3).Arg(#a4, #n4).Arg(#a5, #n5).Arg(#a6, #n6);
#define METHOD0R(name, r) c->AddFunction(#name).Ret(#r);
#define METHOD1R(name, r, a0, n0) c->AddFunction(#name).Ret(#r).Arg(#a0, #n0);
#define METHOD2R(name, r, a0, n0, a1, n1) c->AddFunction(#name).Ret(#r).Arg(#a0, #n0).Arg(#a1, #n1);
#define METHOD3R(name, r, a0, n0, a1, n1, a2, n2) c->AddFunction(#name).Ret(#r).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2);
#define METHOD4R(name, r, a0, n0, a1, n1, a2, n2, a3, n3) c->AddFunction(#name).Ret(#r).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3);
#define METHOD5R(name, r, a0, n0, a1, n1, a2, n2, a3, n3, a4, n4) c->AddFunction(#name).Ret(#r).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3).Arg(#a4, #n4);
#define METHOD6R(name, r, a0, n0, a1, n1, a2, n2, a3, n3, a4, n4, a5, n5) c->AddFunction(#name).Ret(#r).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3).Arg(#a4, #n4).Arg(#a5, #n5);
#define METHOD7R(name, r, a0, n0, a1, n1, a2, n2, a3, n3, a4, n4, a5, n5, a6, n6) c->AddFunction(#name).Ret(#r).Arg(#a0, #n0).Arg(#a1, #n1).Arg(#a2, #n2).Arg(#a3, #n3).Arg(#a4, #n4).Arg(#a5, #n5).Arg(#a6, #n6);
*/

// deprecated:
#define FUNCTION0V(name) i->AddFunction(#name);
#define FUNCTION1V(name, a0) i->AddFunction(#name).Arg(#a0);
#define FUNCTION2V(name, a0, a1) i->AddFunction(#name).Arg(#a0).Arg(#a1);
#define FUNCTION3V(name, a0, a1, a2) i->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2);
#define FUNCTION4V(name, a0, a1, a2, a3) i->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3);
#define FUNCTION5V(name, a0, a1, a2, a3, a4) i->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4);
#define FUNCTION6V(name, a0, a1, a2, a3, a4, a5) i->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5);
#define FUNCTION7V(name, a0, a1, a2, a3, a4, a5, a6) i->AddFunction(#name).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5).Arg(#a6);
#define FUNCTION0R(name, r) i->AddFunction(#name).Ret(#r);
#define FUNCTION1R(name, r, a0) i->AddFunction(#name).Ret(#r).Arg(#a0);
#define FUNCTION2R(name, r, a0, a1) i->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1);
#define FUNCTION3R(name, r, a0, a1, a2) i->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2);
#define FUNCTION4R(name, r, a0, a1, a2, a3) i->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3);
#define FUNCTION5R(name, r, a0, a1, a2, a3, a4) i->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4);
#define FUNCTION6R(name, r, a0, a1, a2, a3, a4, a5) i->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5);
#define FUNCTION7R(name, r, a0, a1, a2, a3, a4, a5, a6) i->AddFunction(#name).Ret(#r).Arg(#a0).Arg(#a1).Arg(#a2).Arg(#a3).Arg(#a4).Arg(#a5).Arg(#a6);



#endif
