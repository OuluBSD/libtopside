#ifndef __LocalVR_BLOBWATCH_H__
#define __LocalVR_BLOBWATCH_H__


NAMESPACE_HMD_BEGIN


struct leds;

#define MAX_BLOBS_PER_FRAME  42

struct blob {
	/* center of bounding box */
	uint16 x;
	uint16 y;
	int16 vx;
	int16 vy;
	/* bounding box */
	uint16 width;
	uint16 height;
	uint32 area;
	uint32 last_area;
	uint32 age;
	int16 track_index;
	uint16 pattern;
	int8 led_id;
};

/*
 * Stores all blobs observed in a single frame.
 */
struct blobservation {
	int num_blobs;
	struct blob blobs[MAX_BLOBS_PER_FRAME];
	int tracked_blobs;
	uint8 tracked[MAX_BLOBS_PER_FRAME];
};

struct blobwatch;

struct blobwatch *blobwatch_new(int width, int height);
void blobwatch_process(struct blobwatch *bw, uint8 *frame,
		       int width, int height, uint8 led_pattern_phase,
		       struct leds *leds, struct blobservation **output);
void blobwatch_set_flicker(bool enable);


NAMESPACE_HMD_END


#endif
