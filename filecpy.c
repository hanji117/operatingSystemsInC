/*
============================================================================
HW#: Assignment 1 Simple File Copy Program
Name: Edgar Cruz
Compiler: g++
Description : Copy input file into output file
============================================================================
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h> 
#include <sys/stat.h>

#define BUF_SIZE 256
 
int main(int argc, char* argv[])
{
 
  int input_fd, output_fd;    /* Input and output file descriptors */
  ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
  char buffer[BUF_SIZE];      /* Character buffer */
 
  /* Are src and dest file name arguments missing */
  if(argc != 3)//3 arguments are allowed only to pass
  {
    printf ("Error only 2 files are allowed %s\n",strerror(errno));
    return 1;
  }
 
  /* Create input file descriptor */
  //displays error message if the input file doesn't exist
  input_fd = open (argv [1], O_RDONLY);
  if (input_fd == -1) 
  {
    printf ("Error input file doesn't exist %s\n",strerror(errno));
    return 2;
  }
 
  /* Create output file descriptor */
  output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
  if(output_fd == -1)
  {
    printf ("the output file can't be written %s\n",strerror(errno));
    return 3;
  }
 
  /* Copy process */

  while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
    ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
    if(ret_out != ret_in){
      /* Write error */
      perror("copy not successful");
      return 4;
    }
  }
 
  /* Close file descriptors */
  close (input_fd);
  close (output_fd);
 
  return (EXIT_SUCCESS);
}
