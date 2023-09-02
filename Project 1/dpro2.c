#include "types.h"
#include "user.h"
#include "syscall.h"



#define MAX_CHILD 5

int main(int argc , char*argv[]){
  int child[MAX_CHILD];
  int inChild = 0;

  printf(1 , "%s is runnigng (pid: %d) to make 5 childs\n" , argv[0] , getpid());
  for(int i = 0; i < MAX_CHILD; i++){
    child[i] = fork();
    if(child[i] == 0){
      inChild = 1;
      break;
      sleep(2);
    }
    else{
      printf(1 , "Parent (pid : %d) creating child %d (pid : %d)\n" , getpid() , i+1 , child[i] );
    }
  }

  if(inChild){
    sleep(20);
    printf(1 , "Child (pid: %d) created\n", getpid());
    for(int i = 0; i < 100000; i++)
      sleep(0.01);
    exit();
  }

  if(!inChild){
    for(int i = 0; i < MAX_CHILD; i++){
      wait();
    }
    exit();
  }
}
