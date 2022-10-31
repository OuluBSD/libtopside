#ifndef _ports_hcidump_internal_h_
#define _ports_hcidump_internal_h_


#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#ifdef flagPOSIX
	#include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include "parser.h"
#include "sdp.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#ifdef __cplusplus
extern "C" {
#endif
	
	/* Modes */
	enum {
		PARSE,
		READ,
		WRITE,
		PPPDUMP,
		AUDIO
	};

	struct hcidump_hdr {
		uint16_t	len;
		uint8_t		in;
		uint8_t		pad;
		uint32_t	ts_sec;
		uint32_t	ts_usec;
	} __attribute__ ((packed));
	#define HCIDUMP_HDR_SIZE (sizeof(struct hcidump_hdr))

	struct hcidump_process_data {
		struct cmsghdr *cmsg;
		struct msghdr msg;
		struct iovec  iv;
		struct hcidump_hdr *dh;
		struct btsnoop_pkt *dp;
		struct frame frm;
		struct pollfd fds[2];
		int nfds;
		char *buf, *ctrl;
		int len, hdr_size;
		
	};

	int open_socket(int dev, unsigned long flags);
	int init_process_frames(struct hcidump_process_data* d, int dev, int sock, int fd, unsigned long flags);
	int iterate_process_frames(struct hcidump_process_data* d, int dev, int sock, int fd, unsigned long flags, unsigned char* data, int* len);

#ifdef __cplusplus
}
#endif

#endif
