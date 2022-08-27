#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AstExporter::AstExporter() :
	ErrorSource("AstExporter")
{
	
}

bool AstExporter::Process(const AstNode& n) {
	output.Clear();
	
	Visit(n);
	
	return true;
}

void AstExporter::Visit(const AstNode& n) {
	
	switch (n.src) {
		case SEMT_BUILTIN:
			return;
		
		case SEMT_ROOT:
		case SEMT_IDPART:
			for (const AstNode& s : n.sub)
				Visit(s);
			return;
		
		case SEMT_NULL:
		case SEMT_NAMESPACE:
		case SEMT_TYPEDEF:
		case SEMT_CLASS_DECL:
		case SEMT_CLASS:
		case SEMT_CLASS_TEMPLATE:
		case SEMT_METAFN_CLASS_DECL:
		case SEMT_METAFN_CLASS:
		case SEMT_FUNCTION_STATIC:
		case SEMT_FUNCTION_METHOD:
		case SEMT_VARIABLE:
		case SEMT_PARAMETER:
		case SEMT_STATEMENT:
		case SEMT_STATEMENT_BLOCK:
		case SEMT_EXPR:
		case SEMT_CONSTANT:
			TODO
			break;
			
		default:
			TODO
	}
	
}


NAMESPACE_TOPSIDE_END
