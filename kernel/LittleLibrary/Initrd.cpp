#include "LittleLibrary.h"

EXTERN_C_BEGIN

static size_t initrd_read(FsNode *node, size_t offset, size_t size, uint8 *buffer) {
	InitrdFileHeader header = global->file_headers[node->inode];
	if (offset > header.length)
		return 0;
	if (offset + size > header.length)
		size = header.length - offset;
	memcpy(buffer, (uint8*)(header.offset + offset), size);
	return size;
}

static struct DirectoryEntity *initrd_readdir(FsNode *node, uint32 index) {
	auto& dirent = global->dirent;
	auto& root_nodes = global->root_nodes;
	auto& nroot_nodes = global->nroot_nodes;
	
	if (node == global->initrd_root && index == 0) {
		strcpy(dirent.name, "dev");
		dirent.name[3] = 0;
		dirent.ino = 0;
		return &dirent;
	}
	
	if ((int)index - 1 >= (int)nroot_nodes)
		return 0;
	strcpy(dirent.name, root_nodes[index-1].name);
	dirent.name[strlen(root_nodes[index-1].name)] = 0;
	dirent.ino = root_nodes[index-1].inode;
	return &dirent;
}

static FsNode *initrd_finddir(FsNode *node, char *name) {
	auto& initrd_root = global->initrd_root;
	auto& initrd_dev = global->initrd_dev;
	auto& root_nodes = global->root_nodes;
	auto& nroot_nodes = global->nroot_nodes;
	
	if (node == initrd_root &&
		!strcmp(name, "dev"))
		return initrd_dev;
		
	int i;
	for (i = 0; i < nroot_nodes; i++)
		if (!strcmp(name, root_nodes[i].name))
			return &root_nodes[i];
	return 0;
}


struct FsNode* InitialiseInitrd(size_t location) {
	ASSERT(location);
	auto& initrd_header = global->initrd_header;
	auto& file_headers = global->file_headers;
	auto& initrd_root = global->initrd_root;
	auto& initrd_dev = global->initrd_dev;
	auto& root_nodes = global->root_nodes;
	auto& nroot_nodes = global->nroot_nodes;
	
	// Initialise the main and file header pointers and populate the root directory.
	initrd_header = (InitrdHeader *)location;
	file_headers = (InitrdFileHeader *)(location + sizeof(InitrdHeader));
	
	// Initialise the root directory.
	initrd_root = (FsNode*)KMemoryAllocate(sizeof(FsNode));
	strcpy(initrd_root->name, "initrd");
	initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->length = 0;
	initrd_root->flags = FS_DIRECTORY;
	initrd_root->read = 0;
	initrd_root->write = 0;
	initrd_root->open = 0;
	initrd_root->close = 0;
	initrd_root->readdir = &initrd_readdir;
	initrd_root->finddir = &initrd_finddir;
	initrd_root->ptr = 0;
	initrd_root->impl = 0;
	
	// Initialise the /dev directory (required!)
	initrd_dev = (FsNode*)KMemoryAllocate(sizeof(FsNode));
	strcpy(initrd_dev->name, "dev");
	initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
	initrd_dev->flags = FS_DIRECTORY;
	initrd_dev->read = 0;
	initrd_dev->write = 0;
	initrd_dev->open = 0;
	initrd_dev->close = 0;
	initrd_dev->readdir = &initrd_readdir;
	initrd_dev->finddir = &initrd_finddir;
	initrd_dev->ptr = 0;
	initrd_dev->impl = 0;
	
	root_nodes = (FsNode*)KMemoryAllocate(sizeof(FsNode) * initrd_header->nfiles);
	nroot_nodes = initrd_header->nfiles;
	
	// For every file...
	uint32 i;
	for (i = 0; i < initrd_header->nfiles; i++) {
		// Edit the file's header - currently it holds the file offset
		// relative to the start of the ramdisk. We want it relative to the start
		// of memory.
		file_headers[i].offset += location;
		// Create a new file node.
		strcpy(root_nodes[i].name, file_headers[i].name);
		root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
		root_nodes[i].length = file_headers[i].length;
		root_nodes[i].inode = i;
		root_nodes[i].flags = FS_FILE;
		root_nodes[i].read = &initrd_read;
		root_nodes[i].write = 0;
		root_nodes[i].readdir = 0;
		root_nodes[i].finddir = 0;
		root_nodes[i].open = 0;
		root_nodes[i].close = 0;
		root_nodes[i].impl = 0;
	}
	return initrd_root;
}


EXTERN_C_END
