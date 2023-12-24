/* a simple producer/consumer using semaphores and threads

   usage on Solaris:
     gcc thisfile.c -lpthread -lposix4
     a.out numIters

*/
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#define SHARED 1


void *Producer(void *);  /* the two threads */
void *Consumer(void *);

sem_t empty, full;    /* the global semaphores */
int data;             /* shared buffer         */
int numIters;

/* main() -- read command line and create threads, then
             print result when the threads have quit */

int main(int argc, char *argv[]) {
  /* thread ids and attributes */
  pthread_t pid, cid;  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

  numIters = atoi(argv[1]);
  sem_init(&empty, SHARED, 1);  /* sem empty = 1 */
  sem_init(&full, SHARED, 0);   /* sem full = 0  */

  printf("main started\n");
  pthread_create(&pid, &attr, Producer, NULL);
  pthread_create(&cid, &attr, Consumer, NULL);
  pthread_join(pid, NULL);
  pthread_join(cid, NULL);
  printf("main done\n");
}

/* deposit 1, ..., numIters into the data buffer */
void *Producer(void *arg) {
  int produced;
//   printf("Producer created\n");
  for (produced = 0; produced < numIters; produced++) {
    sem_wait(&empty);
    data = produced;
    printf("\033[0;36m\t\tdata = %d\033[1;37m\n",data);
    sem_post(&full);
  }
}
// 
/* fetch numIters items from the buffer and sum them */
void *Consumer(void *arg) {
  int total = 0, consumed;
  printf("Consumer created\n");
  for (consumed = 0; consumed < numIters; consumed++) {
    sem_wait(&full);
    total = total+data;
    printf("\033[0;32mtotal = %d\n\033[0m", total);
    sem_post(&empty);
  }
//   printf("\033[0;36m");
  printf("for %d iterations, the total is %d\n", numIters, total);
//   printf("\033[1;37m>");
}