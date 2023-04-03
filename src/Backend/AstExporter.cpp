#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstExporter::AstExporter() :
	ErrorSource("AstExporter")
{
	
}

bool AstExporter::Process(const AstNode& n) {
	output.Clear();
	PushScope(n);
	Visit(n);
	PopScope();
	
	return true;
}

String AstExporter::GetIndentString(int offset) const {
	ASSERT(indent >= 0);
	ASSERT(!inline_mode);
	String s;
	s.Cat('\t', max(0, indent + offset));
	return s;
}

void AstExporter::PushScope(const AstNode& n, bool skip_indent) {
	Scope& scope = scopes.Add();
	scope.pop_this = !n.IsPartially(SEMT_UNDEFINED);
	scope.n = &n;
	scope.skip_indent = skip_indent;
	if (n.src == SEMT_STATEMENT_BLOCK && !skip_indent)
		++indent;
}

void AstExporter::PopScope() {
	Scope& scope = scopes.Top();
	if (scope.n->src == SEMT_STATEMENT_BLOCK && !scope.skip_indent) {
		ASSERT(indent > 0);
		--indent;
	}
	scopes.SetCount(scopes.GetCount()-1);
}

void AstExporter::PushInlineScope() {
	InlineScope& is = inline_scopes.Add();
	
}

void AstExporter::PopInlineScope() {
	ASSERT(!inline_scopes.IsEmpty());
	inline_scopes.SetCount(inline_scopes.GetCount()-1);
}

void AstExporter::Visit(const AstNode& n, bool force, bool declare) {
	
	switch (n.src) {
	case SEMT_BUILTIN:
		if (force) {
			VisitBuiltin(n);
			return;
		}
	case SEMT_FUNCTION_BUILTIN:
	case SEMT_META_BUILTIN:
	case SEMT_META_FUNCTION_STATIC:
	case SEMT_META_RVAL:
	case SEMT_META_PARAMETER:
	case SEMT_LOOP:
	case SEMT_CHAIN:
	case SEMT_ATOM:
	case SEMT_MACHINE:
	case SEMT_WORLD:
	case SEMT_SYSTEM:
	case SEMT_POOL:
	case SEMT_ENTITY:
	case SEMT_COMPONENT:
		return;
	
	case SEMT_META_RESOLVE:
		ASSERT(n.rval);
		if (n.rval)
			Visit(*n.rval);
		return;
		
	case SEMT_ROOT:
	case SEMT_IDPART:
		for (const AstNode& s : n.sub) {
			if (s.src == SEMT_RVAL)
				continue;
			
			CHECK_SCOPES_BEGIN
			
			PushScope(s);
			Visit(s, false, true);
			PopScope();
			
			CHECK_SCOPES_END
		}
		return;
		
	case SEMT_STATEMENT_BLOCK:
		for (const AstNode& s : n.sub) {
			if (s.src != SEMT_STATEMENT &&
				s.src != SEMT_STATEMENT_BLOCK &&
				!s.IsPartially(SEMT_META_ANY))
				continue;
			
			// merge statement blocks which meta created with current block
			if (s.src == SEMT_STATEMENT_BLOCK && s.i64 == 1) {
				Visit(s, false, true);
				continue;
			}
			
			CHECK_SCOPES_BEGIN
			
			PushScope(s);
			Visit(s, false, true);
			PopScope();
			
			CHECK_SCOPES_END
		}
		return;
	
	case SEMT_FUNCTION_STATIC:
		VisitFunction(n);
		break;
	
	case SEMT_PARAMETER:
		VisitParameter(n);
		break;
	
	case SEMT_STATEMENT:
		VisitStatement(n);
		break;
		
	case SEMT_EXPR:
		VisitExpression(n, 0);
		break;
		
	case SEMT_CONSTANT:
		VisitConstant(n);
		break;
	
	case SEMT_VARIABLE:
		VisitVariable(n, declare);
		break;
	
	case SEMT_META_VARIABLE:
		ASSERT_(0, "meta code should be executed before this, and non-existent here");
		break;
	
	case SEMT_ARGUMENT:
		VisitArgument(n);
		break;
		
	case SEMT_RESOLVE:
		VisitResolve(n, true);
		break;
	
	case SEMT_RVAL:
		VisitRval(n);
		break;
	
	case SEMT_NULL:
	case SEMT_NAMESPACE:
	case SEMT_TYPEDEF:
	case SEMT_CLASS_DECL:
	case SEMT_CLASS:
	case SEMT_CLASS_TEMPLATE:
	case SEMT_FUNCTION_METHOD:
		TODO
		break;
		
	case SEMT_ARGUMENT_LIST:
		VisitArgumentList(n);
		break;
		
	case SEMT_CTOR:
		VisitConstructor(n);
		break;
		
	case SEMT_ARRAYSIZE:
		VisitArraySize(n);
		break;
		
	case SEMT_OBJECT:
		break;
		
	default:
		TODO
	}
	
}

