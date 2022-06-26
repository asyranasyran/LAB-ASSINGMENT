#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int main(void){

void sigint_handler(int sig);
char s[200];

if(signal(SIGINT, sigint_handler) == SIG_ERR){
perror("error to catch SIGINT");
exit(1);
}

else if(signal(SIGTSTP, sigint_handler) == SIG_ERR){
perror("error to catch SIGTSTP");
exit(1);
}

else if(signal(SIGQUIT, sigint_handler) == SIG_ERR){
perror("error to catch SIGQUIT");
exit(1);
}

printf("Enter a string:\n");

if(fgets(s,200,stdin)==NULL)
perror("gets");

else
printf("You entered: %s\n", s);

return 0;

}

void sigint_handler(int sig){
if(sig == SIGINT) 
printf("This is a special signal handler for SIGINT\n");

else if(sig == SIGTSTP)
printf("This is a special signal handler for SIGTSTP\n");

else if(sig == SIGQUIT)
printf("This is a special signal handler for SIGQUIT\n");
}
