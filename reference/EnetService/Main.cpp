#include <Local/Local.h>
#include <ports/enet/enet.h>
using namespace TS;


enum {
	ENET_TEST_INT = 20100,
	ENET_TEST_VEC,
	
};

struct Tester : public DaemonService {
	RTTI_DECL1(Tester, DaemonService)
	typedef Tester CLASSNAME;
	
	EnetServiceServer* server = 0;
	EnetServiceClient* client = 0;
	
	bool Init(String name) override {
		Attach(*base);
		return true;
	}
	
	void Update() override {
		
		if (client && client->IsConnected()) {
			int fn = Random(2);
			if (fn == 0) {
				int in = 1 + Random(16), out = 0;
				LOG("TESTER: client called ENET_TEST_INT " << in);
				client->CallEvent<int>(ENET_TEST_INT, in, [=](const int& out) {
					LOG("TESTER: client received ENET_TEST_INT " << out);
					ASSERT(out == 2 * in);
				});
			}
			else if (fn == 1) {
				Vector<int> in;
				for(int i = 0; i < 5; i++)
					in.Add(1 + Random(16));
				LOG("TESTER: client called ENET_TEST_VEC");
				client->CallEventSerialized<Vector<int>>(ENET_TEST_VEC, in, [=](const Vector<int>& out) {
					LOG("TESTER: client received ENET_TEST_VEC " << out.GetCount());
					ASSERT(out.GetCount() == 10);
					for(int i = 0; i < 5; i++) {
						ASSERT(out[i] != 0);
						ASSERT(out[i+5] == 2 * out[i]);
					}
				});
			}
		}
		
	}
	
	void Deinit() override {
		
	}
	
	void Stop() override {
	
	}
	
	void Attach(DaemonBase& d) {
		server = CastPtr<EnetServiceServer>(base->FindService("EnetServer"));
		client = CastPtr<EnetServiceClient>(base->FindService("EnetClient"));
		
		if (server) Attach(*server);
	}
	
	void Attach(EnetServiceServer& d) {
		d.AddFixed<int,int>(ENET_TEST_INT, THISBACK(ServerInt));
		d.AddSerializer<Vector<int>,Vector<int>>(ENET_TEST_VEC, THISBACK(ServerVec));
		//d.AddStream(ENET_TEST_INT, THISBACK(ServerInt));
	}
	
	void ServerInt(const int& in, int& out) {
		out = in * 2;
		LOG("TESTER: server got call ENET_TEST_INT " << in << " --> sending " << out);
	}
	
	void ServerVec(const Vector<int>& in, Vector<int>& out) {
		int c = in.GetCount();
		out.SetCount(c * 2);
		for(int i = 0; i < c; i++) {
			out[i] = in[i];
			out[c + i] = in[i] * 2;
		}
		LOG("TESTER: server got call ENET_TEST_VEC, count " << c);
	}
	
	void ClientInt(Stream& in, Stream& out) {
		
	}
};

CONSOLE_APP_MAIN {
	SetCoutLog();
	
	DaemonBase::Register<Tester>("EnetServiceTester");
	
	CommandLineArguments cmd;
	DaemonBase daemon;
	
	cmd.AddArg('l', "Listen to connections", false);
	cmd.AddArg('c', "Connect to a server", true, "address");
	cmd.AddArg('p', "Port", true, "integer");
	cmd.AddArg('t', "Program timeout", true, "seconds");
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	int daemon_timeout = cmd.IsArg('t') ? StrInt(cmd.GetArg('t')) : 0;
	
	if (cmd.IsArg('l')) {
		daemon.Add("EnetServer");
		EnetServiceServer::port_arg = StrInt(cmd.GetArg('p'));
		LOG("Listening port " << (int)EnetServiceServer::port_arg);
	}
	else if (cmd.IsArg('c')) {
		daemon.Add("EnetClient");
		EnetServiceClient::close_daemon_on_fail = true;
		EnetServiceClient::addr_arg = cmd.GetArg('c');
		EnetServiceClient::port_arg = StrInt(cmd.GetArg('p'));
		LOG("Connecting to port " << (int)EnetServiceClient::port_arg);
	}
	else {
		cmd.PrintHelp();
		return;
	}
	
	daemon.Add("EnetServiceTester");
	daemon.SetTimeout(daemon_timeout);
	daemon.DefaultProcedure();
}
