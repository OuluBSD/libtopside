#ifndef _Parser_Frontend_h_
#define _Parser_Frontend_h_


NAMESPACE_TOPSIDE_BEGIN



typedef enum : byte {
	ACT_INVALID,
	ACT_ADD_ERROR,
	
	/*
	ACT_PUSH_SCOPE,
	ACT_POP_SCOPE,ACT_ADD_GOTO_LABEL,
	ACT_ADD_VAR,
	ACT_ADD_CLASS,
	ACT_ADD_TMPL_PARAM_CLASS,
	ACT_ADD_SIMPLE_TYPE_SPEC,
	ACT_ADD_DECLARATOR,
	ACT_ADD_TEMPLATE,
	ACT_ADD_CLASS_NAME,
	ACT_ADD_NS,
	ACT_ADD_NS_ALIAS,
	ACT_PATH_SEARCH_STARTED,
	ACT_PATH_SEARCH_STOPPED,
	ACT_PATH_ENTER,
	ACT_FINISH_NS_ALIAS,
	ACT_ADD_ALIAS,
	ACT_FINISH_ALIAS,
	ACT_FINISH_USING_DIRECTIVE,
	ACT_FINISH_USING_DECLARATION,
	ACT_ENABLE_IDENTIFIER_TYPENAME_ONLY,*/
} ActionType;


struct Action : Moveable<Action> {
	ActionType type = ACT_INVALID;
	String str_data;
	Node* node_data = NULL;
	int int_data;
	void* ptr_data = NULL;
	
};


typedef enum : byte {
	ERR_INVALID,
	ERR_PARSER,
	ERR_PARSER_PROBABLE,
	ERR_CONTEXT,
	ERR_SEMANTIC,
} ErrorType;


struct ErrorThread : Moveable<ErrorThread> {
	int succ_cursor;
	
	int max_cursor = -1;
	String max_msg;
	ErrorType type;
	
	int err_cursor = -1;
	String pending_err;
	
	String ToString() const {
		String o;
		o << "At " << succ_cursor << ", " << max_cursor << ": " << max_msg << " (" << (int)type << ")";
		return o;
	}
};



#define GRAMMAR_NAME Grammar
#define GRAMMAR_FILE "Generated_Grammar.inl"
#define GRAMMAR_ENUM_FILE "Generated_Enum_Grammar.inl"
#define GRAMMAR_ENUM_BEGIN 20000
#include "ParserHeader.inl"
#undef GRAMMAR_NAME
#undef GRAMMAR_FILE
#undef GRAMMAR_ENUM_FILE
#undef GRAMMAR_ENUM_BEGIN



#define GRAMMAR_NAME Meta
#define GRAMMAR_FILE "Generated_Meta.inl"
#define GRAMMAR_ENUM_FILE "Generated_Enum_Meta.inl"
#define GRAMMAR_ENUM_BEGIN 20000
#include "ParserHeader.inl"
#undef GRAMMAR_NAME
#undef GRAMMAR_FILE
#undef GRAMMAR_ENUM_FILE
#undef GRAMMAR_ENUM_BEGIN




#define RET(x) ScopeGuard guard(this, #x); One<Node> ret = new Node(NODE_##x);
#define BLOCK_BEGIN(x) ret->SetBlock(x);
//#define CLEAR_RET(x) ret->Clear(); ret->SetType(x);
#define OPT_INIT
#define OPT_FAIL
#define SINGLE_ACT(a) if (a != ACT_INVALID) Act(a, "", &*ret);
#define SINGLE_PRE_ACT(a) if (a != ACT_INVALID) Act(a, "", &*ret);
//#define TEST(x, a) if (x()) {/*ret->Add(DetachReturned()); SetReturned(ret.Detach());*/ SINGLE_ACT(a); return true;}
#define TEST(x, a) if (x()) {ret->Add(DetachReturned()); SetReturned(ret.Detach()); SINGLE_ACT(a); return true;}
#define TEST_TOKEN(x, a) if (PassToken(x)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); return true;}
#define TEST_TOKEN_ID(x, a) if (PassTokenId(x)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); return true;}
#define TEST_TOKEN2(x, a) if (PassToken(x, 2)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); return true;}
#define TEST_TOKEN3(x,a ) if (PassToken(x, 3)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); return true;}
#define TEST_DISCARDSAVED(x, a) if (x()) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); Discard(save_id); return true;}
#define TEST_TOKEN_DISCARDSAVED(x, a) if (PassToken(x)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); Discard(save_id); return true;}
#define TEST_TOKEN_ID_DISCARDSAVED(x, a) if (PassTokenId(x)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); Discard(save_id); return true;}
#define TEST_TOKEN2_DISCARDSAVED(x, a) if (PassToken(x, 2)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); Discard(save_id); return true;}
#define TEST_TOKEN3_DISCARDSAVED(x, a) if (PassToken(x, 3)) {ret->Add(DetachReturned()); SINGLE_ACT(a); SetReturned(ret.Detach()); Discard(save_id); return true;}
#define TEST_PART(x) if (!x()) {is_fail = true; break;} ret->Add(DetachReturned());
#define TEST_PART_ITER_ACT(x, a) if (!x()) {is_fail = true; break;} ret->Add(DetachReturned()); SINGLE_ACT(a);
#define TEST_PART_OPT(x) {OPT_INIT if (x()) {ret->Add(DetachReturned());} else {OPT_FAIL}}
#define TEST_PART_OPT_BREAK(x) {OPT_INIT if (x()) {ret->Add(DetachReturned());} else {OPT_FAIL; break;}}
#define TEST_PART_TOKEN(x) if (!PassToken(x)) {is_fail = true; break;} ret->Add(DetachReturned());
#define TEST_PART_TOKEN_OPT(x) {OPT_INIT if (PassToken(x)) {ret->Add(DetachReturned());} else {OPT_FAIL}}
#define TEST_PART_TOKEN_ID(x) if (!PassTokenId(x)) {is_fail = true; break;} ret->Add(DetachReturned());
#define TEST_PART_TOKEN_ID_OPT(x) {OPT_INIT if (PassTokenId(x)) {ret->Add(DetachReturned());} else {OPT_FAIL}}
#define TEST_PART_TOKEN2(x) if (!PassToken(x, 2)) {is_fail = true; break;} ret->Add(DetachReturned());
#define TEST_PART_TOKEN3(x) if (!PassToken(x, 3)) {is_fail = true; break;} ret->Add(DetachReturned());
#define TEST_PART_TOKEN2_OPT(x) {OPT_INIT if (PassToken(x, 2)) {ret->Add(DetachReturned());} else {OPT_FAIL}}
#define TEST_PART_TOKEN3_OPT(x) {OPT_INIT if (PassToken(x, 3)) {ret->Add(DetachReturned());} else {OPT_FAIL}}
#define DISCARD Discard(save_id);
// causes memleaks #define SET_RETURNED if (ret->GetCount() == 1) SetReturned(ret->Detach(0)); else SetReturned(ret.Detach());
#define SET_RETURNED SetReturned(ret.Detach());
#define SAVE int save_id = Save(); bool is_fail = false;
#define LOAD_NO_DISCARD LoadNoDiscard(save_id);
#define CLEAR_RET {int type = ret->GetType(); ret->Clear(); ret->SetType(type); is_fail = false;}
#define PRE_MAY_FAIL PushErrScope(); guard.HasErrScope(); try_again:
#define POST_MAY_FAIL ProcessErrorThreads(is_fail); if (is_fail && CanTryAgain()) {is_fail = false; goto try_again;}
#define UPDATE_SUCC_POINT UpdateErrScopeSuccess();

}

#endif