void AstExporter::Visit(const AstNode& n, SemanticType t) {
	for(const AstNode& sub : n.sub) {
		if (sub.IsPartially(t)) {
			PushScope(sub);
			Visit(sub);
			PopScope();
		}
	}
}

void AstExporter::VisitStmt(const AstNode& n, StmtType t) {
	for(const AstNode& sub : n.sub) {
		if (sub.src == SEMT_STATEMENT && sub.stmt == t) {
			PushScope(sub);
			Visit(sub);
			PopScope();
		}
	}
}

void AstExporter::VisitCtorExpr(const AstNode& n) {
	for(const AstNode& sub : n.sub) {
		if (sub.src == SEMT_CTOR || (sub.src == SEMT_STATEMENT && sub.stmt == STMT_EXPR)) {
			PushScope(sub);
			Visit(sub);
			PopScope();
		}
	}
}

void AstExporter::VisitBuiltin(const AstNode& n) {
	output << GetCPath(n);
}

void AstExporter::VisitFunction(const AstNode& n) {
	ASSERT(n.src == SEMT_FUNCTION_STATIC);
	
	output << GetIndentString();
	
	if (n.type) {
		Visit(*n.type, true);
		output << " ";
	}
	
	output << GetCPath();
	
	PushInlineScope();
	output << "(";
	Visit(n, SEMT_PARAMETER_PATH);
	output << ")";
	PopInlineScope();
	
	const AstNode* block = n.Find(SEMT_STATEMENT_BLOCK);
	if (!block) {
		output << ";\n";
	}
	else {
		output << " {\n";
		Visit(n, SEMT_STATEMENT_BLOCK);
		output << GetIndentString() << "}\n";
	}
}

void AstExporter::VisitParameter(const AstNode& n) {
	ASSERT(inline_scopes.GetCount());
	InlineScope& is = inline_scopes.Top();
	
	if (is.count)
		output << ", ";
	
	if (n.type)
		output << GetCPath(*n.type) << " ";
	
	output << GetCPath(n);
	
	is.count++;
}

