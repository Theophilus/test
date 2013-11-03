#ifndef CRYPT_IOCTL_H
#define CRYPT_IOCTL_H
#include <linux/ioctl.h>


extern struct file_operations ctl_fops;
extern dev_t ctl_dev;
extern struct cdev *ctl_cdev;
extern struct class *ctl_class;
//extern struct device *samplectl_device;

int ctl_init(void);
void ctl_destroy(void);

#define CRYPT_CREATE _IO('q', 1)
#define CRYPT_WRITE _IO('q',2)
#define CRYPT_DESTROY _IO('q',3)


#endif
