#include <LanguageCtrl/LanguageCtrl.h>

using namespace UPP;
using namespace TS;
using namespace TS::Language;


class LanguageEditorWindow : public TopWindow {
	LanguageEditorCtrl edit;
	
public:
	typedef LanguageEditorWindow CLASSNAME;
	LanguageEditorWindow() {
		Add(edit.SizePos());
		Title("LanguageEditorWindow");
		Sizeable().MaximizeBox().Maximize();
	}
	
	bool Load(int mode=1) {
		String nl_path = GetDataFile("Apple.txt");
		String conllu_path = GetDataFile("Example.conllu");
		int server_port = 7690;
		
		// This is made to work with Turku-NPP parser...
		// ... but it requires external server, so it's not opened by default.
		if (mode == 0) {
			String conll = GetConllEnglish(LoadFile(nl_path), server_port);
			
			if (conll.IsEmpty()) {
				LOG("error: empty source file");
				return false;
			}
			
			ConllParser p;
			if(!p.ParseEnglish(conll.ToWString())) {
				LOG("error: parsing failed");
				return false;
			}
			p.Dump();
			edit.SetNode(*p.root);
		}
		// Connl doesn't look good yet, but it doesn't require external server
		else if (mode == 1) {
			String conll = LoadFile(conllu_path);
		
			if (conll.IsEmpty()) {
				LOG("error: empty source file");
				return false;
			}
			
			ConllParser p;
			if(!p.ParseEnglish(conll.ToWString())) {
				LOG("error: parsing failed");
				return false;
			}
			p.Dump();
			edit.SetNode(*p.root);
		}
		
		// This doesn't seem to work at all yet
		else {
			Vector<String> lines = Split(LoadFile(nl_path), "\n");
			Node node_list;
			for (String line : lines) {
				StatParser p;
				p.LoadModel();
				if (!p.Parse(line.ToWString())) {
					LOG("error: parsing failed");
					return false;
				}
				p.Dump();
				node_list.Add(p.root.Detach());
			}
			
			edit.SetNode(node_list);
		}
		
		return true;
	}
};


GUI_APP_MAIN {
	LanguageEditorWindow win;
	if (!win.Load())
		SetExitCode(1);
	else
		win.Run();
}

