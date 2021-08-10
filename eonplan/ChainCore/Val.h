#ifndef _ChainCore_Val_h_
#define _ChainCore_Val_h_


class ValSpec {
	
public:
	
	
};


#define VAL(x) \
	class x : public ValSpec { \
		 \
	public: \
		 \
	};


#define VAL_LIST \
	VAL(Order) \
	VAL(Receipt) \
	VAL(Audio) \
	VAL(Video) \
	VAL(Midi) \
	VAL(Event)

#define VAL2_LIST(x) \
	VAL2(x, Order) \
	VAL2(x, Receipt) \
	VAL2(x, Audio) \
	VAL2(x, Video) \
	VAL2(x, Midi) \
	VAL2(x, Event)

VAL_LIST

#undef VAL


#endif
