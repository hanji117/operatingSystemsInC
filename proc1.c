#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define MAX_COUNT 50

int main(int argc,  char **argv)
{

  int i, j;
  int counter = 0;

  /* Fork a process */
  pid_t pid = fork();

  if (pid == 0) {
    /* This is the child process */
    for (i = 0; i < MAX_COUNT; i++) {
      printf("Child PID = 0x%x, counter = %d \n", pid, ++counter);
    }
  } else if (pid > 0) {
    /* This is the parent process */
    for (j = 0; j < MAX_COUNT; j++) {
      printf("Parent PID = 0x%x, counter = %d \n", pid, ++counter);
    }
  }
  else {
    /* Fork command failed - check the error */
    printf("fork failed errno = 0x%x, (%s) \n", __FILE__,
	   errno, strerror(errno));
    return -1;
  }

  return 0;

}
