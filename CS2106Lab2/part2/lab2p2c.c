#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    if(fork() ==  0) {
        char *a[] = {"cat", "file.txt", NULL};
        execvp("cat", a);
    }
    else
        wait(NULL);
}

