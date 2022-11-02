#ifndef _Backend_EonStd_h_
#define _Backend_EonStd_h_

NAMESPACE_TOPSIDE_BEGIN

#define CHECK_SPATH_BEGIN int exp_count = spath.GetCount();
#define CHECK_SPATH_BEGIN1 int exp_count = spath.GetCount()+ 1;
#define CHECK_SPATH_END ASSERT(spath.GetCount() == exp_count);
#define CHECK_SPATH_INIT int exp_count;
#define CHECK_SPATH_BEGIN_ exp_count = spath.GetCount();
#define CHECK_SPATH_BEGIN_1 exp_count = spath.GetCount() + 1;
#define CHECK_SPATH_END ASSERT(spath.GetCount() == exp_count);
#define CHECK_SCOPES_BEGIN int exp_count = scopes.GetCount();
#define CHECK_SCOPES_END ASSERT(scopes.GetCount() == exp_count);

class EonStd {
	
public:
	struct Scope : Moveable<Scope> {
		AstNode* n;
		bool pop_this;
		bool must_declare = false;
		bool no_declare = false;
		
		void Set(AstNode* sn, bool b) {n = sn; pop_this = b;}
	};
	Vector<Scope> spath;
	
public:
	AstNode* builtin_void = 0;
	AstNode* builtin_int = 0;
	AstNode* builtin_long = 0;
	AstNode* builtin_uint = 0;
	AstNode* builtin_ulong = 0;
	AstNode* builtin_float = 0;
	AstNode* builtin_double = 0;
	AstNode* builtin_byte = 0;
	AstNode* builtin_char = 0;
	AstNode* builtin_short = 0;
	AstNode* builtin_ushort = 0;
	AstNode* builtin_cstring = 0;
	AstNode* meta_builtin_void = 0;
	AstNode* meta_builtin_int = 0;
	AstNode* meta_builtin_double = 0;
	AstNode* meta_builtin_cstring = 0;
	AstNode* meta_builtin_stmt = 0;
	AstNode* meta_builtin_machstmt = 0;
	AstNode* meta_builtin_chainstmt = 0;
	AstNode* meta_builtin_loopstmt = 0;
	AstNode* meta_builtin_atomstmt = 0;
	AstNode* meta_builtin_worldstmt = 0;
	AstNode* meta_builtin_systemstmt = 0;
	AstNode* meta_builtin_poolstmt = 0;
	AstNode* meta_builtin_entitystmt = 0;
	AstNode* meta_builtin_compstmt = 0;
	AstNode* meta_builtin_params = 0;
	AstNode* meta_builtin_expr = 0;
	
	
	virtual AstNode& GetRoot() = 0;
	
	void InitDefault(bool add_root=true);
	AstNode* AddBuiltinType(String name);
	AstNode* AddMetaBuiltinType(String name);
	String GetRelativePartStringArray(const AstNode& n) const;
	
	String GetPathString() const;
	AstNode* FindDeclaration(const PathIdentifier& id, SemanticType accepts=SEMT_NULL);
	AstNode* FindDeclaration(const Vector<String>& id, SemanticType accepts=SEMT_NULL);
	AstNode* GetDeclaration(const PathIdentifier& id, SemanticType accepts=SEMT_NULL);
	AstNode* GetDeclaration(AstNode* owner, const Vector<String>& id, SemanticType accepts);
	AstNode* GetDeclaration(AstNode* owner, const PathIdentifier& id, SemanticType accepts);
	AstNode& Declare(AstNode& owner, const PathIdentifier& id, bool insert_before=false);
	AstNode& DeclareRelative(const PathIdentifier& id);
	AstNode* GetClosestType(bool skip_locked=false);
	AstNode& GetBlock();
	AstNode& GetNonLockedOwner();
	void PushScope(AstNode& n, bool non_continuous=false);
	void PushScopeRVal(AstNode& n);
	AstNode* PopScope();
	AstNode& GetTopNode() {return *spath.Top().n;}
	AstNode* FindStackName(String name, SemanticType accepts=SEMT_NULL);
	AstNode* FindStackObject(String name);
	AstNode* FindStackWithPrev(const AstNode* prev);
	AstNode* FindStackWithPrevDeep(const AstNode* prev);
	
	String GetTypeInitValueString(AstNode& n) const;
	
	
	static bool ForwardUserspace(AstNode*& n);
	
};

NAMESPACE_TOPSIDE_END

#endif
