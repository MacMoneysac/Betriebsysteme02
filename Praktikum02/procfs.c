// Einfaches Kernelmodul zur Erzeugung einer Datei
// im /proc-Filesystem
//
// Die Meldungen, die mit pr_info() ausgegeben werden,
// koennen mit 
// > dmesg
// angesehen werden.

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

// Groesse des Eingabepuffers
#define PROCFS_MAX_SIZE 32

// Name der Datei in /proc
#define PROCFS_ENTRY_FILENAME "procfsbuf"

static struct proc_dir_entry *our_proc_file;
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;


// Diese Funktion wird aufgerufen, wenn ein Prozess read() auf
// die Datei in /proc aufruft
// z.B.: > cat /proc/procfsbuf
//
static ssize_t procfs_read(struct file *filp, char __user *buffer,
                           size_t length, loff_t *offset)
{
    static int finished = 0;

    if (finished) {
        pr_info("procfs_read: End\n");
        finished = 0;
        return 0;
    }
    finished = 1;

    if (copy_to_user(buffer, procfs_buffer, procfs_buffer_size))
        return -EFAULT;

    pr_info("procfs_read: read %lu bytes\n", procfs_buffer_size);
    return procfs_buffer_size;
}

// Diese Funktion wird aufgerufen, wenn ein Prozess write() auf
// die Datei in /proc aufruft
// z.B.: > echo "Hallo, ein Text fuer den Puffer." > /proc/procfsbuf
//
static ssize_t procfs_write(struct file *file, const char __user *buffer,
                            size_t len, loff_t *off)
{
    if (len > PROCFS_MAX_SIZE)
        procfs_buffer_size = PROCFS_MAX_SIZE;
    else
        procfs_buffer_size = len;
    if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
        return -EFAULT;

    pr_info("procfs_write: write %lu bytes\n", procfs_buffer_size);
    return procfs_buffer_size;
}

// fopen() fuehrt hierhin
static int procfs_open(struct inode *inode, struct file *file)
{
    pr_info("procfs open()");
    try_module_get(THIS_MODULE);
    return 0;
}

// fclose() fuehrt hierhin
static int procfs_close(struct inode *inode, struct file *file)
{
    pr_info("procfs close()");
    module_put(THIS_MODULE);
    return 0;
}

#ifdef HAVE_PROC_OPS
static struct proc_ops file_ops_proc_file = {
    .proc_read = procfs_read,
    .proc_write = procfs_write,
    .proc_open = procfs_open,
    .proc_release = procfs_close,
};
#else
static const struct file_operations file_ops_proc_file = {
    .read = procfs_read,
    .write = procfs_write,
    .open = procfs_open,
    .release = procfs_close,
};
#endif

static int __init procfs_init(void)
{
    // Erzeugen der Datei, diese ist sofort sichtbar
    // Berechtigung 644
    our_proc_file = proc_create(PROCFS_ENTRY_FILENAME, 0644, NULL,
                                &file_ops_proc_file);
    if (our_proc_file == NULL) {
        remove_proc_entry(PROCFS_ENTRY_FILENAME, NULL);
        pr_info("Error: Could not initialize /proc/%s\n",
                 PROCFS_ENTRY_FILENAME);
        return -ENOMEM;
    }
    // Weitere Attribute der Datei festelegen
    // Die Datei ist nur eine Pseudodatei und belegt keinen Speicher,
    // auch wenn Sie mit 80 Bytes angezeigt wird
    proc_set_size(our_proc_file, 80);
    proc_set_user(our_proc_file, GLOBAL_ROOT_UID, GLOBAL_ROOT_GID);

    pr_info("/proc/%s created\n", PROCFS_ENTRY_FILENAME);
    return 0;
}

static void __exit procfs_exit(void)
{
    remove_proc_entry(PROCFS_ENTRY_FILENAME, NULL);
    pr_info("/proc/%s removed\n", PROCFS_ENTRY_FILENAME);
}

module_init(procfs_init);
module_exit(procfs_exit);

MODULE_LICENSE("GPL");
