#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/ioctl.h>
#include <linux/kdev_t.h>
#include <asm/uaccess.h>

#include "crypt_ioctl.h"

static int times=0;
dev_t ctl_dev;
struct cdev *ctl_cdev;
struct class *ctl_class;
struct device *ctl_device;

int dev_open(struct inode *, struct file *filep);
int dev_rls(struct inode *, struct file *filep);
static long crypt_ioctl(struct file *f, unsigned int cmd, unsigned long arg);

struct file_operations ctl_fops = {
  .owner = THIS_MODULE,
  .open = dev_open,
  .release = dev_rls,
  .unlocked_ioctl = crypt_ioctl,
};

long crypt_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
  switch (cmd) {
  
  case CRYPT_CREATE:
		  //return sampledev_create_device();
      	break;
  case CRYPT_DESTROY:
	//sampledev_destroy_device((int)arg);
       	break;
  }
  return 0;
}

int ctl_init(void){

  if( alloc_chrdev_region(&ctl_dev, 0, 1, "cryptctl") < 0) {
    //destroy_ctl();
    return -ENOMEM;
  }

  ctl_cdev = cdev_alloc();
  if (!ctl_cdev) {
    //ctl_destroy();
    return -ENOMEM;
  }
  ctl_cdev->ops = &ctl_fops;
  ctl_cdev->owner = THIS_MODULE;
  
  if(cdev_add(ctl_cdev, ctl_dev, 1) < 0) {
    // ctl_destroy();
    return -ENOMEM;
  }

  if(class_create(THIS_MODULE, "ctl_class") == NULL) {
    //ctl_destroy();
    return -ENOMEM;
  }

  if(device_create(ctl_class, NULL, ctl_dev, NULL, "cryptctl") == NULL) {
    // ctl_destroy();
    return -ENOMEM;
  }
  return 0;
}

void ctl_destroy(void){
  if (ctl_device) {
    device_destroy(ctl_class,ctl_dev);
  }

  if (ctl_class) {
    class_destroy(ctl_class);
  }
  if (ctl_cdev) {
    cdev_del(ctl_cdev);
  }
  unregister_chrdev_region(ctl_dev, 1);
}


//when the device is opened by a user program this runs
int dev_open(struct inode *inode, struct file *filep)
{
  times++;
  printk(KERN_INFO"Device opened %d times\n", times);
  return 0;
}

//when the device is closed by a user program this runs
int dev_rls(struct inode *inode, struct file *filep)
{
  printk(KERN_INFO "Device closed\n");
  return 0;
}

