#include "mapdriver.h"

static driver_status_t status =
{
	'0',   /* Starting ASCII char is '0' */
	false, /* Not busy at the beginning */
	{0},   /* buffer */
	NULL,  /* buffer's ptr */
	-1,    /* major */
	-1     /* minor */
};

static int device_open(inode, file)
	struct inode* inode;
	struct file* file;
{
	static int counter = 0;
	
#ifdef _DEBUG
	printk("device_open(%p, %p)\n", inode, file);
#endif
	
	/* Get the minor version of the driver */
	status.minor = inode->i_rdev >> 8;
	status.minor = inode->i_rdev & 0xFF;

	printk
	(
		"Device: %d.%d, busy: %d\n",
		status.major,
		status.minor,
		status.busy
	);

	if (status.busy)
		return -EBUSY;

	status.busy = true;
	
	sprintf
	(
		status.buf, 
		"If I told you once, I told you %d times - %s",
		counter++,
		"Hello, World\n"
	);
	status.buf_ptr = status.buf;
	return SUCCESS;
}

static int device_release(inode, file)
	struct inode* inode;
	struct file* file;
{
#ifdef _DEBUG
	printk("device_release(%p,%p)\n", inode, file);
#endif

	status.busy = false;
	return SUCCESS;
}

static int device_read(file, buffer, length, offset)
	struct file* file;
	char*        buffer;
	size_t       length;
	loff_t*      offset;
{
	 
}

static int device_write(file, buffer, length, offset)
	struct file* file;
	char*        buffer;
	size_t       length;
	loff_t*      offset;
{

}

int init_module(void)
{
	/* Register the character device (atleast try) */
	status.major = register_chrdev
	(
		0,
		DEVICE_NAME,
		&Fops
	);

	/* Negative values signify an error */
	if(status.major < 0)
	{
		printk
		(
			"Sorry, registering the ASCII device failed with %d\n",
			status.major
		);

		return status.major;
	}

	printk
	(
		"Registeration is a success. The major device number is %d.\n",
		status.major
	);

	printk
	(
		"If you want to talk to the device driver,\n" \
		"you'll have to create a device file. \n" \
		"We suggest you use:\n\n" \
		"mknod %s c %d <minor>\n\n" \
		"You can try different minor numbers and see what happens.\n",
		DEVICE_NAME,
		status.major
	);

	return SUCCESS;
}

void cleanup_module(void)
{
	unregister_chrdev(status.major, DEVICE_NAME);
}
