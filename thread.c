#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *message_printer(void *ptr)
{

    char	*msg;

    msg = (char *) ptr;
    printf("%s::%x: %s \n", __FUNCTION__, pthread_self(), msg);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{

    char *msg = NULL;
    pthread_t   tid[5];
    int i;

    /* Get the comand line parameters */
    if (argc != 2 ) {
       printf("Usage: %s <msg> \n", argv[0]);
       exit( -1);
    }

    msg = argv[1];

    /* Create each thread */
    for (i = 0; i < 5; i++)
    {
	printf("Creating thread %d ... \n", i);
	pthread_create(&tid[i], NULL, &message_printer,
			(void *)msg);
    }

    /* Wait for each thread to complete */
    for (i = 0; i < 5; i++)
    {
	pthread_join(tid[i], NULL);
	printf("Completed join with thread %d \n", i);
    }

    exit(0);

}

