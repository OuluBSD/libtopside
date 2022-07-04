#ifndef __LocalVR_DEBUG_H__
#define __LocalVR_DEBUG_H__


NAMESPACE_HMD_BEGIN


#define DEBUG_MODE_SHM	1
#define DEBUG_MODE_X	2
#define DEBUG_MODE_PNG	3

extern int debug_mode;

struct debug_stream;

struct fraction {
	unsigned int numerator;
	unsigned int denominator;
};

#define FORMAT_GRAY	0x56595559
#define FORMAT_YUYV	0x59415247
#define FORMAT_RGBX	0x58424752

struct DebugStreamDescription {
	unsigned int width;
	unsigned int height;
	unsigned int format;
	struct fraction framerate;
};

struct DebugAttachment {
	struct blobservation blobservation;
	quat rot;
	vec3 trans;
	int num_imu_samples;
	struct imu_state imu_samples[32];
	double timestamps[4];
};

int DebugParseArg(const char *arg);

unsigned int debug_imu_fifo_in(struct imu_state *samples, unsigned int n);
unsigned int debug_imu_fifo_out(struct imu_state *samples, unsigned int n);

#ifdef HAVE_DEBUG_STREAM
void debug_stream_init(int *argc, char **argv[]);
struct debug_stream *debug_stream_new(const struct DebugStreamDescription *desc);
struct debug_stream *debug_stream_unref(struct debug_stream *stream);
void debug_stream_frame_push(struct debug_stream *stream,
			     void *frame, size_t size, size_t attach_offset,
			     struct blobservation *ob, quat *rot,
			     vec3 *trans, double timestamps[3]);
void debug_stream_deinit(void);
#else
static inline void debug_stream_init(int *argc, char **argv[])
{
}

static inline struct debug_stream *debug_stream_new(struct DebugStreamDescription *d)
{
	return NULL;
}

static inline struct debug_stream *debug_stream_unref(struct debug_stream *s)
{
	return NULL;
}

static inline void debug_stream_frame_push(struct debug_stream *stream,
					   void *frame, size_t size,
					   size_t attach_offset,
					   struct blobservation *ob, quat *rot,
					   vec3 *trans, double timestamps[3])
{
}

static inline void debug_stream_deinit(void)
{
}
#endif


NAMESPACE_HMD_END


#endif
