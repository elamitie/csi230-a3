#ifndef _MAP_DEVICE_H
#define _MAP_DEVICE_H

/* Standard in kernel modules */
#include <linux/kernel.h>   /* We're doing kernel work */
#include <linux/module.h>   /* Specifically, a module */

/* For character devices */
#include <linux/fs.h>       /* The character device
                             * definitions are here
                             */
#include <linux/string.h>
#include <asm/uaccess.h>  /* for put/get_user */

#define SUCCESS    	   0
#define DRV_BUF_SIZE       80
#define DEVICE_NAME 	   "/dev/asciimap"
#define DEFAULT_MAP_WIDTH  50
#define DEFAULT_MAP_HEIGHT 50
#define BSIZE              4096

static char map[(DEFAULT_MAP_WIDTH * DEFAULT_MAP_HEIGHT) - 1];

typedef struct _driver_status
{
	int    curr_pos;
	char   mapbuffer[BSIZE];
	bool   busy;
	char   buf[DRV_BUF_SIZE];
	char*  buf_ptr;
	int    major;
	int    minor;
} driver_status_t;

static int device_open(struct inode*, struct file*);
static int  device_release(struct inode*, struct file*);
static loff_t device_lseek(struct file*, loff_t, int);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);

struct file_operations Fops =
{
	NULL,   /* owner */
	device_lseek,
	device_read,
	device_write,
	NULL,   /* readdir */
	NULL,   /* poll/select */
	NULL,   /* ioctl */
	NULL,   /* mmap */
	device_open,
	NULL,   /* flush */
	device_release  /* a.k.a. close */
};

int init_module(void);
void cleanup_module(void);

#endif /* _MAP DRIVER H */
