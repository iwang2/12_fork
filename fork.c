#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    Forks off 2 child processes
    Child process instructions:
        At the start print its pid
        Sleep for a random number of seconds in the range [5, 20]
            Each child should sleep for a (potentially) different amount of seconds
        At the end print a message that it is finished
    Parent process instructions
        Before forking, print out some initial message
        After the fork, wait for any child to finish
        Once a child has finished, print out the pid of the completed child as well as how many seconds it was asleep for.
            Do not run any kind of timer, think about how the child could send this information back to the parent.
        Print a message that the parent is done and then end the program
            The other child might still be running, that's ok.
 */

int main(){
  srand(time(NULL));

  printf("I am parent %d\n", getpid());
  printf("about to fork...\n");
  
  int child1, child2, status;
  
  child1 = fork();
  
  if(child1){
    child2 = fork();
    waitpid(-1, &status, 0);
    printf("status: %d\n", status);
  }
  
  if(!child1 || !child2){
    printf("I am child %d\n", getpid());
    if(!child2) rand();
    int s = rand() % 16 + 5;
    printf("child %d sleeping for %d seconds...\n", getpid(), s);
    sleep(s);
    printf("child %d has woken up!\n", getpid());
    exit(s);
  }
}
