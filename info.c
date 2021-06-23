#undef __KERNEL__
#undef MODULE

#define __KERNEL__
#define MODULE

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/prinfo.h>
#include <linux/list.h>
#include <asm/current.h>
#include <asm/uaccess.h>

//Function sys_getPrinfo:
long get_state(struct task_struct *taskInfo);
long get_nice(struct task_struct *taskInfo);
pid_t get_pid(struct task_struct *taskInfo);
pid_t get_parent_pid(struct task_struct *taskInfo);
pid_t get_youngest_child_pid(struct task_struct *taskInfo);
unsigned long get_start_time(struct task_struct *taskInfo);
long get_user_time(struct task_struct *taskInfo);
long get_system_time(struct task_struct *taskInfo);
long get_uid(struct task_struct *taskInfo);
char* get_comm(struct task_struct *taskInfo);

asmlinkage long sys_getPrinfo(struct prinfo *info){
	
	struct prinfo newInfo;
	char* _comm;
	//get current process info
	struct task_struct *taskInfo;
	taskInfo = get_current();
	//store data into newInfo
	newInfo.state = get_state(taskInfo);
	newInfo.nice = get_nice(taskInfo);
	newInfo.pid = get_pid(taskInfo);
	newInfo.parent_pid = get_parent_pid(taskInfo);
	newInfo.youngest_child_pid = get_youngest_child_pid(taskInfo);
	newInfo.start_time = get_start_time(taskInfo);
	newInfo.user_time = get_user_time(taskInfo);
	newInfo.sys_time = get_system_time(taskInfo);
	newInfo.uid = get_uid2(taskInfo);
	_comm = get_comm(taskInfo);
	strcpy(newInfo.comm, _comm);
	
	/*copy info from kernel to user*/
	if (copy_to_user(info,&newInfo,sizeof(struct prinfo))){
		return -EFAULT;	
	}
	return 0;//successful
}

/*current state of process*/
long get_state(struct task_struct *taskInfo){
	printk("current state of process : %ld\n",taskInfo->state);
	return taskInfo->state;
}

/*nice value*/
long get_nice(struct task_struct *taskInfo){
	printk("process nice value : %ld\n",	
	(long)PRIO_TO_NICE(taskInfo)->static_prio);
	return taskInfo->state;
}

/*process id*/
pid_t get_pid(struct task_struct *taskInfo){
	printk("process id: %ld\n",taskInfo->pid);
	return taskInfo->pid;
}

/*process id of parent*/
pid_t get_parent_pid(struct task_struct *taskInfo){
	printk("process id of parent: %ld\n",taskInfo->parent->pid);
	return taskInfo->parent->pid;
}
/*pid of youngest child*/
pid_t get_youngest_child_pid(struct task_struct *taskInfo){
	struct task_struct *youngest_child_pid;
	//check if taskInfo has choldren
	if (&taskInfo->children == NULL){
		return -1;
	}
	youngest_child_pid = list_entry(taskInfo->children.prev,struct 	task_struct,children);
	printk("pid of youngest child: %d\n",youngest_child_pid->pid);
	return youngest_child_pid->pid;
}

/*process start time*/
unsigned long get_start_time(struct task_struct *taskInfo){
	struct timespec start_time = taskInfo->start_time;
	unsigned long return_time;
	//return time(ms)
	return_time = (long)start_time.tv_sec*1000000 + start_time.tv_nsec/1000;
	printk("return start time is : %ld\n",return_time);
	return return_time;
}

/*CPU time for user mode*/
long get_user_time(struct task_struct *taskInfo){
	printk("CPU time for user mode: %ld\n",taskInfo->utime);
	return taskInfo->utime;
}

/*CPU time for kernel mode*/
long get_system_time(struct task_struct *taskInfo){
	printk("CPU time for kernel mode: %ld\n",taskInfo->stime);
	return taskInfo->stime;
}

/*user id of program*/
long get_uid(struct task_struct *taskInfo){
	printk("user id of process owner: %d\n",taskInfo->cred->uid);
	return taskInfo->cred->uid;
}
/*name of program*/
char* get_comm(struct task_struct *taskInfo){
	printk("name of program executed: %ld\n",taskInfo->stime);
	return taskInfo->stime;
}


