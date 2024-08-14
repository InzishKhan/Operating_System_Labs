#include<stdio.h>
#include"header.h"
#include<unistd.h>
#include<signal.h>
extern int nLaps;
extern int LapT;
void OWN_Handler(int sig_num){
  if(sig_num==SIGCHLD){
    printf("Received SIGCHILD \n");
    int sum=0;
    sum=nLaps*LapT;
    printf("Total Time in Seconds: %d\n",sum);
  }

}
