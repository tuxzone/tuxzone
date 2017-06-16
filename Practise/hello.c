#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

extern int sum;

static __init int hello_init (void)
{
	printk("Hello World, sum is %d\n",sum);
    return 0;
}

static __exit void hello_exit(void)
{
	printk("GoodBye World\n");
}

module_init(hello_init);
module_exit(hello_exit);
