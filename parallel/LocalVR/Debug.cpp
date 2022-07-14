#include "LocalVR.h"


NAMESPACE_HMD_BEGIN


int debug_mode = 0;

#define IMU_FIFO_LEN 32
static struct imu_state imu_fifo[IMU_FIFO_LEN];
static unsigned int fifo_in = 0;
static unsigned int fifo_out = 0;

unsigned int debug_imu_fifo_in(struct imu_state *samples, unsigned int n)
{
	int i = 0;

	while (n--) {
		if (((fifo_out + 1) % IMU_FIFO_LEN) == (fifo_in % IMU_FIFO_LEN))
			return i;
		imu_fifo[fifo_out % IMU_FIFO_LEN] = *samples;
		__sync_synchronize();
		fifo_out++;
		samples++;
		i++;
	}

	return i;
}

unsigned int debug_imu_fifo_out(struct imu_state *samples, unsigned int n)
{
	int i = 0;

	while (n--) {
		if ((fifo_in % IMU_FIFO_LEN) == (fifo_out % IMU_FIFO_LEN))
			return i;
		*samples = imu_fifo[fifo_in % IMU_FIFO_LEN];
		__sync_synchronize();
		fifo_in++;
		samples++;
		i++;
	}

	return i;
}




#ifdef flagDEBUG_SERVER

DebugService* dbg_srv;


void debug_stream_init(int *argc, char **argv[]) {
	SetCoutLog();
	
	dbg_srv = new DebugService();
}

struct debug_stream *debug_stream_new(const struct DebugStreamDescription *desc) {
	for(int i = 0; i < DebugService::STREAM_COUNT; i++) {
		if (!dbg_srv->streams[i].in_use) {
			dbg_srv->streams[i].in_use = true;
			
			LOG(i << ": " << desc->width << "x" << desc->height << ", fmt=" << desc->format << ", framerate=" << desc->framerate.numerator << "/" << desc->framerate.denominator);
			return (debug_stream*)&dbg_srv->streams[i];
		}
	}
	return NULL;
}

struct debug_stream *debug_stream_unref(struct debug_stream *stream) {
	return NULL;
}

void debug_stream_frame_push(struct debug_stream *stream,
			     void *frame, size_t size, size_t w, size_t h, size_t attach_offset,
			     struct blobservation *ob, quat *rot,
			     vec3 *trans, double timestamps[3], int exposure) {
	if (!stream)
		return;
	
	DebugService::Stream& s = *(DebugService::Stream*)stream;
	
	//LOG("debug_stream_frame_push: size=" << IntStr64(size) << ", " << HexStr(frame) << ", exposure=" << exposure);
	
	if (s.frame_lock)
		return;
	
	s.sz = Size(w,h);
	s.frame.SetCount(size);
	memcpy(s.frame.Begin(), frame, size);
	
	if (!exposure)
		dbg_srv->WhenDarkFrame(s);
	else
		dbg_srv->WhenBrightFrame(s);
}

void debug_stream_deinit() {
	if (dbg_srv) {
		delete dbg_srv;
		dbg_srv = 0;
	}
}









LocalVRDebugService::LocalVRDebugService() {
	
}

bool LocalVRDebugService::Init(String name) {
	DaemonService* ds = FindService("TcpServer");
	SerialServiceServer* server = dynamic_cast<SerialServiceServer*>(ds);
	if (!server) {
		LOG("LocalVRDebugService::Init: error: tcp server is required");
		return false;
	}
	
	server->AddTcpSocket(NET_LATEST_BRIGHT_FRAME, THISBACK(LatestBrightFrame));
	server->AddTcpSocket(NET_LATEST_DARK_FRAME, THISBACK(LatestDarkFrame));
	
	return true;
}

void LocalVRDebugService::Update() {
	
}

void LocalVRDebugService::Deinit() {
	
}

void LocalVRDebugService::LatestBrightFrame(TcpSocket& out) {
	DebugService::Stream& s = dbg_srv->streams[0];
	if (s.frame.IsEmpty())
		return;
	Send(out, s.frame, s.sz);
}

void LocalVRDebugService::LatestDarkFrame(TcpSocket& out) {
	DebugService::Stream& s = dbg_srv->streams[1];
	if (s.frame.IsEmpty())
		return;
	Send(out, s.frame, s.sz);
}

void LocalVRDebugService::SetBrightCallback(Callback1<DebugService::Stream&> cb) {
	dbg_srv->WhenBrightFrame << cb;
}

void LocalVRDebugService::SetDarkCallback(Callback1<DebugService::Stream&> cb) {
	dbg_srv->WhenDarkFrame << cb;
}

void LocalVRDebugService::Send(TcpSocket& out, const Vector<byte>& frame, Size sz) {
	//LOG("Send: " << HexStr(frame) << ", " << size << ", " << sz.ToString());
	out.Put(&sz.cx, sizeof(sz.cx));
	out.Put(&sz.cy, sizeof(sz.cy));
	int size = frame.GetCount();
	out.Put(&size, sizeof(size));
	out.Put(frame.Begin(), size);
}


#endif


NAMESPACE_HMD_END

