#include <Language/Language.h>

using namespace UPP;
using namespace TS;
using namespace TS::Language;

/*

	This program dumps parsed English conllu tree.
	
	E.g.:
		"ANSI-89 describes the traditional Jet SQL syntax."
		
		--->
		
		nl: UNKNOWN
			nl: SG-NOM,nsubj
				text: ANSI-89
					lemma: ANSI-89
			nl: PRES,root
				text: describes
					lemma: describe
			nl: UNKNOWN
				nl: DEF,det
					text: the
						lemma: the
				nl: UNKNOWN
					nl: POS,amod
						text: traditional
							lemma: traditional
					nl: SG-NOM,compound
						text: Jet
							lemma: Jet
					nl: SG-NOM,flat
						text: SQL
							lemma: SQL
				nl: SG-NOM,obj
					text: syntax
						lemma: syntax
			nl: Period,punct
				text: .
					lemma: .
	
	Pros:
		It's usable
	Cons:
		The output is still ugly and should be improved
	

	Pre-requirements:
		- English Turku-neural-parser-pipeline running in server mode in port 7690
			- https://turkunlp.org/Turku-neural-parser-pipeline/
	
*/
CONSOLE_APP_MAIN {
	String nl_path = GetDataFile("Apple.txt");
	String conllu_path = GetDataFile("Example.conllu");
	int server_port = 7690;
	bool use_caching = false;
	
	/*
	You can try the ud-treebank too:
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_English-ESL/en_esl-ud-train.conllu");
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_English-EWT/en_ewt-ud-train.conllu");
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_English-GUM/en_gum-ud-train.conllu");
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_English-LinES/en_lines-ud-train.conllu");
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_English-PUD/en_pud-ud-test.conllu");
	
	Note: these takes long time to load
	
	*/
	
	
	for (int i = 0; i < 2; i++) {
		String conll;
		
		// 1. Load existing conllu file
		if (i == 0) {
			conll = LoadFile(conllu_path);
		}
		// 2. Load natural language textfile (regular text)
		else if (i == 1) {
			if (use_caching) {
				// For faster processing in later runs
				conll = LoadFile(ConfigFile("cached.txt"));
				if (conll.IsEmpty()) {
					conll = GetConllEnglish(LoadFile(nl_path), server_port);
					FileOut fout(ConfigFile("cached.txt"));
					fout << conll;
				}
			}
			else {
				conll = GetConllEnglish(LoadFile(nl_path), server_port);
			}
		}
		
		if (conll.IsEmpty()) {
			LOG("error: empty source file");
			SetExitCode(1); return;
		}
		
		ConllParser p;
		if(p.ParseEnglish(conll.ToWString()))
			p.Dump();
		else {
			LOG("error: parsing failed");
			SetExitCode(1); return;
		}
	}
}
