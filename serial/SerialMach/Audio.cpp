#include "SerialMach.h"


NAMESPACE_SERIAL_BEGIN


template <typename SRC, typename DST, bool SRC_NATIVE_ENDIAN, bool DST_NATIVE_ENDIAN>
static void AudioTypeConvert(int src_ch_samples, const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst) {
	int limit = std::min(src_ch_samples, src_fmt.sample_rate);
	const SRC* src_it = (const SRC*)src;
	const SRC* src_end = src_it + limit * src_fmt.channels;
	DST* dst_it = (DST*)dst;
	DST* dst_end = dst_it + limit * dst_fmt.channels;
	for(int i = 0; i < limit; i++) {
		for(int j = 0; j < dst_fmt.channels; j++) {
			SRC src_v = src_it[j % src_fmt.channels];
			DST dst_v = ConvertAudioSample<SRC, DST, SRC_NATIVE_ENDIAN, DST_NATIVE_ENDIAN>(src_v);
			*dst_it++ = dst_v;
		}
		src_it += src_fmt.channels;
	}
	ASSERT(src_it == src_end);
	ASSERT(dst_it == dst_end);
}


bool AudioConvert(int src_ch_samples, const AudioFormat& src_fmt, const byte* src, const AudioFormat& dst_fmt, byte* dst) {
	#define LIST_A(nat_is_be) \
		ITEM_A(nat_is_be, unsigned char, 0) \
		ITEM_A(nat_is_be, unsigned short, 0) \
		ITEM_A(nat_is_be, unsigned int, 0) \
		ITEM_A(nat_is_be, char, 1) \
		ITEM_A(nat_is_be, short, 1) \
		ITEM_A(nat_is_be, int, 1) \
		ITEM_A(nat_is_be, float, 0) \
		ITEM_A(nat_is_be, double, 0) \
		ITEM_A(nat_is_be, float, 1) \
		ITEM_A(nat_is_be, double, 1)
	#define ITEM_A(nat_is_be, a, a_signed) \
		ITEM_B(nat_is_be, a, a_signed, unsigned char, 0) \
		ITEM_B(nat_is_be, a, a_signed, unsigned short, 0) \
		ITEM_B(nat_is_be, a, a_signed, unsigned int, 0) \
		ITEM_B(nat_is_be, a, a_signed, char, 1) \
		ITEM_B(nat_is_be, a, a_signed, short, 1) \
		ITEM_B(nat_is_be, a, a_signed, int, 1) \
		ITEM_B(nat_is_be, a, a_signed, float, 0) \
		ITEM_B(nat_is_be, a, a_signed, double, 0) \
		ITEM_B(nat_is_be, a, a_signed, float, 1) \
		ITEM_B(nat_is_be, a, a_signed, double, 1)
	#define ITEM_B(nat_is_be, a, a_signed, b, b_signed) \
		if (src_fmt_var_size == sizeof(a) && \
			src_fmt_is_var_float == (std::is_same<a,float>() || std::is_same<a,double>()) && \
			src_fmt_is_var_signed == a_signed && \
			dst_fmt_var_size == sizeof(b) && \
			dst_fmt_is_var_float == (std::is_same<b,float>() || std::is_same<b,double>()) && \
			dst_fmt_is_var_signed == b_signed) {\
			if (src_fmt_is_var_bigendian == nat_is_be) { \
				if (dst_fmt_is_var_bigendian == nat_is_be) \
					AudioTypeConvert<a,b,1,1>(src_ch_samples, src_fmt, src, dst_fmt, dst); \
				else \
					AudioTypeConvert<a,b,1,0>(src_ch_samples, src_fmt, src, dst_fmt, dst); \
			} \
			else { \
				if (dst_fmt_is_var_bigendian == nat_is_be) \
					AudioTypeConvert<a,b,0,1>(src_ch_samples, src_fmt, src, dst_fmt, dst); \
				else \
					AudioTypeConvert<a,b,0,0>(src_ch_samples, src_fmt, src, dst_fmt, dst); \
			} \
			return true; \
		}
	int src_fmt_var_size = src_fmt.GetSampleSize();
	bool src_fmt_is_var_float = src_fmt.IsSampleFloat();
	bool src_fmt_is_var_signed = src_fmt.IsSampleSigned();
	bool src_fmt_is_var_bigendian = src_fmt.IsSampleBigEndian();
	int dst_fmt_var_size = dst_fmt.GetSampleSize();
	bool dst_fmt_is_var_float = dst_fmt.IsSampleFloat();
	bool dst_fmt_is_var_signed = dst_fmt.IsSampleSigned();
	bool dst_fmt_is_var_bigendian = dst_fmt.IsSampleBigEndian();
	#if CPU_LITTLE_ENDIAN
	LIST_A(false)
	#else
	LIST_A(true)
	#endif
	#undef LIST_A
	#undef ITEM_A
	#undef ITEM_B
	return false;
}


NAMESPACE_SERIAL_END
