#include <stdio.h>
#define NR_mycall 355
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main (void){
     int x1=10, x2=1,y;
     int pid;
	int secim=0;
	printf("1-> Flag With 0 And Prio 0\n");
	printf("2-> Flag With 1 And Prio 0\n");
	printf("3-> Flag With 0 And Prio 33\n");
	printf("4-> Flag With 1 And Prio 33\n");
	
	scanf("%d", &secim);
	
	switch(secim)
	{
	case 1:	
	//do not set both up leave them down
	break;
	
	case 2:
	y=syscall(NR_mycall, x1, x2);
	//set flag one but leave prio low
	break;
	
	case 3:
	setpriority(PRIO_PROCESS, 0, 40);
	//set prio high but flag 0
	break;
	
	case 4:
	y=syscall(NR_mycall, x1, x2);
	setpriority(PRIO_PROCESS, 0, 40);
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
		return 123;
	}
	
	else
	{	
		
		printf("I am the father\n");
		printf("my pid=%d\n", getpid());
		 sleep(1); 
		return 312;
	}
	
	
	
	
    
}
