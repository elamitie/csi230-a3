#ifndef _MAP_DEVICE_H
#define _MAP_DEVICE_H

/* Standard in kernel modules */
#include <linux/kernel.h>   /* We're doing kernel work */
#include <linux/module.h>   /* Specifically, a module */

/* For character devices */
#include <linux/fs.h>       /* The character device
                             * definitions are here
                             */
#include <asm/uaccess.h>  /* for put/get_user */

#define SUCCESS      0
#define DRV_BUF_SIZE 80
#define DEVICE_NAME  "/dev/asciimap"
#define DEFAULT_MAP_WIDTH 50
#define DEFAULT_MAP_HEIGHT 50

static char map[DEFAULT_MAP_WIDTH * DEFAULT_MAP_HEIGHT];

typedef struct _driver_status
{
	//:char   map_buf[DEFAULT_MAP_WIDTH * DEFAULT_MAP_HEIGHT];
	bool   busy;
	char   buf[DRV_BUF_SIZE];
	char*  buf_ptr;
	int    major;
	int    minor;
} driver_status_t;

static int device_open(struct inode*, struct file*);
static int  device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);

struct file_operations Fops =
{
	NULL,   /* owner */
	NULL,   /* seek */
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
