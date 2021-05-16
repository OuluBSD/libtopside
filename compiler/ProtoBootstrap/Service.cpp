#include "Bootstrap.h"

#ifdef flagMAIN

NAMESPACE_TOPSIDE_BEGIN


ParserService::ParserService() {
	env = "export CLASSPATH=\\\".:/usr/local/lib/antlr-4.7.2-complete.jar:$CLASSPATH\\\";";
	dir = GetHomeDirectory() + DIR_SEPS + "fos" DIR_SEPS "antlrserver";
	grammar_dir = GetHomeDirectory() + DIR_SEPS + "fos" DIR_SEPS "grammars";
	//DUMP(dir);
	
}

void ParserService::Start() {
	Stop();
	
	SetCurrentDirectory(dir);
	String cmd = "bash -c \"" + env + " java -Xmx4G TranslatorServer\"";
	//DUMP(cmd);
	
	proc.Create();
	proc->Start(cmd);
	Sleep(1000);
}

void ParserService::Stop() {
	if (proc.IsEmpty()) return;
	proc->Kill();
	proc.Clear();
}

void ParserService::Recompile() {
	Stop();
	
	SetCurrentDirectory(dir);
	
	String cmd, out;
	
	cmd = "rm *.class";
	Sys(cmd, out);
	LOG(out);
	
	cmd = "antlr4 -DcontextSuperClass=GrammarParserRuleContext -o . \"" + grammar_dir + DIR_SEPS + "ANTLRv4Lexer.g4\"";
	Sys(cmd, out);
	LOG(out);
	
	cmd = "antlr4 -DcontextSuperClass=GrammarParserRuleContext -o . \"" + grammar_dir + DIR_SEPS + "ANTLRv4Parser.g4\"";
	Sys(cmd, out);
	LOG(out);
	
	cmd = "antlr4 -DcontextSuperClass=GrammarParserRuleContext -o . \"" + grammar_dir + DIR_SEPS + "CPP14.g4\"";
	Sys(cmd, out);
	LOG(out);
	
	cmd = "antlr4 -DcontextSuperClass=GrammarParserRuleContext -o . \"" + grammar_dir + DIR_SEPS + "CPP14.g4\"";
	Sys(cmd, out);
	LOG(out);
	
	cmd = "bash -c \"" + env + " javac LexerAdaptor.java GrammarParserRuleContext.java ANTLRv4*.java CPP14*.java TranslatorServer.java\"";
	LOG(cmd);
	Sys(cmd, out);
	LOG(out);
	
	Start();
}


NAMESPACE_TOPSIDE_END

#endif
