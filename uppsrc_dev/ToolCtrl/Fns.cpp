#include "ToolCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


void GuiStartup() {
	SetDefaultCharset(CHARSET_UTF8);
	//SetLanguage(GetSystemLNG());
	
	
	
	/*WString ws = String("ˈsi.ʒər").ToWString();
	int first = ws[0];
	PhoneticNanaAnalyser anal;
	anal.Parse(ws.Begin(), ws.GetCount());
	byte nana[256];
	anal.WritePackedNana(nana, 256);*/
	
	#if defined flagX11 && defined flagPOSIX
	SetStdFont(SansSerif(11));
	#endif
	ChFlatSkin();
	InstallRedBar();
	
	
	// Load task manager
	TaskMgrConfig& m = TaskMgrConfig::Single();
	m.Load();
	m.Start();
	
	
	// Aquiring initial OpenAI token
	if (m.openai_token.IsEmpty()) {
		String token;
		bool b = EditTextNotNull(
			token,
			t_("OpenAI token"),
			t_("OpenAI token"),
			0
		);
		if (b) {
			m.openai_token = token;
			m.Store();
		}
	}
	//LOG("OpenAI token: " << m.openai_token);
	
	
	// Start OpenAI backend
	openai::OpenAI* instance = 0;
	if (!m.openai_token.IsEmpty())
		instance = &openai::start(m.openai_token.Begin());
	
	
	// For testing
	String proxy;
	String proxy_file = ConfigFile("proxy.bin");
	const Vector<String>& cmds = CommandLine();
	for(int i = 0; i < cmds.GetCount(); i++) {
		const String& cmd = cmds[i];
		
		if (cmd == "-test-openai") {
			auto completion = openai::completion().create(R"_json(
		    {
		        "model": "text-davinci-003",
		        "prompt": "Say this is a test",
		        "max_tokens": 7,
		        "temperature": 0
		    }
		    )_json");
		    LOG("Response is:\n" << completion.dump(2));
		    return;
		}
		else if (cmd == "-proxy" && i+1 < cmds.GetCount()) {
			proxy = cmds[i+1];
			i++;
		}
		else if (cmd == "-permanent-proxy" && i+1 < cmds.GetCount()) {
			proxy = cmds[i+1];
			FileOut fout(proxy_file);
			fout << proxy;
			i++;
		}
		else if (cmd == "-blue") {
			InstallBlueBar();
		}
	}
	
	if (FileExists(proxy_file))
		proxy = LoadFile(proxy_file);
	
	if (instance && proxy.GetCount())
		instance->setProxy(proxy.Begin());
	
	SetGlobalProxy(proxy);
}

void SetCountForArray(ArrayCtrl& arr, int count) {
	INHIBIT_CURSOR(arr);
	arr.SetCount(count);
}

void SetCountWithDefaultCursor(ArrayCtrl& arr, int count) {
	INHIBIT_CURSOR(arr);
	arr.SetCount(count);
	if (!arr.IsCursor() && arr.GetCount())
		arr.SetCursor(0);
}

void SetCountWithDefaultCursor(ArrayCtrl& arr, int count, int sort_row, bool descending) {
	INHIBIT_CURSOR(arr);
	arr.SetCount(count);
	arr.SetSortColumn(sort_row, descending);
	if (!arr.IsCursor() && arr.GetCount())
		arr.SetCursor(0);
}

int FindArrayIndex(ArrayCtrl& arr, int idx) {
	for(int i = 0; i < arr.GetCount(); i++) {
		int idx1 = arr.Get(i, "IDX");
		if (idx1 == idx)
			return i;
	}
	return -1;
}


END_TEXTLIB_NAMESPACE
