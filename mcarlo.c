//=========================================================     
//HW#: HW3 Threads                                       
//Your name: Edgar Cruz                           
//Complier:  gcc                                                             
//File type: Thread implementation file               
//========================================================= 

//.h for c header
#include <errno.h>
#include <stdio.h>       //#include <iostream>
#include <string.h>    //#inlcude<string>
#include <pthread.h>
#include <math.h>        //defines math functions
#include <stdlib.h>      //defines rand(), srand(), RAND_MAX

//using namespace std; not used in c

//Global variables
int  hit_count = 0;
int npoints = 0;

// Generates a double precision random number 
double random_double() 
{
  return random() / ((double)RAND_MAX + 1);
}

//void *count(void *unused) //threads calls this function
void *count(void *ptr)//threads calls this function
{
  int hit = 0;

   for (int i = 0; i < npoints; i++) 
   {
       // generate random numbers between -1.0 and +1.0 (exclusive) 
       double x = random_double() * 2.0 - 1.0;
       double y = random_double() * 2.0 - 1.0;
       
       if (sqrt(x*x + y*y) < 1.0 )
	 ++hit;
   }
   hit_count += hit;  
   return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t thread;
  
  if(argc != 2)//2 arguments are allowed only to pass                              
  {
      printf ("Error only 2 arguments are allowed \n",strerror(errno));
      return -1;
  }
  
  npoints = atoi (argv[1]); 

  if (npoints < 0)
  {
      printf("Error negative values are not allowed \n", strerror(errno));
      return -1;
  }
  if (npoints == 0)
  {
      printf("Error 0 is  not allowed \n", strerror(errno));
      return -1;
  }

    for (int a = 0; a < 5; a++){
    pthread_create(&thread, NULL, &count, NULL);//create the thread
    }  
    for (int a = 0; a < 5; a++){
    pthread_join(thread, NULL);/*wait for the thread to exit*/
    }
  
  double points = 4.0 * hit_count;
  double pi = points/(npoints * 5);
  
  printf("The approximate value of pi for the desired amount of points (%d) is: %f \n",npoints, pi);  
  return 0;
}


