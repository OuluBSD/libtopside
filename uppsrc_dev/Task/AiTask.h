#ifndef _Task_AiTask_h_
#define _Task_AiTask_h_


BEGIN_TEXTLIB_NAMESPACE



struct TaskMgr;

struct OpenAiResponse {
	struct Msg : Moveable<Msg> {
		String content, role;
		
		void Jsonize(JsonIO& json) {
			json("content", content)
				("role", role);
		}
		String ToString() const {
			String s;
			s	<< "content: " << content << "\n"
				<< "role: " << role << "\n";
			return s;
		}
	};
	struct Choice : Moveable<Choice> {
		String text;
		String finish_reason;
		int index;
		Vector<double> logprobs;
		Msg message;
		
		void Jsonize(JsonIO& json) {
			json("text", text)
				("finish_reason", finish_reason)
				("logprobs", logprobs)
				("index", index)
				("message", message)
				;
		}
		String ToString() const {
			String s;
			s	<< "text: " << text << "\n"
				<< "finish_reason: " << finish_reason << "\n"
				<< "logprobs: ";
			for (double d : logprobs)
				s << d <<", ";
			s	<< "\nindex: " << index << "\n";
			return s;
		}
		String GetText() const {
			return text.IsEmpty() ? message.content : text;
		}
	};
	struct Usage {
		int completion_tokens;
		int prompt_tokens;
		int total_tokens;
		void Jsonize(JsonIO& json) {
			json("completion_tokens", completion_tokens)
				("prompt_tokens", prompt_tokens)
				("total_tokens", total_tokens);
		}
		String ToString() const {
			String s;
			s	<< "completion_tokens: " << completion_tokens << "\n"
				<< "prompt_tokens: " << prompt_tokens << "\n"
				<< "total_tokens: " << total_tokens << "\n";
			return s;
		}
	};
	Vector<Choice> choices;
	String id;
	String model;
	String object;
	Usage usage;
	
	void Jsonize(JsonIO& json) {
		json
			("choices", choices)
			("id", id)
			("model", model)
			("object", object)
			("usage", usage)
			;
	}
	String ToString() const {
		String s;
		for(auto& c : choices)
			s << c.ToString();
		s	<< "id: " << id << "\n"
			<< "model: " << model << "\n"
			<< "object: " << object << "\n"
			<< usage.ToString() << "\n";
		return s;
	}
};

struct DalleResponse {
	struct Data : Moveable<Data> {
		String b64_json;
		
		void Jsonize(JsonIO& json) {
			json("b64_json", b64_json);
		}
		String ToString() const {
			String s;
			s	<< "b64_json: " << b64_json << "\n";
			return s;
		}
	};
	
	int64 created = 0;
	Vector<Data> data;
	
	void Jsonize(JsonIO& json) {
		json
			("created", created)
			("data", data)
			;
	}
	String ToString() const {
		String s;
		s << "created: " << created << "\n";
		s << data.ToString();
		return s;
	}
};


struct AiTask;

struct TaskRule {
	int code = -1;
	String name;
	void (AiTask::*input)() = 0;
	void (AiTask::*process)() = 0;
	bool spawnable = false;
	bool multi_spawnable = false;
	bool allow_cross_mode = false;
	bool separate_items = false;
	bool debug_input = false;
	bool image_task = false;
	bool imageedit_task = false;
	bool imagevariate_task = false;
	bool vision_task = false;
	VectorMap<int, Tuple2<int,int>> req_mode_ranges;
	
	TaskRule& SetRule(int code, const String& name);
	TaskRule& Input(void (AiTask::*fn)());
	TaskRule& Process(void (AiTask::*fn)());
	TaskRule& Spawnable(bool b=true);
	TaskRule& MultiSpawnable(bool b=true);
	TaskRule& CrossMode(bool b=true);
	TaskRule& SeparateItems(bool b=true);
	TaskRule& DebugInput(bool b=true);
	TaskRule& ImageTask(bool b=true);
	TaskRule& ImageEditTask(bool b=true);
	TaskRule& ImageVariateTask(bool b=true);
	
};


struct AiTask : TaskRule {
	
protected:
	friend struct TaskMgr;
	int created_task_count = 0;
	int id = 0;
	mutable hash_t order_hash = 0;
public:

	
	Vector<String> args;
	String output;
	String error;
	bool skip_load = false;
	bool ready = false;
	bool fast_exit = false;
	bool failed = false;
	bool fatal_error = false;
	bool processing = false;
	bool changed = false;
	bool whole_song = false;
	bool wait_task = false;
	bool allow_multi_spawn = false;
	int tries = 0;
	bool keep_going = false;
	bool ret_fail = false;
	bool auto_ret_fail = false;
	int quality = 0;
	
	AiPrompt input;
	String raw_input;
	String jpeg;
	
	// Temp
	Array<AiTask> result_tasks;
	Vector<Vector<String>> str_map;
	Event<> WhenDone;
	Event<String> WhenResult;
	Event<Array<Image>&> WhenResultImages;
	Event<> WhenError;
	String image_n, image_sz, tmp_str;
	Array<Image> send_images, recv_images;
	
	inline static constexpr int common_mask_gen_multiplier		= 8;
	inline static constexpr int common_mask_max_values			= 10;
	inline static constexpr int common_mask_gens				= 200;
	inline static constexpr int separate_mask_gen_multiplier	= 8;
	inline static constexpr int separate_mask_max_values		= 50;
	inline static constexpr int separate_mask_gens				= 100;
	inline static constexpr int snap_gen_multiplier			= 20;
	inline static constexpr int snap_max_values				= 10;
	inline static constexpr int snap_max_per_mode				= snap_max_values / 3;
	inline static constexpr int snap_gens						= 100;
	
	
	void Store(bool force=false);
	void Load();
	bool RunOpenAI();
	bool RunOpenAI_Completion();
	bool RunOpenAI_Image();
	bool RunOpenAI_Vision();
	bool ProcessInput();
	void Process();
	void SetError(String s);
	void SetFatalError(String s) {SetError(s); fatal_error = true;}
	void SetWaiting() {wait_task = true;}
	void SetFastExit() {fast_exit = true;}
	void SetHighQuality() {quality = 1;}
	void ReturnFail();
	void SetAutoReturnFail() {auto_ret_fail = true;}
	String GetInputHash() const;
	String GetOutputHash() const;
	
	void CreateInput_Translate();
	void CreateInput_CreateImage();
	void CreateInput_EditImage();
	void CreateInput_VariateImage();
	void CreateInput_RawCompletion();
	void CreateInput_Vision();
	void CreateInput_GenericPrompt();
	
	void Process_CreateImage();
	void Process_EditImage();
	void Process_VariateImage();
	void Process_Default();
	
	void Retry(bool skip_prompt, bool skip_cache);
	String GetDescription() const;
	String GetTypeString() const;
	
	TaskMgr& GetTaskMgr();
	
};




END_TEXTLIB_NAMESPACE


#endif
