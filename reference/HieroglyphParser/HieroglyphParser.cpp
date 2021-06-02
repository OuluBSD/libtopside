#include <Language/Language.h>

using namespace UPP;
using namespace TS::Language;


CONSOLE_APP_MAIN {
	TimeStop ts;
	
	Vector<WString> hieros;
	hieros << "qmA";
	hieros << "xnsw-HAt-nTr-nb";
	
	
	for (WString hiero : hieros) {
		DUMP(hiero);
		
		
		// This gives dummy pronounciation for english speaking people
		WString en_pronon = GetHieroLang().Pronounce(hiero);
		DUMP(en_pronon);
		
		
		// This gives dummy pronounciation for finnish speaking people
		WString fi_pronon = GetFinnish().PronounceNatively(en_pronon);
		DUMP(fi_pronon);
	}
	
	// This tries to find words based on the dictionary...
	// ...but actual texts are complicated and doesn't match the dictionary well :/
	JseshParser jp;
	jp.Parse(LoadFile(GetDataFile("Louvre E 116a.gly")).ToWString());
	//jp.DumpTokens();
	jp.DumpRoot();
	
	LOG(ts.ToString());
	
	
	/*
	
	I am no way any expert on this topic.
	Actually, I'm not even a hobbyist.
	I'm just a geek who wanted to read hieroglyph files for technical reasons...
	
	However, I think you could try to understand the text like this.
	The program exports parsed node tree like this:
	
		horz-group:
			word: (4070)  (suffix prn.) I,me,my
			parenthesis:
				vert-group:
					word: (6260)  obelisk
					word: (5272)  (genitival adj. masc.) of, belonging to
		word: (10658)  (suffix prn.) you,your
		vert-group:
			word: (10241)  (suffix prn.) you, your
			word: (1102)  measure, examine (patient), patrol
	
	That's like:
		"My obelisk you examine".
		"You examine my obelisk".
		
	But I don't really have a clue.
	
	I hope that you understand this better and that this is useful for you :)
	
	
	- Seppo Pakonen, 4.4.2021
	
	*/
}

