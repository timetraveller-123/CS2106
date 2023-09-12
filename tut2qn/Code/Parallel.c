#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int pids[10000000];

int main()
{
  /*
    int userInput, childPid, childResult;
    //Since largest number is 10 digits, a 12 characters string is more
    //than enough
    char cStringExample[12];

    scanf("%d", &userInput);
   
    childPid = fork();

    if (childPid != 0 ){
        wait( &childResult);
        printf("%d has %d prime factors\n", userInput, childResult >> 8);

    } else {
        //Easy way to convert a number into a string
        sprintf(cStringExample, "%d", userInput);

        execl("./PF", "PF", cStringExample, NULL);
    }
      */
        
    

    int n;
    scanf("%d", &n);
    int m[n];
    for(int i = 0;i<n;i++)scanf("%d", &m[i]);
    char input[12];
   
    int val;
    
    for(int i = 0; i < n ; i++) {
      int pid = fork();
      pids[pid] = m[i];
      if (pid == 0) {
        
        sprintf(input, "%d", m[i]);
       
        execl("./PF", "PF", input, NULL);
      }
    }

    for(int i = 0; i< n;i++) {
      int pid = wait(&val);
      printf("%d has %d prime factors.\n", pids[pid], val>>8);
    }
    return 0;
}
