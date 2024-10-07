#include "LlamaCpp.h"


LlamaCppResponse::LlamaCppResponse() {
	model = GetHomeDirFile("llama-2-7b.Q4_K_M.gguf");
	
	SetThreadCount();
}

void LlamaCppResponse::Log(String line) {
	line_tmp << line;
}

void LlamaCppResponse::LogLine(String line) {
	full_log << line_tmp << line;
	line_tmp.Clear();
}

void LlamaCppResponse::SetThreadCount(int n) {
	if (n < 0)
		n_threads = CPU_Cores() + n;
	else
		n_threads = n;
}
