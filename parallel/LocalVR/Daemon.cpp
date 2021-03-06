#include "LocalVR.h"

#include <errno.h>
#include <getopt.h>
#include <glib.h>
#include <gio/gio.h>
#include <libudev.h>
#include <locale.h>
#include <poll.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>


NAMESPACE_HMD_BEGIN


/*#include "dbus.h"
#include "debug.h"
#include "device.h"
#include "usb-ids.h"
#include "psvr.h"
#include "rift.h"
#include "rift-sensor.h"
#include "camera-dk2.h"
#include "hololens-camera.h"
#include "hololens-camera2.h"
#include "hololens-imu.h"
#include "motion-controller.h"
#include "lenovo-explorer.h"
#include "pipewire.h"
#include "telemetry.h"
#include "vive-headset.h"
#include "vive-headset-mainboard.h"
#include "vive-controller.h"
#include "vive-controller-usb.h"*/

#define NUM_MATCHES	14

struct interface_match {
	int iface;
	const char *subsystem;
	const char *name;
};

struct device_match {
	uint16 vid;
	uint16 pid;
	const char *name;
	union {
		const char *subsystem;
		const struct interface_match *interfaces;
	};
	int num_interfaces;
	OuvrtDevice *(*create)(const char *devnode);
};

static const struct device_match device_matches[NUM_MATCHES] = {
	#if 0
	{
		.vid = VID_SONY,
		.pid = PID_PSVR,
		.subsystem = "usb",
		.name = "PSVR",
		.create = psvr_new,
	}, {
		.vid = VID_OCULUSVR,
		.pid = PID_RIFT_CV1,
		.name = "Rift CV1",
		.interfaces = (const struct interface_match[]){
			{ 0, .subsystem = "hidraw", .name = "IMU" },
			{ 1, .subsystem = "hidraw", .name = "Radio" },
		},
		.num_interfaces = 2,
		.create = rift_cv1_new,
	}, {
		.vid = VID_OCULUSVR,
		.pid = PID_RIFT_DK2,
		.subsystem = "hidraw",
		.name = "Rift DK2",
		.create = rift_dk2_new,
	}, {
		.vid = VID_OCULUSVR,
		.pid = PID_RIFT_SENSOR,
		.subsystem = "usb",
		.name = "Rift Sensor",
		.create = rift_sensor_new,
	}, {
		.vid = VID_OCULUSVR,
		.pid = PID_CAMERA_DK2,
		.subsystem = "video4linux",
		.name = "Camera DK2",
		.create = camera_dk2_new,
	}, {
		.vid = VID_HTC,
		.pid = PID_VIVE,
		.subsystem = "hidraw",
		.name = "Vive Headset Mainboard",
		.create = vive_headset_mainboard_new,
	}, {
		.vid = VID_LENOVO,
		.pid = PID_VR_2511N,
		.subsystem = "hidraw",
		.name = "Lenovo Explorer",
		.create = lenovo_explorer_new,
	},
	#endif
	{
		.vid = VID_MICROSOFT,
		.pid = PID_HOLOLENS_SENSORS,
		.subsystem = "video4linux",
		.name = "HoloLens Sensors",
		.create = hololens_camera_new,
	}, {
		.vid = VID_MICROSOFT,
		.pid = PID_HOLOLENS_SENSORS,
		.subsystem = "usb",
		.name = "HoloLens Sensors",
		.create = hololens_camera2_new,
	}, {
		.vid = VID_MICROSOFT,
		.pid = PID_HOLOLENS_SENSORS,
		.name = "HoloLens IMU",
		.interfaces = (const struct interface_match[]){
			{ 2, .subsystem = "hidraw", .name = "IMU" },
		},
		.num_interfaces = 1,
		.create = hololens_imu_new,
	}, {
		.vid = VID_MICROSOFT,
		.pid = PID_MOTION_CONTROLLER,
		.subsystem = "hidraw",
		.name = "Motion Controller",
		.create = motion_controller_new,
	},
	#if 0
	{
		.vid = VID_VALVE,
		.pid = PID_VIVE_HEADSET,
		.name = "Vive Headset",
		.interfaces = (const struct interface_match[]){
			{ 0, .subsystem = "hidraw", .name = "IMU" },
			{ 1, .subsystem = "hidraw", .name = "Lighthouse RX" },
		},
		.num_interfaces = 2,
		.create = vive_headset_new,
	}, {
		.vid = VID_VALVE,
		.pid = PID_VIVE_CONTROLLER_USB,
		.name = "Vive Controller",
		.interfaces = (const struct interface_match[]){
			{ 0, .subsystem = "hidraw", .name = "IMU" },
			{ 1, .subsystem = "hidraw", .name = "Lighthouse RX" },
			{ 2, .subsystem = "hidraw", .name = "Buttons" },
		},
		.num_interfaces = 3,
		.create = vive_controller_usb_new,
	}, {
		.vid = VID_VALVE,
		.pid = PID_VIVE_CONTROLLER,
		.subsystem = "hidraw",
		.name = "Vive Wireless Receiver",
		.create = vive_controller_new,
	},
	#endif
};

