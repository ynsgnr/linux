#include <stdio.h>
#define NR_mycall 355
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main (void){
     int y;
     int pid;
     int which=PRIO_PROCESS;
     id_t pids=getpid();
	int secim=0;
	printf("1-> Flag With 0 And Prio 0\n");
	printf("2-> Flag With 1 And Prio 0\n");
	printf("3-> Flag With 0 And Prio 33\n");
	printf("4-> Flag With 1 And Prio 33\n");
	printf("5-> Flag With 2 And Prio 33\n");

	scanf("%d", &secim);
	
	switch(secim)
	{
	case 1:	
	//do not set both up leave them down
	break;
	
	case 2:
	y=syscall(NR_mycall, pids, 1);
	//set flag one but leave prio low
	break;
	
	case 3:
	setpriority(which, pids, -15);
	//set prio high but flag 0
	break;
	
	case 4:
	y=syscall(NR_mycall, pids, 1);
	setpriority(which, pids, -15);
	//set both up
	break;

	case 5:
	y=syscall(NR_mycall, pids, 2);
	setpriority(which, pids, -15);
	//set both up
	break;
	
	default:
	return 1;
	}

	pid=fork();
	
	if(pid==0)
	{
		printf("I am the child\n");
        printf("my pid=%d\n", getpid());
			while(1)
			{
				//empty must wait father to exit
				//or CTRL+C to stop
			}
			
		exit(0);
	}
	
	else
	{	
		int waits;
		printf("I am the father\n");
		printf("my pid=%d\n", getpid());
		printf("My Prio %d\n", getpriority(which, getpid()));
		//sleep(1); 
		 scanf("%d", &waits);
		 exit(0);
		//return 1;
	}
	
	
	
	
    
}
