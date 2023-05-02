#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>

/*
	* This module is a vmalloc implementation that is used for kernel allocation memory
	* vmalloc is used when allocating a variable sized blocks of memory unlike of the 
	* kmalloc that is used for small,fixed-size blocks.  
 */

MODULE_LICENSE("GPLv2+");

#define MEM_SIZE (1024 * 1024)  // 1MB of memory

static char *mem_ptr;  // Pointer to the allocated memory

int init_module(void) {
    // Allocate memory using vmalloc()
    mem_ptr = vmalloc(MEM_SIZE);

    if (mem_ptr == NULL) {
        printk(KERN_ERR "Failed to allocate memory using vmalloc()\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "Allocated %d bytes of memory using vmalloc()\n", MEM_SIZE);

    // Use the allocated memory
    // ...

    return 0;
}

void cleanup_module(void) {
    // Free the allocated memory using vfree()
    vfree(mem_ptr);

    printk(KERN_INFO "Freed %d bytes of memory using vfree()\n", MEM_SIZE);
}

