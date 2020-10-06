#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h> 
#include <linux/slab.h>
#include<linux/moduleparam.h>
struct collatz {
	int n;
	struct list_head list;
};

static LIST_HEAD(collatz_list);
static int start = 25;

module_param(start,int,0);
/* Module entry point */

int Collatz_init(void) {

/* Creating each Color struct in list */

	printk(KERN_INFO "Creating Color list\n");
	while(1){
	struct collatz *col;
	col = kmalloc(sizeof(*col), GFP_KERNEL);
	col->n = start;
	
	INIT_LIST_HEAD(&col->list);
	list_add_tail(&col->list, &collatz_list);
	if(start==1){
	break;	
	}
	else if(start%2==0)
	{
	start=start/2;
	}
	else{
	start=3*start+1;	
	}
	}

/* Traversing the list */

	printk(KERN_INFO "Traversing color list\n");

	struct collatz *ptr;

	list_for_each_entry(ptr, &collatz_list, list) {
		printk(KERN_INFO "VALUE: N: %d\n", 
			ptr->n);
	}

	return 0;
}

/* Module exit point */

void Collatz_exit(void) {

	printk(KERN_INFO "Removing module\n");

/* Removes each struct from list */
	struct collatz *ptr,*next;
	list_for_each_entry_safe(ptr, next, &collatz_list, list) {
		printk(KERN_INFO "VALUE: N: %d\n", 
			ptr->n);

		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Register module entry/exit pts */

module_init(Collatz_init);
module_exit(Collatz_exit);

MODULE_LICENSE("CO327 PROJECT_03");
MODULE_DESCRIPTION("COLORS_PART01");
MODULE_AUTHOR("THINESH_e15366");
