#ifndef _Backend_Field_h_
#define _Backend_Field_h_


NAMESPACE_TOPSIDE_BEGIN


class Field : public CompilerNode<Field,Class> {
public:
	One<Expression>		ctor;
	Class*				cls = 0;
	CodeAccess			access = ACC_PUBLIC;
	String				name;
	
public:
	typedef Field CLASSNAME;
	Field() {}
	
	String		GetTreeString(int indent=0) const override;
	String		GetCodeString(const CodeArgs& args) const override;
	String		ToString() const override;
	
};


NAMESPACE_TOPSIDE_END


#endif
