#ifndef __LocalVR_OPENCV_H__
#define __LocalVR_OPENCV_H__


NAMESPACE_HMD_BEGIN


#ifdef flagOPENCV
void estimate_initial_pose(struct blob *blobs, int num_blobs,
			   vec3 *leds, int num_leds,
			   mat3 *camera_matrix, double dist_coeffs[5],
			   quat *rot, vec3 *trans, bool use_extrinsic_guess);
#else
static inline
void estimate_initial_pose(struct blob *blobs, int num_blobs,
			   vec3 *leds, int num_leds,
			   mat3 *camera_matrix, double dist_coeffs[5],
			   quat *rot, vec3 *trans, bool use_extrinsic_guess)
{
	(void)blobs;
	(void)num_blobs;
	(void)leds;
	(void)num_leds;
	(void)camera_matrix;
	(void)dist_coeffs;
	(void)rot;
	(void)trans;
	(void)use_extrinsic_guess;
}
#endif


NAMESPACE_HMD_END


#endif
