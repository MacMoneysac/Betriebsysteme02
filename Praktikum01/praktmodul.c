#include <linux / kernel.h>
#include <linux / module.h>
#include <linux / timer.h>
#include <linux / types.h>

#define PRINTK(x...) printk(KERN_DEBUG "Praktmodul: " x)

static int __init prakt_module_init(void)
{
    PRINTK("Praktikumsmodul init\n");
    return 0;
}
static void __exit prakt_module_exit(void)
{
    PRINTK("Praktikumsmodul exit\n");
}

module_init(prakt_module_init);
module_exit(prakt_module_exit);
MODULE_DESCRIPTION("Praktikum Kernelmodul");
MODULE_LICENSE("GPL");