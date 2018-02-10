#include<stdio.h>
#include<stdlib.h> 
#include<sched.h> 
#include<time.h> 
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h> 
#define CRC_POLY 0XEDB88320
#define CRC_SIZE 256
int nitems=0; //producer and consumer read only 
unsigned int crcTable[CRC_SIZE]; 
int BUFF_SIZE=0;  //shared data memory size
sem_t producer, consumer; 
pthread_mutex_t mutex; //mutex identification

void *pro(void*); //the two threads 
void *con(void*);

unsigned int crc_computation(char*, int); 
//void crc_init(void);



void crc_init(void)
{
  int i,j; 
  unsigned int crc; 

  for(i=0; i<CRC_SIZE; i++)
  {
    crc=i;
    
    for(j=8;j>0;j--)
    {
      if((crc&1)==1)
      {
	crc=(crc>>1)^CRC_POLY;
      }
      else
      {
	crc=crc>>1;
      }
    }
    crcTable[i]=crc;
    printf("CRC:%d\n ",crcTable[i]); 
  }
             
} 

unsigned int crc_computation(char *buff, int nbytes){
  unsigned int crc; 
  unsigned int n1,n2;
  crc=0XFFFFFFFF; 
  
  while(nbytes!=0){
    n1=crc>>8; 
    n2=crcTable[(crc ^ *buff) & 0xff];
    crc=n1^n2;
    buff++;
    nbytes--;
  }
  return(crc);
}

void *pro(void *para)
{
  unsigned int i;
  int buff[BUFF_SIZE];   /* data portion, then checksum */
  for(i=0;i<nitems;i++)
  {
    sem_wait(&consumer);
    pthread_mutex_lock(&mutex); // lock;
    sched_yield(); //calling thread to relinquish the CPU
    buff[i%BUFF_SIZE]=i; /* store i into circular buffer */
    printf("Produced: buff[%d]=%d \n",i,buff[i%BUFF_SIZE]);
    pthread_mutex_unlock(&mutex); //unlock;
    sem_post(&producer);
  }
  if(i==(nitems/2))
    return(NULL);
}

void *con(void *para)
{
  int i;
  int buff[BUFF_SIZE];
  for(i=0;i<nitems;i++)
  {
    sem_wait(&producer); 
    pthread_mutex_lock(&mutex); // setlock();
    sched_yield(); //calling thread to relinquish the CPU
    if(i!=buff[i%BUFF_SIZE])
      printf("Consumed: buff[%d] = %d \n",i,buff[i%BUFF_SIZE]);
    else
    {  
      printf("buff[%d] = %d \n ", i, buff[i % BUFF_SIZE]);
      crc_init();
      printf("CRC Computation:%d\n",crc_computation(buff[i%BUFF_SIZE],i));    

    }
    
    pthread_mutex_unlock(&mutex); // setunlock();
    sem_post(&consumer);
  }
  return(NULL);
}

int main(int argc, char *argv[]){
  BUFF_SIZE=atoi(argv[1]);
  pthread_t id1,id2;
  //  pthread_attr_t attr;  
  if(argc!=3)
    /*incase an argument has passed thru comd line  */
    {
      printf("Usage:%s #stuff \n",argv[0]);
      exit(1);
    }
  if(pthread_mutex_init(&mutex,NULL)<0){

    perror("pthread_mutex_init");
    exit(1);
  }

  if(sem_init(&producer,0,1)<0){
    perror("sem_init");
    exit(1);
  }
  if(sem_init(&consumer,0,1)<0){
    perror("sem_init");
    exit(1);
  }
  nitems=atoi(argv[2]);
   
  if(nitems<0){
    perror("Must Enter an integer 0 or greater!");
    exit(1);
  }
  if(BUFF_SIZE>64000){
    perror("Memory size is 64K");
    exit(1);
  }
  if(pthread_create(&id2,NULL,&con,NULL)!=0){
    perror("pthread_create");
    exit(1);
  }
  if(pthread_create(&id1,NULL,&pro,NULL)!=0){
    perror("pthread_create");
    exit(1);
  }

  (void)pthread_join(id1,NULL);
  (void)pthread_join(id2,NULL);
  (void)sem_destroy(&producer);
  (void)pthread_mutex_destroy(&mutex);
  exit(0);
  return 0;  
 
}


