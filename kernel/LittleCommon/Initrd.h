#ifndef _LittleCommon_Initrd_h_
#define _LittleCommon_Initrd_h_


EXTERN_C_BEGIN

struct FsNode;

typedef struct {
	uint32 nfiles; // The number of files in the ramdisk.
} InitrdHeader;

typedef struct {
	uint8 magic;     // Magic number, for error checking.
	char name[64];  // Filename.
	size_t offset;   // Offset in the initrd that the file starts.
	uint32 length;   // Length of the file.
} InitrdFileHeader;



// Initialises the initial ramdisk. It gets passed the address of the multiboot module,
// and returns a completed filesystem node.
FsNode *InitialiseInitrd(size_t location);

EXTERN_C_END

#endif
