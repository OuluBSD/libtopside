#include <signal.h>
#include "CommandBridge.h"

#define IMAGECLASS CommandBridgeImg
#define IMAGEFILE <CommandBridge/CommandBridge.iml>
#include <Draw/iml_source.h>

#if defined flagDEBUG && !__MINGW32__
	#define DEBUG_APP_PROFILE 1
#endif

volatile sig_atomic_t hupflag = 0;

extern "C" void hangup(int) {
	hupflag = 1;
}


bool is_tray;
bool is_cons_toggled;
TrayApp* last_tray;

void ToggleWindow(CommandBridge* cons) {
	is_cons_toggled = true;
	if (is_tray)
		last_tray->Close();
	else
		cons->PostClose();
}

String GetKeysFile() {
	return ConfigFile("keys.key");
}

void LoadKeys() {
	String keyfile = GetKeysFile();
	if (FileExists(keyfile)) {
		String s = LoadFile(keyfile);
		if (!s.IsEmpty())
			RestoreKeys(s);
	}
}

void SaveKeys() {
	FileOut fout(GetKeysFile());
	fout << StoreKeys();
	fout.Close();
}

GUI_APP_MAIN {
	StdLogSetup(LOG_COUT|LOG_FILE);
	
	#if defined flagPOSIX
	signal(SIGHUP, hangup);
	#elif defined flagWIN32
	signal(SIGBREAK, hangup);
	#endif
	
	
	if (!CommandLine().IsEmpty()) {
		#ifdef flagHAVE_FTP
		if (CommandLine()[0] == "ftpd") {
			FTPServer f;
			f.Start();
			while(!Thread::IsShutdownThreads()) Sleep(1000);
			return;
		}
		#endif
	}
	
	LoadKeys();
	
	CommandBridge cons;
	cons.AddDefault();
	
	dword key;
	#if DEBUG_APP_PROFILE
	key = K_CTRL|K_SHIFT|K_X;
	#elif defined flagPOSIX
	key = 0xa7 | K_DELTA; // §
	is_tray = true;
	#else
	key = 65756;
	is_tray = true;
	#endif
	
	Ctrl::RegisterSystemHotKey(key, callback1(ToggleWindow, &cons));
	
	
	bool is_exit = false;
	is_cons_toggled = true;
	while (!is_exit && !Thread::IsShutdownThreads()) {
		if (!is_cons_toggled)
			break;
		is_cons_toggled = false;
		
		if (is_tray) {
			TrayApp tray;
			last_tray = &tray;
			tray.Run();
			is_exit = tray.IsExit();
			is_cons_toggled = !is_exit;
		}
		else {
			#if !DEBUG_APP_PROFILE
			cons.PostTopMost();
			#endif
			cons.Run();
			cons.CloseTopCtrls();
			SaveKeys();
		}
		
		is_tray = !is_tray;
		
		#if DEBUG_APP_PROFILE
		is_exit = true;
		#endif
		
		if (hupflag)
			is_exit = true;
	}
	
	SaveKeys();
}
