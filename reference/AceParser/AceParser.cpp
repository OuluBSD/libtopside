#include <Language/Language.h>

using namespace UPP;
using namespace TS;
using namespace TS::Language;

/*

	English parsing based on ACE: the Answer Constraint Engine
	
	
	Pre-requirements:
		- download and install files to your ~/bin file from http://sweaglesw.org/linguistics/ace/
	
	Pros:
		- Ace is accurate parser for rule-based approach
		- it gives the Constituency-based parse tree, which is useful for structured analysis
	Cons:
		- it's slow
	
*/
CONSOLE_APP_MAIN {
	String nl_path = GetDataFile("Apple.txt");
	String content = LoadFile(nl_path);
	Vector<String> lines = Split(content, "\n");
	
	for (String line : lines) {
		String ace_out = GetAceEnglish(line);
		LOG("Ace output:");
		LOG(ace_out);
		
		AceParser ap;
		if (!ap.Parse(ace_out)) {
			SetExitCode(1);
			LOG("error: parsing apple.txt failed");
			return;
		}
		
		ap.Dump();
	}
}
