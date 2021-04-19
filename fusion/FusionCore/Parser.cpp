#include "FusionCore.h"


NAMESPACE_FUSION_BEGIN

Parser::Parser(const char *source, const char *file_name)
    : ast(0)
    , lexer(source)
    , file_name(file_name)
{
    oom = NewString("Out of memory");
    error = NewString("");
}

Parser::~Parser() {
	if (ast) {
		delete ast;
		ast = 0;
	}
    for (int i = 0; i < strings.GetCount(); i++)
        free(strings[i]);
    strings.Clear();
}

#define IS_TYPE(TOKEN, TYPE) \
    ((TOKEN).type == (TYPE))
#define IS_KEYWORD(TOKEN, KEYWORD) \
    (IS_TYPE((TOKEN), TYPE_keyword) && (TOKEN).as_keyword == (KEYWORD))
#define IS_OPERATOR(TOKEN, OPERATOR) \
    (IS_TYPE((TOKEN), TYPE_operator) && (TOKEN).as_operator == (OPERATOR))

#define GC_NEW(X) new(&memory)

bool Parser::IsType(int type) const {
    return IS_TYPE(token, type);
}

bool Parser::IsKeyword(int keyword) const {
    return IS_KEYWORD(token, keyword);
}

bool Parser::IsOperator(int oper) const {
    return IS_OPERATOR(token, oper);
}

bool Parser::IsEndCondition(EndCondition condition) const {
    return ((condition & END_CONDITION_SEMICOLON)    && IsType(TYPE_semicolon))
        || ((condition & END_CONDITION_PARENTHESIS)  && IsOperator(OPERATOR_paranthesis_end))
        || ((condition & END_CONDITION_BRACKET)      && IsOperator(OPERATOR_bracket_end))
        || ((condition & END_CONDITION_COLON)        && IsOperator(OPERATOR_colon))
        || ((condition & END_CONDITION_COMMA)        && IsOperator(OPERATOR_comma));
}

// Constant expression evaluator
bool Parser::IsConstant(Expression *expression) const {
    if (IsConstantObject(expression))
        return true;
    else if (expression->type == Expression::VAR_ID) {
        Variable *reference = ((VariableIdentifier*)expression)->variable;
        if (reference->type != Variable::GLOBAL)
            return false;
        Expression *initial_value = ((GlobalVariable*)reference)->initial_value;
        if (!initial_value)
            return false;
        return IsConstant(initial_value);
    } else if (expression->type == Expression::UNARY_MINUS)
        return IsConstant(((UnaryExpression*)expression)->operand);
    else if (expression->type == Expression::UNARY_PLUS)
        return IsConstant(((UnaryExpression*)expression)->operand);
    else if (expression->type == Expression::OPERATION) {
        OperationExpression *operation = (OperationExpression*)expression;
        return IsConstant(operation->operand1) && IsConstant(operation->operand2);
    }
    return false;
}

bool Parser::IsConstantObject(Expression *expression) const {
    return expression->type == Expression::INT_CONST ||
           expression->type == Expression::UINT_CONST ||
           expression->type == Expression::FLOAT_CONST ||
           expression->type == Expression::DOUBLE_CONST ||
           expression->type == Expression::BOOL_CONST;
}

#define ICONST(X) ((IntConstant*)(X))
#define UCONST(X) ((UIntConstant*)(X))
#define FCONST(X) ((FloatConstant*)(X))
#define DCONST(X) ((DoubleConstant*)(X))
#define BCONST(X) ((BoolConstant*)(X))

#define ICONST_NEW(X) GC_NEW(ConstantExpression) IntConstant(X)
#define UCONST_NEW(X) GC_NEW(ConstantExpression) UIntConstant(X)
#define FCONST_NEW(X) GC_NEW(ConstantExpression) FloatConstant(X)
#define DCONST_NEW(X) GC_NEW(ConstantExpression) DoubleConstant(X)
#define BCONST_NEW(X) GC_NEW(ConstantExpression) BoolConstant(X)

#define IVAL(X) (ICONST(X)->value)
#define UVAL(X) (UCONST(X)->value)
#define FVAL(X) (FCONST(X)->value)
#define DVAL(X) (DCONST(X)->value)
#define BVAL(X) (BCONST(X)->value)

