#include <Language/Language.h>

using namespace UPP;
using namespace TS;
using namespace TS::Language;

/*

	This program dumps parsed Finnish conllu tree.
	
	E.g.:
		"ANSI-89 describes the traditional Jet SQL syntax."
		
		--->




	
	Pros:
		It's usable
	Cons:
		The output is still ugly and should be improved
	

	Pre-requirements:
		- Finnish Turku-neural-parser-pipeline running in server mode in port 7689
			- https://turkunlp.org/Turku-neural-parser-pipeline/
	
*/
CONSOLE_APP_MAIN {
	String nl_path = GetDataFile("Omena.txt");
	String conllu_path = GetDataFile("Example.conllu");
	int server_port = 7689;
	bool use_caching = false;
	
	/*
	You can try the ud-treebank too:
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_Finnish-FTB/fi_ftb-ud-train.conllu");
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_Finnish-OOD/fi_ood-ud-test.conllu");
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_Finnish-PUD/fi_pud-ud-test.conllu");
		String conllu_path = GetHomeDirFile("ud-treebanks-v2.7/UD_Finnish-TDT/fi_tdt-ud-train.conllu");
	
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
					conll = GetConllFinnish(LoadFile(nl_path), server_port);
					FileOut fout(ConfigFile("cached.txt"));
					fout << conll;
				}
			}
			else {
				conll = GetConllFinnish(LoadFile(nl_path), server_port);
			}
		}
		
		if (conll.IsEmpty()) {
			LOG("error: empty source file");
			SetExitCode(1); return;
		}
		
		ConllParser p;
		if(p.ParseFinnish(conll.ToWString()))
			p.Dump();
		else {
			LOG("error: parsing failed");
			SetExitCode(1); return;
		}
	}
}
