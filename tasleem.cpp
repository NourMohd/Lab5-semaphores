#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <random>
#include <signal.h>
#include "myQueue.hpp" 

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define NORMAL "\033[1;37m"

#define SHARED 1
#define N 5
#define CHECKING_MSG 5
#define BUFFER_SIZE 4
void *producer(void *); 
void *consumer(void *);

sem_t empty,full,mutex1,mutex2;
int data=0;             
myQueue q= myQueue(BUFFER_SIZE);

std::random_device rd;
std::mt19937 gen(rd()); // Mersenne Twister PRNG

void *monitor(void*){

while (1)
{
    sleep(CHECKING_MSG);
	int temp;
    // sem_wait(&full);
	printf("%sMonitor thread: waiting to read counter\n",GREEN);
    sem_wait(&mutex1);
	temp = data;
	printf("%sMonitor thread: reading a count value of %d\n",GREEN,data);
    // printf("\t\t %smessage received = %d\033[1;37m\n%s",GREEN,data,NORMAL);
    data = 0;
    sem_post(&mutex1);
    //   sem_post(&empty);

	producer(&temp);
        
  
}

  
}

void *counter(void* prm){
    int* id = (int*)prm;
    // srand(time(0));
    // int x = rand()%10+1;
    
    // Define the distribution
    std::uniform_int_distribution<> distribution(1, 10); // Random numbers between 1 and 100

    while(1){
        
    int x = distribution(gen);

    // printf("%srandom = %d in mcounter %d%s\n",CYAN,x,*id,NORMAL);
    
    sleep(x);
	// Counter thread %I%: received a message
    printf("%sCounter thread %d: received a message%s\n",CYAN,*id,NORMAL);
	printf("%sCounter thread %d: waiting to write%s\n",CYAN,*id,NORMAL);
    sem_wait(&mutex1);
    data++;
    printf("%sCounter thread %d: now adding to counter, counter value=%d%s\n",CYAN,*id,data,NORMAL);
    sem_post(&mutex1);
    // sem_post(&full);
    }

}

void ctrlC_handler(int signal){
	printf("you pressed ctrl+c\n");
	printf("terminating program\n");
	exit(signal);
}

int main(int argc, char *argv[]) {
  	
	printf("main started\n");
    
	pthread_t mCounter[N], mMonitor,mCollector; 

    sem_init(&empty, SHARED, BUFFER_SIZE);
    sem_init(&full, SHARED, 0);   
    sem_init(&mutex1,SHARED,1);
    sem_init(&mutex2,SHARED,1);
    
	int temp[N];
    
	for (int i = 0; i < N; i++){
		temp[i]=i;
		pthread_create(&mCounter[i],NULL,counter,(void*)&temp[i]);
    }

	pthread_create(&mMonitor,NULL,monitor,NULL);
	pthread_create(&mCollector,NULL,consumer,NULL);

    

    for (int i = 0; i < N; i++){
    	pthread_join(mCounter[i],NULL);
    }

    pthread_join(mMonitor,NULL);
    pthread_join(mCollector,NULL);
  
}

void *producer(void *arg) {
	int *n_of_msg = (int*)arg;

	if(empty.__align == 0) // full
		printf("%sMonitor thread: Buffer full!!\n",GREEN);
	
	sem_wait(&empty); 
	sem_wait(&mutex2); 
	
	printf("%sMonitor thread: writing to buffer at position %d\n",GREEN,q.getTail());
    q.enqueue(*n_of_msg); 
						  
	sem_post(&mutex2); 
    sem_post(&full); 

}

void *consumer(void *arg) {

	while (1)
	{
		if(full.__align==0) //empty
			printf("%sCollector thread: nothing is in the buffer!\n",RED);
		
		sem_wait(&full);
		sem_wait(&mutex2);

		printf("%sCollector thread: reading from the buffer at position %d\n",RED,q.getHead());
		q.dequeue();
		
		sem_post(&empty);
		sem_post(&mutex2);
		
		std::uniform_int_distribution<> distribution(8, 12); // Random numbers between 8 and 12
		int x = distribution(gen);
		sleep(x);
	}
	
    
}