GMainLoop *loop = NULL;
GList *device_list = NULL;
static int num_devices;

/*
 * Compares the device's parent against a given parent.
 */
static gint ouvrt_device_cmp_parent_devpath(OuvrtDevice *dev,
					    const char *parent_devpath)
{
	return g_strcmp0(dev->parent_devpath, parent_devpath);
}

/*
 * Compares the device's serial against a given serial.
 */
static gint ouvrt_device_cmp_serial(OuvrtDevice *dev, const char *serial)
{
	return g_strcmp0(dev->serial, serial);
}

/*
 * Links Rift DK2 HMD and Tracker DK2 camera.
 */
#if 0
static void ouvrt_link_rift_dk2(OuvrtDevice *dev)
{
	GList *link;
	OuvrtRift *rift;
	OuvrtCameraDK2 *camera;

	link = g_list_find_custom(device_list, dev->serial,
				  (GCompareFunc)ouvrt_device_cmp_serial);
	if (!link)
		return;

	if (OUVRT_IS_RIFT(dev) &&
	    OUVRT_IS_CAMERA_DK2(link->data)) {
		g_print("Associate %s and %s\n", dev->devnode,
			OUVRT_DEVICE(link->data)->devnode);
		rift = OUVRT_RIFT(dev);
		camera = OUVRT_CAMERA_DK2(link->data);
	} else if (OUVRT_IS_CAMERA_DK2(dev) &&
		   OUVRT_IS_RIFT(link->data)) {
		camera = OUVRT_CAMERA_DK2(dev);
		rift = OUVRT_RIFT(link->data);
	} else {
		return;
	}

	g_print("Associate %s and %s\n", dev->devnode,
		OUVRT_DEVICE(link->data)->devnode);

	ouvrt_camera_dk2_set_tracker(camera, ouvrt_rift_get_tracker(rift));
}

static void ouvrt_link_rift_sensor_to_rift(gpointer data, gpointer user_data)
{
	OuvrtRift *rift = OUVRT_RIFT(user_data);
	OuvrtRiftSensor *camera;

	if (!OUVRT_IS_RIFT_SENSOR(data))
		return;

	camera = OUVRT_RIFT_SENSOR(data);

	if (!rift || !camera) {
		rift = OUVRT_RIFT(data);
		camera = OUVRT_RIFT_SENSOR(user_data);
	}
	if (!rift || !camera)
		return;

	g_print("Associate %s and %s\n", OUVRT_DEVICE(rift)->devnode,
		OUVRT_DEVICE(camera)->devnode);

	ouvrt_rift_sensor_set_tracker(camera, ouvrt_rift_get_tracker(rift));
}

/*
 * Links Rift CV1 HMD and Sensor CV1 cameras.
 */
static void ouvrt_link_rift_cv1(OuvrtDevice *dev)
{
	if (OUVRT_IS_RIFT(dev)) {
		g_list_foreach(device_list, ouvrt_link_rift_sensor_to_rift, dev);
		return;
	}

	if (OUVRT_IS_RIFT_SENSOR(dev)) {
		GList *link;

		for (link = device_list; link != NULL; link = link->next) {
			if (OUVRT_IS_RIFT(link->data)) {
				ouvrt_link_rift_sensor_to_rift(dev, link->data);
				return;
			}
		}
	}
}
#endif

