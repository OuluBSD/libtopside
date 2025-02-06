#include "LittleCore.h"
#include <Emu/Emu.h>

KStream& KStream::operator << (const KString& s) {
	if (fn) {
		fn(s.str, s.sz, arg);
	}
	return *this;
}

KStream& KStream::operator << (char c) {
	if (fn) {
		fn(&c, 1, arg);
	}
	return *this;
}

KStream& KCout() {
	static KStream s;
	return s;
}

KStream& KCerr() {
	static KStream s;
	return s;
}