ConstantExpression *Parser::Evaluate(Expression *expression) {
    if (!expression) return 0;
    else if (IsConstantObject(expression))
        return expression;
    else if (expression->type == Expression::VAR_ID)
        return Evaluate(((GlobalVariable*)((VariableIdentifier*)expression)->variable)->initial_value);
    else if (expression->type == Expression::UNARY_MINUS) {
        Expression *operand = Evaluate(((UnaryExpression*)expression)->operand);
        if (!operand) return 0;
        switch (operand->type) {
        case Expression::INT_CONST:    return ICONST_NEW(-IVAL(operand));
        case Expression::FLOAT_CONST:  return FCONST_NEW(-FVAL(operand));
        case Expression::DOUBLE_CONST: return DCONST_NEW(-DVAL(operand));
        default:
            Fatal("invalid operation in constant expression");
            return 0;
        }
    } else if (expression->type == Expression::UNARY_PLUS) {
        Expression *operand = Evaluate(((UnaryExpression*)expression)->operand);
        if (!operand) return 0;
        switch (operand->type) {
        case Expression::INT_CONST:
        case Expression::UINT_CONST:
        case Expression::FLOAT_CONST:
        case Expression::DOUBLE_CONST:
            return operand;
        default:
            Fatal("invalid operation in constant expression");
            return 0;
        }
    } else if (expression->type == Expression::OPERATION) {
        int operation = ((OperationExpression*)expression)->operation;
        Expression *lhs = Evaluate(((BinaryExpression*)expression)->operand1);
        Expression *rhs = Evaluate(((BinaryExpression*)expression)->operand2);
        if (!lhs) return 0;
        if (!rhs) return 0;
        switch (lhs->type) {
        case Expression::INT_CONST:
            switch (operation) {
            case OPERATOR_multiply:       return ICONST_NEW(IVAL(lhs) * IVAL(rhs));
            case OPERATOR_divide:         return ICONST_NEW(IVAL(lhs) / IVAL(rhs));
            case OPERATOR_modulus:        return ICONST_NEW(IVAL(lhs) % IVAL(rhs));
            case OPERATOR_plus:           return ICONST_NEW(IVAL(lhs) + IVAL(rhs));
            case OPERATOR_minus:          return ICONST_NEW(IVAL(lhs) - IVAL(rhs));
            case OPERATOR_shift_left:     return ICONST_NEW(IVAL(lhs) << IVAL(rhs));
            case OPERATOR_shift_right:    return ICONST_NEW(IVAL(lhs) >> IVAL(rhs));
            case OPERATOR_less:           return BCONST_NEW(IVAL(lhs) < IVAL(rhs));
            case OPERATOR_greater:        return BCONST_NEW(IVAL(lhs) > IVAL(rhs));
            case OPERATOR_less_equal:     return BCONST_NEW(IVAL(lhs) <= IVAL(rhs));
            case OPERATOR_greater_equal:  return BCONST_NEW(IVAL(lhs) >= IVAL(rhs));
            case OPERATOR_equal:          return BCONST_NEW(IVAL(lhs) == IVAL(rhs));
            case OPERATOR_not_equal:      return BCONST_NEW(IVAL(lhs) != IVAL(rhs));
            case OPERATOR_bit_and:        return ICONST_NEW(IVAL(lhs) & IVAL(rhs));
            case OPERATOR_bit_xor:        return ICONST_NEW(IVAL(lhs) ^ IVAL(rhs));
            case OPERATOR_logical_and:    return BCONST_NEW(IVAL(lhs) && IVAL(rhs));
            case OPERATOR_logical_xor:    return BCONST_NEW(!IVAL(lhs) != !IVAL(rhs));
            case OPERATOR_logical_or:     return BCONST_NEW(IVAL(lhs) || IVAL(rhs));
            default:
                Fatal("invalid operation in constant expression");
                return 0;
            }
            break;
        case Expression::UINT_CONST:
            switch (operation) {
            case OPERATOR_multiply:       return UCONST_NEW(UVAL(lhs) * UVAL(rhs));
            case OPERATOR_divide:         return UCONST_NEW(UVAL(lhs) / UVAL(rhs));
            case OPERATOR_modulus:        return UCONST_NEW(UVAL(lhs) % UVAL(rhs));
            case OPERATOR_plus:           return UCONST_NEW(UVAL(lhs) + UVAL(rhs));
            case OPERATOR_minus:          return UCONST_NEW(UVAL(lhs) - UVAL(rhs));
            case OPERATOR_shift_left:     return UCONST_NEW(UVAL(lhs) << UVAL(rhs));
            case OPERATOR_shift_right:    return UCONST_NEW(UVAL(lhs) >> UVAL(rhs));
            case OPERATOR_less:           return BCONST_NEW(UVAL(lhs) < UVAL(rhs));
            case OPERATOR_greater:        return BCONST_NEW(UVAL(lhs) > UVAL(rhs));
            case OPERATOR_less_equal:     return BCONST_NEW(UVAL(lhs) <= UVAL(rhs));
            case OPERATOR_greater_equal:  return BCONST_NEW(UVAL(lhs) >= UVAL(rhs));
            case OPERATOR_equal:          return BCONST_NEW(UVAL(lhs) == UVAL(rhs));
            case OPERATOR_not_equal:      return BCONST_NEW(UVAL(lhs) != UVAL(rhs));
            case OPERATOR_bit_and:        return UCONST_NEW(UVAL(lhs) & UVAL(rhs));
            case OPERATOR_bit_xor:        return UCONST_NEW(UVAL(lhs) ^ UVAL(rhs));
            case OPERATOR_logical_and:    return BCONST_NEW(UVAL(lhs) && UVAL(rhs));
            case OPERATOR_logical_xor:    return BCONST_NEW(!UVAL(lhs) != !UVAL(rhs));
            case OPERATOR_logical_or:     return BCONST_NEW(UVAL(lhs) || UVAL(rhs));
            default:
                Fatal("invalid operation in constant expression");
                return 0;
            }
            break;
        case Expression::FLOAT_CONST:
            switch (operation) {
            case OPERATOR_multiply:       return FCONST_NEW(FVAL(lhs) * FVAL(rhs));
            case OPERATOR_divide:         return FCONST_NEW(FVAL(lhs) / FVAL(rhs));
            case OPERATOR_plus:           return FCONST_NEW(FVAL(lhs) + FVAL(rhs));
            case OPERATOR_minus:          return FCONST_NEW(FVAL(lhs) - FVAL(rhs));
            case OPERATOR_less:           return BCONST_NEW(FVAL(lhs) < FVAL(rhs));
            case OPERATOR_greater:        return BCONST_NEW(FVAL(lhs) > FVAL(rhs));
            case OPERATOR_less_equal:     return BCONST_NEW(FVAL(lhs) <= FVAL(rhs));
            case OPERATOR_greater_equal:  return BCONST_NEW(FVAL(lhs) >= FVAL(rhs));
            case OPERATOR_equal:          return BCONST_NEW(FVAL(lhs) == FVAL(rhs));
            case OPERATOR_not_equal:      return BCONST_NEW(FVAL(lhs) != FVAL(rhs));
            case OPERATOR_logical_and:    return BCONST_NEW(FVAL(lhs) && FVAL(rhs));
            case OPERATOR_logical_xor:    return BCONST_NEW(!FVAL(lhs) != !FVAL(rhs));
            case OPERATOR_logical_or:     return BCONST_NEW(FVAL(lhs) || FVAL(rhs));
            default:
                Fatal("invalid operation in constant expression");
                return 0;
            }
            break;
        case Expression::DOUBLE_CONST:
            switch (operation) {
            case OPERATOR_multiply:       return DCONST_NEW(DVAL(lhs) * DVAL(rhs));
            case OPERATOR_divide:         return DCONST_NEW(DVAL(lhs) / DVAL(rhs));
            case OPERATOR_plus:           return DCONST_NEW(DVAL(lhs) + DVAL(rhs));
            case OPERATOR_minus:          return DCONST_NEW(DVAL(lhs) - DVAL(rhs));
            case OPERATOR_less:           return BCONST_NEW(DVAL(lhs) < DVAL(rhs));
            case OPERATOR_greater:        return BCONST_NEW(DVAL(lhs) > DVAL(rhs));
            case OPERATOR_less_equal:     return BCONST_NEW(DVAL(lhs) <= DVAL(rhs));
            case OPERATOR_greater_equal:  return BCONST_NEW(DVAL(lhs) >= DVAL(rhs));
            case OPERATOR_equal:          return BCONST_NEW(DVAL(lhs) == DVAL(rhs));
            case OPERATOR_not_equal:      return BCONST_NEW(DVAL(lhs) != DVAL(rhs));
            case OPERATOR_logical_and:    return BCONST_NEW(DVAL(lhs) && DVAL(rhs));
            case OPERATOR_logical_xor:    return BCONST_NEW(!DVAL(lhs) != !DVAL(rhs));
            case OPERATOR_logical_or:     return BCONST_NEW(DVAL(lhs) || DVAL(rhs));
            default:
                Fatal("invalid operation in constant expression");
                return 0;
            }
            break;
        case Expression::BOOL_CONST:
            switch (operation) {
            case OPERATOR_equal:          return BCONST_NEW(BVAL(lhs) == BVAL(rhs));
            case OPERATOR_not_equal:      return BCONST_NEW(BVAL(lhs) != BVAL(rhs));
            case OPERATOR_logical_and:    return BCONST_NEW(BVAL(lhs) && BVAL(rhs));
            case OPERATOR_logical_xor:    return BCONST_NEW(!BVAL(lhs) != !BVAL(rhs));
            case OPERATOR_logical_or:     return BCONST_NEW(BVAL(lhs) || BVAL(rhs));
            default:
                Fatal("invalid operation in constant expression");
                return 0;
            }
            break;
        }
    } else {
        return Evaluate(expression);
    }
    return 0;
}

void Parser::Fatal(const char *fmt, ...) {
    // Format banner
    char *banner = 0;
    int bannerLength = allocfmt(&banner, "%s:%zu:%zu: error: ", file_name, lexer.GetLine(), lexer.GetColumn());
    if (bannerLength == -1) {
        error = oom;
        return;
    }

    // Format message
    char *message = 0;
    va_list va;
    va_start(va, fmt);
    int messageLength = allocvfmt(&message, fmt, va);
    if (messageLength == -1) {
        va_end(va);
        error = oom;
        return;
    }
    va_end(va);

    // Concatenate the two things
    char *concat = (char *)malloc(bannerLength + messageLength + 1);
    if (!concat) {
        free(banner);
        free(message);
        error = oom;
        return;
    }

    memcpy(concat, banner, bannerLength);
    memcpy(concat + bannerLength, message, messageLength + 1); // +1 for '\0'
    free(banner);
    free(message);

    error = concat;
    strings.Add(error);
}

#undef TYPENAME
#define TYPENAME(X) case KEYWORD_##X:
bool Parser::IsBuiltin() const {
    if (!IsType(TYPE_keyword))
        return false;
    switch (token.as_keyword) {
    #include "Lexemes.h"
        return true;
    default:
        break;
    }
    return false;
}
#undef TYPENAME
#define TYPENAME(...)

/// The Parser entry point
CHECK_RETURN TU *Parser::Parse(int type) {
    ast = new TU(type);
    scopes.Add(Scope());
    for (;;) {
        lexer.Read(token, true);

        if (lexer.GetError()) {
            Fatal("%s", lexer.GetError());
            return 0;
        }

        if (IsType(TYPE_eof))
            break;

        Vector<TopLevel> items;
        if (!ParseTopLevel(items))
            return 0;

        if (IsType(TYPE_semicolon)) {
            for (int i = 0; i < items.GetCount(); i++) {
                TopLevel &Parse = items[i];
                GlobalVariable *global = GC_NEW(Variable) GlobalVariable();
                global->storage = Parse.storage;
                global->auxiliary = Parse.auxiliary;
                global->memory = Parse.memory;
                global->precision = Parse.precision;
                global->interpolation = Parse.interpolation;
                global->base_type = Parse.type;
                global->name = NewString(Parse.name);
                global->is_invariant = Parse.is_invariant;
                global->is_precise = Parse.is_precise;
                global->layout_qualifiers <<= Parse.layout_qualifiers;
                if (Parse.initial_value) {
                    if (!(global->initial_value = Evaluate(Parse.initial_value)))
                        return 0;
                }
                global->is_array = Parse.is_array;
                global->array_sizes <<= Parse.array_sizes;
                ast->globals.Add(global);
                scopes.Top().Add(global);
            }
        } else if (IsOperator(OPERATOR_paranthesis_begin)) {
            Function *function = ParseFunction(items[0]);
            if (!function)
                return 0;
            ast->functions.Add(function);
        } else if (IsType(TYPE_whitespace)) {
            continue; // whitespace Tokens will be used later for the preprocessor
        } else {
            Fatal("syntax error at top level %d", token.as_keyword);
            return 0;
        }
    }
    return ast;
}