/*
 * Check if an added device matches the table of known hardware, if yes create
 * a new device structure and start the device.
 */
static void ouvrtd_device_add(struct udev_device *dev)
{
	const char *devnode, *parent_devpath, *serial, *subsystem, *value;
	const char *parent_subsystem;
	uint16 vid = 0;
	uint16 pid = 0;
	struct udev_device *parent;
	OuvrtDevice *d;
	int i, j = 0, iface;

	subsystem = udev_device_get_subsystem(dev);
	if (!subsystem)
		return;

	if (g_strcmp0(subsystem, "usb") == 0) {
		parent = dev;
		parent_subsystem = subsystem;
		iface = 0;
	} else if (g_strcmp0(subsystem, "hidraw") == 0) {
		const char *hid_id, *hid_name, *hid_phys, *hid_uniq;

		/* HID subsystem parent */
		parent = udev_device_get_parent(dev);
		if (!parent)
			return;

		hid_id = udev_device_get_property_value(parent, "HID_ID");
		hid_name = udev_device_get_property_value(parent, "HID_NAME");
		hid_phys = udev_device_get_property_value(parent, "HID_PHYS");
		hid_uniq = udev_device_get_property_value(parent, "HID_UNIQ");
		if (!hid_id || !hid_name || !hid_phys || !hid_uniq)
			return;

		if (strlen(hid_id) != 22)
			return;
		if (hid_id[4] != ':' || hid_id[13] != ':')
			return;

		vid = strtol(hid_id + 6, NULL, 16);
		pid = strtol(hid_id + 15, NULL, 16);

		/* Bluetooth device or USB interface */
		parent = udev_device_get_parent(parent);
		if (!parent)
			return;

		parent_subsystem = udev_device_get_subsystem(parent);

		if (g_strcmp0(parent_subsystem, "bluetooth") == 0) {
			iface = 0;
		} else if (g_strcmp0(parent_subsystem, "usb") == 0) {
			value = udev_device_get_sysattr_value(parent,
							      "bInterfaceNumber");
			if (!value)
				return;
			iface = atoi(value);

			/* USB device */
			parent = udev_device_get_parent(parent);
			if (!parent)
				return;
		} else {
			return;
		}
	} else if (g_strcmp0(subsystem, "video4linux") == 0) {
		/* video4linux subsystem parent */
		parent = udev_device_get_parent(dev);
		if (!parent)
			return;

		/* USB interface */
		parent = udev_device_get_parent(parent);
		if (!parent)
			return;

		parent_subsystem = udev_device_get_subsystem(parent);
		iface = 0;
	} else {
		return;
	}

	parent_devpath = udev_device_get_devpath(parent);
	if (!parent_devpath)
		return;

	if (g_strcmp0(parent_subsystem, "usb") == 0) {
		value = udev_device_get_sysattr_value(parent, "idVendor");
		if (!value)
			return;
		vid = strtol(value, NULL, 16);

		value = udev_device_get_sysattr_value(parent, "idProduct");
		if (!value)
			return;
		pid = strtol(value, NULL, 16);
	}

	for (i = 0; i < NUM_MATCHES; i++) {
		if (vid != device_matches[i].vid ||
		    pid != device_matches[i].pid)
			continue;

		if (device_matches[i].num_interfaces == 0) {
			if (strcmp(device_matches[i].subsystem,
				   subsystem) == 0 && iface == 0)
				break;
			continue;
		}

		for (j = 0; j < device_matches[i].num_interfaces; j++) {
			if (strcmp(device_matches[i].interfaces[j].subsystem,
				   subsystem) == 0 &&
			    device_matches[i].interfaces[j].iface == iface)
				break;
		}

		if (j < device_matches[i].num_interfaces)
			break;
	}
	if (i == NUM_MATCHES)
		return;

	devnode = udev_device_get_devnode(dev);
	if (device_matches[i].num_interfaces)
		g_print("udev: Found %s %s: %s\n", device_matches[i].name,
			device_matches[i].interfaces[j].name, devnode);
	else
		g_print("udev: Found %s: %s\n", device_matches[i].name, devnode);

	/*
	 * If this is a new interface of an already existing multi-interface
	 * device, join the existing device.
	 */
	if (device_matches[i].num_interfaces > 1) {
		GList *link;

		link = g_list_find_custom(device_list, parent_devpath,
					  (GCompareFunc)ouvrt_device_cmp_parent_devpath);
		if (link) {
			d = OUVRT_DEVICE(link->data);
			if (d->devnodes[j]) {
				g_print("udev: Interface %d occupied by %s\n",
					iface, d->devnodes[j]);
				return;
			} else {
				d->devnodes[j] = g_strdup(devnode);
			}

			for (j = 0; j < device_matches[i].num_interfaces; j++) {
				if (d->devnodes[j] == NULL)
					break;
			}
			if (j == device_matches[i].num_interfaces)
				goto start;

			return;
		}
	}

	/* Otherwise create a new device */
	d = device_matches[i].create(devnode);
	if (d == NULL)
		return;
	d->parent_devpath = g_strdup(parent_devpath);
	if (!d->devnodes[j]) {
		if (device_matches[i].num_interfaces)
			d->devnodes[j] = g_strdup(devnode);
		else
			d->devnode = g_strdup(devnode);
	}
	if (d->name == NULL)
		d->name = strdup(device_matches[i].name);

	if (d->serial == NULL) {
		serial = udev_device_get_sysattr_value(parent, "serial");
		if (serial)
			d->serial = strdup(serial);
	}
	if (d->serial) {
		g_print("%s: Serial %s\n", device_matches[i].name, d->serial);

		//ouvrt_link_rift_dk2(d);
	}

	//ouvrt_link_rift_cv1(d);

	device_list = g_list_append(device_list, d);

	for (j = 0; j < device_matches[i].num_interfaces; j++) {
		if (d->devnodes[j] == NULL)
			return;
	}

start:
	ouvrt_device_start(d);
	//ouvrt_dbus_export_device(d);
}

