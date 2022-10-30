#ifndef _LocalPlan_Interface_h_
#define _LocalPlan_Interface_h_

NAMESPACE_TOPSIDE_BEGIN


class InterfaceBuilder {
	struct Dependency : Moveable<Dependency> {
		String conditional;
		bool have_header;
	};
	
	struct Pkg {
		String name, abbr;
		Color clr;
		VectorMap<String,Dependency> deps;
		VectorMap<String,String> libs, ifaces, vendors;
		Index<String> enable_if;
		bool enable_always = false;
		bool have_recv_finalize = false;
		bool have_update = false;
		bool have_is_ready = false;
		bool have_negotiate_format = false;
		bool have_context_fns = false;
		
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
		Header& InOpt(int count, String vd);
		Header& Out(String vd);
		Header& OutOpt(String vd);
		Header& OutOpt(int count, String vd);
		Header& Action(String act);
		Header& Arg(String key, String value);
		Header& Link(String key, String value);
		String GetMacro() const;
		
	};
	
	Array<Header> headers;
	Array<Pkg> packages;
	VectorMap<String,String> custom_atom_bases;
	Pkg* cur = 0;
	
	
public:
	void Package(String s, String a);
	void SetColor(byte r, byte g, byte b);
	void Dependency(String lib, String conditional="", bool have_header=true);
	void Library(String lib, String conditional="");
	void HaveRecvFinalize();
	void HaveUpdate();
	void HaveIsReady();
	void HaveNegotiateFormat();
	void HaveContextFunctions();
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
	void AddAudioFileOut();
	
	bool HasBase(String base) const;
	String GetBaseConds(String base) const;
	
public:
	
	void AddCustomBase(String s, String cond="") {custom_atom_bases.Add(s, cond);}
	Header& AddHeader(String name, String base, String role);
	
	
	void Headers();
	void Generate(bool write_actually=false);
	
	static String GetMacroConditionals(String cond_str);
	static String GetVD(String vd_name);
	static String GetMacroName(String vd_name);
	static String GetMacroFlags(String flags);
	
};


NAMESPACE_TOPSIDE_END

#endif
