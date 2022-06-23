#ifndef _LittleKernel_Global_h_
#define _LittleKernel_Global_h_


struct SVar {
	DescriptorTable dt;
	Monitor monitor;
	Timer timer;
	Heap kheap;
	
	uint32 *frames;
	uint32 nframes;
	PageDirectory* kernel_directory = 0;
	PageDirectory* current_directory = 0;
	uint32 placement_address;
	
	FixedArray<Callback1<int>, 1> cbtestarr;
	FixedArray<Callback1<Registers>, 256 > interrupt_handlers;
	
	
	
	// Initrd
	InitrdHeader *initrd_header;     // The header.
	InitrdFileHeader *file_headers;  // The list of file headers.
	FsNode *initrd_root;             // Our root directory node.
	FsNode *initrd_dev;              // We also add a directory node for /dev, so we can mount devfs later on.
	FsNode *root_nodes;              // List of file nodes.
	int nroot_nodes;                 // Number of file nodes.
	struct DirectoryEntity dirent;
	
	
	// Task
	
	// The currently running task.
	volatile Task *current_task;
	
	// The start of the task linked list.
	volatile Task *ready_queue;
	
	// Some externs are needed to access members in paging.c...
	uint32 initial_esp;
	uint32 read_eip();
	
	// The next available process ID.
	uint32 next_pid = 1;

	void *syscalls[3] = {
		(void*)&syscall_MonitorWrite,
		(void*)&syscall_MonitorWriteHex,
		(void*)&syscall_MonitorWriteDec,
	};
	uint32 num_syscalls = 3;
	
};
extern SVar* global;



#endif
