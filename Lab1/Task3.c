#include<stdio.h>
#include<unistd.h>

int main(){
  printf("Level 1 (Parent): PID = %d, PPID: %d\n", getpid(),getppid());
  
  int pid1 = fork();
  
  if(pid1 == 0){
    printf("Level 2 (Child): PID = %d, PPID: %d\n", getpid(), getppid());
    
    int pid2 = fork();
    if(pid2 == 0){
      printf("Level 3 (Grand Child): PID = %d, PPID =%d\n", getpid(), getppid());
      }
    }
  sleep(1);

return 0;
}