/*
 * Compares the device's devnode against a given device node.
 */
static gint ouvrt_device_cmp_devnode(OuvrtDevice *dev, const char *devnode)
{
	return g_strcmp0(dev->devnode, devnode);
}

/*
 * Check if a removed device matches a registered device structure. If yes,
 * dereference the device to stop it and free the device structure.
 */
static int ouvrtd_device_remove(struct udev_device *dev)
{
	const char *devnode;
	OuvrtDevice *d;
	GList *link;

	devnode = udev_device_get_devnode(dev);
	link = g_list_find_custom(device_list, devnode,
				  (GCompareFunc)ouvrt_device_cmp_devnode);
	if (link == NULL)
		return 0;

	d = OUVRT_DEVICE(link->data);

	//ouvrt_dbus_unexport_device(d);

	g_print("Removing device: %s\n", devnode);
	device_list = g_list_remove_link(device_list, link);
	g_object_unref(d);
	g_list_free_1(link);
	num_devices--;

	return 0;
}

/*
 * Enumerate currently present USB devices to find known hardware.
 */
static int ouvrtd_enumerate(udev *udev)
{
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;

	enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "usb");
	udev_enumerate_add_match_subsystem(enumerate, "hidraw");
	udev_enumerate_add_match_subsystem(enumerate, "video4linux");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);

	udev_list_entry_foreach(dev_list_entry, devices) {
		const char *path;
		struct udev_device *dev;

		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);

		ouvrtd_device_add(dev);

		udev_device_unref(dev);
	}

	udev_enumerate_unref(enumerate);

	return 0;
}

struct udev_source {
	GSource base;
	gpointer tag;
};

static gboolean udev_source_prepare(G_GNUC_UNUSED GSource *source,
				    gint *timeout)
{
	*timeout = -1;
	return FALSE;
}

