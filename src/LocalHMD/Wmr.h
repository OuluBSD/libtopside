#ifndef _LocalHMD_WMR_H
#define _LocalHMD_WMR_H


NAMESPACE_HMD_BEGIN


#define MICROSOFT_VID                   0x045e
#define HOLOLENS_SENSORS_PID            0x0659
#define MOTION_CONTROLLER_PID           0x065b
#define MOTION_CONTROLLER_PID_SAMSUNG   0x065d


typedef enum {
	HOLOLENS_IRQ_SENSORS = 1,
	HOLOLENS_IRQ_CONTROL = 2,
	HOLOLENS_IRQ_DEBUG = 3,
} HololensSensorsIrqCmd;

typedef enum {
	CONTROLLER_IRQ_SENSORS = 1,
} MotionControllerIrqCmd;

typedef struct {
	uint8 id;
	uint16 temperature[4];
	uint64 gyro_timestamp[4];
	int16 gyro[3][32];
	uint64 accel_timestamp[4];
	int32 accel[3][4];
	uint64 video_timestamp[4];
} HololensSensorsPacket;

#define MOTION_CONTROLLER_BUTTON_STICK     0x01
#define MOTION_CONTROLLER_BUTTON_WINDOWS   0x02
#define MOTION_CONTROLLER_BUTTON_MENU      0x04
#define MOTION_CONTROLLER_BUTTON_GRIP      0x08
#define MOTION_CONTROLLER_BUTTON_PAD_PRESS 0x10
#define MOTION_CONTROLLER_BUTTON_PAD_TOUCH 0x40

typedef struct
{
	uint8 id;
	uint8 buttons;
	uint16 stick[2];
	uint8 trigger;
	uint8 touchpad[2];
	uint8 battery;
	int32 accel[3];
	int32 gyro[3];
	uint32 timestamp;
} MotionControllerPacket;

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

static const unsigned char MotionControllerImuOn[64] = {
	0x06, 0x03, 0x01, 0x00, 0x02
};

static const unsigned char MotionControllerLedsBright[12] = {
	0x03, 0x01, 0x21, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x2c,
};

bool HololensSensorsDecodePacket(HololensSensorsPacket* pkt, const unsigned char* buffer, int size);
bool MotionControllerDecodePacket(MotionControllerPacket* pkt, const unsigned char* buffer, int size);

Device* OpenMotionControllerDevice(Driver* driver, DeviceDescription* desc);


NAMESPACE_HMD_END


#endif
