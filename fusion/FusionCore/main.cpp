#ifdef flagMAIN

#include "FusionCore.h"

NAMESPACE_FUSION_BEGIN

void PrintTU(TU *tu);


struct SourceFile : Moveable<SourceFile> {
    const char *file_name;
    FILE *file;
    int shader_type;
};

int OldMain(int argc, char **argv) {
	//MemoryBreakpoint(10286);
	
	int shader_type = -1;
    Vector<SourceFile> sources;
    while (argc > 1) {
        ++argv;
        --argc;
        if (argv[0][0] == '-' && argv[0][1]) {
            const char *what = argv[0] + 1;
            if (!strcmp(what, "c"))
                shader_type = TU::kCompute;
            else if (!strcmp(what, "v"))
                shader_type = TU::kVertex;
            else if (!strcmp(what, "tc"))
                shader_type = TU::kTessControl;
            else if (!strcmp(what, "te"))
                shader_type = TU::kTessEvaluation;
            else if (!strcmp(what, "g"))
                shader_type = TU::kGeometry;
            else if (!strcmp(what, "f"))
                shader_type = TU::kFragment;
            else {
                fprintf(stderr, "unknown option: `%s'\n", argv[0]);
                return 1;
            }
        } else {
            // Treat as fragment shader by default
            if (shader_type == -1)
                shader_type = TU::kFragment;
            SourceFile source;
            if (!strcmp(argv[0], "-")) {
                source.file_name = "<stdin>";
                source.file = stdin;
                source.shader_type = shader_type;
                sources.Add(source);
            } else {
                source.file_name = argv[0];
                if ((source.file = fopen(argv[0], "r"))) {
                    source.shader_type = shader_type;
                    sources.Add(source);
                } else {
                    fprintf(stderr, "failed to read shader file: `%s' (ignoring)\n", argv[0]);
                }
            }
        }
    }

    for (int i = 0; i < sources.GetCount(); i++) {
        Vector<char> contents;
        // Read contents of file
        if (sources[i].file != stdin) {
            fseek(sources[i].file, 0, SEEK_END);
            contents.SetCount(ftell(sources[i].file));
            fseek(sources[i].file, 0, SEEK_SET);
            fread(&contents[0], 1, contents.GetCount(), sources[i].file);
            fclose(sources[i].file);
        } else {
            char buffer[1024];
            int c;
            while ((c = fread(buffer, 1, sizeof(buffer), stdin))) {
                int begin = contents.GetCount();
                contents.SetCount(begin + c);
                memcpy(contents.Begin() + begin, buffer, c);
            }
        }
        contents.Add('\0');
        Parser p(&contents[0], sources[i].file_name);
        TU *tu = p.Parse(sources[i].shader_type);
        if (tu) {
            PrintTU(tu);
        } else {
            fprintf(stderr, "%s\n", p.GetError());
        }
    }
    return 0;
}

void CompileToUSSL(MultiStage& pipe) {
	// 
	// 
	// 
	// 
	// 
	// 
	
}

void CompileToUSSL(String path) {
	#define EXPECT(cond, fail_msg) if (!(cond)) {LOG("error: " << fail_msg); SetExitCode(1); return;}
	
	EXPECT(DirectoryExists(path), "expecting the GLSL toy shader directory as argument");
	path = TrimTrailingDirSep(path);
	
	String file_name = GetFileName(path);
	String toy_filename = file_name + ".toy";
	String toy_path = AppendFileName(path, toy_filename);
	EXPECT(FileExists(toy_path), "expecting file " + toy_filename + " in the given directory");
	
	MultiStage pipe;
	EXPECT(pipe.Load(path), "couldn't load pipeline from .toy file");
	
	// 
	// 
	// 
	// 
	// 
	// 
	LOG("Compilation ended successfully");
}

void NewMain() {
	SetCoutLog();
	
	enum {
		MODE_NONE,
		MODE_GLSLTOY_TO_USSL,
	};
	
	CommandLineArguments cmd;
	cmd.AddArg('h', "Show help.", false);
	cmd.AddArg('u', "Convert GLSL toy shader to USSL project.", true);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	int mode = MODE_NONE;
	const auto& inputs = cmd.GetInputs();
	String path;
	for(const auto& in : inputs) {
		if (in.key == 'h') {cmd.PrintHelp(); return;}
		if (in.key == 'u') {mode = MODE_GLSLTOY_TO_USSL; path = in.value;}
	}
	
	if (mode == MODE_GLSLTOY_TO_USSL) {
		CompileToUSSL(path);
	}
	else {
		cmd.PrintHelp();
	}
}

NAMESPACE_FUSION_END

#if 0
int main(int argc, char **argv) {return Topside::Shader::OldMain(argc, argv);}
#else
CONSOLE_APP_MAIN {Topside::Shader::NewMain();}
#endif

#endif
