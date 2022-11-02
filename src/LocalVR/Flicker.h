#ifndef __LocalVR_FLICKER_H__
#define __LocalVR_FLICKER_H__


NAMESPACE_HMD_BEGIN


struct blob;
struct leds;

void flicker_process(struct blob *blobs, int num_blobs,
		     uint8 led_pattern_phase, struct leds *leds);


NAMESPACE_HMD_END


#endif
