#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN

String GetAccessString(CodeAccess acc) {
	switch (acc) {
		case ACC_PRIVATE:	return "private";
		case ACC_PROTECTED:	return "protected";
		case ACC_PUBLIC:	return "public";
		default:			return "invalid";
	}
}


NAMESPACE_TOPSIDE_END
