#ifndef __LocalVR_TRACKER_H__
#define __LocalVR_TRACKER_H__


NAMESPACE_HMD_BEGIN


#define OUVRT_TYPE_TRACKER (ouvrt_tracker_get_type())
G_DECLARE_FINAL_TYPE(OuvrtTracker, ouvrt_tracker, OUVRT, TRACKER, GObject)

struct leds;
struct blob;
struct blobservation;

void ouvrt_tracker_register_leds(OuvrtTracker *tracker, struct leds *leds);
void ouvrt_tracker_unregister_leds(OuvrtTracker *tracker, struct leds *leds);

void ouvrt_tracker_set_radio_address(OuvrtTracker *tracker,
				     const uint8 address[5]);
void ouvrt_tracker_get_radio_address(OuvrtTracker *tracker, uint8 address[5]);

void ouvrt_tracker_add_exposure(OuvrtTracker *tracker,
				uint64 device_timestamp, uint64 time,
				uint8 led_pattern_phase);

void ouvrt_tracker_process_frame(OuvrtTracker *tracker, uint8 *frame,
				 int width, int height, uint64 sof_time,
				 struct blobservation **ob);
void ouvrt_tracker_process_blobs(OuvrtTracker *tracker,
				 struct blob *blobs, int num_blobs,
				 mat3 *camera_matrix, double dist_coeffs[5],
				 quat *rot, vec3 *trans);

OuvrtTracker *ouvrt_tracker_new();


NAMESPACE_HMD_END


#endif
