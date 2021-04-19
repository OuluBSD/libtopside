#include "FusionCore.h"

NAMESPACE_FUSION_BEGIN

// Lookup table of keywords
#undef KEYWORD
#define KEYWORD(X) { #X, KEYWORD_##X },
static const KeywordInfo keywords[] = {
    #include "Lexemes.h"
};
#undef KEYWORD
#define KEYWORD(...)

// Lookup table of operators
#undef OPERATOR
#define OPERATOR(X, S, PREC) { #X, S, PREC },
static const OperatorInfo operators[] = {
    #include "Lexemes.h"
};
#undef OPERATOR
#define OPERATOR(...)

Token::Token()
    : type(0)
{
    as_double = 0.0;
}

int Token::GetPrecedence() const {
    if (type == TYPE_operator)
        return operators[as_operator].precedence;
    return -1;
}

/// Location
Location::Location()
    : column(1)
    , line(1)
    , position(0)
{
}

void Location::AdvanceColumn(int count) {
    column += count;
    position += count;
}

void Location::AdvanceLine() {
    line++;
    position++;
    column = 1;
}

static inline bool IsDigit(int ch) {
    return unsigned(ch) - '0' < 10;
}

static inline bool IsChar(int ch) {
    return (unsigned(ch) | 32) - 'a' < 26;
}

static inline bool IsOctal(int ch) {
    return unsigned(ch) - '0' < 8;
}

