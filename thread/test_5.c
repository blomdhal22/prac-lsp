#include <pthread.h>
#include <stdio.h>

#define MAX_THREAD 4
/*
 * 자체 구현 spin_lock
 */
typedef int int32_t;
int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
	int32_t prev;
	__asm__ __volatile__ ("lock; cmpxchgl %1, %2"
			: "=a" (prev)
			: "q" (new_value), "m" (*ptr), "0" (old_value)
			: "memory");
	return prev != old_value;
}


void spin_lock(int *mutex)
{
	while(__bionic_cmpxchg(0, 1, mutex));
}

void spin_unlock(int *mutex)
{
	while(__bionic_cmpxchg(1, 0, mutex));
}

int sum = 0;
int mutex = 0;
void *thread_routine(void *arg)
{
	int i;
	/*
	 * mov    0x200947(%rip),%eax        # 601054 <sum>
	 * add    $0x1,%eax
	 * mov    %eax,0x20093e(%rip)        # 601054 <sum>
	 */

	for (i=0; i<100000000/MAX_THREAD; i++) {
		spin_lock(&mutex);
		sum++;
		spin_unlock(&mutex);
	}

	return arg;
}

int main(void)
{
	pthread_t thread_id[MAX_THREAD];
	void *thread_result;
	int status, i;

	for(i=0; i<MAX_THREAD; i++)
		status = pthread_create(&thread_id[i], 0, thread_routine, 0);

	for(i=0; i<MAX_THREAD; i++)
		status = pthread_join(thread_id[i], &thread_result);

	printf("sum=%d\n", sum);

	return 0;
}
