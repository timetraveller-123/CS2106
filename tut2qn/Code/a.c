#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int i;
  pid_t a[3];

  for(i = 0; i < 3; i++) {
    a[i] = fork();
    if (a[i] == 0) {
      printf("%d is done\n", getpid());
      return 0;
    }
  }

  for(i = 0; i < 3; i++) {
    waitpid(a[i], NULL, 0);
    printf("one child exited\n");
  }
  printf("parent %d is done.\n", getpid());
  return 0;
}
