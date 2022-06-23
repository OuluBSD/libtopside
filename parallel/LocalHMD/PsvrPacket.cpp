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

inline static uint32 read32(const unsigned char** buffer)
{
	uint32 ret = **buffer | (*(*buffer + 1) << 8) | (*(*buffer + 2) << 16) | (*(*buffer + 3) << 24);
	*buffer += 4;
	return ret;
}

bool PsvrDecodeSensorPacket(PsvrSensorPacket* pkt, const unsigned char* buffer, int size)
{
	if(size != 64){
		LOGE("invalid psvr sensor packet size (expected 64 but got %d)", size);
		return false;
	}

	pkt->buttons = read8(&buffer);
	buffer += 1; //skip 1
	pkt->volume = read16(&buffer); //volume
	buffer += 1; //unknown, skip 1
	pkt->state = read8(&buffer);
	buffer += 10; //unknown, skip 10
	pkt->samples[0].tick = read32(&buffer); //TICK
	// acceleration
	for(int i = 0; i < 3; i++){
		pkt->samples[0].gyro[i] = read16(&buffer);
	}

	// rotation
	for(int i = 0; i < 3; i++){
		pkt->samples[0].accel[i] = read16(&buffer);
	}//34
	pkt->samples[1].tick = read32(&buffer);
	for(int i = 0; i < 3; i++){
		pkt->samples[1].gyro[i] = read16(&buffer);
	}
	for(int i = 0; i < 3; i++){
		pkt->samples[1].accel[i] = read16(&buffer);
	}//50
	buffer += 5; //unknown, skip 5
	pkt->button_raw = read16(&buffer);
	pkt->proximity = read16(&buffer); // ~150 (nothing) to 1023 (headset is on)
	buffer += 6; //unknown, skip 6
	pkt->seq = read8(&buffer);

	return true;
}


NAMESPACE_HMD_END

