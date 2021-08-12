#ifndef _ChainCore_Dev_h_
#define _ChainCore_Dev_h_

NAMESPACE_PLAN_BEGIN


class DevSpec {
	
public:
	
	
};

#define DEV(x) \
	class x : public DevSpec { \
		 \
	public: \
		 \
	};

#define DEV_LIST \
	DEV(Center) \
	DEV(Accel) \
	DEV(Net) \
	DEV(Perma)

DEV_LIST

#undef DEV


NAMESPACE_PLAN_END

#endif
