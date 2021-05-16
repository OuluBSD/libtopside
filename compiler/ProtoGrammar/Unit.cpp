#include "Grammar.h"


NAMESPACE_TOPSIDE_BEGIN


ParsingUnit::ParsingUnit() : ErrorSourceBuffered("ParsingUnit") {
	
}

/*bool ParsingUnit::Load(UppProject& prj, UppAssembly& as) {
	this->prj = &prj;
	this->as = &as;
	
	for(int i = 0; i < prj.GetFileCount(); i++) {
		String file = prj.GetFile(i);
		String path = prj.GetFilePath(i);
		
		if (!FileExists(path)) {
			AddError(FileLocation(), Format(t_("file doesn't exist: %s"), path));
			return false;
		}
		
		if (!LoadFile(path))
			return false;
	}
	
	TODO
	
	return true;
}*/

bool ParsingUnit::LoadFile(String filepath) {
	ClearMessages();
	root.Clear();
	
	String content = Upp::LoadFile(filepath);
	if (content.IsEmpty())
		return false;
	
	Tokenizer t;
	t.WhenMessage = THISBACK(OnMessage);
	t.SkipNewLines();
	t.SkipComments();
	if (!t.Process(content, filepath))
		return false;
	t.CombineTokens();
	if (0) // pythonic
		t.NewlineToEndStatement();
	//t.Dump();
	
	MacroInterpreter mi0;
	mi0.WhenMessage = THISBACK(OnMessage);
	mi0.SetSource(t.GetTokens());
	if (!mi0.ProcessTokenizer()) {LOG("MacroInterpreter failed"); return false;}
	//mi0.Dump();
	
	Grammar::Parser tp;
	tp.WhenMessage = THISBACK(OnMessage);
	tp.SetSource(mi0.GetOutput());
	if (!tp.Process()) {return false;}
	//tp.Dump();
	
	#ifdef flagBOOTSTRAP
	
	Swap(tp.root, root);
	return true;
	
	#else
	Grammar::PostParser pp;
	pp.WhenMessage = THISBACK(OnMessage);
	pp.SetSource(tp.GetOutput());
	if (!pp.Process()) {return false;}
	pp.Dump();
	//DUMPC(pp.GetTokens());
	
	//Swap(pp.root, root);
	
	MacroInterpreter mi1;
	mi1.WhenMessage = THISBACK(OnMessage);
	mi1.SetSource(pp.GetTokens());
	if (!mi1.ProcessTokenizer()) {LOG("MacroInterpreter failed"); return false;}
	//mi1.Dump();
	
	Meta::Parser mp;
	mp.WhenMessage = THISBACK(OnMessage);
	mp.SetSource(mi1.GetOutput());
	if (!mp.Process()) {return false;}
	mp.Dump();
	
	//Swap(mp.root, root);
	
	
	
	AstResolver ar;
	ar.Init();
	
	MetaSimplifier ms(ar);
	ms.WhenMessage = THISBACK(OnMessage);
	ms.SetSource(mp.GetOutput());
	if (!ms.Process()) {DumpMessages(); return false;}
	ms.Dump();
	
	if (ar.IsFail()) {
		DumpMessages();
		return false;
	}
	
	return true;
	
	#endif
}

void ParsingUnit::Dump() {
	TODO
}

void ParsingUnit::OnMessage(ProcMsg msg) {
	InternalAddMessage(msg);
}


NAMESPACE_TOPSIDE_END
