#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

pthread_t tid[2];
pthread_mutex_t mutex1;

int counter = 5;

void *producer(void *arg)
{
  int i, register1;


  pthread_mutex_lock(&mutex1);

  /* Begin the critical section */
  register1 = counter;
  register1 = register1 + 1;

  /* use loop to simulate some processing */
  for (i = 0; i< (0xFFFFF); i++);

  /* enforce a thread switch to illustrate "interleaving" */
  sched_yield();

  counter = register1;
  /* end the critical section */

  pthread_mutex_unlock(&mutex1);

  printf("%s:Counter = %d \n", __FUNCTION__, counter);

  return NULL;
}

void *consumer(void *arg)
{

  int i,register2;

  pthread_mutex_lock(&mutex1);

  /* Begin the critical section */
  register2 = counter;
  register2 = register2 - 1;

  /* use loop to simulate processing */
  for (i = 0; i< (0xFFFFF); i++);

  counter = register2;
  /* End the critical section */

  pthread_mutex_unlock(&mutex1);

  printf("%s:Counter = %d \n", __FUNCTION__, counter);

  return NULL;
}


int main(void)
{
  int i = 0;
  int err;

  /* Create the mutex semaphore to protect the critical section */
  if (pthread_mutex_init(&mutex1, NULL) != 0) {
    printf("\n error creating mutex\n");
    return -1;
  }

  err = pthread_create(&(tid[0]), NULL, &producer, NULL);
  if (err != 0) {
    printf("\ncan't create thread 1 :[%s]", strerror(err));
  }

  err = pthread_create(&(tid[1]), NULL, &consumer, NULL);
  if (err != 0) {
    printf("\ncan't create thread 2 :[%s]", strerror(err));
  }

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  printf("Final Counter = %d \n", counter);

  pthread_mutex_destroy(&mutex1);


  return 0;

}
