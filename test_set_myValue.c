#include <stdio.h>
#define NR_mycall 355
#include <unistd.h>


int main (void){
     int x1=10, x2=1,y;
     y=syscall(NR_mycall, x1, x2);
	 printf("Main MyFlag Value: %d\n",y);
	 int pid;
	
	pid=fork();
	
	if(pid==0)
	{
		printf("I am the child\n");
        printf("my pid=%d\n", getpid());
			//while(1)
			{
				//empty must wait father to exit
			}
		return 0;
	}
	
	else
	{	
		 
		printf("I am the father\n");
		printf("my pid=%d\n", getpid());
		return 1;
	}
	
	
	
	
    
}
