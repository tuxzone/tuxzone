#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>

MODULE_LICENSE("GPL");

dev_t adev;
struct cdev *myCdev;
char kernBuff[20];

int myChar_open(struct inode*, struct file*);
int myChar_release(struct inode*, struct file*);
ssize_t myChar_read(struct file*, char __user*,size_t,loff_t*);
ssize_t myChar_write(struct file*, const char __user*,size_t,loff_t*);

static struct file_operations myChar_fops=
{
	.open = myChar_open,
	.release = myChar_release,
	.read = myChar_read,
	.write = myChar_write
};

int myChar_open(struct inode* i_node, struct file* filp)
{
	printk("myCharDev opened successfully\n");
   return 0;
}

int myChar_release(struct inode* i_node, struct file* filp)
{
	printk("myCharDev released successfully\n");
   return 0;
}

ssize_t myChar_read(struct file* flip, char __user* userBuff, size_t count, loff_t *pos)
{
	printk("Reading the opened device \n");
	if(*pos != 0)
		return 0;

	strcpy(kernBuff,"Harman");
	printk("kernel string is %s, size is %d\n",kernBuff,sizeof(kernBuff));
	if(copy_to_user((char*)userBuff,(char*)kernBuff,sizeof(kernBuff))){
		printk("Coping Kernel buffer to user buffer failed\n");
		return -1;
	}
	else{
		printk("Copy successfull !!!, count is %d \n",count);
		*pos=sizeof(kernBuff);
		return sizeof(kernBuff);
	}
		
}

ssize_t myChar_write(struct file* flip,const char __user* userBuff, size_t count, loff_t *pos)
{
	printk("Writing to device, count is %d\n",count);
	
	if(copy_from_user(kernBuff,userBuff,count)){
		printk("Coping User buffer to Kernel buffer failed\n");
		return -1;
	}
	else{
		kernBuff[count]='\0';
		printk("Recieved from user %s, size is %d\n",kernBuff,sizeof(kernBuff));
		return count;
	}
			
}

static int __init myChar_init(void)
{
	int ret;
	adev=MKDEV(255,0);
	printk("Major no is %d, Minor no is %d\n",MAJOR(adev),MINOR(adev));
	ret=register_chrdev_region(adev,1,"myCharDev");
	if(ret<0)
		printk(" register_chrdev_region FAILED\n");
	else{
		myCdev=cdev_alloc();
		myCdev->ops = &myChar_fops;

		ret=cdev_add(myCdev,adev,1);
		if(ret<0)
			printk("Cdev adding failed\n");
				
	}
  return 0;
}

static void __exit myChar_exit(void)
{

	printk("GoodBye World\n");
	unregister_chrdev_region(adev,1);
	cdev_del(myCdev);

}

module_init(myChar_init);
module_exit(myChar_exit);

