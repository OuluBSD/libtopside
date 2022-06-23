#include "LocalHMD.h"


NAMESPACE_HMD_BEGIN


#ifdef _MSC_VER
#define inline __inline
#endif

inline static uint8 read8(const unsigned char** buffer)
{
	uint8 ret = **buffer;
	*buffer += 1;
	return ret;
}

inline static int16 read16(const unsigned char** buffer)
{
	int16 ret = **buffer | (*(*buffer + 1) << 8);
	*buffer += 2;
	return ret;
}

inline static int32 read32(const unsigned char** buffer)
{
	int32 ret = **buffer | (*(*buffer + 1) << 8) | (*(*buffer + 2) << 16) | (*(*buffer + 3) << 24);
	*buffer += 4;
	return ret;
}

inline static uint64 read64(const unsigned char** buffer)
{
	uint64 ret = (uint64)**buffer |
		       ((uint64)*(*buffer + 1) << 8) |
		       ((uint64)*(*buffer + 2) << 16) |
		       ((uint64)*(*buffer + 3) << 24) |
		       ((uint64)*(*buffer + 4) << 32) |
		       ((uint64)*(*buffer + 5) << 40) |
		       ((uint64)*(*buffer + 6) << 48) |
		       ((uint64)*(*buffer + 7) << 56);
	*buffer += 8;
	return ret;
}

bool HololensSensorsDecodePacket(HololensSensorsPacket* pkt, const unsigned char* buffer, int size)
{
	if(size != 497 &&
	   size != 381){
		LOGE("invalid hololens sensor packet size (expected 497 but got %d)", size);
		return false;
	}

	pkt->id = read8(&buffer);
	for(int i = 0; i < 4; i++)
		pkt->temperature[i] = read16(&buffer);
	for(int i = 0; i < 4; i++)
		pkt->gyro_timestamp[i] = read64(&buffer);
	for(int i = 0; i < 3; i++){
		for (int j = 0; j < 32; j++)
			pkt->gyro[i][j] = read16(&buffer);
	}
	for(int i = 0; i < 4; i++)
		pkt->accel_timestamp[i] = read64(&buffer);
	for(int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++)
			pkt->accel[i][j] = read32(&buffer);
	}
	for(int i = 0; i < 4; i++)
		pkt->video_timestamp[i] = read64(&buffer);

	return true;
}


NAMESPACE_HMD_END