CHECK_RETURN bool Parser::ParseStorage(TopLevel &current) {
    // const, in, out, attribute, uniform, varying, buffer, shared
    if (IsKeyword(KEYWORD_const)) {
        current.storage = QUAL_CONST;
        if (!Next()) return false; // skip 'const'
    } else if (IsKeyword(KEYWORD_in)) {
        current.storage = QUAL_IN;
        if (!Next()) return false; // skip 'in'
    } else if (IsKeyword(KEYWORD_out)) {
        current.storage = QUAL_OUT;
        if (!Next()) return false; // skip 'out'
    } else if (IsKeyword(KEYWORD_attribute)) {
        current.storage = QUAL_ATTR;
        if (!Next()) return false; // skip 'attribute'
    } else if (IsKeyword(KEYWORD_uniform)) {
        current.storage = QUAL_UNIFORM;
        if (!Next()) return false; // skip 'uniform'
    } else if (IsKeyword(KEYWORD_varying)) {
        current.storage = QUAL_VARYING;
        if (!Next()) return false; // skip 'varying'
    } else if (IsKeyword(KEYWORD_buffer)) {
        current.storage = QUAL_BUFFER;
        if (!Next()) return false; // skip 'buffer'
    } else if (IsKeyword(KEYWORD_shared)) {
        current.storage = QUAL_SHARED;
        if (!Next()) return false; // skip 'shared'
    }
    return true;
}

CHECK_RETURN bool Parser::ParseAuxiliary(TopLevel &current) {
    // centroid, sample, patch
    if (IsKeyword(KEYWORD_centroid)) {
        current.auxiliary = AUX_CENTROID;
        if (!Next()) return false; // skip 'centroid'
    } else if (IsKeyword(KEYWORD_sample)) {
        current.auxiliary = AUX_SAMPLE;
        if (!Next()) return false; // skip 'sample'
    } else if (IsKeyword(KEYWORD_patch)) {
        current.auxiliary = AUX_PATCH;
        if (!Next()) return false; // skip 'patch'
    }
    return true;
}

CHECK_RETURN bool Parser::ParseInterpolation(TopLevel &current) {
    // smooth, flat, noperspective
    if (IsKeyword(KEYWORD_smooth)) {
        current.interpolation = IPOL_SMOOTH;
        if (!Next()) return false; // skip 'smooth'
    } else if (IsKeyword(KEYWORD_flat)) {
        current.interpolation = IPOL_FLAT;
        if (!Next()) return false; // skip 'flat'
    } else if (IsKeyword(KEYWORD_noperspective)) {
        current.interpolation = IPOL_NO_PERSPECTIVE;
        if (!Next()) return false; // skip 'noperspective'
    }
    return true;
}

CHECK_RETURN bool Parser::ParsePrecision(TopLevel &current) {
    // highp, mediump, lowp
    if (IsKeyword(KEYWORD_highp)) {
        current.precision = HIGH_PRECISION;
        if (!Next()) return false; // skip 'highp'
    } else if (IsKeyword(KEYWORD_mediump)) {
        current.precision = MEDIUM_PRECISION;
        if (!Next()) return false; // skip 'mediump'
    } else if (IsKeyword(KEYWORD_lowp)) {
        current.precision = LOW_PRECISION;
        if (!Next()) return false; // skip 'lowp'
    }
    return true;
}

CHECK_RETURN bool Parser::ParseInvariant(TopLevel &current) {
    // invariant
    if (IsKeyword(KEYWORD_invariant)) {
        current.is_invariant = true;
        if (!Next()) return false; // skip 'invariant'
    }
    return true;
}

CHECK_RETURN bool Parser::ParsePrecise(TopLevel &current) {
    // precise
    if (IsKeyword(KEYWORD_precise)) {
        current.is_precise = true;
        if (!Next()) return false; // skip 'precise'
    }
    return true;
}

CHECK_RETURN bool Parser::ParseMemory(TopLevel &current) {
    // coherent, volatile, restrict, readonly, writeonly
    if (IsKeyword(KEYWORD_coherent)) {
        current.memory |= MEM_COHERENT;
        if (!Next()) return false; // skip 'coherent'
    } else if (IsKeyword(KEYWORD_volatile)) {
        current.memory |= MEM_VOLATILE;
        if (!Next()) return false; // skip 'volatile'
    } else if (IsKeyword(KEYWORD_restrict)) {
        current.memory |= MEM_RESTRICT;
        if (!Next()) return false; // skip 'restrict'
    } else if (IsKeyword(KEYWORD_readonly)) {
        current.memory |= MEM_READONLY;
        if (!Next()) return false; // skip 'readonly'
    } else if (IsKeyword(KEYWORD_writeonly)) {
        current.memory |= MEM_WRITEONLY;
        if (!Next()) return false; // skip 'writeonly;
    }
    return true;
}

static struct {
    const char *qualifier;
    bool isAssign;
} kLayoutQualifiers[] = {
    { "shared",                     false },
    { "packed",                     false },
    { "std140",                     false },
    { "row_major",                  false },
    { "column_major",               false },
    { "binding",                    true  },
    { "offset",                     true  },
    { "align",                      true  },
    { "Location",                   true  },
    { "component",                  true  },
    { "index",                      true  },
    { "triangles",                  false },
    { "quads",                      false },
    { "isolines",                   false },
    { "equal_spacing",              false },
    { "fractional_even_spacing",    false },
    { "fractional_odd_spacing",     false },
    { "cw",                         false },
    { "ccw",                        false },
    { "point_mode",                 false },
    { "points",                     false },
    { "lines",                      false },
    { "lines_adjacency",            false },
    { "triangles_adjacency",        false },
    { "invocations",                true  },
    { "origin_upper_left",          false },
    { "pixel_center_integer",       false },
    { "early_fragment_tests",       false },
    { "local_size_x",               true  },
    { "local_size_y",               true  },
    { "local_size_z",               true  },
    { "xfb_buffer",                 true  },
    { "xfb_stride",                 true  },
    { "xfb_offset",                 true  },
    { "vertices",                   true  },
    { "line_strip",                 false },
    { "triangle_strip",             false },
    { "max_vertices",               true  },
    { "stream",                     true  },
    { "depth_any",                  false },
    { "depth_greater",              false },
    { "depth_less",                 false },
    { "depth_unchanged",            false }
};

