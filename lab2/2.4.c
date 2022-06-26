#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childTask(int i, char name[]){
printf("Person %d ",i);
printf("is %s.",name);
printf("\n");
}

int main(void){

char  name[100];

        pid_t pid = fork();

        if(pid==0){
	      for(int i=1;i<5;i++){	  
  	      // printf("Child process => PPID=%d, PID=%d\n", getppid(), getpid());
              printf("Hi, what is your name?> ");
	      scanf("%s", name);
	      childTask( i, name);
          }
           exit(0);
	  }

	else{
       // printf("Parent process => PID=%d\n", getpid());
        printf("Waiting for child process to finish. . .\n");
	wait(NULL);
        printf("Job is done.\n");
        }

        return EXIT_SUCCESS;
     }
