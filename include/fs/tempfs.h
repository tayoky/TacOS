#pragma once
#include <mem/paging.h>
#include <fs/vfs.h>

#define FILE_DATA_BLOCK_LEN (PAGE_SIZE - sizeof(TempfsDirEntry*))

typedef struct TempfsFileNode TempfsFileNode;
typedef struct TempfsDirEntry TempfsDirEntry;
typedef struct TempfsInode TempfsInode;

typedef enum {
    RegularFile,
    Directory,
} TempfsInodeType;

struct TempfsFileNode {
    TempfsFileNode *next;
    char data[FILE_DATA_BLOCK_LEN];
};

struct TempfsDirEntry {
    TempfsDirEntry *next;
    TempfsInode *inode;
};

struct TempfsInode {
    char name[MAX_FILENAME_LEN]; // TODO: Allocate dynamically
    TempfsInode *parent;
    TempfsInodeType type;
    union {
        TempfsFileNode *first_file_node;
        TempfsDirEntry *first_dir_entry;
    };
};

typedef struct {
    TempfsInode    *inode;
    TempfsDirEntry *current_entry;
} TempfsDirIter;

TempfsInode *tempfs_new();
TempfsInode *tempfs_find_root(TempfsInode *fs);
TempfsInode *tempfs_create_entry(TempfsInode *dir);
TempfsInode *tempfs_new_file(TempfsInode *dir, char *name);
TempfsInode *tempfs_mkdir(TempfsInode *parentdir, char *name);
TempfsInode *tempfs_open(TempfsInode *file);
int tempfs_close(TempfsInode *file);
TempfsDirIter *tempfs_opendir(TempfsInode *dir);
int tempfs_write(TempfsInode *file, char *buf, size_t len, size_t offset);
int tempfs_read(TempfsInode *file, char *buf, size_t len, size_t offset);
TempfsInode *tempfs_diriter(TempfsDirIter *iter);
int tempfs_closedir(TempfsDirIter *dir);
int tempfs_rmdir(TempfsDirIter *dir);
int tempfs_rmfile(TempfsInode *file);
int tempfs_identify(TempfsInode *inode, char *namebuf, bool *is_dir_buf);
void *tempfs_file_from_diriter(TempfsDirIter *iter);
extern FileSystem tempfs;
