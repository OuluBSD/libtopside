#ifndef _LlamaCpp_LlamaCpp_h_
#define _LlamaCpp_LlamaCpp_h_

#include <llama.h>

#include <Core/Core.h>
using namespace Upp;

#include "common.h"




#ifdef __cplusplus
extern "C" {
#endif

    //
    // C interface
    //
    // TODO: show sample usage
    //

    struct llama_model;
    struct llama_context;
    
#ifdef __cplusplus
}
#endif


struct gpt_params;



class LlamaCppResponse {
	String model;
	String line_tmp;
	String full_log;
	String prompt;
	String output;
	int context_size = 4096;
	int n_predict = 1024;
	int n_threads = 1;
	int n_gpu_layers = 33;
	
	
	
	llama_token llama_sampling_sample(
	        struct llama_sampling_context * ctx_sampling,
	        struct llama_context * ctx_main,
	        struct llama_context * ctx_cfg,
	        int idx = 0);
	
	llama_token llama_sampling_sample_impl(
                  struct llama_sampling_context * ctx_sampling,
                  struct llama_context * ctx_main,
                  struct llama_context * ctx_cfg,
                  const int idx,
                  bool is_resampling);
    
	void write_logfile(
	    const llama_context * ctx, const gpt_params & params, const llama_model * model,
	    const std::vector<llama_token> & input_tokens, const std::string & output,
	    const std::vector<llama_token> & output_tokens
	);
	void sigint_handler(int signo);
	
public:
	LlamaCppResponse();
	
	void SetPrompt(String s) {prompt = s;}
	void SetModel(String s) {model = s;}
	void SetMaxTokens(int n) {n_predict = n;}
	void SetGpuLayers(int n) {n_gpu_layers = n;}
	void SetContextSize(int n) {context_size = n;}
	void SetThreadCount(int n=-1);
	int Process();
	
	void Log(String line);
	void LogLine(String line);
	const String& GetLog() const {return full_log;}
	
	const String& GetOutput() const {return output;}
	
};




#endif
