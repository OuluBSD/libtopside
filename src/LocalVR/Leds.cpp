#include "LocalVR.h"


NAMESPACE_HMD_BEGIN


void leds_init(struct leds *leds, int num_leds)
{
	tracking_model_init(&leds->model, num_leds);
	leds->patterns = (uint16*)malloc(num_leds * sizeof(uint16));
}

void leds_fini(struct leds *leds)
{
	free(leds->patterns);
	leds->patterns = NULL;
	tracking_model_fini(&leds->model);
}

void leds_copy(struct leds *dst, struct leds *src)
{
	size_t size = src->model.num_points * sizeof(uint16);

	tracking_model_copy(&dst->model, &src->model);
	free(dst->patterns);
	dst->patterns = (uint16*)malloc(size);
	memcpy(dst->patterns, src->patterns, size);
}


NAMESPACE_HMD_END

