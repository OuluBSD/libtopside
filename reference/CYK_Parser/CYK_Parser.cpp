#include <Language/Language.h>

/*

	StatParser parses English text based on CYK algorithm.
	The parsing quality is quite poor, so it will give bad results for advanced use cases.
	
	Pros:
		- this gives decent heuristics for sentence parsing
		- it gives the Constituency-based parse tree, which is useful for structured analysis
	Cons:
		- forget about using this for translation etc.
	

*/
using namespace UPP;
using namespace TS;
using namespace TS::Language;


CONSOLE_APP_MAIN {
	String path = GetDataFile("Apple.txt");
	
	StatParser p;
	p.LoadModel();
	
	{
		String line = "It is possible, that the Western Europeans mixed up two Russian words, which were A and B.";
		
		p.Parse(line.ToWString());
		p.Dump();
	}
	
	{
		String content = LoadFile(path);
		Vector<String> lines = Split(content, "\n");
		
		for(String line : lines) {
			p.Parse(line.ToWString());
			p.Dump();
			LOG(line);
		}
	}
}
