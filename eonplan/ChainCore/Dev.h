#ifndef _ChainCore_Dev_h_
#define _ChainCore_Dev_h_


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


#endif
