#ifndef __LocalVR_LEDS_H__
#define __LocalVR_LEDS_H__


NAMESPACE_HMD_BEGIN


struct leds {
	struct tracking_model model;
	uint16 *patterns;
};

void leds_init(struct leds *leds, int num_leds);
void leds_fini(struct leds *leds);
void leds_copy(struct leds *dst, struct leds *src);

void leds_dump_obj(struct leds *leds);


NAMESPACE_HMD_END


#endif