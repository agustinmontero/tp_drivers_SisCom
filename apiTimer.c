#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

static struct timer_list my_timer;
static int myint = 500;
/*
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits,
 * for exposing parameters in sysfs (if non−zero) at a later stage.
 */

module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");

void my_timer_callback( unsigned long data )
{
  printk( "my_timer_callback called (%ld).\n", jiffies );
}

int init_module( void )
{
  int ret;

  printk("Timer module installing\n");

  // my_timer.function, my_timer.data
  setup_timer( &my_timer, my_timer_callback, 0 );

  printk( "Starting timer to fire in %dms (%ld)\n", myint,jiffies );
  ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(myint) );
  if (ret) printk("Error in mod_timer\n");

  return 0;
}

void cleanup_module( void )
{
  int ret;

  ret = del_timer( &my_timer );
  if (ret) printk("The timer is still in use...\n");

  printk("Timer module uninstalling\n");

  return;
}