CHECK_RETURN bool Parser::ParseLayout(TopLevel &current) {
    Vector<LayoutQualifier*> &qualifiers = current.layout_qualifiers;
    if (IsKeyword(KEYWORD_layout)) {
        if (!Next()) // skip 'layout'
            return false;
        if (!IsOperator(OPERATOR_paranthesis_begin)) {
            Fatal("expected `(' after `layout'");
            return false;
        }
        if (!Next()) // skip '('
            return false;
        while (!IsOperator(OPERATOR_paranthesis_end)) {
            LayoutQualifier *qualifier = GC_NEW(LayoutQualifier) LayoutQualifier();

            // "The Tokens used for layout-qualifier-name are identifiers,
            //  not keywords, however, the shared keyword is allowed as a
            //  layout-qualifier-id."
            if (!IsType(TYPE_identifier) && !IsKeyword(KEYWORD_shared))
                return false;

            int found = -1;
            qualifier->name = NewString(IsType(TYPE_identifier) ? token.as_identifier : "shared");
            for (int i = 0; i < sizeof(kLayoutQualifiers)/sizeof(kLayoutQualifiers[0]); i++) {
                if (strcmp(qualifier->name, kLayoutQualifiers[i].qualifier))
                    continue;
                found = int(i);
                break;
            }

            if (found == -1) {
                Fatal("unknown layout qualifier `%s'", qualifier->name);
                return false;
            }

            if (!Next()) // skip identifier or 'shared' keyword
                return false;

            if (IsOperator(OPERATOR_assign)) {
                if (!kLayoutQualifiers[found].isAssign) {
                    Fatal("unexpected layout qualifier value on `%s' layout qualifier", qualifier->name);
                    return false;
                }
                if (!Next()) // skip '='
                    return false;
                if (!(qualifier->initial_value = ParseExpression(END_CONDITION_COMMA | END_CONDITION_PARENTHESIS)))
                    return false;
                if (!IsConstant(qualifier->initial_value)) {
                    // TODO: check integer-constant-expression
                    Fatal("value for layout qualifier `%s' is not a valid constant expression",
                        qualifier->name);
                    return false;
                }
                if (!(qualifier->initial_value = Evaluate(qualifier->initial_value)))
                    return false;
            } else if (kLayoutQualifiers[found].isAssign) {
                Fatal("expected layout qualifier value for `%s' layout qualifier", qualifier->name);
                return false;
            }

            if (IsOperator(OPERATOR_comma)) {
                if (!Next()) // skip ','
                    return false;
            }
            qualifiers.Add(qualifier);
        }
        if (!Next()) // skip ')'
            return false;
    }
    return true;
}

CHECK_RETURN bool Parser::ParseTopLevelItem(TopLevel &level, TopLevel *continuation) {
    Vector<TopLevel> items;
    while (!IsBuiltin() && !IsType(TYPE_identifier)) {
        // If this is an empty file don't get caught in this loop indefinitely
        Token peek = lexer.Peek();
        if (IS_TYPE(peek, TYPE_eof))
            return false;

        TopLevel next;
        if (continuation)
            next = *continuation;

        if (!ParseStorage(next))       return false;
        if (!ParseAuxiliary(next))     return false;
        if (!ParseInterpolation(next)) return false;
        if (!ParsePrecision(next))     return false;
        if (!ParseInvariant(next))     return false;
        if (!ParsePrecise(next))       return false;
        if (!ParseMemory(next))        return false;
        if (!ParseLayout(next))        return false;

        if (IsKeyword(KEYWORD_struct)) {
            Struct *unique = ParseStruct();
            if (!unique)
                return false;
            ast->structures.Add(unique);
            if (IsType(TYPE_semicolon))
            {
                return true;
            } else {
                level.type = unique;
            }
        } else {
            items.Add(next);
        }
    }

    if (continuation) {
        level = *continuation;
        // erase anything that is not an array size on the type, e.g
        // int[2] a[2], b; should produce: int a[2][2]; int b[2];
        level.array_sizes.Remove(level.array_on_type_offset, level.array_sizes.GetCount()-level.array_on_type_offset);
    }

    for (int i = 0; i < items.GetCount(); i++) {
        TopLevel &next = items[i];
        const int storage = level.storage != -1 ? level.storage : next.storage;
        if (ast->type == TU::kVertex && storage == QUAL_IN) {
            // "It's a compile-time error to use any auxiliary or interpolation
            //  qualifiers on a vertex shader input"
            if (level.auxiliary != -1 || next.auxiliary != -1) {
                Fatal("cannot use auxiliary storage qualifier on vertex shader input");
                return false;
            } else if (level.interpolation != -1 || next.interpolation != -1) {
                Fatal("cannot use interpolation qualifier on vertex shader input");
                return false;
            }
        }
        if (ast->type == TU::kFragment && storage == QUAL_OUT) {
            // "It's a compile-time error to use auxiliary storage qualifiers or
            //  interpolation qualifiers on an output in a fragment shader."
            if (level.auxiliary != -1 || next.auxiliary != -1) {
                Fatal("cannot use auxiliary storage qualifier on fragment shader output");
                return false;
            } else if (level.interpolation != -1 || next.interpolation != -1) {
                Fatal("cannot use interpolation qualifier on fragment shader output");
                return false;
            }
        }
        if (ast->type != TU::kTessEvaluation && storage == QUAL_IN) {
            // "Applying the patch qualifier to inputs can only be done in tessellation
            //  evaluation shaders. It is a compile-time error to use patch with inputs
            //  in any other stage."
            if (level.auxiliary == AUX_PATCH || next.auxiliary == AUX_PATCH) {
                Fatal("applying `patch' qualifier to input can only be done in tessellation evaluation shaders");
                return false;
            }
        }
        if (ast->type != TU::kTessControl && storage == QUAL_OUT) {
            // "Applying patch to an output can only be done in a tessellation control
            //  shader. It is a compile-time errot to use patch on outputs in any
            //  other stage."
            if (level.auxiliary == AUX_PATCH || next.auxiliary == AUX_PATCH) {
                Fatal("applying `patch' qualifier to output can only be done in tessellation control shaders");
                return false;
            }
        }
        if (next.storage != -1 && level.storage != -1) {
            Fatal("multiple storage qualifiers in declaration");
            return false;
        } else if (next.auxiliary != -1 && level.auxiliary != -1) {
            Fatal("multiple auxiliary storage qualifiers in declaration");
            return false;
        } else if (next.interpolation != -1 && level.interpolation != -1) {
            Fatal("multiple interpolation qualifiers in declaration");
            return false;
        } if (next.precision != -1 && level.precision != -1) {
            Fatal("multiple precision qualifiers in declaration");
            return false;
        }
        level.storage = next.storage;
        level.auxiliary = next.auxiliary;
        level.interpolation = next.interpolation;
        level.precision = next.precision;
        level.memory |= next.memory;

        for (int i = 0; i < next.layout_qualifiers.GetCount(); i++) {
            // "When the same layout-qualifier-name occurs multiple times, in a single declaration, the
            //  last occurrence overrides the former occurrence(s)"
            for (int j = 0; i < level.layout_qualifiers.GetCount(); j++) {
                if (next.layout_qualifiers[i]->name == level.layout_qualifiers[j]->name)
                    level.layout_qualifiers.Remove(j, level.layout_qualifiers.GetCount() - j);
            }
            level.layout_qualifiers.Add(next.layout_qualifiers[i]);
        }
    }

    // "It's a compile-time error to use interpolation qualifiers with patch"
    if (level.auxiliary == AUX_PATCH && level.interpolation != -1) {
        Fatal("cannot use interpolation qualifier with auxiliary storage qualifier `patch'");
        return false;
    }

    if (!continuation && !level.type) {
        if (IsType(TYPE_identifier)) {
            level.type = FindType(token.as_identifier);
            if (!Next()) // skip identifier
                return false;
        } else {
            level.type = ParseBuiltin();
            if (!Next()) // skip typename
                return false;
        }

        if (level.type) {
            // Could be an array
            while (IsOperator(OPERATOR_bracket_begin)) {
                level.is_array = true;
                ConstantExpression *array_size = ParseArraySize();
                if (!array_size)
                    return false;
                level.array_sizes.Insert(0, array_size);
                level.array_on_type_offset++;
                if (!Next()) // skip ']'
                    return false;
            }
        }
    }

    if (!level.type) {
        Fatal("expected typename");
        return false;
    }

    if (IsType(TYPE_identifier)) {
        level.name = NewString(token.as_identifier);
        if (!Next())// skip identifier
            return false;
    }

    while (IsOperator(OPERATOR_bracket_begin)) {
        level.is_array = true;
        level.array_sizes.Add(ParseArraySize());
        if (!Next()) // skip ']'
            return false;
    }

    if (level.storage == QUAL_CONST || level.storage == QUAL_UNIFORM) {
        // Can have a constant expression assignment
        if (IsOperator(OPERATOR_assign)) {
            if (!Next()) // skip '='
                return false;
            if (!(level.initial_value = ParseExpression(END_CONDITION_SEMICOLON)))
                return false;
            if (!IsConstant(level.initial_value)) {
                Fatal("not a valid constant expression");
                return false;
            }
        } else if (level.storage != QUAL_UNIFORM) {
            Fatal("const-qualified variable declared but not initialized");
            return false;
        }
    }

    // If it isn't a function or prototype than the use of void is not legal
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        if (level.type->builtin && ((Builtin*)level.type)->type == KEYWORD_void) {
            Fatal("`void' cannot be used in declaration");
            return false;
        }
    }

    // if it doesn't have a name than it's illegal
    if (IsStringEmpty(level.name)) {
        Fatal("expected name for declaration");
        return false;
    }

    return true;
}

