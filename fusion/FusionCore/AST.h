#ifndef AST_HDR
#define AST_HDR

NAMESPACE_FUSION_BEGIN

// Type-erasure
template <typename T>
static inline void Destroyer(void *self) {
    ((T*)self)->~T();
    free(self);
}

struct Memory : Moveable<Memory> {
    void *data;
    void (*dtor)(void*);
    
    Memory() : data(0), dtor(0) { }
    Memory(Memory&& m) : data(m.data), dtor(m.dtor) {m.data = 0; m.dtor = 0;}
    ~Memory() {Destroy();}
    template <typename T> Memory(T *data) : data((void*)data), dtor(&Destroyer<T>) {}
    
    template <typename T> void Set(T* data) {Destroy(); this->data = data; dtor = &Destroyer<T>;}
    
    void Destroy() {
        if (data) {
			dtor(data);
			data = 0;
        }
    }
};

// Nodes are to inherit from Node or astCollector
template <typename T>
struct Node {
    void *operator new(size_t size, Vector<Memory> *collector) THROW_SPECIFIER {
        void *data = malloc(size);
        if (data)
            collector->Add().Set((T*)data);
        return data;
    }
    void operator delete(void *);
private:
    void *operator new(size_t);
};


struct Function;
struct Type;
struct GlobalVariable;
struct Expression;
struct LayoutQualifier;
struct Statement;
struct Struct;
struct Variable;

struct TU {
    TU(int type);

    enum {
        kCompute,
        kVertex,
        kTessControl,
        kTessEvaluation,
        kGeometry,
        kFragment
    };

    Vector<Function*> functions;
    Vector<GlobalVariable*> globals;
    Vector<Struct*> structures;

    int type;

private:
    TU(const TU&);
    TU &operator=(const TU&);
};

struct Type : Node<Type> {
    Type(bool builtin);
    bool builtin;
};

struct Builtin : Type {
    Builtin(int type);
    int type; // KEYWORD_*
};

struct Struct : Type {
    Struct();
    char *name;
    Vector<Variable*> fields;
};

typedef Expression ConstantExpression;

enum {
    HIGH_PRECISION,
    MEDIUM_PRECISION,
    LOW_PRECISION
};

struct Variable : Node<Variable> {
    enum {
        FUNCTION,
        PARAMETER,
        GLOBAL,
        FIELD
    };
    Variable(int type);
    
    char *name;
    Type *base_type;
    bool is_array;
    bool is_precise;
    int type;
    Vector<ConstantExpression *> array_sizes;
};

struct FunctionVariable : Variable {
    FunctionVariable();
    
    bool is_const;
    Expression *initial_value;
};

// Storage qualifiers
enum {
    QUAL_CONST,
    QUAL_IN,
    QUAL_OUT,
    QUAL_INOUT,
    QUAL_ATTR,
    QUAL_UNIFORM,
    QUAL_VARYING,
    QUAL_BUFFER,
    QUAL_SHARED
};

// Auxiliary storage qualifiers
enum {
    AUX_CENTROID,
    AUX_SAMPLE,
    AUX_PATCH,
};

// Memory qualifiers
enum {
    MEM_COHERENT = 1 << 0,
    MEM_VOLATILE = 1 << 1,
    MEM_RESTRICT = 1 << 2,
    MEM_READONLY = 1 << 3,
    MEM_WRITEONLY = 1 << 4
};

struct FunctionParameter : Variable {
    FunctionParameter();
    int storage; // in or out only
    int auxiliary;
    int memory;
    int precision;
};

enum {
    IPOL_SMOOTH,
    IPOL_FLAT,
    IPOL_NO_PERSPECTIVE
};

struct GlobalVariable : Variable {
    GlobalVariable();
    
    int storage;
    int auxiliary;
    int memory;
    int precision;
    int interpolation;
    bool is_invariant;
    ConstantExpression *initial_value;
    Vector<LayoutQualifier*> layout_qualifiers;
};

struct LayoutQualifier : Node<LayoutQualifier> {
    LayoutQualifier();
    
    char *name;
    ConstantExpression *initial_value;
};

struct Function : Node<Function> {
    Function();
    
    Type *return_type;
    char *name;
    Vector<FunctionParameter*> parameters;
    Vector<Statement*> statements;
    bool is_prototype;
};

struct Declaration : Node<Declaration> {
    Declaration();
    
    Variable *variable;
};

struct Statement : Node<Statement> {
    Statement(int type);
    enum {
        STMT_COMPOUND,
        STMT_EMPTY,
        STMT_DECLARATION,
        STMT_EXPR,
        STMT_IF,
        STMT_SWITCH,
        STMT_CASE_LABEL,
        STMT_WHILE,
        STMT_DO,
        STMT_FOR,
        STMT_CONTINUE,
        STMT_BREAK,
        STMT_RETURN,
        STMT_DISCARD
    };
    int type;
    
    const char *GetName() const;
};

struct SimpleStatement : Statement {
    SimpleStatement(int type);
};

struct CompoundStatement : Statement {
    CompoundStatement();
    Vector<Statement*> statements;
};

