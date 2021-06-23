#include "prinfo.h"
#include <linux/unistd.h>
#include <stdio.h>

long getProcessInfo(struct prinfo *info){
	return syscall(336,info);
}

int main(void){
	struct prinfo info;
	long num;
	int f_name;
	for(int i=0;i<=30000;i++)
	{
		for(int j=0;j<=1000;j++){	
		f_name=f_name+1;
		}
	}
	num = getProcessInfo(&info);
	printf("state:%ld\n",info.state);
	printf("nice:%ld\n",info.nice);
	printf("pid:%d\n",info.pid);
	printf("parent pid:%d\n",info.parent_pid);
	printf("pid youngestchild:%d\n",info.youngest_child_pid);
	printf("start time:%ld\n",info.start_time);
	printf("user time:%ld\n",info.user_time);
	printf("system time:%ld\n",info.sys_time);
	printf("user id:%ld\n",info.uid);
	printf("name of program:%s\n",info.comm);

}
