#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
  srand(time(NULL));

  printf("I am parent %d\n", getpid());
  printf("about to fork...\n");
  
  int f1, f2, s;
  
  f1 = fork();
  if(f1){
    f2 = fork();
  }

  if(!f1 || !f2){
    int pid = getpid();
    printf("I am child %d\n", pid);
    
    if(!f1) rand();
    int s = rand() % 16 + 5;
    
    printf("child %d is going to sleep for %d seconds...\n", pid, s);
    sleep(s);
    
    printf("child %d has woken up!\n", pid);
    exit(s);
  }
  
  else{
    int child = wait(&s);
    printf("parents says child %d was sleeping for %d seconds\n", child, WEXITSTATUS(s));
    printf("parent finished running\n");
  }
}