struct EmptyStatement : SimpleStatement {
    EmptyStatement();
};

struct DeclarationStatement : SimpleStatement {
    DeclarationStatement();
    Vector<FunctionVariable*> variables;
};

struct ExpressionStatement : SimpleStatement {
    ExpressionStatement(Expression *expression);
    Expression *expression;
};

struct IfStatement : SimpleStatement {
    IfStatement();
    Expression *condition;
    Statement *thenStatement;
    Statement *elseStatement;
};

struct SwitchStatement : SimpleStatement {
    SwitchStatement();
    Expression *expression;
    Vector<Statement*> statements;
};

struct CaseLabelStatement : SimpleStatement {
    CaseLabelStatement();
    ConstantExpression *condition;
    bool isDefault;
};

struct IterationStatement : SimpleStatement {
    IterationStatement(int type);
};

struct WhileStatement : IterationStatement {
    WhileStatement();
    SimpleStatement *condition; // ExpressionStatement or DeclarationStatement only
    Statement *body;
};

struct DoStatement : IterationStatement {
    DoStatement();
    Statement *body;
    Expression *condition;
};

struct ForStatement : IterationStatement {
    ForStatement();
    SimpleStatement *init; // ExpressionStatement or DeclarationStatement only
    Expression *condition;
    Expression *loop;
    Statement *body;
};

struct JumpStatement : Statement {
    JumpStatement(int type);
};

struct ContinueStatement : JumpStatement {
    ContinueStatement();
};

struct BreakStatement : JumpStatement {
    BreakStatement();
};

struct ReturnStatement : JumpStatement {
    ReturnStatement();
    Expression *expression;
};

struct DiscardStatement : JumpStatement {
    DiscardStatement();
};

struct Expression : Node<Expression> {
    Expression(int type);
    // Base class
    enum {
        INT_CONST,
        UINT_CONST,
        FLOAT_CONST,
        DOUBLE_CONST,
        BOOL_CONST,
        VAR_ID,
        FIELD_OR_SWIZZLE,
        ARRAY_SUB,
        FUNCTION_CALL,
        CTOR_CALL,
        POST_INC,
        POST_DEC,
        UNARY_MINUS,
        UNARY_PLUS,
        BIT_NOT,
        LOGICAL_NOT,
        PRE_INC,
        PRE_DEC,
        SEQUENCE,
        ASSIGN,
        OPERATION,
        TERNARY
    };
    int type;
};

struct IntConstant : Expression {
    IntConstant(int value);
    int value;
};

struct UIntConstant : Expression {
    UIntConstant(unsigned int value);
    unsigned int value;
};

struct FloatConstant : Expression {
    FloatConstant(float value);
    float value;
};

struct DoubleConstant : Expression {
    DoubleConstant(double value);
    double value;
};

struct BoolConstant : Expression {
    BoolConstant(bool value);
    bool value;
};

struct VariableIdentifier : Expression {
    VariableIdentifier(Variable *variable);
    Variable *variable;
};

struct FieldOrSwizzle : Expression {
    FieldOrSwizzle();
    Expression *operand;
    char *name;
};

struct ArraySubscript : Expression {
    ArraySubscript();
    Expression *operand;
    Expression *index;
};

struct FunctionCall : Expression {
    FunctionCall();
    char *name;
    Vector<Expression*> parameters;
};

struct ConstructorCall : Expression {
    ConstructorCall();
    Type *type;
    Vector<Expression*> parameters;
};

struct UnaryExpression : Expression {
    // Base class
    UnaryExpression(int type, Expression *operand);
    Expression *operand;
};

struct BinaryExpression : Expression {
    // Base class
    BinaryExpression(int type);
    Expression *operand1;
    Expression *operand2;
};

struct PostIncrementExpression : UnaryExpression {
    PostIncrementExpression(Expression *operand);
};

struct PostDecrementExpression : UnaryExpression {
    PostDecrementExpression(Expression *operand);
};

struct UnaryPlusExpression : UnaryExpression {
    UnaryPlusExpression(Expression *operand);
};

struct UnaryMinusExpression : UnaryExpression {
    UnaryMinusExpression(Expression *operand);
};

struct UnaryBitNotExpression : UnaryExpression {
    UnaryBitNotExpression(Expression *operand);
};

struct UnaryLogicalNotExpression : UnaryExpression {
    UnaryLogicalNotExpression(Expression *operand);
};

struct PrefixIncrementExpression : UnaryExpression {
    PrefixIncrementExpression(Expression *operand);
};

struct PrefixDecrementExpression : UnaryExpression {
    PrefixDecrementExpression(Expression *operand);
};

struct SequenceExpression : BinaryExpression {
    SequenceExpression();
};

struct AssignmentExpression : BinaryExpression {
    AssignmentExpression(int assignment);
    int assignment;
};

struct OperationExpression : BinaryExpression {
    OperationExpression(int operation);
    int operation;
};

struct TernaryExpression : Expression {
    TernaryExpression();
    Expression *condition;
    Expression *on_true;
    Expression *on_false;
};

NAMESPACE_FUSION_END

#endif
