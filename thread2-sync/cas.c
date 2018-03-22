#include <stdio.h>

typedef int int32_t;
int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
	int32_t prev;
	__asm__ __volatile__ ("lock; cmpxchgl %1, %2"
			: "=a" (prev)
			: "q" (new_value), "m" (*ptr), "0" (old_value)
			: "memory");
	return prev != old_value;
}


int mutex = 0;

void spin_lock(int *mutex)
{
	while(__bionic_cmpxchg(0, 1, mutex));
}

void spin_unlock(int *mutex)
{
	while(__bionic_cmpxchg(1, 0, mutex));
}

int main(void)
{

	int ret;
	spin_lock(&mutex);
	printf("Enter critical secion 1.\n");
	//spin_unlock(&mutex);

	spin_lock(&mutex);
	printf("Enter critical secion 2.\n");
	spin_unlock(&mutex);

	return 0;
}
