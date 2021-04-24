#include "ToyHub.h"

NAMESPACE_TOYHUB_BEGIN


UserSession::UserSession() {
	created = GetUtcTime();
	
	
}



String NewCookie() {
	String cookie;
	do {
		cookie = "";
		for(int i = 0; i < 35; i++) {
			cookie.Cat(35 + Random(92));
		}
	}
	while (GetUserSessions().Find(cookie) >= 0);
	
	UserSession& ses = GetUserSessions().GetAdd(cookie);
	
	return cookie;
}


NAMESPACE_TOYHUB_END
