#include <sfs.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#ifdef 	SFS_DEBUG
#define pr_sfs_debug(fmt,args...)\
	perror("Linux error message:");\
	printf(fmt,##args)
#define SFS_DEBUG_FUNC		"In Function %s "
#define SFS_DEBUG_LINE		"At Line %d "
#define SFS_DEBUG_MSG		SFS_DEBUG_FUNC SFS_DEBUG_LINE,__FUNCTION__,__LINE__

#else
#define pr_sfs_debug(fmt,args...)
#endif /*SFS_DEBUG*/

/*
 * @inode: The inode to write.
 * @fd: The device file descriptor.
 * @where: The exact offset from current location.
 *
 * Returns 0 on everything good. -1 on error.
 * */
int write_inode (int fd,struct sfs_inode *inode,loff_t where)
{
	if (lseek64(fd,SEEK_CUR,where) < 0) {
		pr_sfs_debug("Unable to seek in device\n");
		pr_sfs_debug(SFS_DEBUG_MSG);
		return -1;
	}
	if (write(fd,inode,sizeof(struct sfs_inode))
			!=sizeof(struct sfs_inode)) {
		pr_sfs_debug("Unable to write inode on device\n");
		pr_sfs_debug(SFS_DEBUG_MSG);
		return -1;
	}
	pr_sfs_debug("Wrote inode successfully\n");
return 0;
}

/*
 * @inode: The inode to write.
 * @fd: The device file descriptor.
 * @where: The exact offset from current location.
 *
 * Returns 0 on everything good. -1 on error.
 * */
int write_super (int fd,struct sfs_super *super,loff_t where)
{
	if (lseek64(fd,SEEK_CUR,where) < 0) {
		pr_sfs_debug("Unable to seek in device\n");
		pr_sfs_debug(SFS_DEBUG_MSG);
		return -1;
	}
	if (write(fd,super,sizeof(struct sfs_super)) 
			!= sizeof(struct sfs_super)) {
		pr_sfs_debug("Unable to write super block on device\n");
		pr_sfs_debug(SFS_DEBUG_MSG);
		return -1;
	}
	pr_sfs_debug("Wrote super block successfully\n");
return 0;
}

/*
 * @inode: The inode to write.
 * @fd: The device file descriptor.
 * @where: The exact offset from current location.
 *
 * Returns 0 on everything good. -1 on error.
 * */
int write_dentry (int fd,struct sfs_dirent *dentry,loff_t where)
{
	if (lseek64(fd,SEEK_CUR,where) < 0) {
		pr_sfs_debug("Unable to seek in device\n");
		pr_sfs_debug(SFS_DEBUG_MSG);
		return -1;
	}
	if (write(fd,dentry,dentry->length) != dentry->length) {
		pr_sfs_debug("Unable to write in device\n");
		pr_sfs_debug(SFS_DEBUG_MSG);
		return -1;
	}
	pr_sfs_debug("Wrote a dentry for %s successfully\n",dentry->name);
return 0;
}

int main(int argc,char *argv[])
{
	return EXIT_SUCCESS;
}
