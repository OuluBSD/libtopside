#include <Local/Local.h>
using namespace UPP;
using namespace TS;


struct FixedArgs {
	int number;
	char cstr[12];
};

struct FixedAnswer {
	float f32;
	
};

struct SerializedArgs {
	String str;
	
	void Serialize(Stream& s) {s % str;}
};

struct SerializedAnswer {
	String str;
	
	void Serialize(Stream& s) {s % str;}
};

struct FixedProvider {
	typedef FixedProvider CLASSNAME;
	
	void Call(const FixedArgs& args, FixedAnswer& ans) {
		int cstr_len = strnlen(args.cstr, 12);
		String s(args.cstr, cstr_len);
		ans.f32 = args.number * 1.5;
		LOG("FixedProvider::Call: " << s << ", " << args.number << " -> " << ans.f32);
	}
	
	void CallSerialized(const SerializedArgs& args, SerializedAnswer& ans) {
		ans.str = args.str + args.str + args.str;
		LOG("FixedProvider::Call: " << args.str << " -> " << ans.str);
	}
	
	void Register(SerialServiceServer& server) {
		server.AddFixed<FixedArgs, FixedAnswer>(777, THISBACK(Call));
		server.AddSerializer<SerializedArgs, SerializedAnswer>(778, THISBACK(CallSerialized));
	}
	
};

CONSOLE_APP_MAIN {
	SetCoutLog();
	
	SerialServiceServer server;
	FixedProvider provider;
	
	provider.Register(server);
	
	int port = 3124;
	if (!server.ListenTcp(port)) {
		LOG("Couldn't listen tcp port " << port);
		SetExitCode(1);
		return;
	}
	
	server.ListenerHandler();
}
