#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/cred.h>

asmlinkage long set_myFlag(pid_t pid, int flag){

	printk("set my flag starts running with: %d, %d \n",pid,flag);

  struct task_struct *task;
  task=find_task_by_vpid(pid);

	if (task>0)
	{
			printk("found task:  %d  \n", task->pid);
		if(current_cred()>0){
			  if(current_cred()->uid <= 0 || current_cred()->gid<=0){ //https://www.kernel.org/doc/Documentation/security/credentials.txt
			      //Process has root priv. check flag
				if(flag==1 || flag==0){
					task->myFlag=flag;
					printk("my_flag value of process %d has been set to %d \n",pid,task->myFlag);
					//https://www.ibm.com/developerworks/library/l-kernel-logging-apis/index.html
				 	return 0;
				}
				else{
					printk("my_flag value of process %d can not set to %d \n",pid,flag);
					return -EINVAL;
				}

			  }
			  else{
			    //Not Root throw error
			    printk("my_flag value of process %d can not set to %d \n",pid,flag);
				 //https://www.ibm.com/developerworks/library/l-kernel-logging-apis/index.html
			    return -EPERM; // http://man7.org/linux/man-pages/man2/syscalls.2.html
			  }
		}
		else{
			printk("user error \n");
			return -EACCES;
		}
	}
	else{
		printk("no process found \n");
		return -ESRCH;
	}
}
