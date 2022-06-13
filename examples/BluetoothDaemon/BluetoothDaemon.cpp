#ifndef flagLINUX
	#error This application works only in linux
#endif


#include <Local/Local.h>
#include <ports/hcidump/hcidump.h>
using namespace UPP;

struct SimpleBluetoothDaemon {
	typedef SimpleBluetoothDaemon CLASSNAME;
	
	Array<SimpleBluetoothConnection> conns;
	TcpSocket server;
	Array<Vector<byte>> data;
	
	SimpleBluetoothDaemon() {
		data.SetCount(3);
		conns.SetCount(3);
		for(int i = 0; i < conns.GetCount(); i++) {
			if (conns[i].Open(i)) {
				conns[i].ReadPacket(data[i]);
			}
		}
	}
	
	
	void Run() {
		if(!server.Listen(3214, 5)) {
			Cout() << "Unable to initialize server socket!\n";
			return;
		}
		Cout() << "Waiting for requests..\n";
		for(;;) {
			One<TcpSocket> s;
			s.Create();
			if(s->Accept(server)) {
				Cout() << "Accepted connection from " << s->GetPeerAddr() << "\n";
				Thread::Start(THISBACK1(ClientHandler, s.Detach()));
			}
		}
	}
	
	
	void ClientHandler(TcpSocket* s_) {
		One<TcpSocket> s;
		s = s_;
		
		while (s->IsOpen()) {
			Cout() << "Reading connection number\n";
			int conn_i = -1;
			s->Get(&conn_i, sizeof(conn_i));
			if (conn_i >= 0 && conn_i < conns.GetCount()) {
				auto& data = this->data[conn_i];
				SimpleBluetoothConnection& conn = conns[conn_i];
				if (!conn.IsOpen() || !conn.ReadPacket(data) || data.IsEmpty()) {
					Cout() << "could not read data from conn #" << conn_i << "\n";
					if (!conn.IsOpen()) Cout() << "\tconnetion not open\n";
					else if (data.IsEmpty()) Cout() << "\tgot no data\n";
					else Cout() << "\treading hci failed\n";
					s->Close();
					break;
				}
				
				Cout() << "Sending " << data.GetCount() << " from bluetooth #" << conn_i << " to " << s->GetPeerAddr() << "\n";
				
				int len = data.GetCount();
				s->Put(&len, sizeof(len));
				s->Put(data.Begin(), data.GetCount());
			}
			else s->Close();
		}
		
		Cout() << "ClientHandler exit\n";
	}
	
	
};

CONSOLE_APP_MAIN {
	Cout() << "\nThis executable must have 'capabilities' set to work properly in user space\n"
			  "		setcap 'cap_net_raw,cap_net_admin+eip' /path/to/this/executable\n\n";
	
	SimpleBluetoothDaemon().Run();
	
}
