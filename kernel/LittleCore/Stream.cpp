#include "LittleCore.h"

KStream& KStream::operator << (const KString& s) {
	
	
	return *this;
}

KStream& KStream::operator << (char c) {
	
	
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
