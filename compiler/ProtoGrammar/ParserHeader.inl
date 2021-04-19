namespace GRAMMAR_NAME {

#define ENUM_BEGIN_VALUE NODE_GRAMMAR_BEGIN_##GRAMMAR_NAME
enum {
	#include GRAMMAR_ENUM_FILE
};
#undef ENUM_BEGIN_VALUE


class Parser : public ErrorSource {
	
	/*class Err {
		Err() {}
	};*/
	
	struct ScopeGuard {
		Parser* p;
		const char* id;
		bool pop_err_thread;
		
		ScopeGuard(Parser* p, const char* id) : p(p), id(id), pop_err_thread(false) {}
		~ScopeGuard() {
			if (pop_err_thread)
				p->PopErrScope();
		}
		void HasErrScope() {pop_err_thread = true;}
	};
	
	Vector<Action> actions;
	Vector<ErrorThread> err_thrds;
	
	
	struct SaveState : Moveable<SaveState> {
		int cursor;
		int act_count;
	};
	VectorMap<int, SaveState> states;
	int counter = 0;
	
	int end_token = TK_END_STMT;
	int begin_scope = TK_INDENT;
	int end_scope = TK_DEDENT;
	
	One<Node> returned;
	
	
	Node* src = NULL;
	int cursor = 0;
	
	Index<String> keywords;
	
	
	void Next();
	Node& Get() {ASSERT(src); return src->At(cursor);}
	bool IsEof() const {return cursor >= src->GetCount();}
	bool IsToken(int tk) {return Get().GetToken().IsType(tk);}
	int Save();
	void Discard(int save_id);
	void Load(int save_id) {LoadNoDiscard(save_id); Discard(save_id);}
	void LoadNoDiscard(int save_id);
	bool PassTokenId(String id);
	bool PassToken(int token);
	bool PassToken(const char* tks, int count);
	void SetReturned(Node* n);
	Node* DetachReturned();
	void Act(ActionType type, String str="", Node* ptr=NULL);
	bool CanTryAgain();
	void SetError(ErrorType e, String msg);
	void ProcessErrorThreads(bool is_failed);
	void PushErrScope();
	void PopErrScope();
	void UpdateErrScopeSuccess();
	String GetTypeString(Node& n);
	
	#include GRAMMAR_FILE
	
	void Error(String msg, Node& token);
	
	
public:
	Parser();
	
	bool Process();
	
	void Dump() {if (root) {LOG("Dumping parser:"); LOG(NodeTreeString(*root));} else {LOG("No root to dump");}}
	String NodeTreeString(const Node& n, int depth=0, String tab="\t");
	
	void SetTokens(int end_token, int begin_scope, int end_scope) {this->end_token = end_token; this->begin_scope = begin_scope; this->end_scope = end_scope;}
	void SetSource(Node* src) {this->src = src;}
	
	String GetNodeTypeString(const Node& n);
	const Node& GetOutput() {ASSERT(root); return *root;}
	
	

	One<Node> root;

};


inline Parser& StaticParser() {static Parser p; return p;}

}
