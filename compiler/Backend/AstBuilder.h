#ifndef _Backend_AstBuilder_h_
#define _Backend_AstBuilder_h_

NAMESPACE_TOPSIDE_BEGIN


class AstBuilder :
	public EonStd,
	public ParserEmitter,
	public ErrorSource
{
	
	
	
public:
	Vector<Token> tokens[5];
	Index<String> files;
	//CompilationUnit cunit;
	AstNode root;
	
	void LoadLocation(const HiValue& v, FileLocation& loc);
	void LoadPath(const FileLocation& loc, const HiValue& v, PathIdentifier& id, Vector<Token>& tokens);
	
public:
	typedef AstBuilder CLASSNAME;
	AstBuilder();
	
	AstNode& GetRoot() override {return root;}
	void Clear();
	
	#include "ParserOverrides.inl"
	
	void PushRvalConstant(const FileLocation& loc, int32 v);
	void PushRvalConstant(const FileLocation& loc, int64 v);
	void PushRvalConstant(const FileLocation& loc, double v);
	void PushRvalConstant(const FileLocation& loc, String v);
	
	void HiAddFile(HiEscape& e);
	void HiPushFunction(HiEscape& e);
	void HiPushMetaFunction(HiEscape& e);
	void HiParameter(HiEscape& e);
	void HiMetaParameter(HiEscape& e);
	//void HiPushFunctionDefinition(HiEscape& e);
	void HiPopFunctionDefinition(HiEscape& e);
	void HiPopFunction(HiEscape& e);
	void HiPopMetaFunction(HiEscape& e);
	void HiPushStatementList(HiEscape& e);
	void HiPopStatementList(HiEscape& e);
	void HiPushStatement(HiEscape& e);
	void HiPopStatement(HiEscape& e);
	void HiPushStatementParameter(HiEscape& e);
	void HiPopStatementParameter(HiEscape& e);
	void HiDeclareVariable(HiEscape& e);
	void HiDeclareMetaVariable(HiEscape& e);
	void HiVariable(HiEscape& e);
	void HiPushRvalResolve(HiEscape& e);
	void HiPushRvalUnresolved(HiEscape& e);
	void HiPushRvalArgumentList(HiEscape& e);
	void HiArgument(HiEscape& e);
	//void HiPopExprScopeToCtor(HiEscape& e);
	void HiPopExpr(HiEscape& e);
	void HiPushRval(HiEscape& e);
	//void HiPushRvalCall(HiEscape& e);
	void HiPushRvalConstruct(HiEscape& e);
	void HiPushRvalConstant(HiEscape& e);
	void HiExpr1(HiEscape& e);
	void HiExpr2(HiEscape& e);
	void HiExpr3(HiEscape& e);
	void HiPushSystem(HiEscape& e);
	void HiPopSystem(HiEscape& e);
	void HiPushPool(HiEscape& e);
	void HiPopPool(HiEscape& e);
	void HiPushEntity(HiEscape& e);
	void HiPopEntity(HiEscape& e);
	void HiPushComponent(HiEscape& e);
	void HiPopComponent(HiEscape& e);
	void HiPushMachine(HiEscape& e);
	void HiPopMachine(HiEscape& e);
	void HiPushChain(HiEscape& e);
	void HiPopChain(HiEscape& e);
	void HiPushLoop(HiEscape& e);
	void HiPopLoop(HiEscape& e);
	void HiPushAtom(HiEscape& e);
	void HiPopAtom(HiEscape& e);
	void HiPushAtomConnector(HiEscape& e);
	void HiPopAtomConnector(HiEscape& e);
	void HiPushState(HiEscape& e);
	void HiPopState(HiEscape& e);
	void HiPushCall(HiEscape& e);
	void HiPopCall(HiEscape& e);
	void HiPopExprCallArgument(HiEscape& e);
	
	bool Execute(String high_script_content);
	
};


NAMESPACE_TOPSIDE_END

#endif
