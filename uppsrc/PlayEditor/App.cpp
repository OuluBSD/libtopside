#include "PlayEditor.h"

NAMESPACE_TOPSIDE_BEGIN


PlayEditor::PlayEditor() {
	Title("PlayEditor");
	MaximizeBox().MinimizeBox().Sizeable();
	
	
	
}

bool PlayEditor::LoadFile(String path) {
	return Load(UPP::LoadFile(path), path);
}

bool PlayEditor::Load(String content, String path) {
	
	PlayTokenizer t;
	t.WhenMessage << THISBACK(OnMessage);
	if (!t.Process(content, path)) {
		
		return false;
	}
	t.Dump();
	
	PlayParser p;
	p.WhenMessage << THISBACK(OnMessage);
	p.Process(t.GetTokens());
	
	
	p.GetResult().Dump();
	
	return true;
}

void PlayEditor::OnMessage(const ProcMsg& p) {
	
	LOG(p.ToString());
	
}



NAMESPACE_TOPSIDE_END
