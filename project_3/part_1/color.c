#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h> 
#include <linux/slab.h>

struct color {
	int red;
	int blue;
	int green;
	int black;
	struct list_head list;
};

static LIST_HEAD(color_list);

/* Module entry point */

int ColorLinkedList_init(void) {

/* Creating each Color struct in list */

	printk(KERN_INFO "Creating Color list\n");

	struct color *clo1;
	clo1 = kmalloc(sizeof(*clo1), GFP_KERNEL);
	clo1->red = 138;
	clo1->blue = 48;
	clo1->green = 226;
	clo1->black = 01;
	INIT_LIST_HEAD(&clo1->list);
	list_add_tail(&clo1->list, &color_list);

	struct color *clo2;
	clo2 = kmalloc(sizeof(*clo2), GFP_KERNEL);
	clo2->red = 200;
	clo2->blue = 201;
	clo2->green = 202;
	clo2->black = 203;
	INIT_LIST_HEAD(&clo2->list);
	list_add_tail(&clo2->list, &color_list);

	struct color *clo3;
	clo3 = kmalloc(sizeof(*clo3), GFP_KERNEL);
	clo3->red = 300;
	clo3->blue = 301;
	clo3->green = 302;
	clo3->black = 303;
	INIT_LIST_HEAD(&clo3->list);
	list_add_tail(&clo3->list, &color_list);

/* Traversing the list */

	printk(KERN_INFO "Traversing color list\n");

	struct color *ptr;

	list_for_each_entry(ptr, &color_list, list) {
		printk(KERN_INFO "COLOR: RED: %d BLUE: %d GREEN: %d BLACK: %d\n", 
			ptr->red, 
			ptr->blue,
			ptr->green,
			ptr->black);
	}

	return 0;
}

/* Module exit point */

void ColorLinkedList_exit(void) {

	printk(KERN_INFO "Removing module\n");

/* Removes each struct from list */
	struct color *ptr,*next;
	list_for_each_entry_safe(ptr, next, &color_list, list) {
		printk(KERN_INFO "REMOVING COLOR: RED: %d BLUE: %d GREEN: %d BLACK: %d\n", 
			ptr->red, 
			ptr->blue,
			ptr->green,
			ptr->black);

		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Register module entry/exit pts */

module_init(ColorLinkedList_init);
module_exit(ColorLinkedList_exit);

MODULE_LICENSE("CO327 PROJECT_03");
MODULE_DESCRIPTION("COLORS_PART01");
MODULE_AUTHOR("THINESH_e15366");
