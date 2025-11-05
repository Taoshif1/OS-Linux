#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

  int pid1 = fork();
  
  if(pid1 == 0){

    //child1
    printf("Child 1 (PID = %d): Running...\n", getpid());
    sleep(1);
    printf("Child 1 (PID = %d): Finished...\n", getpid());
    return 0;
  }
else
  {
    //Parent waits for child 1 to finish
    wait(NULL);
    printf("Parent: Child 1 completed.\n");
    
    int pid2 = fork();

    if(pid2 == 0){

      //child2
      printf("Child 2 (PID = %d): Running...\n", getpid());
      sleep(2);
      printf("Child 2 (PID = %d): Finished...\n", getpid());
      return 0;
    }
else
  {
      int status;
      waitpid(pid2, &status, 0);
      printf("Parent: Child 2 completed (using waitpid).\n");
    } 
  }
    return 0;
}
