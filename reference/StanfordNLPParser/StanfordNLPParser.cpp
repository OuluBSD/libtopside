#include <Language/Language.h>

using namespace UPP;
using namespace TS;
using namespace TS::Language;

/*

	Pre-requirements:
		- Stanford NLP xml server running
			- https://github.com/stanfordnlp/CoreNLP
			- https://stanfordnlp.github.io/CoreNLP/corenlp-server.html
			- for example:
				1. wget https://nlp.stanford.edu/software/stanford-corenlp-latest.zip
				2. unzip stanford-corenlp-latest.zip
				3. cd stanford-corenlp-4.2.0
				4. wget http://nlp.stanford.edu/software/stanford-corenlp-4.2.0-models.jar
				5. *modify and run in bash*  export CLASSPATH=$CLASSPATH:/path/to/stanford-corenlp-4.2.0/
				6. java -mx4g -cp "*" edu.stanford.nlp.pipeline.StanfordCoreNLPServer -port 7688 -timeout 15000
			- note: running the server and this first time might take long to process (read server log)
			- note: if you get "error: empty xml file", then you are not receiving base64 encoded xml
*/

CONSOLE_APP_MAIN {
	String nl_path = GetDataFile("Apple.txt");
	
	Vector<String> lines = Split(LoadFile(nl_path), "\n");
	StanfordXmlParser p;
	for (String line : lines) {
		LOG("Processing line: " << line);
		
		String output = GetStanfordEnglish(line);
		if (output.IsEmpty()) {
			LOG("error: empty output file");
			SetExitCode(1);
			return;
		}
		
		if (!p.Parse(output) || p.root.IsEmpty()) {
			LOG("error: parsing output failed");
			SetExitCode(1);
			return;
		}
		
		p.Dump();
	}
}
