//========================================================= 
//HW#: HW5 Virtual Address Translator                                 
//Your name: Edgar Cruz       
//Complier:  gcc                                                         
//File type: vmexp.c implementation file                              
//                                                                     
//I got some of the code from google, and                                   
//I modified some of it.                                                  
//=========================================================                 

#include <errno.h>//The errno.h header file of the C standard
//Library defines the integer variable errno, which is set by 
//system calls and some library functions in the event of an error
//to indicate what went wrong.
#include <stdio.h>//For printf()

int main(int argc, char *argv[])
/*argc refers to the number of command line arguments passed in, 
which includes the actual name of the program, as invoked by the user.  

argv contains the actual arguments,
starting with index 1. Index 0 is the program name.   
So, if you ran your program like this:   
                      
./program hello world                                                      
  Then:                                                                     
argc would be 3.                             
argv[0] would be "./program".                                               
argv[1] would be "hello".                                                  
argv[2] would be "world".        

*/
{
  if (argc != 2)
    {
      printf("Error only 2 arguments are allowed \n", strerror(errno));
      return -1;
    }

  
  unsigned long page;
  unsigned long offset;
  unsigned long address;

  address = atoi(argv[1]);

  //page (Page Number) = quotient of [address/ 4 KB]
  page = address >> 12;//page size is 4KB => 12 bits holding 
                       //the virtual address
  //address >> 12 == [address/(2^12)]
  offset = address & 0xfff;//Converts address to binary and converts the 
  //hex to binary. To do an and table.
  //offset == remainder
  printf("The address %lu contains: \n", address);
  printf("page number = %lu\n", page);
  printf("offset = %lu\n", offset);//l is a length modifier meaning "long."
                                   //u is a specifier meaning 
                                   //"unsigned decimal integer."


  return 0;
}
