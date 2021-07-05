#include "TemplatesMach.h"

NAMESPACE_ECS_BEGIN


DevCls GetCenterDevCls() {
	DevCls c;
	c.type = DevCls::CENTER;
	return c;
}

String ValCls::GetName(Type t) {
	switch (t) {
		case AUDIO:		return "audio";
		case VIDEO:		return "video";
		case MIDI:		return "midi";
		case EVENT:		return "event";
		case DATA:		return "data";
		case ORDER:		return "order";
		case RECEIPT:	return "receipt";
		case INVALID:
		default: return "invalid";
	}
}

String DevCls::GetName(Type t) {
	switch (t) {
		case CENTER:	return "center";
		case PERMA:		return "perma";
		case ACCEL:		return "accel";
		case NET:		return "net";
		case INVALID:
		default: return "invalid";
	}
}

DevCls::Type DevCls::Get(String s) {
	if (s == "center")
		return CENTER;
	if (s == "perma")
		return PERMA;
	if (s == "accel")
		return ACCEL;
	if (s == "net")
		return NET;
	
	return INVALID;
}

String EcsTypeCls::GetTypeString(Type t) {
	switch (t) {
		case IFACE:					return "interface";
		case COMP_EXT:				return "ext-component";
		case EXT_TEST_CUSTOMER:		return "test-customer-component";
		case EXT_TEST_AUDIO_OUT:	return "test-audio-out-component";
		case EXT_DBG_CONVERTER:		return "dbg-conv-component";
		default: return "invalid";
	}
}

String GetSubCompString(SubCompCls t) {
	switch (t) {
		case CUSTOMER:		return "customer";
		case INPUT:			return "input";
		case OUTPUT:		return "output";
		case CONVERTER:		return "converter";
		case PIPE:			return "pipe";
		case SIDE_INPUT:	return "side-input";
		case SIDE_OUTPUT:	return "side-output";
		default: return "invalid";
	}
}

hash_t TypeCompCls::GetHashValue() const {
	CombineHash c;
	c.Put(sink.GetHashValue());
	c.Put(src.GetHashValue());
	c.Put(side.GetHashValue());
	c.Put((int)sub);
	return c;
}

hash_t TypeExtCls::GetHashValue() const {
	CombineHash c;
	c.Put(sink.GetHashValue());
	c.Put(src.GetHashValue());
	c.Put(side.GetHashValue());
	c.Put(sub);
	c.Put(ext);
	return c;
}



