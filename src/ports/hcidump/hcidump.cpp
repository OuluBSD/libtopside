#include "hcidump.h"
#include "internal.h"


NAMESPACE_TOPSIDE_BEGIN

SimpleBluetoothConnection::SimpleBluetoothConnection() {
	
}

SimpleBluetoothConnection::~SimpleBluetoothConnection() {
	Close();
}

bool SimpleBluetoothConnection::Open(int device_idx) {
	this->device_idx = device_idx;
	flags = 0;
	
	unsigned long filter = 0;
	int defpsm = 0;
	int defcompid = DEFAULT_COMPID;
	int opt, pppdump_fd = -1, audio_fd = -1;
	uint16_t obex_port;

	flags |= DUMP_RAW;

	
	/* Default settings */
	if (!filter)
		filter = ~0L;

	//if (pppdump_file)
	//	pppdump_fd = open_file(pppdump_file, PPPDUMP, flags);

	//if (audio_file)
	//	audio_fd = open_file(audio_file, AUDIO, flags);

	
	data.nfds = 0;
	data.hdr_size = HCIDUMP_HDR_SIZE;
	
	mode = PARSE;
	flags |= DUMP_VERBOSE;
	init_parser(flags, filter, defpsm, defcompid,
						pppdump_fd, audio_fd);
	
	sock = open_socket(device_idx, flags);
	
	if (init_process_frames(&data, device_idx, sock, -1, flags))
		return false;
	
	is_open = true;
	return true;
}

void SimpleBluetoothConnection::Close() {
	if (!is_open)
		return;
	
	TODO
}

bool SimpleBluetoothConnection::ReadPacket(Vector<byte>& data) {
	int sz = 1024;
	data.SetCount(sz);
	if (iterate_process_frames(&this->data, device_idx, sock, -1, flags, data.Begin(), &sz) != 0)
		return false;
	
	data.SetCount(sz);
	return true;
}


NAMESPACE_TOPSIDE_END