static gboolean udev_source_check(GSource *source)
{
	struct udev_source *usrc = (struct udev_source *)source;

	return (g_source_query_unix_fd(source, usrc->tag) > 0);
}

static gboolean udev_source_dispatch(GSource *source, GSourceFunc callback,
				     gpointer user_data)
{
	struct udev_source *usrc = (struct udev_source *)source;
	GIOCondition revents = g_source_query_unix_fd(source, usrc->tag);

	if (revents & G_IO_IN) {
		if (callback == NULL)
			return FALSE;
		return callback(user_data);
	}

	return TRUE;
}

GSourceFuncs udev_source_funcs = {
	.prepare = udev_source_prepare,
	.check = udev_source_check,
	.dispatch = udev_source_dispatch,
};

static gboolean udev_source_callback(gpointer user_data)
{
	struct udev_monitor *monitor = (struct udev_monitor *)user_data;
	struct udev_device *dev;
	const char *action;

	dev = udev_monitor_receive_device(monitor);
	if (!dev) {
		g_print("udev: Monitor receive_device error\n");
		return TRUE;
	}

	action = udev_device_get_action(dev);
	if (strcmp(action, "add") == 0)
		ouvrtd_device_add(dev);
	else if (strcmp(action, "remove") == 0)
		ouvrtd_device_remove(dev);

	return TRUE;
}

/*
 * Set up a udev event monitor, call device enumeration, and then monitor
 * for appearing and disappearing known hardware.
 */
static void ouvrtd_startup(struct udev *udev)
{
	struct udev_monitor *monitor;
	struct udev_source *source;
	int fd;

	/* Set up monitoring udev events for hidraw and video4linux devices */
	monitor = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(monitor, "usb", NULL);
	udev_monitor_filter_add_match_subsystem_devtype(monitor, "hidraw",
							NULL);
	udev_monitor_filter_add_match_subsystem_devtype(monitor, "video4linux",
							NULL);
	udev_monitor_enable_receiving(monitor);
	fd = udev_monitor_get_fd(monitor);

	/* Enumerate presently available hidraw and video4linux devices */
	ouvrtd_enumerate(udev);

	/* Watch udev events for hidraw and video4linux devices */
	source = (struct udev_source *)g_source_new(&udev_source_funcs,
						    sizeof(*source));
	g_source_set_callback(&source->base, udev_source_callback, monitor,
			      NULL); /* destroy_notify */
	source->tag = g_source_add_unix_fd(&source->base, fd, G_IO_IN);
	g_source_attach(&source->base, g_main_context_default());
	g_source_unref(&source->base);
}

static void device_stop(gpointer data, G_GNUC_UNUSED gpointer user_data)
{
	ouvrt_device_stop((OuvrtDevice*)data);
}

static void ouvrtd_signal_handler(int sig)
{
	signal(sig, SIG_IGN);
	g_print(" - stopping all devices\n");

	g_list_foreach(device_list, device_stop,
		       NULL); /* user_data */

	g_main_loop_quit(loop);
}

static void ouvrtd_usage(void)
{
	g_print("ouvrtd [OPTIONS...] ...\n\n"
		"Positional tracking daemon for Oculus VR Rift DK2.\n\n"
		"  -h --help          Show this help\n");
}

static const struct option ouvrtd_options[] = {
	{ "help", no_argument, NULL, 'h' },
	{ NULL }
};




bool LocalVRService::Init(String name) {
	debug_stream_init(0, 0);
	//pipewire_init(0, 0);
	telemetry_init(0, 0);

	udev = udev_new();
	if (!udev) {
		return false;
	}
	
	ouvrtd_startup(udev);
	
	return true;
}

void LocalVRService::Update() {
	
}

void LocalVRService::Stop() {
	LOG("LocalVRService::Stop");
	g_list_foreach(device_list, device_stop,
		       NULL); /* user_data */
}

void LocalVRService::Deinit() {
	udev_unref(udev);
	
	telemetry_deinit();
	//pipewire_deinit();
	debug_stream_deinit();
}

















WmrFusionService::WmrFusionService() {
	
}