template <> BinarySample::Type BinarySample::GetSampleType<uint8>() {return U8_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<uint16>() {return U16_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<uint32>() {return U32_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<uint64>() {return U64_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<int8>() {return S8_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<int16>() {return S16_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<int32>() {return S32_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<int64>() {return S64_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<float>() {return FLT_LE;}
template <> BinarySample::Type BinarySample::GetSampleType<double>() {return DBL_LE;}

String BinarySample::ToString(Type t) {
	switch (t) {
		case INVALID: return "INVALID";
		case DEV_INTERNAL: return "DEV_INTERNAL";
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return #type_code "_" #endianess;
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return #type_code "_" #endianess "_" #pack_code;
		PACKED_SAMPLE_LIST
		#undef TYPE
		default: break;
	}
	return "<invalid-sample-type>";
}

int BinarySample::GetSize(Type t) {
	return GetPackedSingleSize(t) * GetPackedCount(t);
}

int BinarySample::GetPackedSingleSize(Type t) {
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 1;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return type_sz;
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return type_sz;
		PACKED_SAMPLE_LIST
		#undef TYPE
		default: break;
	}
	THROW(Exc("BinarySample::GetPackedSingleSize invalid type"));
	return 0;
}

int BinarySample::GetPackedCount(Type t) {
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 1;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return 1;
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return pack_sz;
		PACKED_SAMPLE_LIST
		#undef TYPE
		default: break;
	}
	THROW(Exc("BinarySample::GetPackedCount invalid type"));
	return 0;
}

bool BinarySample::IsUnsigned(Type t) {
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 1;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return !(type_signed);
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return !(type_signed);
		PACKED_SAMPLE_LIST
		#undef TYPE
		default: break;
	}
	THROW(Exc("BinarySample::IsUnsigned invalid type"));
	return false;
}

bool BinarySample::IsSigned(Type t) {
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 0;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return type_signed;
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return type_signed;
		PACKED_SAMPLE_LIST
		#undef TYPE
		default: break;
	}
	THROW(Exc("BinarySample::IsSigned invalid type"));
	return false;
}

bool BinarySample::IsFloating(Type t) {
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 0;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return type_flt;
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return type_flt;
		PACKED_SAMPLE_LIST
		#undef TYPE
		default: break;
	}
	THROW(Exc("BinarySample::IsFloating invalid type"));
	return false;
}

bool BinarySample::IsDecimal(Type t) {
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 0;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return !(type_flt);
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return !(type_flt);
		PACKED_SAMPLE_LIST
		#undef TYPE
		default: break;
	}
	THROW(Exc("BinarySample::IsDecimal invalid type"));
	return false;
}

bool BinarySample::IsLittleEndian(Type t) {
	static const bool LE = true;
	static const bool BE = false;
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 1;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess : return endianess;
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code : return endianess;
		PACKED_SAMPLE_LIST
		#undef TYPE
		#undef ENDIANESS
		default: break;
	}
	THROW(Exc("BinarySample::IsLittleEndian invalid type"));
	return false;
}

bool BinarySample::IsBigEndian(Type t) {
	static const bool BE = true;
	static const bool LE = false;
	switch (t) {
		case INVALID: return 0;
		case DEV_INTERNAL: return 0;
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess: return endianess;
		SAMPLE_LIST
		#undef TYPE
		#define TYPE(type_code, type_sz, type_signed, type_flt, type_aligned, endianess, pack_code, pack_sz) \
			case type_code##_##endianess##_##pack_code: return endianess;
		PACKED_SAMPLE_LIST
		#undef TYPE
		#undef ENDIANESS
		default: break;
	}
	THROW(Exc("BinarySample::IsBigEndian invalid type"));
	return false;
}
















String EventSample::ToString(Type t) {
	switch (t) {
		case CTRL_EVENT: return "CtrlEvent";
		default: break;
	}
	return "<invalid>";
}

int EventSample::GetSize(Type t) {
	switch (t) {
		case CTRL_EVENT: return sizeof(CtrlEvent);
		default: break;
	}
	ASSERT_(0, "invalid type");
	return 0;
}









String OrderSample::ToString(Type t) {
	switch (t) {
		case INVALID: return "INVALID";
		case GENERIC: return "GENERIC";
		case DEV_INTERNAL: return "DEV_INTERNAL";
		#define ORDER_SMPL(type) \
			case type: return #type;
		ORDER_SMPL_LIST
		#undef ORDER_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int OrderSample::GetSize(Type t) {
	PANIC("Invalid call. (Do not use OrderSample with SimpleBufferedValue)");
}






String ReceiptSample::ToString(Type t) {
	switch (t) {
		case INVALID: return "INVALID";
		case GENERIC: return "GENERIC";
		case DEV_INTERNAL: return "DEV_INTERNAL";
		#define RECEIPT_SMPL(type) \
			case type: return #type;
		RECEIPT_SMPL_LIST
		#undef RECEIPT_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int ReceiptSample::GetSize(Type t) {
	PANIC("Invalid call. (Do not use ReceiptSample with SimpleBufferedValue)");
}








String DataSample::ToString(Type t) {
	switch (t) {
		case INVALID: return "INVALID";
		#define DATA_SMPL(type) \
			case type: return #type;
		DATA_SMPL_LIST
		#undef DATA_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int DataSample::GetSize(Type t) {
	PANIC("Invalid call. (Do not use DataSample with SimpleBufferedValue)");
}









String DevBase::ToString() const {
	TODO
	/*#define DEV(x) if (dev_spec == AsTypeCls<x##Spec>()) return #x;
	DEV_LIST
	#undef DEV
	#define IFACE(x) if (dev_spec == AsTypeCls<x##Spec>()) Panic(#x "Spec as DevSpec in DevBase");
	IFACE_LIST
	#undef IFACE*/
	return "invalid";
}


NAMESPACE_ECS_END
