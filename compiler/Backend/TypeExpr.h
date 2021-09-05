#ifndef _Backend_TypeExpr_h_
#define _Backend_TypeExpr_h_

NAMESPACE_TOPSIDE_BEGIN

class ClassDecl;


class TypeExpr {
public:
	typedef enum {
		EMPTY,
		VOID,
		MOVE,
		REFERENCE,
		PTR,
		STATIC_CALL,
		OBJECT_CALL,
		
	} Type;
	
	Array<TypeExpr>		sub;
	TypeExpr*			global_ptr = 0;
	ClassDecl*			clsdecl = 0;
	Type				type = EMPTY;
	
public:
	TypeExpr() {}
	TypeExpr(const TypeExpr& o) {*this = o;}
	
	
	void		Clear();
	TypeExpr&	SetMove(ClassDecl& cdecl);
	TypeExpr&	SetReference(ClassDecl& cdecl);
	TypeExpr&	SetVoid();
	
	String		ToString() const;
	bool		IsEmpty() const {return type == EMPTY;}
	bool		IsActivated() const {return global_ptr != 0;}
	
	TypeExpr&	operator=(const TypeExpr& o);
	
};


NAMESPACE_TOPSIDE_END

#endif
