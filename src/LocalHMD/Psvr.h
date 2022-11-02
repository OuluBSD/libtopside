#ifndef _LocalHMD_PSVR_H
#define _LocalHMD_PSVR_H


NAMESPACE_HMD_BEGIN


typedef enum {
	PSVR_BUTTON_VOLUME_PLUS = 2,
	PSVR_BUTTON_VOLUME_MINUS = 4,
	PSVR_BUTTON_MIC_MUTE = 8
} PsvrButton;

typedef struct {
	int16 accel[3];
	int16 gyro[3];
	uint32 tick;
} PsvrSensorSample;

typedef struct {
	uint8 buttons;
	uint8 state;
	uint16 volume;
	PsvrSensorSample samples[2];
	uint16 button_raw;
	uint16 proximity;
	uint8 seq;
} PsvrSensorPacket;

static const unsigned char PsvrCinematicmodeOn[8]  = {
	0x23, 0x00, 0xaa, 0x04, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PsvrVrmodeOn[8]  = {
	0x23, 0x00, 0xaa, 0x04, 0x01, 0x00, 0x00, 0x00
};

static const unsigned char PsvrTrackingOn[12]  = {
	0x11, 0x00, 0xaa, 0x08, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
};


static const unsigned char PsvrPowerOn[8]  = {
	0x17, 0x76, 0xaa, 0x04, 0x01, 0x00, 0x00, 0x00
};


void GetVec3FromPsvrVec(const int16* smp, vec3* out_vec);
bool PsvrDecodeSensorPacket(PsvrSensorPacket* pkt, const unsigned char* buffer, int size);


NAMESPACE_HMD_END


#endif
