#ifndef _LINUX_PRINFO_H
#define _LINUX_PRINFO_H

#ifndef __KERNEL__
//if the header files are from loadable kernel modules.
#include <linux/types.h>
#include <linux/pid.h>

#else
//else the header files are from the use-space programs.

#include <asm/unistd.h>
#include <sys/types.h>
#endif
struct prinfo{
	long state;/*current process state*/
	long nice;/*process nice value*/
	pid_t pid;/*process id*/
	pid_t parent_pid;/*process id of parent*/
	pid_t youngest_child_pid;/*process of youngest child*/
	unsigned long start_time;/*process start time*/
	long user_time;/*CPU time for user mode*/
	long sys_time;/*CPU time for kernel mode*/
	long uid;/*user id for process owner*/
	char comm[16];/*name of the program executed */
};

#endif
