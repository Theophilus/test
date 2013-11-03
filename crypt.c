#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#include "crypt_ioctl.h"
#include 


// Module init
static int  cryptctl_init(void)
{
	// init the control device
	ctl_init();
	
	// init the sampledev stuff
	//sampledev_init();
	
	return 0;
}

// Module exit
static void  cryptctl_exit(void){
	// Clean up the sampledev stuff
	//sampledev_cleanup();
	
	// Clean up the control device
	ctl_destroy();
}

module_init(cryptctl_init);
module_exit(cryptctl_exit);

MODULE_LICENSE("GPL");
