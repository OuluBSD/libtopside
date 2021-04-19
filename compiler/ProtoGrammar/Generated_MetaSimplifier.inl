Ast::Node* VisitNode(const Node& n);

Ast::Node* FileInput(const Node& n);
Ast::Node* ExprStmt(const Node& n);
Ast::Node* CallWithArgs(const Node& n);
Ast::Node* Arg(const Node& n);
Ast::Node* Call(const Node& n);
Ast::Node* ArgId(const Node& n);
Ast::Node* IdLit(const Node& n);
