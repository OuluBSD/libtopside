#include "TemplatesMach.h"

NAMESPACE_TOPSIDE_BEGIN


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
	#define DEV(x) if (dev_spec == AsTypeCls<x##Spec>()) return #x;
	DEV_LIST
	#undef DEV
	#define IFACE(x) if (dev_spec == AsTypeCls<x##Spec>()) Panic(#x "Spec as DevSpec in DevBase");
	IFACE_LIST
	#undef IFACE
	return "invalid";
}


NAMESPACE_TOPSIDE_END
