#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include<fcntl.h>
#include<unistd.h>

int N;
int *fibS;

void *fibonacciGenerator(void *arg) {
    int n = *(int *)arg;
    int *series = (int *)malloc(n * sizeof(int));
    series[0] = 0;
    series[1] = 1;

    for (int i = 2; i < n; i++) {
        series[i] = series[i - 1] + series[i - 2];
    }

    fibS = series;
    pthread_exit(NULL);
}

void *evenCount(void *arg) {
    int *series = (int *)arg;
    int count = 0;

    for (int i = 0; i < N; i++) {
        if (series[i] % 2 == 0) {
            count++;
        }
    }
    pthread_exit((void *)(intptr_t)count);
}

void *oddCount(void *arg) {
    int *series = (int *)arg;
    int count = 0;

    for (int i = 0; i < N; i++) {
        if (series[i] % 2 != 0) {
            count++;
        }
    }
    pthread_exit((void *)(intptr_t)count);
}

void *sumCalculator(void *arg) {
    int *series = (int *)arg;
    int sum = 0;

    for (int i = 0; i < N; i++) {
        sum += series[i];
    }

    // Write the sum to a file
    int fd=open("output.txt",O_WRONLY);
    ssize_t bytes_written;
    bytes_written= write(fd,&sum, sizeof(sum));
    printf("Successfully written to the file \n");
    pthread_exit((void *)(intptr_t)sum);
}

int main(int argc, char *argv[]) {
    N = atoi(argv[1]);
    pthread_t threads[4];
    int results[4];

    printf("N = %d\n", N);

    // Fibonacci Generator
    pthread_create(&threads[0], NULL, fibonacciGenerator,&N);
    pthread_join(threads[0], NULL);
    printf("Series:");
    for (int i = 0; i < N; i++) {
        printf(" %d", fibS[i]);
    }
    printf("\n");

    // Even Count
    pthread_create(&threads[1], NULL, evenCount,fibS);
    pthread_join(threads[1], (void *)&results[1]);
    printf("Even Numbers: %d\n", results[1]);

    // Odd Count
    pthread_create(&threads[2], NULL, oddCount, fibS);
    pthread_join(threads[2], (void *)&results[2]);
    printf("Odd Numbers: %d\n", results[2]);

    // Sum 
    pthread_create(&threads[3], NULL, sumCalculator, fibS);
    pthread_join(threads[3], (void *)&results[3]);
    printf("Sum: %d\n", results[3]);

    return 0;
}

