#include "FusionCore.h"

NAMESPACE_FUSION_BEGIN

const char *Statement::GetName() const {
    switch (type) {
    case STMT_COMPOUND:     return "compound";
    case STMT_DECLARATION:  return "declaration";
    case STMT_EXPR:         return "expression";
    case STMT_IF:           return "if";
    case STMT_SWITCH:       return "switch";
    case STMT_CASE_LABEL:   return "case label";
    case STMT_WHILE:        return "while";
    case STMT_DO:           return "do";
    case STMT_FOR:          return "for";
    case STMT_CONTINUE:     return "continue";
    case STMT_BREAK:        return "break";
    case STMT_RETURN:       return "return";
    case STMT_DISCARD:      return "discard";
    }
    return "(unknown)";
}

TU::TU(int type)
    : type(type)
{
}

Type::Type(bool builtin)
    : builtin(builtin)
{
}

Struct::Struct()
    : Type(false)
    , name(0)
{
}

Builtin::Builtin(int type)
    : Type(true)
    , type(type)
{
}

Variable::Variable(int type)
    : name(0)
    , base_type(0)
    , is_array(false)
    , is_precise(false)
    , type(type)
{
}

FunctionVariable::FunctionVariable()
    : Variable(Variable::FUNCTION)
    , is_const(false)
    , initial_value(0)
{
}

FunctionParameter::FunctionParameter()
    : Variable(Variable::PARAMETER)
    , storage(-1)
    , auxiliary(-1)
    , memory(0)
    , precision(-1)
{
}

GlobalVariable::GlobalVariable()
    : Variable(Variable::GLOBAL)
    , storage(-1)
    , auxiliary(-1)
    , memory(0)
    , precision(-1)
    , interpolation(-1)
    , is_invariant(false)
    , initial_value(0)
{
}

SimpleStatement::SimpleStatement(int type)
    : Statement(type)
{
}

CompoundStatement::CompoundStatement()
    : Statement(Statement::STMT_COMPOUND)
{
}

EmptyStatement::EmptyStatement()
    : SimpleStatement(Statement::STMT_EMPTY)
{
}

DeclarationStatement::DeclarationStatement()
    : SimpleStatement(Statement::STMT_DECLARATION)
{
}

LayoutQualifier::LayoutQualifier()
    : name(0)
    , initial_value(0)
{
}

Function::Function()
    : return_type(0)
    , name(0)
    , is_prototype(false)
{
}

Declaration::Declaration()
    : variable(0)
{
}

Statement::Statement(int type)
    : type(type)
{
}

ExpressionStatement::ExpressionStatement(Expression *expression)
    : SimpleStatement(Statement::STMT_EXPR)
    , expression(expression)
{
}

IfStatement::IfStatement()
    : SimpleStatement(Statement::STMT_IF)
    , condition(0)
    , thenStatement(0)
    , elseStatement(0)
{
}

SwitchStatement::SwitchStatement()
    : SimpleStatement(Statement::STMT_SWITCH)
    , expression(0)
{
}

CaseLabelStatement::CaseLabelStatement()
    : SimpleStatement(Statement::STMT_CASE_LABEL)
    , condition(0)
    , isDefault(false)
{
}

IterationStatement::IterationStatement(int type)
    : SimpleStatement(type)
{
}

WhileStatement::WhileStatement()
    : IterationStatement(Statement::STMT_WHILE)
    , condition(0)
    , body(0)
{
}

DoStatement::DoStatement()
    : IterationStatement(Statement::STMT_DO)
    , body(0)
    , condition(0)
{
}

ForStatement::ForStatement()
    : IterationStatement(Statement::STMT_FOR)
    , init(0)
    , condition(0)
    , loop(0)
    , body(0)
{
}

JumpStatement::JumpStatement(int type)
    : Statement(type)
{
}

ContinueStatement::ContinueStatement()
    : JumpStatement(Statement::STMT_CONTINUE)
{
}

BreakStatement::BreakStatement()
    : JumpStatement(Statement::STMT_BREAK)
{
}

ReturnStatement::ReturnStatement()
    : JumpStatement(Statement::STMT_RETURN)
    , expression(0)
{
}

DiscardStatement::DiscardStatement()
    : JumpStatement(Statement::STMT_DISCARD)
{
}

Expression::Expression(int type)
    : type(type)
{
}

IntConstant::IntConstant(int value)
    : Expression(Expression::INT_CONST)
    , value(value)
{
}

UIntConstant::UIntConstant(unsigned int value)
    : Expression(Expression::UINT_CONST)
    , value(value)
{
}

FloatConstant::FloatConstant(float value)
    : Expression(Expression::FLOAT_CONST)
    , value(value)
{
}

DoubleConstant::DoubleConstant(double value)
    : Expression(Expression::DOUBLE_CONST)
    , value(value)
{
}

BoolConstant::BoolConstant(bool value)
    : Expression(Expression::BOOL_CONST)
    , value(value)
{
}

VariableIdentifier::VariableIdentifier(Variable *variable)
    : Expression(Expression::VAR_ID)
    , variable(variable)
{
}

FieldOrSwizzle::FieldOrSwizzle()
    : Expression(FIELD_OR_SWIZZLE)
    , operand(0)
    , name(0)
{
}

ArraySubscript::ArraySubscript()
    : Expression(ARRAY_SUB)
    , operand(0)
    , index(0)
{
}

FunctionCall::FunctionCall()
    : Expression(Expression::FUNCTION_CALL)
    , name(0)
{
}

ConstructorCall::ConstructorCall()
    : Expression(Expression::CTOR_CALL)
    , type(0)
{
}

UnaryExpression::UnaryExpression(int type, Expression *operand)
    : Expression(type)
    , operand(operand)
{
}

BinaryExpression::BinaryExpression(int type)
    : Expression(type)
    , operand1(0)
    , operand2(0)
{
}

PostIncrementExpression::PostIncrementExpression(Expression *operand)
    : UnaryExpression(Expression::POST_INC, operand)
{
}

PostDecrementExpression::PostDecrementExpression(Expression *operand)
    : UnaryExpression(Expression::POST_DEC, operand)
{
}

UnaryPlusExpression::UnaryPlusExpression(Expression *operand)
    : UnaryExpression(Expression::UNARY_PLUS, operand)
{
}

UnaryMinusExpression::UnaryMinusExpression(Expression *operand)
    : UnaryExpression(Expression::UNARY_MINUS, operand)
{
}

UnaryBitNotExpression::UnaryBitNotExpression(Expression *operand)
    : UnaryExpression(Expression::BIT_NOT, operand)
{
}

UnaryLogicalNotExpression::UnaryLogicalNotExpression(Expression *operand)
    : UnaryExpression(Expression::LOGICAL_NOT, operand)
{
}

PrefixIncrementExpression::PrefixIncrementExpression(Expression *operand)
    : UnaryExpression(Expression::PRE_INC, operand)
{
}

PrefixDecrementExpression::PrefixDecrementExpression(Expression *operand)
    : UnaryExpression(Expression::PRE_DEC, operand)
{
}

SequenceExpression::SequenceExpression()
    : BinaryExpression(Expression::SEQUENCE)
{
}

AssignmentExpression::AssignmentExpression(int assignment)
    : BinaryExpression(Expression::ASSIGN)
    , assignment(assignment)
{
}

OperationExpression::OperationExpression(int operation)
    : BinaryExpression(Expression::OPERATION)
    , operation(operation)
{
}

TernaryExpression::TernaryExpression()
    : Expression(Expression::TERNARY)
    , condition(0)
    , on_true(0)
    , on_false(0)
{
}

NAMESPACE_FUSION_END
