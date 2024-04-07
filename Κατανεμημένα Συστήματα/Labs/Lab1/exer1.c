#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    int x = 5;
    printf("A. pid=%d, value of x is %d\n", getpid(), x);
    pid_t chid=fork();

    if (chid==0) {
        x++;
        printf("B. pid=%d, value of x is %d\n", getpid(), x);
    } else {
        x--;
        printf("C. pid=%d, value of x is %d\n", getpid(), x);
    }
    printf("D. pid=%d, value of x is %d\n", getpid(), x);
    return 0;
}