bool WmrFusionService::Init(String name) {
	DaemonService* ds = FindService("TcpServer");
	server = dynamic_cast<SerialServiceServer*>(ds);
	if (!server) {
		LOG("LocalVRDebugService::Init: error: tcp server is required");
		return false;
	}
	sys.Attach(*server);
	
	
	DaemonService* lvrd = FindService("LocalVRDebug");
	lvrd_svc = dynamic_cast<LocalVRDebugService*>(lvrd);
	if (!lvrd_svc) {
		LOG("LocalVRDebugService::Init: error: LocalVRDebugService required");
		return false;
	}
	
	
	DaemonService* lhmd = FindService("LocalHMD");
	lhmd_svc = dynamic_cast<LocalHMDService*>(lhmd);
	if (!lhmd_svc) {
		LOG("LocalVRDebugService::Init: error: LocalHMDService is required");
		return false;
	}
	
	
	lvrd_svc->SetBrightCallback(THISBACK(OnBrightFrame));
	lvrd_svc->SetDarkCallback(THISBACK(OnDarkFrame));
	
	lhmd_svc->SetSensorCallback(THISBACK(OnSensorData));
	
	flag.Start(1);
	UPP::Thread::Start(THISBACK(FusionProcess));
	
	return true;
}

void WmrFusionService::Update() {
	
}

void WmrFusionService::Stop() {
	flag.Stop();
}

void WmrFusionService::Deinit() {
	
}

void WmrFusionService::FusionProcess() {
	
	while (flag.IsRunning()) {
		
		sys.Process();
		
		Sleep(10);
	}
	
	flag.DecreaseRunning();
}

void WmrFusionService::OnBrightFrame(DebugService::Stream& s) {
	sys.PutBrightFrame(s.frame_lock, s.sz, s.frame);
}

void WmrFusionService::OnDarkFrame(DebugService::Stream& s) {
	sys.PutDarkFrame(s.frame_lock, s.sz, s.frame);
}

void WmrFusionService::OnSensorData(CtrlEvent& e) {
	sys.PutSensorData(e);
}



NAMESPACE_HMD_END


INITBLOCK_(LocalVR) {
	::TS::DaemonBase::Register<TS::HMD::LocalVRService>("LocalVR");
	::TS::DaemonBase::Register<TS::HMD::WmrFusionService>("WmrFusion");
	
	#ifdef flagDEBUG_SERVER
	::TS::DaemonBase::Register<TS::HMD::LocalVRDebugService>("LocalVRDebug");
	#endif
}



#ifdef flagMAIN

/*
 * Main function. Initialize GStreamer for debugging purposes and udev for
 * device detection.
 */

CONSOLE_APP_MAIN
{
	using namespace TS;
	using namespace TS::HMD;
	
	const auto& cmd = CommandLine();
	int argc = 0;
	char** argv = 0;
	Vector<char*> arg_ptrs;
	arg_ptrs.SetCount(cmd.GetCount());
	for(int i = 0; i < arg_ptrs.GetCount(); i++) {
		arg_ptrs[i] = const_cast<char*>((const char*)cmd[i].Begin());
	}
	
	
	struct udev *udev;
	guint owner_id;
	int longind;
	int ret;

	setlocale(LC_CTYPE, "");

	debug_stream_init(&argc, &argv);
	//pipewire_init(&argc, &argv);
	telemetry_init(&argc, &argv);

	do {
		ret = getopt_long(argc, argv, "h", ouvrtd_options, &longind);
		switch (ret) {
		case -1:
			break;
		case 'h':
		default:
			ouvrtd_usage();
			exit(0);
		}
	} while (ret != -1);

	signal(SIGINT, ouvrtd_signal_handler);

	udev = udev_new();
	if (!udev) {
		SetExitCode(1);
		return;
	}

	loop = g_main_loop_new(NULL, TRUE);
	//owner_id = ouvrt_dbus_own_name();

	ouvrtd_startup(udev);
	g_main_loop_run(loop);

	//g_bus_unown_name(owner_id);
	udev_unref(udev);
	g_main_loop_unref(loop);
	telemetry_deinit();
	//pipewire_deinit();
	debug_stream_deinit();

}

#endif
