#include "TopTool.h"

#ifdef flagMAIN

GUI_APP_MAIN {
	using namespace TextLib;
	
	String sharedir = "share";
	
	bool my_data = false;
	for (const String& s : CommandLine()) {
		if (s == "-my")				{my_data = true;}
		if (s == "-finshare")		{sharedir += "-fi";}
	}
	
	MetaDatabase::Single().share = sharedir;
	
	GuiStartup();
	MetaStartup(my_data);
	
	AppModeStartup();
	
	
	// Run main program
	bool save_data = false;
	bool fast_exit = false;
	{
		TopTool t;
		
		t.GetOrganization().Init();
		t.GetEditor().Init();
		t.GetEditor().InitSimplified();
		t.GetLeads().InitSimplified();
		
		t.Run();
		
		save_data = t.GetEditor().GetSaveSongdata();
		fast_exit = t.GetEditor().IsFastExit();
	}
	
	Thread::ShutdownThreads();
	
	if (!fast_exit)
		MetaShutdown();
	
	AppModeShutdown(fast_exit, save_data);
	
}

#endif