CHECK_RETURN bool Parser::ParseTopLevel(Vector<TopLevel> &items) {
    TopLevel item;
    if (!ParseTopLevelItem(item))
        return false;
    if (item.type)
        items.Add(item);
    while (items.GetCount() && IsOperator(OPERATOR_comma)) {
        if (!Next())
            return false; // skip ','
        TopLevel nextItem;
        if (!ParseTopLevelItem(nextItem, &items[0]))
            return false;
        if (nextItem.type)
            items.Add(nextItem);
    }
    return true;
}

CHECK_RETURN Struct *Parser::ParseStruct() {
    if (!Next()) return 0; // skip struct

    Struct *unique = GC_NEW(Type) Struct;

    if (IsType(TYPE_identifier)) {
        unique->name = NewString(token.as_identifier);
        if (!Next()) return 0; // skip identifier
    }

    if (!IsType(TYPE_scope_begin)) {
        Fatal("expected '{' for structure definition");
        return 0;
    }

    if (!Next()) return 0; // skip '{'

    Vector<TopLevel> items;
    while (!IsType(TYPE_scope_end)) {
        if (!ParseTopLevel(items))
            return 0;
        if (!Next())
            return 0;
    }

    for (int i = 0; i < items.GetCount(); i++) {
        TopLevel &Parse = items[i];
        Variable *field = GC_NEW(Variable) Variable(Variable::FIELD);
        field->base_type = Parse.type;
        field->name = NewString(Parse.name);
        field->is_precise = Parse.is_precise;
        field->is_array = Parse.is_array;
        field->array_sizes <<= Parse.array_sizes;
        unique->fields.Add(field);
    }

    if (!Next()) return 0; // skip '}'

    return unique;
}

CHECK_RETURN Expression *Parser::ParseBinary(int lhsPrecedence, Expression *lhs, EndCondition end) {
    // Precedence climbing
    while (!IsEndCondition(end)) {
        int binaryPrecedence = token.GetPrecedence();
        if (binaryPrecedence < lhsPrecedence)
            break;

        BinaryExpression *expression = CreateExpression();
        if (!Next())
            return 0;

        Expression *rhs = ParseUnary(end);
        if (!rhs)
            return 0;
        if (!Next())
            return 0;

        if (((Expression*)expression)->type == Expression::ASSIGN) {
            Expression *find = lhs;
            while (find->type == Expression::ARRAY_SUB
                || find->type == Expression::FIELD_OR_SWIZZLE)
            {
                find = (find->type == Expression::ARRAY_SUB)
                    ? ((ArraySubscript*)find)->operand
                    : ((FieldOrSwizzle*)find)->operand;
            }
            if (find->type != Expression::VAR_ID) {
                Fatal("not a valid lvalue");
                return 0;
            }
            Variable *variable = ((VariableIdentifier*)lhs)->variable;
            if (variable->type == Variable::GLOBAL) {
                GlobalVariable *global = (GlobalVariable*)variable;
                // "It's a compile-time error to write to a variable declared as an input"
                if (global->storage == QUAL_IN) {
                    Fatal("cannot write to a variable declared as input");
                    return 0;
                }
                // "It's a compile-time error to write to a const variable outside of its declaration."
                if (global->storage == QUAL_CONST) {
                    Fatal("cannot write to a const variable outside of its declaration");
                    return 0;
                }
            }
        }

        int rhsPrecedence = token.GetPrecedence();

        // climb
        if (binaryPrecedence < rhsPrecedence) {
            if (!(rhs = ParseBinary(binaryPrecedence + 1, rhs, end)))
                return 0;
        }

        expression->operand1 = lhs;
        expression->operand2 = rhs;
        lhs = expression;
    }
    return lhs;
}

CHECK_RETURN Expression *Parser::ParseUnaryPrefix(EndCondition condition) {
    if (IsOperator(OPERATOR_paranthesis_begin)) {
        if (!Next()) return 0; // skip '('
        return ParseExpression(END_CONDITION_PARENTHESIS);
    } else if (IsOperator(OPERATOR_logical_not)) {
        if (!Next()) return 0; // skip '!'
        return GC_NEW(Expression) UnaryLogicalNotExpression(ParseUnary(condition));
    } else if (IsOperator(OPERATOR_bit_not)) {
        if (!Next()) return 0; // skip '~'
        return GC_NEW(Expression) UnaryBitNotExpression(ParseUnary(condition));
    } else if (IsOperator(OPERATOR_plus)) {
        if (!Next()) return 0; // skip '+'
        return GC_NEW(Expression) UnaryPlusExpression(ParseUnary(condition));
    } else if (IsOperator(OPERATOR_minus)) {
        if (!Next()) return 0; // skip '-'
        return GC_NEW(Expression) UnaryMinusExpression(ParseUnary(condition));
    } else if (IsOperator(OPERATOR_increment)) {
        if (!Next()) return 0; // skip '++'
        return GC_NEW(Expression) PrefixIncrementExpression(ParseUnary(condition));
    } else if (IsOperator(OPERATOR_decrement)) {
        if (!Next()) return 0; // skip '--'
        return GC_NEW(Expression) PrefixDecrementExpression(ParseUnary(condition));
    } else if (IsBuiltin()) {
        return ParseConstructorCall();
    } else if (IsType(TYPE_identifier)) {
        Token peek = lexer.Peek();
        if (IS_OPERATOR(peek, OPERATOR_paranthesis_begin)) {
            Type *type = FindType(token.as_identifier);
            if (type)
                return ParseConstructorCall();
            else
                return ParseFunctionCall();
        } else {
            Variable *find = FindVariable(token.as_identifier);
            if (find)
                return GC_NEW(Expression) VariableIdentifier(find);
            Fatal("`%s' was not declared in this scope", token.as_identifier);
            return 0;
        }
    } else if (IsKeyword(KEYWORD_true)) {
        return BCONST_NEW(true);
    } else if (IsKeyword(KEYWORD_false)) {
        return BCONST_NEW(false);
    } else if (IsType(TYPE_constant_int)) {
        return ICONST_NEW(token.as_int);
    } else if (IsType(TYPE_constant_uint)) {
        return UCONST_NEW(token.as_unsigned);
    } else if (IsType(TYPE_constant_float)) {
        return FCONST_NEW(token.as_float);
    } else if (IsType(TYPE_constant_double)) {
        return DCONST_NEW(token.as_double);
    } else if (condition == END_CONDITION_BRACKET) {
        return 0;
    }
    Fatal("syntax error during unary prefix");
    return 0;
}

Type* Parser::GetType(Expression *expression)
{
    switch (expression->type)
    {
    case Expression::VAR_ID:
        return ((VariableIdentifier*)expression)->variable->base_type;
    case Expression::FIELD_OR_SWIZZLE:
        return GetType(((FieldOrSwizzle*)expression)->operand);
    case Expression::ARRAY_SUB:
        return GetType(((ArraySubscript*)expression)->operand);
    case Expression::FUNCTION_CALL:
        for (int i = 0; i < ast->functions.GetCount(); i++) {
            if (strcmp(ast->functions[i]->name, ((FunctionCall*)expression)->name))
                continue;
            return ast->functions[i]->return_type;
        }
        break;
    case Expression::CTOR_CALL:
        return ((ConstructorCall*)expression)->type;
    }
    return 0;
}