static inline bool IsHex(int ch) {
    return (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F') || IsDigit(ch);
}

static inline bool IsSpace(int ch) {
    return (ch >= '\t' && ch <= '\r') || ch == ' ';
}

Lexer::Lexer(const char *string)
    : data(string)
    , length(0)
    , error(0)
{
    if (data)
        length = strlen(data);
}

int Lexer::At(int offset) const {
    if (GetPosition() + offset < length)
        return data[GetPosition() + offset];
    return 0;
}

void Lexer::Read(Token &out) {
    // Any previous identifier must be freed
    if (out.type == TYPE_identifier)
        free(out.as_identifier);

    // TODO: Line continuation (backslash `\'.)
    if (GetPosition() == length) {
        out.type = TYPE_eof;
        return;
    }

    int ch1 = At(1);
    int ch2 = At(2);

    // Lex numerics
    if (IsDigit(At()) || (At() == '.' && IsDigit(ch1)))
    {
        bool is_float = false;
        bool is_double = false;
        bool is_unsigned = false;
        bool is_octalish = false;
        bool is_hexish = false;

        if (At() == '0') {
            if (ch1 && (ch1 == 'x' || ch1 == 'X')) {
                is_hexish = true;
                location.AdvanceColumn(2);
            } else {
                is_octalish = true;
            }
        }

        Vector<char> numeric = ReadNumeric(is_octalish, is_hexish);
        if (GetPosition() != length && At() == '.') {
            is_float = true;
            is_octalish = false;
            numeric.Add('.');
            location.AdvanceColumn();
            Vector<char> others = ReadNumeric(is_octalish, is_hexish);
            numeric.Reserve(numeric.GetCount() + others.GetCount());
            numeric.Append(others);
        }

        if (GetPosition() != length && (At() == 'e' || At() == 'E')) {
            ch1 = At(1);
            ch2 = At(2);
            if ((ch1 == '+' || ch1 == '-') && (ch2 >= '0' && ch2 <= '9')) {
                numeric.Add(ch1);
                numeric.Add(ch2);
                location.AdvanceColumn(2);
                Vector<char> others = ReadNumeric(is_octalish, is_hexish);
                numeric.Reserve(numeric.GetCount() + others.GetCount());
                numeric.Append(others);
                is_float = true;
                is_octalish = false;
            } else {
                error = "invalid numeric literal";
                return;
            }
        }

        if (GetPosition() != length && IsChar(At())) {
            ch1 = At(1);
            if (At() == 'f' || At() == 'F') {
                is_float = true;
                is_octalish = false;
            } else if ((At() == 'l' && ch1 == 'f') || (At() == 'L' && ch1 == 'F')) {
                is_float = false;
                is_double = true;
                is_octalish = false;
                location.AdvanceColumn();
            } else if (At() == 'u' || At() == 'U') {
                if (is_float) {
                    error = "invalid use of suffix on literal";
                    return;
                }
                is_unsigned = true;
            } else {
                error = "invalid numeric literal";
                return;
            }
            location.AdvanceColumn();
        }

        if (is_hexish && (is_float || is_double)) {
            error = "invalid numeric literal";
            return;
        }

        numeric.Add('\0');
        int base = is_hexish ? 16 : (is_octalish ? 8 : 10);
        char *error;
        if (is_float) {
            out.type = TYPE_constant_float;
            out.as_float = strtof(&numeric[0], &error);
            if (error == &numeric[0]) {
                this->error = "invalid numeric literal";
                return;
            }
        } else if (is_double) {
            out.type = TYPE_constant_double;
            out.as_double = strtod(&numeric[0], &error);
            if (error == &numeric[0]) {
                this->error = "invalid numeric literal";
                return;
            }
        } else if (is_unsigned) {
            out.type = TYPE_constant_uint;
            unsigned long long value = strtoull(&numeric[0], 0, base);
            if (value <= UINT_MAX) {
                out.as_unsigned = (unsigned int)value;
            } else {
                this->error = "literal needs more than 32-bits";
            }
        } else {
            out.type = TYPE_constant_int;
            long long value = strtoll(&numeric[0], 0, base);
            if (value <= INT_MAX) {
                out.as_int = (int)value;
            } else {
                this->error = "literal needs more than 32-bits";
            }
        }
    } else if (IsChar(At()) || At() == '_') {
        // Identifiers
        out.type = TYPE_identifier;
        Vector<char> identifier;
        while (GetPosition() != length && (IsChar(At()) || IsDigit(At()) || At() == '_')) {
            identifier.Add(At());
            location.AdvanceColumn();
        }
        identifier.Add('\0');
        out.as_identifier = (char *)malloc(identifier.GetCount());
        if (!out.as_identifier) {
            error = "Out of memory";
            return;
        }
        memcpy(out.as_identifier, &identifier[0], identifier.GetCount());

        // Or is it a keyword?
        for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
            if (strcmp(keywords[i].name, out.as_identifier))
                continue;
            free(out.as_identifier);
            out.as_identifier = 0;
            out.type = TYPE_keyword;
            out.as_keyword = int(i);
            break;
        }
    } else {
        switch (At()) {
        // Non operators
        case '\n':
        case '\t':
        case '\f':
        case '\v':
        case '\r':
        case ' ':
            while (GetPosition() < length && IsSpace(At())) {
                if (At() == '\n')
                    location.AdvanceLine();
                else
                    location.AdvanceColumn();
            }
            out.type = TYPE_whitespace; // Whitespace already skippped
            break;
        case ';':
            out.type = TYPE_semicolon;
            location.AdvanceColumn();
            break;
        case '{':
            out.type = TYPE_scope_begin;
            location.AdvanceColumn();
            break;
        case '}':
            out.type = TYPE_scope_end;
            location.AdvanceColumn();
            break;

        // Operators
        case '.':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_dot;
            break;
        case '+':
            out.type = TYPE_operator;
            if (ch1 == '+')
                out.as_operator = OPERATOR_increment;
            else if (ch1 == '=')
                out.as_operator = OPERATOR_add_assign;
            else
                out.as_operator = OPERATOR_plus;
            break;
        case '-':
            out.type = TYPE_operator;
            if (ch1 == '-')
                out.as_operator = OPERATOR_decrement;
            else if (ch1 == '=')
                out.as_operator = OPERATOR_sub_assign;
            else
                out.as_operator = OPERATOR_minus;
            break;
        case '/':
            if (ch1 == '/') {
                // Skip line comments
                while (GetPosition() != length) {
                    if (At() == '\n') {
                        location.AdvanceLine();
                        break;
                    }
                    location.AdvanceColumn();
                }
                out.type = TYPE_comment;
            } else if (ch1 == '*') {
                // Skip block comments
                while (GetPosition() != length) {
                    if (At() == '\n') {
                        location.AdvanceLine();
                        continue;
                    }
                    if (At() == '*' && GetPosition() + 1 < length && data[GetPosition() + 1] == '/') {
                        location.AdvanceColumn(2);
                        break;
                    }
                    location.AdvanceColumn();
                }
                out.type = TYPE_comment;
            } else if (ch1 == '=') {
                out.type = TYPE_operator;
                out.as_operator = OPERATOR_divide_assign;
            } else {
                out.type = TYPE_operator;
                out.as_operator = OPERATOR_divide;
            }
            break;
        case '*':
            out.type = TYPE_operator;
            if (ch1 == '=')
                out.as_operator = OPERATOR_multiply_assign;
            else
                out.as_operator = OPERATOR_multiply;
            break;
        case '%':
            out.type = TYPE_operator;
            if (ch1 == '=')
                out.as_operator = OPERATOR_modulus_assign;
            else
                out.as_operator = OPERATOR_modulus;
            break;
        case '<':
            out.type = TYPE_operator;
            if (ch1 == '<' && ch2 == '=')
                out.as_operator = OPERATOR_shift_left_assign;
            else if (ch1 == '<')
                out.as_operator = OPERATOR_shift_left;
            else if (ch1 == '=')
                out.as_operator = OPERATOR_less_equal;
            else
                out.as_operator = OPERATOR_less;
            break;
        case '>':
            out.type = TYPE_operator;
            if (ch1 == '>' && ch2 == '=')
                out.as_operator = OPERATOR_shift_right_assign;
            else if (ch1 == '>')
                out.as_operator = OPERATOR_shift_right;
            else if (ch1 == '=')
                out.as_operator = OPERATOR_greater_equal;
            else
                out.as_operator = OPERATOR_greater;
            break;
        case '[':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_bracket_begin;
            break;
        case ']':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_bracket_end;
            break;
        case '(':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_paranthesis_begin;
            break;
        case ')':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_paranthesis_end;
            break;
        case '^':
            out.type = TYPE_operator;
            if (ch1 == '^')
                out.as_operator = OPERATOR_logical_xor;
            else if (ch1 == '=')
                out.as_operator = OPERATOR_bit_xor_assign;
            else
                out.as_operator = OPERATOR_bit_xor;
            break;
        case '|':
            out.type = TYPE_operator;
            if (ch1 == '|')
                out.as_operator = OPERATOR_logical_or;
            else if (ch1 == '=')
                out.as_operator = OPERATOR_bit_or_assign;
            else
                out.as_operator = OPERATOR_bit_or;
            break;
        case '&':
            out.type = TYPE_operator;
            if (ch1 == '&')
                out.as_operator = OPERATOR_logical_and;
            else if (ch1 == '=')
                out.as_operator = OPERATOR_bit_and_assign;
            else
                out.as_operator = OPERATOR_bit_and;
            break;
        case '~':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_bit_not;
            break;
        case '=':
            out.type = TYPE_operator;
            if (ch1 == '=')
                out.as_operator = OPERATOR_equal;
            else
                out.as_operator = OPERATOR_assign;
            break;
        case '!':
            out.type = TYPE_operator;
            if (ch1 == '=')
                out.as_operator = OPERATOR_not_equal;
            else
                out.as_operator = OPERATOR_logical_not;
            break;
        case ':':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_colon;
            break;
        case ',':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_comma;
            break;
        case '?':
            out.type = TYPE_operator;
            out.as_operator = OPERATOR_questionmark;
            break;
        default:
            error = "invalid character encountered";
            return;
        }
        // Skip whitespace for operator
        if (out.type == TYPE_operator)
            location.AdvanceColumn(strlen(operators[out.as_operator].string));
    }
}

Vector<char> Lexer::ReadNumeric(bool is_octalish, bool is_hexish) {
    Vector<char> digits;
    if (is_octalish) {
        while (GetPosition() < length && IsOctal(At())) {
            digits.Add(At());
            location.AdvanceColumn();
        }
    } else if (is_hexish) {
        while (GetPosition() < length && IsHex(At())) {
            digits.Add(At());
            location.AdvanceColumn();
        }
    } else {
        while (GetPosition() < length && IsDigit(At())) {
            digits.Add(At());
            location.AdvanceColumn();
        }
    }
    return digits;
}

Token Lexer::Peek() {
    Token out;
    Backup();
    Read(out, true);
    Restore();
    return out;
}

void Lexer::Read(Token &out, bool) {
    do {
        Read(out);
    }
    while ((out.type == TYPE_whitespace || out.type == TYPE_comment) && !error);
}

const char *Lexer::GetError() const {
    return error;
}

void Lexer::Backup() {
    backup = location;
}

void Lexer::Restore() {
    location = backup;
}

NAMESPACE_FUSION_END
