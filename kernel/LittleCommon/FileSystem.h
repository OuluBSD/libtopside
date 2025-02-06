#ifndef _LittleCommon_FileSystem_h_
#define _LittleCommon_FileSystem_h_

EXTERN_C_BEGIN

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08 // Is the file an active mountpoint?


// These typedefs define the type of callbacks - called when read/write/open/close
// are called.
typedef size_t(*ReadTypeFn)(struct FsNode*, size_t, size_t, uint8*);
typedef size_t(*WriteTypeFn)(struct FsNode*, size_t, size_t, uint8*);
typedef void (*OpenTypeFn)(struct FsNode*);
typedef void (*CloseTypeFn)(struct FsNode*);
typedef struct DirectoryEntity * (*ReadDirTypeFn)(struct FsNode*, uint32);
typedef struct FsNode * (*FindDirTypeFn)(struct FsNode*, char *name);

struct FsNode {
	char name[128];     // The filename.
	uint32 mask;        // The permissions mask.
	uint32 uid;         // The owning user.
	uint32 gid;         // The owning group.
	uint32 flags;       // Includes the node type. See #defines above.
	uint32 inode;       // This is device-specific - provides a way for a filesystem to identify files.
	uint32 length;      // Size of the file, in bytes.
	uint32 impl;        // An implementation-defined number.
	ReadTypeFn read;
	WriteTypeFn write;
	OpenTypeFn open;
	CloseTypeFn close;
	ReadDirTypeFn readdir;
	FindDirTypeFn finddir;
	struct FsNode *ptr; // Used by mountpoints and symlinks.
};

struct DirectoryEntity {
	char name[128]; // Filename.
	uint32 ino;     // Inode number. Required by POSIX.
};

extern FsNode *fs_root; // The root of the filesystem.

// Standard read/write/open/close functions. Note that these are all suffixed with
// _fs to distinguish them from the read/write/open/close which deal with file descriptors
// , not file nodes.
size_t ReadFs(FsNode *node, size_t offset, size_t size, uint8 *buffer);
size_t WriteFs(FsNode *node, size_t offset, size_t size, uint8 *buffer);
void OpenFs(FsNode *node, uint8 read, uint8 write);
void CloseFs(FsNode *node);
struct DirectoryEntity *ReadDirFs(FsNode *node, uint32 index);
FsNode *FindDirFs(FsNode *node, char *name);


EXTERN_C_END

#endif
