#ifndef _LocalHMD_WMR_H
#define _LocalHMD_WMR_H


NAMESPACE_HMD_BEGIN


typedef enum {
	HOLOLENS_IRQ_SENSORS = 1,
	HOLOLENS_IRQ_CONTROL = 2,
	HOLOLENS_IRQ_DEBUG = 3,
} HololensSensorsIrqCmd;

typedef struct {
	uint8 id;
	uint16 temperature[4];
	uint64 gyro_timestamp[4];
	int16 gyro[3][32];
	uint64 accel_timestamp[4];
	int32 accel[3][4];
	uint64 video_timestamp[4];
} HololensSensorsPacket;

static const unsigned char HololensSensorsImuOn[64] = {
	0x02, 0x07
};

typedef struct {
	uint32 json_start;
	uint32 json_size;
	char manufacturer[0x40];
	char device[0x40];
	char serial[0x40];
	char uid[0x26];
	char unk[0xd5];
	char name[0x40];
	char revision[0x20];
	char revision_date[0x20];
} WmrConfigHeader;

bool HololensSensorsDecodePacket(HololensSensorsPacket* pkt, const unsigned char* buffer, int size);


NAMESPACE_HMD_END


#endif
