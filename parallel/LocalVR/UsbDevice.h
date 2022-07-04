#ifndef __LocalVR_USB_DEVICE_H__
#define __LocalVR_USB_DEVICE_H__


NAMESPACE_HMD_BEGIN


G_BEGIN_DECLS

#define OUVRT_TYPE_USB_DEVICE (ouvrt_usb_device_get_type())
G_DECLARE_DERIVABLE_TYPE(OuvrtUSBDevice, ouvrt_usb_device, OUVRT, USB_DEVICE, \
			 OuvrtDevice)

struct _OuvrtUSBDeviceClass {
	OuvrtDeviceClass parent_class;
};

libusb_device_handle *ouvrt_usb_device_get_handle(OuvrtUSBDevice *self);
void ouvrt_usb_device_set_vid_pid(OuvrtUSBDevice *self, uint16 vid,
				  uint16 pid);

G_END_DECLS


NAMESPACE_HMD_END


#endif
