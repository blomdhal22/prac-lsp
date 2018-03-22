#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int flag;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int sum = 0;
void * producer(void *data)
{
	pthread_mutex_lock(&mutex);
	sleep(3);
	printf("finish decoding\n");
	flag = 10;
	// 하나의 thread만 깨울 때
	//pthread_cond_signal(&cond);
	// 모든 thread 깨울 때,
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	return 0;
}

void * consumer(void *data)
{
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond, &mutex);
	printf("start video play, flag=%d\n", flag);
	pthread_mutex_unlock(&mutex);

	return 0;
}

int main(void)
{
	pthread_t thread[3];
	pthread_create(&thread[0], 0, producer, 0);
	pthread_create(&thread[1], 0, consumer, 0);
	pthread_create(&thread[2], 0, consumer, 0);
	pthread_join(thread[0], 0);
	pthread_join(thread[1], 0);
	pthread_join(thread[2], 0);

	return 0;
}
