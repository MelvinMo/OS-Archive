#include <linux/string.h>
#include <linux/init.h> // For module init and exit
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // For fops
#include <linux/uaccess.h>
#include <linux/slab.h>
//#include <string.h> // Can't use it!

static int account[100];

#define DEVICE_NAME "iut_device"
MODULE_LICENSE("GPL");


// FILE OPERATIONS
static int iut_open(struct inode *, struct file *);
static int iut_release(struct inode *, struct file *);
static ssize_t iut_read(struct file *, char *, size_t, loff_t *);
static ssize_t iut_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = iut_open,
    .read = iut_read,
    .write = iut_write,
    .release = iut_release,
};

// Why "static"? --> To bound it to the current file.
static int major; // Device major number. Driver reacts to this major number.

// Event --> LOAD
static int __init iut_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops); // 0: dynamically assign a major number ||| name is displayed in /proc/devices ||| fops.
    if (major < 0)
    {
        printk(KERN_ALERT "iut_device load failed.\n");
        return major;
    }

    int i = 0;
    while (i<100)
    {
        account[i] = 2000000;
    	i = i + 1;
    }

    printk(KERN_INFO "iut_device module loaded: %d\n", major);
    return 0;
}

// Event --> UNLOAD
static void __exit iut_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "iut_device module unloaded.\n");
}

// Event --> OPEN
static int iut_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "iut_device opened.\n");
    return 0;
}

// Event --> CLOSE
static int iut_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "iut_device closed.\n");
    return 0;
}

// Event --> READ
static ssize_t iut_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    char message[2000] = "";
    char temp_buffer[20];
    int i = 0;
    for (i = 0; i < 100; i++)
    {
        sprintf(temp_buffer, "%d,", account[i]);
        strcat(message, temp_buffer);
    }

    int errors = 0;
    errors = copy_to_user(buffer, message, strlen(message));
    return errors == 0 ? strlen(message) : -EFAULT;
}

static ssize_t iut_write(struct file *filep, const char *buffer, size_t length, loff_t *offset)
{
    char message2[500] = ""; 
    

    if (copy_from_user(message2, buffer, length) != 0)
        return -EFAULT;
	int from,to,amount;
   char* message = (char *)kzalloc(sizeof(message2) * sizeof(char), GFP_KERNEL);
   
sprintf(message, "%s", message2);

        if (strcmp(message, "r") == 0)
        {
            printk(KERN_INFO "Received %s from user\n", message);
        }
    
    else
    {
      char *pt;
    pt = strsep (&message,",");
    if(strcmp(pt,"e")==0)
    {
    pt = strsep (&message,",");
     kstrtoint(pt, 10, &from);
pt = strsep (&message,",");
    kstrtoint(pt, 10, &to);
pt = strsep (&message,",");
    kstrtoint(pt, 10, &amount);
    if(account[from]-amount<0){
    printk(KERN_INFO "not enough deposit.\n");
    return 0;
    }
    account[from] = account[from] - amount;
    account[to] = account[to] + amount;
    return 0;
    }
    else if(strcmp(pt,"v")==0){
pt = strsep (&message,",");
pt = strsep (&message,",");
    kstrtoint(pt, 10, &to);
pt = strsep (&message,",");
    kstrtoint(pt, 10, &amount);
    account[to] = account[to] + amount;
    return 0;
    }
    else if(strcmp(pt,"b")==0){
pt = strsep (&message,",");
    kstrtoint(pt, 10, &from);
pt = strsep (&message,",");
pt = strsep (&message,",");
    kstrtoint(pt, 10, &amount);
    if(account[from]-amount<0){
    printk(KERN_INFO "not enough deposit.\n");
    return 0;
    }
    account[from] = account[from] - amount;
    return 0;
    }
    else{
    printk(KERN_ALERT "invalid input \n");
    return 0;
    }
    
    }
    

    return 0;
}

// Registering load and unload functions.
module_init(iut_init);
module_exit(iut_exit);
