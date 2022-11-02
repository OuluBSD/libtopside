#ifndef _ToyHub_Session_h_
#define _ToyHub_Session_h_

NAMESPACE_TOYHUB_BEGIN


class UserSession {
	Time created;
	
public:
	UserSession();
	
	
};

inline ArrayMap<String, UserSession>& GetUserSessions() {return Single<ArrayMap<String, UserSession> >();}

String NewCookie();


NAMESPACE_TOYHUB_END

#endif