void AstExporter::VisitStatement(const AstNode& n) {
	AstNode* p = 0;
	
	switch (n.stmt) {
	case STMT_NULL:
		break;
		
	case STMT_FOR:
		ASSERT(inline_scopes.IsEmpty());
		PushInlineScope();
		output << GetIndentString() << "for (";
		VisitCtorExpr(n);
		output << "; ";
		VisitStmt(n, STMT_FOR_COND);
		output << "; ";
		VisitStmt(n, STMT_FOR_POST);
		output << ") {\n";
		PopInlineScope();
		Visit(n, SEMT_STATEMENT_BLOCK);
		output << GetIndentString() << "}\n";
		break;
		
	case STMT_IF:
		ASSERT(inline_scopes.IsEmpty());
		PushInlineScope();
		output << GetIndentString() << "if (";
		Visit(n, SEMT_EXPR);
		output << ") {\n";
		PopInlineScope();
		Visit(n, SEMT_STATEMENT_BLOCK);
		output << GetIndentString() << "}\n";
		break;
		
	case STMT_ELSE:
		ASSERT(inline_scopes.IsEmpty());
		PushInlineScope();
		output << GetIndentString() << "else {\n";
		PopInlineScope();
		Visit(n, SEMT_STATEMENT_BLOCK);
		output << GetIndentString() << "}\n";
		break;
		
	case STMT_FOR_COND:
	case STMT_FOR_POST:
		Visit(n, SEMT_EXPR);
		break;
		
	case STMT_EXPR:
		output << GetIndentString() << "";
		for (int i = n.sub.GetCount()-1; i >= 0; i--) {
			const AstNode& s = n.sub[i];
			if (s.IsPartially((SemanticType)(SEMT_EXPR | SEMT_CTOR))) {
				Visit(s);
				break;
			}
		}
		output << ";\n";
		break;
	
	case STMT_RETURN:
		output << GetIndentString() << "return";
		if (n.rval) {
			const AstNode& s = *n.rval;
			if (IsRvalReturn(s.src)) {
				output << " ";
				Visit(s);
			}
		}
		output << ";\n";
		break;
	
	case STMT_CTOR:
		if (!n.rval)
			break;
		output << GetIndentString();
		VisitConstructor(*n.rval);
		output << ";\n";
		break;
		
	case STMT_DOWHILE:
	case STMT_WHILE:
	case STMT_FOR_RANGE:
	case STMT_BREAK:
	case STMT_CONTINUE:
	case STMT_CASE:
	case STMT_DEFAULT:
	case STMT_SWITCH:
	case STMT_BLOCK:
	default:
		TODO
		break;
	}
}

void AstExporter::VisitExpression(const AstNode& n, int depth) {
	if (n.src == SEMT_VARIABLE || n.src == SEMT_PARAMETER) {
		VisitVariable(n);
		return;
	}
	else if (n.src == SEMT_CONSTANT || n.src == SEMT_OBJECT) {
		VisitConstant(n);
		return;
	}
	else if (n.src == SEMT_RESOLVE) {
		VisitResolve(n);
		return;
	}
	else if (n.src == SEMT_RVAL) {
		VisitRval(n);
		return;
	}
	else if (n.src == SEMT_ARGUMENT_LIST) {
		VisitArgumentList(n);
		return;
	}
	else if (n.IsPartially(SEMT_FUNCTION)) {
		VisitFunctionRval(n);
		return;
	}
	else if (n.src == SEMT_META_RVAL) {
		LOG(n.GetTreeString(0));
		TODO
	}
	
	ASSERT(n.src == SEMT_EXPR && n.op != OP_NULL);
	
	if (depth > 0)
		output << "(";
	
	switch (n.op) {
	case OP_NULL:
		break;
		
	case OP_INC:
	case OP_DEC:
	case OP_NEGATIVE:
	case OP_POSITIVE:
	case OP_NOT:
	case OP_NEGATE:
		ASSERT(n.arg[0]);
		output << GetOpCodeString(n.op);
		VisitExpression(*n.arg[0], depth+1);
		break;
		
	case OP_POSTINC:
	case OP_POSTDEC:
		ASSERT(n.arg[0]);
		VisitExpression(*n.arg[0], depth+1);
		output << GetOpCodeString(n.op);
		break;
	
	case OP_ADD:
	case OP_SUB:
	case OP_MUL:
	case OP_DIV:
	case OP_MOD:
	case OP_LSH:
	case OP_RSH:
	case OP_GREQ:
	case OP_LSEQ:
	case OP_GREATER:
	case OP_LESS:
	case OP_EQ:
	case OP_INEQ:
	case OP_BWAND:
	case OP_BWXOR:
	case OP_BWOR:
	case OP_AND:
	case OP_OR:
		ASSERT(n.arg[0]);
		ASSERT(n.arg[1]);
		VisitExpression(*n.arg[0], depth+1);
		output << " " << GetOpCodeString(n.op) << " ";
		VisitExpression(*n.arg[1], depth+1);
		break;
		
	case OP_ASSIGN:
	case OP_ADDASS:
	case OP_SUBASS:
	case OP_MULASS:
	case OP_DIVASS:
	case OP_MODASS:
		ASSERT(n.arg[0]);
		ASSERT(n.arg[1]);
		VisitExpression(*n.arg[0], depth);
		output << " " << GetOpCodeString(n.op) << " ";
		VisitExpression(*n.arg[1], depth);
		break;
		
	case OP_COND:
		ASSERT(n.arg[0]);
		ASSERT(n.arg[1]);
		ASSERT(n.arg[2]);
		output << "(";
		VisitExpression(*n.arg[0], depth+1);
		output << ") ? (";
		VisitExpression(*n.arg[1], depth+1);
		output << ") : (";
		VisitExpression(*n.arg[2], depth+1);
		output << ")";
		break;
		
	case OP_CALL:
		ASSERT(n.arg[0]);
		ASSERT(n.arg[1]);
		VisitExpression(*n.arg[0], depth+1);
		VisitExpression(*n.arg[1], depth+1);
		break;
		
	case OP_SUBSCRIPT:
		ASSERT(n.arg[0]);
		ASSERT(n.arg[1]);
		VisitExpression(*n.arg[0], depth+1);
		output << "[";
		VisitExpression(*n.arg[1], depth+1);
		output << "]";
		break;
		
	default:
		TODO
	}
	
	if (depth > 0)
		output << ")";
	
}

