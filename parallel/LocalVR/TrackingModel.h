#ifndef __LocalVR_TRACKING_MODEL_H__
#define __LocalVR_TRACKING_MODEL_H__


NAMESPACE_HMD_BEGIN


/*
 * The tracking model contains reference points of known position and
 * orientation in the tracked device local coordinate system. These represent
 * the tracked object's LEDs (Rift) or Photodiode sensors (Vive).
 */
struct tracking_model {
	unsigned int num_points;
	vec3 *points;
	vec3 *normals;
};

void tracking_model_init(struct tracking_model *model, unsigned int num_points);
void tracking_model_fini(struct tracking_model *model);
void tracking_model_copy(struct tracking_model *dst,
			 struct tracking_model *src);

void tracking_model_dump_obj(struct tracking_model *model, const char *name);
void tracking_model_dump_struct(struct tracking_model *model);


NAMESPACE_HMD_END


#endif
