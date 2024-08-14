#include <stdlib.h>
#include<unistd.h>
#include<stdio.h>

void printFibonacci(int n) {
    int f= 0; 
    int s= 1;
    int np;
    int i;

    printf("Fibonacci Series: \n");

    for (i = 0; i < n; i++) {
        printf("%d ", f);
        np = f + s;
        f = s;
        s = np;
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("File used : %s\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    if (num <= 0) {
        printf("Invalid value for num !!..Enter valid number\n");
        return 1;
    }

    printFibonacci(num);

    return 0;
}