void AstExporter::VisitVariable(const AstNode& n, bool declare) {
	ASSERT(n.src == SEMT_VARIABLE || n.src == SEMT_PARAMETER);
	
	if (declare) {
		if (n.type) {
			// use ctor instead
				//output << GetIndentString() << GetCPath(*n.type) << " " << GetCPath(n) << ";\n";
		}
	}
	else {
		output << GetCPath(n);
	}
	
}

void AstExporter::VisitArgument(const AstNode& n) {
	ASSERT(n.src == SEMT_ARGUMENT);
	
	ASSERT(n.rval);
	const AstNode& arg = *n.rval;
	
	InlineScope& is = inline_scopes.Top();
	if (is.count)
		output << ", ";
	
	if (arg.src == SEMT_CONSTANT) {
		VisitConstant(arg);
	}
	else if (arg.IsPartially(SEMT_FIELD)) {
		output << GetCPath(arg);
	}
	else if (arg.src == SEMT_RVAL) {
		VisitRval(arg);
	}
	else if (arg.src == SEMT_EXPR) {
		VisitExpression(arg, 0);
	}
	else {
		TODO
	}
	
	is.count++;
}

void AstExporter::VisitConstant(const AstNode& n) {
	ASSERT(n.src == SEMT_CONSTANT || n.src == SEMT_OBJECT);
	
	if (n.src == SEMT_CONSTANT) {
		switch (n.con) {
		case CONST_NULL:	output << "void"; break;
		case CONST_BOOL:	output << (n.i64 ? "true" : "false"); break;
		case CONST_INT32:	output << IntStr((int)n.i64); break;
		case CONST_INT64:	output << IntStr64(n.i64); break;
		case CONST_DOUBLE:	output << DblStr(n.dbl); break;
		case CONST_STRING:	output << "\"" << n.str << "\""; break;
		default:
			TODO
			output << "<internal error>";
			break;
		}
	}
	else if (n.src == SEMT_OBJECT) {
		output << n.obj.ToString();
	}
}

