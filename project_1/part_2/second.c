#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>

#define BUFFER_SIZE 128
#define PROC_NAME "second"
ssize_t proc_read(struct file *file, char __user *usr_buf,size_t count, loff_t *pos);
int t;
static struct file_operations proc_ops = {
.owner = THIS_MODULE,
.read = proc_read,
};

/* This function is called when the module is loaded. */
int proc_init(void)
{
/* creates the /proc/hello entry */
   proc_create(PROC_NAME, 0666, NULL, &proc_ops);
   t=jiffies;
   return 0;
}

/* This function is called when the module is removed. */
void proc_exit(void)
{
/* removes the /proc/hello entry */
remove_proc_entry(PROC_NAME, NULL);
}

/* This function is called each time /proc/hello is read */
ssize_t proc_read(struct file *file, char __user *usr_buf,size_t count, loff_t *pos)
{
int rv = 0;
	char buffer[BUFFER_SIZE];
	static int completed = 0;
	
	if (completed) {
		completed = 0;
		return 0;
	}
	
	completed = 1;
	
	rv = sprintf(buffer, "%lu\n", (jiffies-t)/HZ);
	
	/* copies kernel space buffer to user space usr buf */
	copy_to_user(usr_buf, buffer, rv);
	
	return rv;
}
module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PROJECT 1.2");
MODULE_AUTHOR("THINESH_E15366");


