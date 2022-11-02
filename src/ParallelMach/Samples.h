#ifndef _ParallelMach_Samples_h_
#define _ParallelMach_Samples_h_

NAMESPACE_PARALLEL_BEGIN


class SoundSample : public BinarySample {
	
public:
	static const int def_sample_rate = 128;
	
};


class LightSampleFD : public BinarySample {
	
public:
	
	#define LTFD_SMPL_LIST \
		LTFD_SMPL(R_U8_LE,		U8_LE_A) \
		LTFD_SMPL(RG_U8_LE,		U8_LE_AB) \
		LTFD_SMPL(RGB_U8_LE,	U8_LE_ABC) \
		LTFD_SMPL(RGBA_U8_LE,	U8_LE_ABCD) \
		LTFD_SMPL(BGR_U8_LE,	U8_LE_CBA) \
		LTFD_SMPL(R_FLT_LE,		FLT_LE_A) \
		LTFD_SMPL(RG_FLT_LE,	FLT_LE_AB) \
		LTFD_SMPL(RGB_FLT_LE,	FLT_LE_ABC) \
		LTFD_SMPL(RGBA_FLT_LE,	FLT_LE_ABCD) \
		LTFD_SMPL(BGR_FLT_LE,	FLT_LE_CBA)
	
	#define LTFD_SMPL(a,b) static const Type a = b;
	LTFD_SMPL_LIST
	#undef LTFD_SMPL
	
};





class MidiSample : RTTIBase {
	RTTI_DECL0(MidiSample)

public:
	static const int def_sample_rate = 1;

	#define MIDI_SMPL_LIST \
		MIDI_SMPL(MIDI_EVENT)

	typedef enum : byte {
		INVALID,
		DEV_INTERNAL,
		#define MIDI_SMPL(x) x ,
		MIDI_SMPL_LIST
		#undef MIDI_SMPL
		TYPE_COUNT,
		
		DEFAULT = MIDI_EVENT
	} Type;


	static void Clear(Type& t) {t = INVALID;}
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static String ToString(Type t);
	static int GetSize(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};


class EventSample : RTTIBase {
	RTTI_DECL0(EventSample)

public:
	static const int def_sample_rate = 1;

	#define DEV_SMPL_LIST \
		DEV_SMPL(CTRL_EVENT)

	typedef enum : byte {
		INVALID,
		DEV_INTERNAL,
		#define DEV_SMPL(x) x ,
		DEV_SMPL_LIST
		#undef DEV_SMPL
		TYPE_COUNT,
		
		DEFAULT = CTRL_EVENT
	} Type;


	static void Clear(Type& t) {t = INVALID;}
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static String ToString(Type t);
	static int GetSize(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};


class OrderSample : RTTIBase {
	RTTI_DECL0(OrderSample)

public:
	static const int def_sample_rate = 1;

	#define ORDER_SMPL_LIST \
		ORDER_SMPL(AUDIO_ORDER)

	typedef enum : byte {
		INVALID,
		GENERIC,
		DEV_INTERNAL,
		#define ORDER_SMPL(x) x ,
		ORDER_SMPL_LIST
		#undef ORDER_SMPL
		TYPE_COUNT,
		
		DEFAULT = GENERIC
	} Type;


	static void Clear(Type& t) {t = INVALID;}
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static String ToString(Type t);
	static int GetSize(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};


class ReceiptSample : RTTIBase {
	RTTI_DECL0(ReceiptSample)

public:
	static const int def_sample_rate = 1;

	#define RECEIPT_SMPL_LIST \
		RECEIPT_SMPL(AUDIO_RECEIPT)

	typedef enum : byte {
		INVALID,
		DEV_INTERNAL,
		GENERIC,
		#define RECEIPT_SMPL(x) x ,
		RECEIPT_SMPL_LIST
		#undef RECEIPT_SMPL
		TYPE_COUNT,
		
		DEFAULT = GENERIC
	} Type;


	static void Clear(Type& t) {t = INVALID;}
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static String ToString(Type t);
	static int GetSize(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};


class DataSample : RTTIBase {
	RTTI_DECL0(DataSample)

public:
	static const int def_sample_rate = 1;

	#define DATA_SMPL_LIST \
		DATA_SMPL(MODEL_DATA)

	typedef enum : byte {
		INVALID,
		DEV_INTERNAL,
		#define DATA_SMPL(x) x ,
		DATA_SMPL_LIST
		#undef DATA_SMPL
		TYPE_COUNT,
		
		DEFAULT = INVALID
	} Type;


	static void Clear(Type& t) {t = INVALID;}
	static bool IsCopyCompatible(Type a, Type b) {return a == b;}
	static String ToString(Type t);
	static int GetSize(Type t);
	static bool IsValid(Type t) {return (int)t > (int)INVALID && (int)t < (int)TYPE_COUNT;}
};


NAMESPACE_PARALLEL_END

#endif
