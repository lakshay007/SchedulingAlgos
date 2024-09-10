#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
    printf("hi lakshay from parent\n");
    pid_t pid = fork();
    if(pid == 0){
        printf("hi from child\n");
        pid_t pidch = getpid();
        pid_t pidp = getppid();
        printf("the child and parent pid are resp : %ld %ld\n", pidch, pidp);
    }
    if(pid>0){
        wait(NULL);
        printf("hi again from parent\n");
        
   }

}