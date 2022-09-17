#ifndef _Backend_AstBuilder_h_
#define _Backend_AstBuilder_h_

#if 0

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
	RunningFlag flag;
	bool fail = false;
	
	void LoadLocation(const HiValue& v, FileLocation& loc);
	void LoadPath(const FileLocation& loc, const HiValue& v, PathIdentifier& id, Vector<Token>& tokens);
	
public:
	typedef AstBuilder CLASSNAME;
	AstBuilder();
	
	AstNode& GetRoot() override {return root;}
	void Clear();
	
	#include "ParserOverrides.inl"
	
	
	
	
	void AddError(const FileLocation& loc, String msg);
};


NAMESPACE_TOPSIDE_END

#endif
#endif
