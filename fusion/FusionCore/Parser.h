#ifndef PARSE_HDR
#define PARSE_HDR

NAMESPACE_FUSION_BEGIN

#if __GNUC__ >= 4
#   define CHECK_RETURN __attribute__((warn_unused_result))
#elif _MSC_VER >= 1700
#   define CHECK_RETURN _Check_return_
#else
#   define CHECK_RETURN
#endif

struct TopLevel : Moveable<TopLevel> {
    TopLevel()
        : storage(-1)
        , auxiliary(-1)
        , memory(0)
        , precision(-1)
        , interpolation(-1)
        , type(0)
        , initial_value(0)
        , array_on_type_offset(0)
        , is_invariant(false)
        , is_precise(false)
        , is_array(false)
    {
    }
	
	TopLevel(const TopLevel& tl) {*this = tl;}
	void operator=(const TopLevel& s) {
		storage = s.storage;
	    auxiliary = s.auxiliary;
	    memory = s.memory;
	    precision = s.precision;
	    interpolation = s.interpolation;
	    type = s.type;
	    initial_value = s.initial_value;
	    array_sizes <<= s.array_sizes;
	    array_on_type_offset = s.array_on_type_offset;
	    layout_qualifiers <<= s.layout_qualifiers;
	    structures <<= s.structures;
	    is_invariant = s.is_invariant;
	    is_precise = s.is_precise;
	    is_array = s.is_array;
	    name = s.name;
	}
    int storage;
    int auxiliary;
    int memory;
    int precision;
    int interpolation;
    Type *type;
    ConstantExpression *initial_value;
    Vector<ConstantExpression*> array_sizes;
    int array_on_type_offset;
    Vector<LayoutQualifier*> layout_qualifiers;
    Vector<Struct*> structures;
    bool is_invariant;
    bool is_precise;
    bool is_array;
    char *name;
};

struct Parser {
    ~Parser();
    Parser(const char *source, const char *file_name);
    CHECK_RETURN TU *Parse(int type);

    const char *GetError() const;

protected:
    void Cleanup();

    enum {
        END_CONDITION_SEMICOLON = 1 << 0,
        END_CONDITION_PARENTHESIS = 1 << 1,
        END_CONDITION_BRACKET = 1 << 2,
        END_CONDITION_COLON = 1 << 3,
        END_CONDITION_COMMA = 1 << 4
    };

    typedef int EndCondition;

    CHECK_RETURN bool Next();

    CHECK_RETURN bool ParseStorage(TopLevel &current); // const, in, out, attribute, uniform, varying, buffer, shared
    CHECK_RETURN bool ParseAuxiliary(TopLevel &current); // centroid, sample, patch
    CHECK_RETURN bool ParseInterpolation(TopLevel &current); // smooth, flat, noperspective
    CHECK_RETURN bool ParsePrecision(TopLevel &current); // highp, mediump, lowp
    CHECK_RETURN bool ParseInvariant(TopLevel &current); // invariant
    CHECK_RETURN bool ParsePrecise(TopLevel &current); // precise
    CHECK_RETURN bool ParseMemory(TopLevel &current); // coherent, volatile, restrict, readonly, writeonly
    CHECK_RETURN bool ParseLayout(TopLevel &current);

    CHECK_RETURN bool ParseTopLevelItem(TopLevel &level, TopLevel *continuation = 0);
    CHECK_RETURN bool ParseTopLevel(Vector<TopLevel> &top);

    CHECK_RETURN bool IsType(int type) const;
    CHECK_RETURN bool IsKeyword(int keyword) const;
    CHECK_RETURN bool IsOperator(int oper) const;
    CHECK_RETURN bool IsEndCondition(EndCondition condition) const;
    CHECK_RETURN bool IsBuiltin() const;

    CHECK_RETURN bool IsConstantObject(Expression *expression) const;
    CHECK_RETURN bool IsConstant(Expression *expression) const;

    void Fatal(const char *fmt, ...);

    CHECK_RETURN ConstantExpression *Evaluate(Expression *expression);

    // Type Parsers
    Builtin *ParseBuiltin();
    Struct *ParseStruct();

    CHECK_RETURN Function *ParseFunction(const TopLevel &Parse);

    // Call Parsers
    CHECK_RETURN ConstructorCall *ParseConstructorCall();
    CHECK_RETURN FunctionCall *ParseFunctionCall();

    // Expression Parsers
    CHECK_RETURN Expression *ParseExpression(EndCondition end);
    CHECK_RETURN Expression *ParseUnary(EndCondition end);
    CHECK_RETURN Expression *ParseBinary(int lhsPrecedence, Expression *lhs, EndCondition condition);
    CHECK_RETURN Expression *ParseUnaryPrefix(EndCondition end);
    CHECK_RETURN ConstantExpression *ParseArraySize();

    // Statement Parsers
    CHECK_RETURN Statement *ParseStatement();
    CHECK_RETURN SwitchStatement *ParseSwitchStatement();
    CHECK_RETURN CaseLabelStatement *ParseCaseLabelStatement();
    CHECK_RETURN ForStatement *ParseForStatement();
    CHECK_RETURN CompoundStatement *ParseCompoundStatement();
    CHECK_RETURN IfStatement *ParseIfStatement();
    CHECK_RETURN SimpleStatement *ParseDeclarationOrExpressionStatement(EndCondition condition);
    CHECK_RETURN DeclarationStatement *ParseDeclarationStatement(EndCondition condition);
    CHECK_RETURN ExpressionStatement *ParseExpressionStatement(EndCondition condition);
    CHECK_RETURN ContinueStatement *ParseContinueStatement();
    CHECK_RETURN BreakStatement *ParseBreakStatement();
    CHECK_RETURN DiscardStatement *ParseDiscardStatement();
    CHECK_RETURN ReturnStatement *ParseReturnStatement();
    CHECK_RETURN DoStatement *ParseDoStatement();
    CHECK_RETURN WhileStatement *ParseWhileStatement();

    BinaryExpression *CreateExpression();

    Type *FindType(const char *identifier);
    Variable *FindVariable(const char *identifier);
    Type* GetType(Expression *expression);
private:
    typedef Vector<Variable *> Scope;

    TU *ast = 0;
    Lexer lexer;
    Token token;
    Vector<Scope> scopes;
    Vector<Builtin*> builtins;
    char *error;
    char *oom;
    const char *file_name;

    void DeleteString(char **what) {
        if (!*what)
            return;
        free(*what);
        *what = 0;
    }

    char *NewString(const char *what) {
        if (!what)
            return 0;
        int length = strlen(what) + 1;
        char *copy = (char*)malloc(length);
        memcpy(copy, what, length);
        strings.Add(copy);
        return copy;
    }

    bool IsStringEmpty(const char *what) {
        return !what || !*what;
    }

    Vector<Memory> memory; // Memory of AST held here
    Vector<char *> strings; // Memory of strings held here
};

NAMESPACE_FUSION_END

#endif
