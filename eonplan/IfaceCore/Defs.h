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
#define UTIL_CLASS(name) i->AddUtilClass(#name);
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
#define VENDOR(name) for (Vendor* v = &AddVendor(#name); v; v = 0)
#define DEPENDENCY(x) this->AddDependency(#x);
#define MAINFLAG(x) this->AddMainFlag(#x);
#define COLOR(r,g,b) this->SetColor(r,g,b);
#define INHERIT(x) c->Inherit(#x);



#endif
