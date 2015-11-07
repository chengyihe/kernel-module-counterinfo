#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/seq_file.h>

static struct proc_dir_entry *hello_dentry;

static int hello_show(struct seq_file *m, void *v)
{
	seq_printf(m, "procfs hello world\n");

	return 0;
}

static int hello_open(struct inode *inode, struct file *file)
{
	return single_open(file, hello_show, inode->i_private);
}

static const struct file_operations hello_fops = {
	.open = hello_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init procfs_hello_init(void)
{
	hello_dentry = proc_create("hello", 0, NULL, &hello_fops);

	if (!hello_dentry) {
		pr_err("failed to create /proc/hello\n");
		return -ENOMEM;
	}

	return 0;
}

static void __exit procfs_hello_exit(void)
{
	proc_remove(hello_dentry);
}

module_init(procfs_hello_init);
module_exit(procfs_hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("chengyihe");
