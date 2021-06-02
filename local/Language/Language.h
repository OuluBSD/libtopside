#ifndef _Language_Language_h
#define _Language_Language_h

#include <Local/Local.h>


#define LANGUAGE						Language
#define NAMESPACE_LANGUAGE_BEGIN		namespace  TS { namespace  LANGUAGE {
#define NAMESPACE_LANGUAGE_END			}}

NAMESPACE_LANGUAGE_BEGIN
using namespace UPP;
NAMESPACE_LANGUAGE_END


#include "Dictionary.h"
#include "Lexer.h"
#include "Parser.h"

#include "Jsesh.h"

#include "Lang.h"
#include "HieroLang.h"

#include "StatParser.h"
#include "ConllParser.h"
#include "AceParser.h"
#include "StanfordParser.h"


NAMESPACE_LANGUAGE_BEGIN



WString TrimBoth(WString s);

class Finnish : public Lang {
	VectorMap<WString, WString> en_native_pronon;
	
public:
	Finnish();
	
	WString PronounceNatively(WString en_pron);
};

inline Finnish& GetFinnish() {return Single<Finnish>();}



NAMESPACE_LANGUAGE_END

#endif