void AstExporter::VisitResolve(const AstNode& n, bool rval) {
	ASSERT(n.rval);
	if (n.rval) {
		const AstNode& l = *n.rval;
		if (l.IsPartially(SEMT_META_FUNCTION)) {
			output << "<error>";
		}
		else {
			if (l.IsPartially(SEMT_FUNCTION)) {
				DUMP(GetSemanticTypeString(l.src));
			}
			output << GetCPath(l);
		}
	}
}

void AstExporter::VisitRval(const AstNode& n) {
	ASSERT(n.rval);
	ASSERT(n.rval != &n);
	if (n.rval) {
		AstNode& s = *n.rval;
		if (s.src == SEMT_CONSTANT || s.src == SEMT_OBJECT)
			VisitConstant(s);
		else if (s.IsPartially(SEMT_FIELD))
			output << GetCPath(*n.rval);
		else if (s.src == SEMT_META_PARAMETER || s.src == SEMT_META_VARIABLE) {
			TODO // this s.src shouldn't appear in this phase anymore
		}
		else
			Visit(*n.rval);
	}
	else {
		AddError(n.loc, "internal error: expected link");
	}
}

void AstExporter::VisitArgumentList(const AstNode& n) {
	PushInlineScope();
	output << "(";
	Visit(n, SEMT_ARGUMENT);
	output << ")";
	PopInlineScope();
}

void AstExporter::VisitFunctionRval(const AstNode& n) {
	output << GetCPath(n);
}

void AstExporter::VisitConstructor(const AstNode& n) {
	ASSERT(n.src == SEMT_CTOR);
	
	if (n.type) {
		output << GetCPath(*n.type) << " ";
	}
	
	if (n.rval)
		output << GetCPath(*n.rval);
	
	ASSERT(n.arg[0]);
	for(int i = 0; i < AstNode::ARG_COUNT; i++) {
		if (n.arg[i])
			Visit(*n.arg[i]);
	}
}

void AstExporter::VisitArraySize(const AstNode& n) {
	output << "[";
	ASSERT(n.rval);
	Visit(*n.rval);
	output << "]";
}

String AstExporter::GetCPath() const {
	int c = scopes.GetCount();
	int begin = c-1;
	for(int i = c-2; i >= 0; i--) {
		const Scope& scope = scopes[i];
		if (scope.pop_this)
			break;
		begin = i;
	}
	String s;
	for(int i = begin, j = 0; i < c; i++, j++) {
		const Scope& scope = scopes[i];
		if (j) s.Cat('_');
		s.Cat(scope.n->name);
	}
	return s;
}

String AstExporter::GetCPath(const AstNode& n) const {
	int c = scopes.GetCount();
	int common_i = -1;
	const AstNode* parts[PathIdentifier::MAX_PARTS];
	int part_count = 0;
	for(int i = 0; i < c && common_i < 0; i++) {
		int j = c-1-i;
		const Scope& scope = scopes[j];
		const AstNode* iter = &n;
		part_count = 0;
		while (iter) {
			if (iter == scope.n) {
				common_i = j;
				break;
			}
			parts[part_count++] = iter;
			iter = iter->GetSubOwner();
		}
	}
	if (common_i < 0) {
		TODO
	}
	else {
		String s;
		if (!part_count) {
			String name = n.name;
			ASSERT(name.GetCount());
			s.Cat(name);
		}
		else {
			for (int i = 0; i < part_count; i++) {
				const AstNode* part = parts[part_count - 1 -i];
				if (part->src == SEMT_TYPE_POINTER)
					s.Cat('*');
				else if (part->src == SEMT_TYPE_LREF)
					s.Cat('&');
				else {
					if (i) s.Cat('_');
					s.Cat(part->name);
				}
			}
		}
		return s;
	}
}





void InitHighExporter(AstExporterLanguage& l) {
	
}

void InitCppExporter(AstExporterLanguage& l) {
	
}



NAMESPACE_TOPSIDE_END
