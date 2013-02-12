#ifndef SFS_H
#define SFS_H
#include <sys/types.h>
#include <inttypes.h>

#define SFS_NR_DIRECT_BLOCKS 12

struct sfs_inode {
	uint64_t ino;
	uint64_t block_no[SFS_NR_DIRECT_BLOCKS];
	uint64_t size;
	uint32_t flags;
}__attribute__((packed));

#define SFS_MAX_NAME	256
#define SFS_MIN_DIRENT	14 /*Size of minimum dirent in bytes.*/

#define SFS_DIRENT_REG	(1<<0)
#define SFS_DIRENT_DIR	(1<<1)
#define SFS_DIRENT_REM	(1<<2)
#define SFS_DIRENT_LNK	(1<<3)

struct sfs_dirent {
	uint64_t ino; /*Inode entry of the file stored in directory.*/
	uint32_t flags;
	uint16_t length;
	char	name[0];/*Variable Length name*/
};

/*
 * The disk structure contains the following.
 *
 * +---------------+---------------+---------------+------------------+
 * |               |               |               |                  |
 * |  SUPER BLOCK  | INODE TABLE   | BITMAP INODE  | BITMAP BLOCK     |
 * |               |               |               |                  |
 * |               |               |               |                  |
 * +---------------+---------------+---------------+------------------+
 * */
struct sfs_super {
	uint64_t block_size; /*Block size*/
	uint64_t nr_inodes; /*Total inodes*/
	uint64_t nr_blocks; /*Total blocks*/
	uint64_t start_block;/*Start of super_block.*/
	/*
	 * The total number of blocks occupied above.
	 * */
	uint32_t nr_boot_blocks; /*Total boot blocks*/
};

#ifdef __KERNEL__
#include "common.h"
#include <linux/buffer_head.h>

struct sfs_inode_incore {
	struct inode 	vfs_inode;
	uint32_t 	nr_bh;/*Number of bh for this inode below*/
	/*
	 * This would be an array of pointers to bh for this inode. Not that
	 * we need this, but we might need it for meta-data stuff. If it's
	 * not required really I will scrap this off later. 
	 * */
	struct buffer_head 	**bh_size;
};

struct sfs_super_incore {
	struct super_block 	*sb;
	/*
	 * These will be the meta data buffers. From time to time
	 * we got to mark em dirty or flush em straight away.
	 *
	 * A array of pointers is required since a page is home
	 * to as many as 8 bhs (speaking in 512 sectors terms)
	 * and all we need to have the pointer to the first bh
	 * to get a hold of all 8. There might however be multiple
	 * pages required to read-in the meta data so we need to
	 * store all those bhs pointer.
	 * */
	struct buffer_heads 	**meta_data_buffers;
	uint32_t 		nr_bh;

	struct sfs_super
};
#endif
#endif /*SFS_H*/
