#ifndef _LocalPlan_Interface_h_
#define _LocalPlan_Interface_h_

NAMESPACE_TOPSIDE_BEGIN


class InterfaceBuilder {
	struct Pkg {
		String name, abbr;
		Color clr;
		VectorMap<String,String> deps, libs, ifaces, vendors;
		Index<String> enable_if;
		bool enable_always = false;
		bool have_recv_finalize = false;
		bool have_update = false;
		bool have_is_ready = false;
		bool have_negotiate_format = false;
		
	};
	
	struct Header {
		String name, base, role;
		String link_type;
		String link_role;
		
		VectorMap<String, String> args, links;
		VectorMap<String, bool> ins, outs;
		String action;
		
		Header& In(String vd);
		Header& InOpt(String vd);
		Header& Out(String vd);
		Header& OutOpt(String vd);
		Header& Action(String act);
		Header& Arg(String key, String value);
		Header& Link(String key, String value);
		String GetMacro() const;
		
	};
	
	Array<Header> headers;
	Array<Pkg> packages;
	Pkg* cur = 0;
	
	
public:
	void Package(String s, String a);
	void SetColor(byte r, byte g, byte b);
	void Dependency(String lib, String conditional="");
	void Library(String lib, String conditional="");
	void HaveRecvFinalize();
	void HaveUpdate();
	void HaveIsReady();
	void HaveNegotiateFormat();
	void EnableIf(String conditional);
	void EnableAlways();
	void Interface(String name, String conditional="");
	void Vendor(String name, String conditional="");
	
	void AddAudio();
	void AddHal();
	void AddScreen();
	void AddVolumetric();
	void AddCamera();
	void AddHolographic();
	void AddSynth();
	void AddEffect();
	void AddMidiHw();
	
	
public:
	
	Header& AddHeader(String name, String base, String role);
	
	
	void Headers();
	void Generate(bool write_actually=false);
	
	static String GetMacroConditionals(String cond_str);
	static String GetVD(String vd_name);
	static String GetMacroName(String vd_name);
	
};


NAMESPACE_TOPSIDE_END

#endif