CHECK_RETURN Expression *Parser::ParseUnary(EndCondition end) {
    Expression *operand = ParseUnaryPrefix(end);
    if (!operand)
        return 0;
    for (;;) {
        Token peek = lexer.Peek();
        if (IS_OPERATOR(peek, OPERATOR_dot)) {
            if (!Next()) return 0; // skip last
            if (!Next()) return 0; // skip '.'
            if (!IsType(TYPE_identifier)) {
                Fatal("expected field identifier or swizzle after `.'");
                return 0;
            }
            FieldOrSwizzle *expression = GC_NEW(Expression) FieldOrSwizzle();

            Type *type = GetType(operand);
            if (type && !type->builtin) {
                Variable *field = 0;
                Struct *kind = (Struct*)type;
                for (int i = 0; i < kind->fields.GetCount(); i++) {
                    if (strcmp(kind->fields[i]->name, token.as_identifier))
                        continue;
                    field = kind->fields[i];
                    break;
                }
                if (!field) {
                    Fatal("field `%s' does not exist in structure `%s'", token.as_identifier, kind->name);
                    return 0;
                }
            }

            expression->operand = operand;
            expression->name = NewString(token.as_identifier);
            operand = expression;
        } else if (IS_OPERATOR(peek, OPERATOR_increment)) {
            if (!Next()) return 0; // skip last
            operand = GC_NEW(Expression) PostIncrementExpression(operand);
        } else if (IS_OPERATOR(peek, OPERATOR_decrement)) {
            if (!Next()) return 0; // skip last
            operand = GC_NEW(Expression) PostDecrementExpression(operand);
        } else if (IS_OPERATOR(peek, OPERATOR_bracket_begin)) {
            if (!Next()) return 0; // skip last
            if (!Next()) return 0; // skip '['
            ArraySubscript *expression = GC_NEW(Expression) ArraySubscript();
            Expression *find = operand;
            while (find->type == Expression::ARRAY_SUB)
                find = ((ArraySubscript*)find)->operand;
            if (find->type != Expression::VAR_ID) {
                Fatal("cannot be subscripted");
                return 0;
            }
            expression->operand = operand;
            if (!(expression->index = ParseExpression(END_CONDITION_BRACKET)))
                return 0;
            if (IsConstant(expression->index)) {
                if (!(expression->index = Evaluate(expression->index)))
                    return 0;
            }
            operand = expression;
        } else if (IS_OPERATOR(peek, OPERATOR_questionmark)) {
            if (!Next()) return 0; // skip last
            if (!Next()) return 0; // skip '?'
            TernaryExpression *expression = GC_NEW(Expression) TernaryExpression();
            expression->condition = operand;
            expression->on_true = ParseExpression(END_CONDITION_COLON);
            if (!IsOperator(OPERATOR_colon)) {
                Fatal("expected `:' for else case in ternary statement");
                return 0;
            }
            if (!Next()) return 0; // skip ':'
            if (!(expression->on_false = ParseUnary(end))) {
                Fatal("expected expression after `:' in ternary statement");
                return 0;
            }
            operand = expression;
        } else {
            break;
        }
    }
    return operand;
}

CHECK_RETURN Expression *Parser::ParseExpression(EndCondition condition) {
    Expression *lhs = ParseUnary(condition);
    if (!lhs)
        return 0;
    if (!Next()) // skip last
        return 0;
    return ParseBinary(0, lhs, condition);
}

CHECK_RETURN ExpressionStatement *Parser::ParseExpressionStatement(EndCondition condition) {
    Expression *expression = ParseExpression(condition);
    return expression ? GC_NEW(Statement) ExpressionStatement(expression) : 0;
}

CHECK_RETURN ConstantExpression *Parser::ParseArraySize() {
    if (!Next()) // skip '['
        return 0;
    return ParseExpression(END_CONDITION_BRACKET);
}

CHECK_RETURN CompoundStatement *Parser::ParseCompoundStatement() {
    CompoundStatement *statement = GC_NEW(Statement) CompoundStatement();
    if (!Next()) // skip '{'
        return 0;
    while (!IsType(TYPE_scope_end)) {
        Statement *nextStatement = ParseStatement();
        if (!nextStatement) return 0;
        statement->statements.Add(nextStatement);
        if (!Next()) // skip ';'
            return 0;
    }
    return statement;
}

CHECK_RETURN IfStatement *Parser::ParseIfStatement() {
    IfStatement *statement = GC_NEW(Statement) IfStatement();
    if (!Next()) // skip 'if'
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        Fatal("expected `(' after `if'");
        return 0;
    }
    if (!Next()) // skip '('
        return 0;
    if (!(statement->condition = ParseExpression(END_CONDITION_PARENTHESIS)))
        return 0;
    if (!Next()) // skip ')'
        return 0;
    statement->thenStatement = ParseStatement();
    Token peek = lexer.Peek();
    if (IS_KEYWORD(peek, KEYWORD_else)) {
        if (!Next()) // skip ';' or '}'
            return 0;
        if (!Next()) // skip 'else'
            return 0;
        if (!(statement->elseStatement = ParseStatement()))
            return 0;
    }
    return statement;
}

CHECK_RETURN SwitchStatement *Parser::ParseSwitchStatement() {
    SwitchStatement *statement = GC_NEW(Statement) SwitchStatement();
    if (!Next()) // skip 'switch'
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        Fatal("expected `(' after `switch'");
        return 0;
    }
    if (!Next()) // skip '('
        return 0;
    if (!(statement->expression = ParseExpression(END_CONDITION_PARENTHESIS)))
        return 0;
    if (!Next()) // skip next
        return 0;
    if (!IsType(TYPE_scope_begin)) {
        Fatal("expected `{' after `)'");
        return 0;
    }
    if (!Next()) // skip '{'
        return 0;

    Vector<int> seenInts;
    Vector<unsigned int> seenUInts;
    bool hadDefault = false;
    while (!IsType(TYPE_scope_end)) {
        Statement *nextStatement = ParseStatement();
        if (!nextStatement) return 0;
        if (nextStatement->type == Statement::STMT_CASE_LABEL) {
            CaseLabelStatement *caseLabel = (CaseLabelStatement*)nextStatement;
            if (!caseLabel->isDefault) {
                if (!IsConstant(caseLabel->condition)) {
                    Fatal("case label is not a valid constant expression");
                    return 0;
                }
                ConstantExpression *value = Evaluate(caseLabel->condition);
                // "It is a compile-time error to have two case label constant-expression of equal value"
                if (value->type == Expression::INT_CONST) {
                    const int val = IVAL(value);
                    if (NAMESPACE_FUSION::Find(seenInts.begin(), seenInts.end(), val) != seenInts.end()) {
                        Fatal("duplicate case label `%d'", val);
                        return 0;
                    }
                    seenInts.Add(val);
                } else if (value->type == Expression::UINT_CONST) {
                    const unsigned int val = UVAL(value);
                    if (NAMESPACE_FUSION::Find(seenUInts.begin(), seenUInts.end(), val) != seenUInts.end()) {
                        Fatal("duplicate case label `%u'", val);
                        return 0;
                    }
                    seenUInts.Add(val);
                } else {
                    Fatal("case label must be scalar `int' or `uint'");
                    return 0;
                }
            } else {
                // "It's a compile-time error to have more than one default"
                if (hadDefault) {
                    Fatal("duplicate `default' case label");
                    return 0;
                }
                hadDefault = true;
            }
        }
        statement->statements.Add(nextStatement);
        if (!Next())
            return 0;
    }

    // TODO: verify scope of where switches are found
    return statement;
}

CHECK_RETURN CaseLabelStatement *Parser::ParseCaseLabelStatement() {
    CaseLabelStatement *statement = GC_NEW(Statement) CaseLabelStatement();
    if (IsKeyword(KEYWORD_default)) {
        statement->isDefault = true;
        if (!Next()) // skip 'default'
            return 0;
        if (!IsOperator(OPERATOR_colon)) {
            Fatal("expected `:' after `default' in case label");
            return 0;
        }
    } else {
        if (!Next()) // skip 'case'
            return 0;
        statement->condition = ParseExpression(END_CONDITION_COLON);
    }
    return statement;
}

CHECK_RETURN ForStatement *Parser::ParseForStatement() {
    ForStatement *statement = GC_NEW(Statement) ForStatement();
    if (!Next()) // skip 'for'
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        Fatal("expected `(' after `for'");
        return 0;
    }
    if (!Next()) // skip '('
        return 0;
    if (!IsType(TYPE_semicolon))
        if (!(statement->init = ParseDeclarationOrExpressionStatement(END_CONDITION_SEMICOLON)))
            return 0;
    if (!Next()) // skip ';'
        return 0;
    if (!IsType(TYPE_semicolon))
        if (!(statement->condition = ParseExpression(END_CONDITION_SEMICOLON)))
            return 0;
    if (!Next()) // skip ';'
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_end)) {
        if (!(statement->loop = ParseExpression(END_CONDITION_PARENTHESIS)))
            return 0;
    }
    if (!Next()) // skip ')'
        return 0;
    statement->body = ParseStatement();
    return statement;
}

