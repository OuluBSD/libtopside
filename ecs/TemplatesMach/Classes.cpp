#include "TemplatesMach.h"

NAMESPACE_TOPSIDE_BEGIN


template <> SoundSample::Type SoundSample::GetSampleType<uint8>() {return S_U8_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<uint16>() {return S_U16_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<uint32>() {return S_U32_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<uint64>() {return S_U64_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<int8>() {return S_S8_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<int16>() {return S_S16_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<int32>() {return S_S32_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<int64>() {return S_S64_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<float>() {return S_FLT_LE;}
template <> SoundSample::Type SoundSample::GetSampleType<double>() {return S_DBL_LE;}

String SoundSample::ToString(Type t) {
	switch (t) {
		#define SND_SMPL(x) case x: return &(#x[2]);
		SND_SMPL_LIST
		#undef SND_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int SoundSample::GetSize(Type t) {
	switch (t) {
		case INVALID: return 0;
		case S_U8_LE: return 1;
		case S_U16_LE: return 2;
		case S_U24_LE: return 3;
		case S_U32_LE: return 4;
		case S_U64_LE: return 8;
		case S_S8_LE: return 1;
		case S_S16_LE: return 2;
		case S_S24_LE: return 3;
		case S_S32_LE: return 4;
		case S_S64_LE: return 8;
		case S_FLT_LE: return 4;
		case S_DBL_LE: return 8;
		case S_U8_BE: return 1;
		case S_U16_BE: return 2;
		case S_U24_BE: return 3;
		case S_U32_BE: return 4;
		case S_U64_BE: return 8;
		case S_S8_BE: return 1;
		case S_S16_BE: return 2;
		case S_S24_BE: return 3;
		case S_S32_BE: return 4;
		case S_S64_BE: return 8;
		case S_FLT_BE: return 4;
		case S_DBL_BE: return 8;
		default: break;
	}
	THROW(Exc("SoundSample::GetSize invalid type"));
	return 0;
}

bool SoundSample::IsUnsigned(Type t) {
	return	(t >= S_U8_LE && t <= S_U64_LE) || (t >= S_U8_BE && t <= S_U64_BE);
}

bool SoundSample::IsSigned(Type t) {
	return	(t >= S_S8_LE && t <= S_DBL_LE) || (t >= S_S8_BE && t <= S_DBL_BE);
}

bool SoundSample::IsFloating(Type t) {
	return	(t >= S_FLT_LE && t <= S_DBL_LE) || (t >= S_FLT_BE && t <= S_DBL_BE);
}

bool SoundSample::IsDecimal(Type t) {
	return	(t >= S_U8_LE && t <= S_S64_LE) || (t >= S_U8_BE && t <= S_S64_BE);
}

bool SoundSample::IsLittleEndian(Type t) {
	return	(t >= S_U8_LE && t <= S_DBL_LE);
}

bool SoundSample::IsBigEndian(Type t) {
	return	(t >= S_U8_BE && t <= S_DBL_BE);
}




String LightSampleFD::ToString(Type t) {
	switch (t) {
		#define LTFD_SMPL(x) case x: return &(#x[2]);
		LTFD_SMPL_LIST
		#undef LTFD_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int LightSampleFD::GetChannelCountFD(Type t) {
	switch (t) {
		case INVALID: return 0;
		case S_R_U8_LE: return 1;
		case S_RG_U8_LE: return 2;
		case S_RGB_U8_LE: return 3;
		case S_RGBA_U8_LE: return 4;
		case S_BGR_U8_LE: return 3;
		case S_R_FLT_LE: return 1;
		case S_RG_FLT_LE: return 2;
		case S_RGB_FLT_LE: return 3;
		case S_RGBA_FLT_LE: return 4;
		case S_BGR_FLT_LE: return 3;
		default: break;
	}
	THROW(Exc("LightSampleFD::GetSize invalid type"));
	return 0;
}

int LightSampleFD::GetChannelSizeFD(Type t) {
	switch (t) {
		case S_R_U8_LE:
		case S_RG_U8_LE:
		case S_RGB_U8_LE:
		case S_RGBA_U8_LE:
		case S_BGR_U8_LE: return 1;
		
		case S_R_FLT_LE:
		case S_RG_FLT_LE:
		case S_RGB_FLT_LE:
		case S_RGBA_FLT_LE:
		case S_BGR_FLT_LE: return sizeof(float);
		
		default: return 0;
	}
}

int LightSampleFD::GetSize(Type t) {
	return GetChannelSizeFD(t) * GetChannelCountFD(t);
}

bool LightSampleFD::IsUnsigned(Type t) {
	return	(t >= S_R_U8_LE && t <= S_BGR_U8_LE);
}

bool LightSampleFD::IsSigned(Type t) {
	return	(t >= S_R_FLT_LE && t <= S_BGR_FLT_LE);
}

bool LightSampleFD::IsFloating(Type t) {
	return	(t >= S_R_FLT_LE && t <= S_BGR_FLT_LE);
}

bool LightSampleFD::IsDecimal(Type t) {
	return	(t >= S_R_U8_LE && t <= S_BGR_U8_LE);
}

bool LightSampleFD::IsLittleEndian(Type t) {
	return true;
}

bool LightSampleFD::IsBigEndian(Type t) {
	return false;
}














String DeviceSample::ToString(Type t) {
	switch (t) {
		case S_CTRL_EVENT: return "CtrlEvent";
		default: break;
	}
	return "<invalid>";
}

int DeviceSample::GetSize(Type t) {
	switch (t) {
		case S_CTRL_EVENT: return sizeof(CtrlEvent);
		default: break;
	}
	ASSERT_(0, "invalid type");
	return 0;
}


NAMESPACE_TOPSIDE_END
