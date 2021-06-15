#ifndef _GLSL_GLSL_h_
#define _GLSL_GLSL_h_

#include <stdlib.h> // free, malloc, int
#include <string.h> // memcpy, strlen
#include <limits.h> // INT_MAX, UINT_MAX
#include <stdarg.h> // va_list, va_copy, va_start, va_end
#include <stdio.h>  // vsnprintf

#include <Local/Local.h>

#if defined(flagGUI) && !defined(__gl_h_)
	#error OpenGL is not included
#endif

#define NAMESPACE_GLSL_BEGIN namespace TS { namespace GLSL {
#define NAMESPACE_GLSL_END   }}
#define NAMESPACE_GLSL       GLSL
#define NS_SHADER              NAMESPACE_GLSL

#include "Util.h"
#include "Lexer.h"
#include "AST.h"
#include "Parser.h"

#endif