CHECK_RETURN ContinueStatement *Parser::ParseContinueStatement() {
    ContinueStatement *statement = GC_NEW(Statement) ContinueStatement();
    if (!Next()) // skip 'continue'
        return 0;
    return statement;
}

CHECK_RETURN BreakStatement *Parser::ParseBreakStatement() {
    BreakStatement *statement = GC_NEW(Statement) BreakStatement();
    if (!Next())
        return 0; // skip 'break'
    if (!IsType(TYPE_semicolon)) {
        Fatal("expected semicolon after break statement");
        return 0;
    }
    return statement;
}

CHECK_RETURN DiscardStatement *Parser::ParseDiscardStatement() {
    DiscardStatement *statement = GC_NEW(Statement) DiscardStatement();
    if (!Next()) // skip 'discard'
        return 0;
    if (!IsType(TYPE_semicolon)) {
        Fatal("expected semicolon after discard statement");
        return 0;
    }
    return statement;
}

CHECK_RETURN ReturnStatement *Parser::ParseReturnStatement() {
    ReturnStatement *statement = GC_NEW(Statement) ReturnStatement();
    if (!Next()) // skip 'return'
        return 0;
    if (!IsType(TYPE_semicolon)) {
        if (!(statement->expression = ParseExpression(END_CONDITION_SEMICOLON)))
            return 0;
        if (!IsType(TYPE_semicolon)) {
            Fatal("expected semicolon after return statement");
            return 0;
        }
    }
    return statement;
}

CHECK_RETURN DoStatement *Parser::ParseDoStatement() {
    DoStatement *statement = GC_NEW(Statement) DoStatement();
    if (!Next()) // skip 'do'
        return 0;
    if (!(statement->body = ParseStatement()))
        return 0;
    if (!Next())
        return 0;
    if (!IsKeyword(KEYWORD_while)) {
        Fatal("expected `while' after `do'");
        return 0;
    }
    if (!Next()) // skip 'while'
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        Fatal("expected `(' after `while'");
        return 0;
    }
    if (!Next()) // skip '('
        return 0;
    if (!(statement->condition = ParseExpression(END_CONDITION_PARENTHESIS)))
        return 0;
    if (!Next())
        return 0;
    return statement;
}

CHECK_RETURN WhileStatement *Parser::ParseWhileStatement() {
    WhileStatement *statement = GC_NEW(Statement) WhileStatement();
    if (!Next()) // skip 'while'
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        Fatal("expected `(' after `while'");
        return 0;
    }
    if (!Next()) // skip '('
        return 0;
    if (!(statement->condition = ParseDeclarationOrExpressionStatement(END_CONDITION_PARENTHESIS)))
        return 0;
    if (!Next())
        return 0;
    if (!(statement->body = ParseStatement()))
        return 0;
    return statement;
}

CHECK_RETURN DeclarationStatement *Parser::ParseDeclarationStatement(EndCondition condition) {
    lexer.Backup();

    bool is_const = false;
    if (IsKeyword(KEYWORD_const)) {
        is_const = true;
        if (!Next()) // skip 'const'
            return 0;
    }

    Type *type = 0;
    if (IsBuiltin()) {
        type = ParseBuiltin();
    } else if (IsType(TYPE_identifier)) {
        type = FindType(token.as_identifier);
    }

    if (!type) {
        lexer.Restore();
        return 0;
    }

    if (!Next())
        return 0;

    DeclarationStatement *statement = GC_NEW(Statement) DeclarationStatement();
    for (;;) {
        int paranthesisCount = 0;
        while (IsOperator(OPERATOR_paranthesis_begin)) {
            paranthesisCount++;
            if (!Next()) // skip ','
                return 0;
        }
        if (!IsType(TYPE_identifier)) {
            lexer.Restore();
            return 0;
        }

        const char *name = NewString(token.as_identifier);
        if (!Next()) // skip identifier
            return 0;

        for (int i = 0; i < paranthesisCount; i++) {
            if (!IsOperator(OPERATOR_paranthesis_end)) {
                lexer.Restore();
                return 0;
            }
            if (!Next())
                return 0;
        }

        if (statement->variables.IsEmpty() && !IsOperator(OPERATOR_assign)
            && !IsOperator(OPERATOR_comma) && !IsEndCondition(condition))
        {
            lexer.Restore();
            return 0;
        }

        Expression *initial_value = 0;
        if (IsOperator(OPERATOR_assign)) {
            if (!Next()) // skip '='
                return 0;
            if (!(initial_value = ParseExpression(END_CONDITION_COMMA | condition)))
                return 0;
        }

        FunctionVariable *variable = GC_NEW(Variable) FunctionVariable();
        variable->is_const = is_const;
        variable->base_type = type;
        variable->name = NewString(name);
        variable->initial_value = initial_value;
        statement->variables.Add(variable);
        scopes.Top().Add(variable);

        if (IsEndCondition(condition)) {
            break;
        } else if (IsOperator(OPERATOR_comma)) {
            if (!Next()) // skip ','
                return 0;
        } else if (IsOperator(OPERATOR_bracket_begin)) {
            while (IsOperator(OPERATOR_bracket_begin)) {
                variable->is_array = true;
                ConstantExpression *array_size = ParseArraySize();
                if (!array_size)
                    return 0;
                variable->array_sizes.Add(array_size);
                if (!Next()) // skip ']'
                    return 0;
            }
        } else {
            Fatal("syntax error during declaration statement");
            return 0;
        }
    }

    return statement;
}

CHECK_RETURN SimpleStatement *Parser::ParseDeclarationOrExpressionStatement(EndCondition condition) {
    SimpleStatement *declaration = ParseDeclarationStatement(condition);
    if (declaration) {
        return declaration;
    } else {
        return ParseExpressionStatement(condition);
    }
}

CHECK_RETURN Statement *Parser::ParseStatement() {
    if (IsType(TYPE_scope_begin)) {
        return ParseCompoundStatement();
    } else if (IsKeyword(KEYWORD_if)) {
        return ParseIfStatement();
    } else if (IsKeyword(KEYWORD_switch)) {
        return ParseSwitchStatement();
    } else if (IsKeyword(KEYWORD_case) || IsKeyword(KEYWORD_default)) {
        return ParseCaseLabelStatement();
    } else if (IsKeyword(KEYWORD_for)) {
        return ParseForStatement();
    } else if (IsKeyword(KEYWORD_do)) {
        return ParseDoStatement();
    } else if (IsKeyword(KEYWORD_while)) {
        return ParseWhileStatement();
    } else if (IsKeyword(KEYWORD_continue)) {
        return ParseContinueStatement();
    } else if (IsKeyword(KEYWORD_break)) {
        return ParseBreakStatement();
    } else if (IsKeyword(KEYWORD_discard)) {
        return ParseDiscardStatement();
    } else if (IsKeyword(KEYWORD_return)) {
        return ParseReturnStatement();
    } else if (IsType(TYPE_semicolon)) {
        return GC_NEW(Statement) EmptyStatement();
    } else {
        return ParseDeclarationOrExpressionStatement(END_CONDITION_SEMICOLON);
    }
}

