#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

int a=3,b=4,sum;

module_param(a,int,S_IRUGO);
module_param(b,int,S_IRUGO);

static __init int param_init(void)
{
	sum=a+b;
	printk("sum is %d\n",sum);
   return 0;
}

static __exit void param_exit(void)
{
	printk("Bye Param\n");
}

EXPORT_SYMBOL_GPL(sum);

module_init(param_init);
module_exit(param_exit);
