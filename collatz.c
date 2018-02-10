/*                                                                  
============================================================================  
HW#: Assignment 2 Fork System Call                                    
Name: Edgar Cruz                                                           
Compiler: g++                                                                 
File type: Implementation file
============================================================================
*/
//Note: pg. 68 in the book shows unix system calls (fork()).
//fork() is how you create new processes in Unix. When you call 
//fork, you're creating a copy of your own process that has its own 
//address space. This allows multiple tasks to run independently of one 
//another as though they each had the full memory of the machine to 
//themselves.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[])
{   
    pid_t pid;
    
    if (argc != 2)
    {
      printf("ERROR you need to enter a num in < >: ./collatz< >\n", strerror(errno));
     
      return -1;
    }

    int n = atoi (argv[1]);
       
    if (n < 1)
    {
      printf("Error Fork Failed  \n", strerror(errno));      
      return -1;
    }  
    pid = fork();
  
    if (pid > 0) 
    {
      printf("\nThis is the parent process. \n");
      printf("Waiting for the child to terminate. \n");
      wait(pid);
      printf("\nParent process has ended. \n");
      return 1;
    }
    else if (pid == 0)   //child process 
    {
      pid_t child_pid = getpid();

      //printf("Child \n", child_pid);
      printf("Start the sequence at: %d\n",n);
      while (n != 1)
      {
	n = n % 2 ? 3 * n + 1: n /2;
	printf("\n(Child) %d" , n);
      }
      return EXIT_SUCCESS;
    }
    else //parent process
    { //parent will wait for the child to complete
      wait(NULL);
      printf("Child Complete");//, strerror(errno));
 
    }
    return 0;
}





  



