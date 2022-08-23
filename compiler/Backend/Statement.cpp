#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN


Statement& Statement::Add() {
	ASSERT(type == BLOCK);
	auto& s = stmts.Add();
	s.SetOwner(this);
	return s;
}

Expression&	Statement::RealizeExpression() {
	ASSERT(type == STMT);
	if (expr.IsEmpty())
		expr.Create();
	return *expr;
}

String Statement::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << ToString() << "\n";
	for (const Statement& o : stmts) {
		s << o.GetTreeString(indent+1);
	}
	if (expr)
		s << expr->GetTreeString(indent+1);
	return s;
}

String Statement::ToString() const {
	String s;
	s << "Statement";
	return s;
}

String Statement::GetCodeString(const CodeArgs& args) const {
	//if (!IsContained(args))
	//	return String();
	
	String s;
	
	if (args.have_header) {
		
	}
	
	if (args.have_impl) {
		
		if (type == BLOCK) {
			CodeArgs subargs = args;
			subargs.indent++;
			
			s.Cat('\t', args.indent); s << "{\n";
			for (Statement& stmt : stmts) {
				s << stmt.GetCodeString(subargs);
			}
			s.Cat('\t', args.indent); s << "}\n";
		}
		
		else if (type == STMT) {
			s.Cat('\t', args.indent);
			if (expr)
				s << expr->GetCodeString(args) << ";";
			s << "\n";
		}
		
	}
	
	return s;
}















UsingStatement::UsingStatement() {
	Expression& e = expr.Create();
	e.SetOwner(this);
}

String UsingStatement::GetTreeString(int indent) const {
	String s;
	s.Cat('\t', indent);
	s << name << "\n";
	if (expr)
		s << expr->GetTreeString(indent+1);
	return s;
}

String UsingStatement::ToString() const {
	String s;
	s << "UsingStatement: " << name;
	return s;
}

String UsingStatement::GetCodeString(const CodeArgs& args) const {
	//if (!IsContained(args))
	//	return String();
	
	String s;
	
	if (!IsContained(args))
		return s;
	
	if (args.have_header) {
		s << MetaConditional::PreCodeString(args);
		
		s.Cat('\t', args.indent);
		s << "using " << name << " = ";
		if (expr)
			s << expr->GetCodeString(args);
		s << ";\n";
		s << MetaConditional::PostCodeString(args);
		s << "\n";
	}
	
	if (args.have_impl) {
		/*s << MetaConditional::PreCodeString(args);
		
		s << MetaConditional::PostCodeString(args);*/
	}
	
	return s;
}



NAMESPACE_TOPSIDE_END
