#include <Core/Core.h>
using namespace UPP;

void TestBtDaemon()
{
	TcpSocket s;
	if(!s.Connect(CommandLine().GetCount() ? CommandLine()[0] : "127.0.0.1", 3214)) {
		Cout() << "Unable to connect to server!\n";
		SetExitCode(1);
		return;
	}
	for(int i = 0; i < 100; i++) {
		int conn_i = 0;
		s.Put(&conn_i, sizeof(conn_i));
		
		int len = 0;
		s.Get(&len, sizeof(len));
		String data = s.Get(len);
		
		Cout() << "Got " << len << ": " << HexString(data.Begin(), data.GetCount()) << "\n";
	}
}

String Request(const String& r)
{
	TcpSocket s;
	if(!s.Connect(CommandLine().GetCount() ? CommandLine()[0] : "127.0.0.1", 3214)) {
		Cout() << "Unable to connect to server!\n";
		SetExitCode(1);
		return Null;
	}
	s.Put(r + "\n");
	return s.GetLine();
}

// Start reference/SocketServer before starting this program

CONSOLE_APP_MAIN
{
	TestBtDaemon();
	
	Cout() << Request("time") << '\n';
	Cout() << Request("33") << '\n';
}
