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


CONSOLE_APP_MAIN {
	SetCoutLog();
	
	SerialServiceClient client;
	
	int port = 3124;
	if (!client.ConnectTcp("127.0.0.1", port)) {
		LOG("Couldn't connect tcp port " << port);
		SetExitCode(1);
		return;
	}
	
	if (1) {
		for(int i = 0; i < 10; i++) {
			FixedArgs args;
			FixedAnswer ans;
			args.number = Random(1000);
			for(int i = 0; i < 5; i++) {
				args.cstr[i] = 'A' + Random('Z' - 'A' + 1);
			}
			args.cstr[5] = 0;
			
			client.Call(777, args, ans);
			
			LOG(args.number << " --> " << ans.f32);
			if (ans.f32 != args.number * 1.5) {
				LOG("error: unexpected answer: " << ans.f32);
				break;
			}
			
			Sleep(200);
		}
	}
	
	if (1) {
		for(int i = 0; i < 10; i++) {
			SerializedArgs args;
			SerializedAnswer ans;
			for(int i = 0; i < 5; i++) {
				args.str.Cat('A' + Random('Z' - 'A' + 1));
			}
			
			client.CallSerialized(778, args, ans);
			
			LOG(args.str << " --> " << ans.str);
			if (ans.str != args.str + args.str + args.str) {
				LOG("error: unexpected answer: " << ans.str);
				break;
			}
			
			Sleep(200);
		}
	}
}
