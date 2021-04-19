#include "Grammar.h"

using namespace Upp;
using namespace Oulu;


void GenerateBootstrap() {
	struct Grammar {
		const char* title;
		bool generate_frontend;
		bool generate_post;
		bool generate_meta;
	};
	Grammar grammars[] = {
		{"Grammar",		false,	true,	false},
		{"Meta",		false,	false,	true},
		{0}
	};
	
	Grammar* g = grammars;
	while (g->title) {
		String title = g->title;
		String filepath = GetDataFile(title + ".g");
		
		ParsingUnit pu;
		if (!pu.LoadFile(filepath)) {
			pu.DumpMessages();
			LOG("Parsing failed");
			break;
		}
			
		LOG("Successfully parsed " << title);
		
		if (g->generate_frontend) {
			TODO
		}
		
		if (g->generate_post) {
			BootstrapGenerator gen;
			if (!gen.Process(title, pu)) {
				LOG("Generating failed");
				break;
			}
		}
			
		if (g->generate_meta) {
			MetaBootstrapGenerator gen;
			if (!gen.Process(title, pu)) {
				LOG("Generating failed");
				break;
			}
		}
		
		g++;
	}
}

void GeneratePipeline() {
	Vector<String> grammars;
	
	grammars /*<< "Grammar"*/ << "Vire";
	
	DUMPC(grammars);
	for(String title : grammars) {
		String filepath = GetDataFile(title + ".g");
		
		ParsingUnit pu;
		if (!pu.LoadFile(filepath)) {
			pu.DumpMessages();
			LOG("Parsing failed");
			break;
		}
		//pu.Dump();
			
		LOG("Successfully parsed " << title);
	}
}

CONSOLE_APP_MAIN {
	#if 0
	enum {MODE_NULL, MODE_BOOTSTRAP, MODE_PIPELINE};
	int mode = MODE_NULL;
	
	for(int i = 0; i < CommandLine().GetCount(); i++) {
		String arg = CommandLine()[i];
		if (arg == "-b")
			mode = MODE_BOOTSTRAP;
		if (arg == "-p")
			mode = MODE_PIPELINE;
	}
	
	if (mode == MODE_BOOTSTRAP) {
		GenerateBootstrap();
	}
	else if (mode == MODE_PIPELINE) {
		GeneratePipeline();
	}
	else {
		Cout() << "Possible arguments:\n\t-b: Bootstrap mode\n\t-p: Pipeline mode\n\n";
	}
	#else
	
	#ifdef flagBOOTSTRAP
	GenerateBootstrap();
	#else
	GeneratePipeline();
	#endif
	
	#endif
}

