#ifndef flagBOOTSTRAP
#include "Grammar.h"

NAMESPACE_OULU_BEGIN

Ast::Node* MetaSimplifier::VisitNode(const Node& n) {
	switch(n.GetType()) {
		case Meta::NODE_FILE_INPUT: return FileInput(n);
		case Meta::NODE_EXPR_STMT: return ExprStmt(n);
		case Meta::NODE_CALL_WITH_ARGS: return CallWithArgs(n);
		case Meta::NODE_ARG: return Arg(n);
		case Meta::NODE_CALL: return Call(n);
		case Meta::NODE_ARG_ID: return ArgId(n);
		case Meta::NODE_ID_LIT: return IdLit(n);
		case NODE_TOKEN: return AstToken(n);
		default: break;
	}
	PushError("Invalid node type " + IntStr(n.GetType()));
	return 0;
}

Ast::Node* MetaSimplifier::FileInput(const Node& n) {
	ASSERT_TYPE(n, Meta::NODE_FILE_INPUT);
	REF_BLOCK;
	if (IS_BLOCK(1)) {
		Recycler<NodeVec> content0(pool);
		static int content0_count = 4;
		static int content0_pos_i[] = {0, -1, 0, 0};
		static int content0_pos_type[] = {-1, -2, -1, -1};
		if (!Visit(n, *content0, content0_pos_i, content0_pos_type, content0_count)) return 0;
		return AstCompilationUnit(*content0);
	}
	else {PushError("Unimplemented block"); return 0;}
}

Ast::Node* MetaSimplifier::ExprStmt(const Node& n) {
	ASSERT_TYPE(n, Meta::NODE_EXPR_STMT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		Recycler<NodeVec> content0(pool);
		static int content0_count = 1;
		static int content0_pos_i[] = {0};
		static int content0_pos_type[] = {-1};
		AstBeginStmt();
		if (!Visit(n, *content0, content0_pos_i, content0_pos_type, content0_count)) return 0;
		return AstExpressionStatement(*content0);
	}
	else {PushError("Unimplemented block"); return 0;}
}

Ast::Node* MetaSimplifier::CallWithArgs(const Node& n) {
	ASSERT_TYPE(n, Meta::NODE_CALL_WITH_ARGS);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		Recycler<NodeVec> id(pool), content0(pool);
		static int id_count = 3;
		static int id_pos_i[] = {1, 0, -1};
		static int id_pos_type[] = {-1, -1, -3};
		static int content0_count = 3;
		static int content0_pos_i[] = {2, -1, 0};
		static int content0_pos_type[] = {-1, -2, -1};
		if (!Visit(n, *id, id_pos_i, id_pos_type, id_count)) return 0;
		if (!Visit(n, *content0, content0_pos_i, content0_pos_type, content0_count)) return 0;
		return AstCall(*id, *content0);
	}
	else {PushError("Unimplemented block"); return 0;}
}

Ast::Node* MetaSimplifier::Arg(const Node& n) {
	ASSERT_TYPE(n, Meta::NODE_ARG);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		Recycler<NodeVec> pre(pool), pos(pool), content0(pool);
		static int pre_count = 1;
		static int pre_pos_i[] = {-1};
		static int pre_pos_type[] = {Meta::NODE_ARG_QUAL};
		static int pos_count = 1;
		static int pos_pos_i[] = {-1};
		static int pos_pos_type[] = {Meta::NODE_ARG_QUAL_OP};
		static int content0_count = 2;
		static int content0_pos_i[] = {-1, 0};
		static int content0_pos_type[] = {Meta::NODE_ARG_SPEC, -1};
		if (!Visit(n, *pre, pre_pos_i, pre_pos_type, pre_count)) return 0;
		if (!Visit(n, *pos, pos_pos_i, pos_pos_type, pos_count)) return 0;
		if (!Visit(n, *content0, content0_pos_i, content0_pos_type, content0_count)) return 0;
		return AstCallArg(*pre, *pos, *content0);
	}
	else {PushError("Unimplemented block"); return 0;}
}

Ast::Node* MetaSimplifier::Call(const Node& n) {
	ASSERT_TYPE(n, Meta::NODE_CALL);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		Recycler<NodeVec> id(pool);
		static int id_count = 3;
		static int id_pos_i[] = {0, 0, -1};
		static int id_pos_type[] = {-1, -1, -3};
		if (!Visit(n, *id, id_pos_i, id_pos_type, id_count)) return 0;
		return AstCall(*id);
	}
	else {PushError("Unimplemented block"); return 0;}
}

Ast::Node* MetaSimplifier::ArgId(const Node& n) {
	ASSERT_TYPE(n, Meta::NODE_ARG_ID);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		Recycler<NodeVec> content0(pool);
		static int content0_count = 2;
		static int content0_pos_i[] = {1, 0};
		static int content0_pos_type[] = {-1, -1};
		if (!Visit(n, *content0, content0_pos_i, content0_pos_type, content0_count)) return 0;
		return AstIdentifier(*content0);
	}
	else {PushError("Unimplemented block"); return 0;}
}

Ast::Node* MetaSimplifier::IdLit(const Node& n) {
	ASSERT_TYPE(n, Meta::NODE_ID_LIT);
	REF_BLOCK;
	if (IS_BLOCK(0)) {
		Recycler<NodeVec> content0(pool);
		static int content0_count = 1;
		static int content0_pos_i[] = {1};
		static int content0_pos_type[] = {-1};
		if (!Visit(n, *content0, content0_pos_i, content0_pos_type, content0_count)) return 0;
		return AstIdentifier(*content0);
	}
	else {PushError("Unimplemented block"); return 0;}
}

}

#endif

