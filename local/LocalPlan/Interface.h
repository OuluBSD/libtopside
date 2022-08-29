#ifndef _LocalPlan_Interface_h_
#define _LocalPlan_Interface_h_

NAMESPACE_TOPSIDE_BEGIN


class InterfaceBuilder {
	
	
public:
	void Color(byte r, byte g, byte b);
	void Dependency(String s, String conditional="");
	void Library(String lib, String conditional="");
	void HaveRecvFinalize();
	void HaveUpdate();
	void HaveIsReady();
	void HaveNegotiateFormat();
	void EnableIf(String conditional);
	void EnableAlways();
	void Interface(String name, String conditional="");
	void Vendor(String s, String conditional="");
	
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
	struct Header {
		Header& In(String vd);
		Header& InOpt(String vd);
		Header& Out(String vd);
		Header& OutOpt(String vd);
		Header& Action(String act);
		Header& Arg(String key, String value);
		Header& Link(String key, String value);
		
	};
	
	
	Header& AddHeader(String name, String base, String role);
	
	
	void Headers();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
