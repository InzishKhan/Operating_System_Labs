#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *SummationF(void *num) {
  int *v = (int *)num;
  int *sum = malloc(sizeof(int));
  *sum = 0;

  for (int i = 0; i <= *v; i++) {
    *sum += i;
  }

  pthread_exit(sum);
}

int main(int argc, char *argv[]) {
  int number = atoi(argv[1]);
  printf("The number is %d\n", number);

  pthread_t thread[number];
  int *ans[number];
  
  for (int i = 0; i < number; i++) {
    int *arg = malloc(sizeof(int));
    *arg = i;
    pthread_create(&thread[i], NULL, SummationF, arg);
  } 

  int totalSum = 0;
  for (int i = 0; i < number; i++) {
    pthread_join(thread[i], (void **)&ans[i]);
    totalSum += *ans[i];
  }

  printf("Summation of the number %d is: %d\n", number, totalSum);

  return 0;
}