CHECK_RETURN Function *Parser::ParseFunction(const TopLevel &Parse) {
    Function *function = GC_NEW(Function) Function();
    function->return_type = Parse.type;
    function->name = NewString(Parse.name);

    if (!Next()) // skip '('
        return 0;
    while (!IsOperator(OPERATOR_paranthesis_end)) {
        FunctionParameter *parameter = GC_NEW(Variable) FunctionParameter();
        while (!IsOperator(OPERATOR_comma) && !IsOperator(OPERATOR_paranthesis_end)) {
            if (IsKeyword(KEYWORD_in)) {
                parameter->storage = QUAL_IN;
            }
            else if (IsKeyword(KEYWORD_out)) {
                parameter->storage = QUAL_OUT;
            }
            else if (IsKeyword(KEYWORD_inout)) {
                parameter->storage = QUAL_INOUT;
            }
            else if (IsKeyword(KEYWORD_highp)) {
                parameter->precision = HIGH_PRECISION;
            }
            else if (IsKeyword(KEYWORD_mediump)) {
                parameter->precision = MEDIUM_PRECISION;
            }
            else if (IsKeyword(KEYWORD_lowp)) {
                parameter->precision = LOW_PRECISION;
            }
            else if (IsKeyword(KEYWORD_coherent)) {
                parameter->memory = MEM_COHERENT;
            }
            else if (IsKeyword(KEYWORD_volatile)) {
                parameter->memory = MEM_VOLATILE;
            }
            else if (IsKeyword(KEYWORD_restrict)) {
                parameter->memory = MEM_RESTRICT;
            }
            else if (IsKeyword(KEYWORD_readonly)) {
                parameter->memory = MEM_READONLY;
            }
            else if (IsKeyword(KEYWORD_writeonly)) {
                parameter->memory = MEM_WRITEONLY;
            }
            else if (IsType(TYPE_identifier)) {
                // TODO: user defined types
                parameter->name = NewString(token.as_identifier);
            }
            else if (IsOperator(OPERATOR_bracket_begin)) {
                while (IsOperator(OPERATOR_bracket_begin)) {
                    parameter->is_array = true;
                    ConstantExpression *array_size = ParseArraySize();
                    if (!array_size)
                        return 0;
                    parameter->array_sizes.Add(array_size);
                }
            }
            else {
                parameter->base_type = ParseBuiltin();
                if (parameter->base_type && parameter->base_type->builtin) {
                    Builtin *builtin = (Builtin*)parameter->base_type;
                    if (builtin->type == KEYWORD_void && !IsStringEmpty(parameter->name)) {
                        Fatal("`void' parameter cannot be named");
                        return 0;
                    }
                }
            }
            if (!Next())
                return 0;
        }

        if (!parameter->base_type) {
            Fatal("expected type");
            return 0;
        }
        function->parameters.Add(parameter);
        if (IsOperator(OPERATOR_comma)) {
            if (!Next())// skip ','
                return 0;
        }
    }
    if (!Next()) // skip ')'
        return 0;

    // If there is just one 'void' than silently drop it
    if (function->parameters.GetCount() == 1) {
        if (function->parameters[0]->base_type->builtin) {
            Builtin *builtin = (Builtin*)function->parameters[0]->base_type;
            if (builtin->type == KEYWORD_void)
                function->parameters.Remove(function->parameters.GetCount()-1);
        }
    }

    // "It is a compile-time or link-time error to declare or define a function main with any other parameters or
    //  return type."
    if (!strcmp(function->name, "main")) {
        if (!function->parameters.IsEmpty()) {
            Fatal("`main' cannot have parameters");
            return 0;
        }
        if (!function->return_type->builtin || ((Builtin*)function->return_type)->type != KEYWORD_void) {
            Fatal("`main' must be declared to return void");
            return 0;
        }
    }

    if (IsType(TYPE_scope_begin)) {
        function->is_prototype = false;
        if (!Next()) // skip '{'
            return 0;

        scopes.Add(Scope());
        for (int i = 0; i < function->parameters.GetCount(); i++)
            scopes.Top().Add(function->parameters[i]);
        while (!IsType(TYPE_scope_end)) {
            Statement *statement = ParseStatement();
            if (!statement)
                return 0;
            function->statements.Add(statement);
            if (!Next())// skip ';'
                return 0;
        }

        scopes.Remove(scopes.GetCount()-1);
    } else if (IsType(TYPE_semicolon)) {
        function->is_prototype = true;
    } else {
        Fatal("expected `{' or `;'");
        return 0;
    }
    return function;
}

// TODO: cleanup
#undef TYPENAME
#define TYPENAME(X) case KEYWORD_##X:
Builtin *Parser::ParseBuiltin() {
    if (!IsType(TYPE_keyword)) {
        Fatal("expected keyword");
        return 0;
    }

    switch (token.as_keyword) {
    #include "Lexemes.h"
        for (int i = 0; i < builtins.GetCount(); i++) {
            if (builtins[i]->type == token.as_keyword) {
                return builtins[i];
            }
        }
        builtins.Add(GC_NEW(Type) Builtin(token.as_keyword));
        return builtins.Top();
        break;
    default:
        break;
    }
    Fatal("internal compiler error: attempted to Parse as builtin type");
    return 0;
}
#undef TYPENAME

CHECK_RETURN ConstructorCall *Parser::ParseConstructorCall() {
    ConstructorCall *expression = GC_NEW(Expression) ConstructorCall();
    if (!(expression->type = ParseBuiltin()))
        return 0;
    if (!Next())
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        Fatal("expected `(' for constructor call");
        return 0;
    }
    if (!Next()) // skip '('
        return 0;
    while (!IsOperator(OPERATOR_paranthesis_end)) {
        Expression *parameter = ParseExpression(END_CONDITION_COMMA | END_CONDITION_PARENTHESIS);
        if (!parameter)
            return 0;
        expression->parameters.Add(parameter);
        if (IsOperator(OPERATOR_comma)) {
            if (!Next()) // skip ','
                return 0;
        }
    }
    return expression;
}

CHECK_RETURN FunctionCall *Parser::ParseFunctionCall() {
    FunctionCall *expression = GC_NEW(Expression) FunctionCall();
    expression->name = NewString(token.as_identifier);
    if (!Next()) // skip identifier
        return 0;
    if (!IsOperator(OPERATOR_paranthesis_begin)) {
        Fatal("expected `(' for function call");
        return 0;
    }
    if (!Next()) return 0; // skip '('
    while (!IsOperator(OPERATOR_paranthesis_end)) {
        Expression *parameter = ParseExpression(END_CONDITION_COMMA | END_CONDITION_PARENTHESIS);
        if (!parameter)
            return 0;
        expression->parameters.Add(parameter);
        if (IsOperator(OPERATOR_comma)) {
            if (!Next()) // skip ','
                return 0;
        }
    }
    return expression;
}

CHECK_RETURN bool Parser::Next() {
    lexer.Read(token, true);
    if (IsType(TYPE_eof)) {
        Fatal("premature end of file");
        return false;
    }
    if (lexer.GetError()) {
        Fatal("%s", lexer.GetError());
        return false;
    }
    return true;
}

BinaryExpression *Parser::CreateExpression() {
    if (!IsType(TYPE_operator)) {
        Fatal("internal compiler error: attempted to create binary expression in wrong context");
        return 0;
    }

    switch (token.as_operator) {
    case OPERATOR_multiply:
    case OPERATOR_divide:
    case OPERATOR_modulus:
    case OPERATOR_plus:
    case OPERATOR_minus:
    case OPERATOR_shift_left:
    case OPERATOR_shift_right:
    case OPERATOR_less:
    case OPERATOR_greater:
    case OPERATOR_less_equal:
    case OPERATOR_greater_equal:
    case OPERATOR_equal:
    case OPERATOR_not_equal:
    case OPERATOR_bit_and:
    case OPERATOR_bit_xor:
    case OPERATOR_logical_and:
    case OPERATOR_logical_xor:
    case OPERATOR_logical_or:
        return GC_NEW(Expression) OperationExpression(token.as_operator);
    case OPERATOR_assign:
    case OPERATOR_add_assign:
    case OPERATOR_sub_assign:
    case OPERATOR_multiply_assign:
    case OPERATOR_divide_assign:
    case OPERATOR_modulus_assign:
    case OPERATOR_shift_left_assign:
    case OPERATOR_shift_right_assign:
    case OPERATOR_bit_and_assign:
    case OPERATOR_bit_xor_assign:
    case OPERATOR_bit_or_assign:
        return GC_NEW(Expression) AssignmentExpression(token.as_operator);
    case OPERATOR_comma:
        return GC_NEW(Expression) SequenceExpression();
    default:
        return 0;
    }
}

Type *Parser::FindType(const char *name) {
    for (int i = 0; i < ast->structures.GetCount(); i++) {
        if (strcmp(ast->structures[i]->name, name))
            continue;
        return (Type*)ast->structures[i];
    }
    return 0;
}

Variable *Parser::FindVariable(const char *identifier) {
    for (int scopeIndex = scopes.GetCount(); scopeIndex > 0; scopeIndex--) {
        Scope &s = scopes[scopeIndex - 1];
        for (int variableIndex = 0; variableIndex < s.GetCount(); variableIndex++) {
            if (!strcmp(s[variableIndex]->name, identifier))
                return s[variableIndex];
        }
    }
    return 0;
}

const char *Parser::GetError() const {
    return error;
}


NAMESPACE_FUSION_END
