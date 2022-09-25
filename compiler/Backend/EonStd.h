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
	
	
	virtual AstNode& GetRoot() = 0;
	
	void InitDefault(bool add_root=true);
	void AddBuiltinType(String name);
	void AddMetaBuiltinType(String name);
	String GetRelativePartStringArray(const AstNode& n) const;
	
	String GetPathString() const;
	AstNode* FindDeclaration(const PathIdentifier& id, SemanticType accepts=SEMT_NULL);
	AstNode* GetDeclaration(const PathIdentifier& id, SemanticType accepts=SEMT_NULL);
	AstNode* GetDeclaration(AstNode* owner, const PathIdentifier& id, SemanticType accepts);
	AstNode& Declare(AstNode& owner, const PathIdentifier& id, bool insert_before=false);
	AstNode& DeclareRelative(const PathIdentifier& id);
	//AstNode* FindTypeDeclaration(const PathIdentifier& id);
	AstNode* GetClosestType(bool skip_locked=false);
	AstNode& GetBlock();
	AstNode& GetNonLockedOwner();
	void PushScope(AstNode& n, bool non_continuous=false);
	void PushScopeRVal(AstNode& n);
	AstNode* PopScope();
	AstNode& GetTopNode() {return *spath.Top().n;}
	AstNode* FindStackObject(String name);
	AstNode* FindStackWithPrev(const AstNode* prev);
	
	String GetTypeInitValueString(AstNode& n) const;
	
	//void Bind(AstNode& from, AstNode& to);
	
	static bool ForwardUserspace(AstNode*& n);
	
};

NAMESPACE_TOPSIDE_END

#endif
