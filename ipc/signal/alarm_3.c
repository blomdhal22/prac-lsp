#include <unistd.h>
#include <stdio.h>
#include <signal.h>


// handler에서 또 다시 alarm을 등록하면 알람이 다시 발생한다.
void my_sig(int signo)
{
	printf("my_sig(%d)\n", signo);
	alarm(1);
}

int main()
{
	unsigned int ret;
	signal (SIGALRM, my_sig);
	alarm(10);
	sleep(3);
	// alarm의 리턴값은 이전 알람의 남은 시간 임으로,
	// 7초가 나오지 않을까?
	ret = alarm(0);		// 0이면, 알람을 취소한 것임으로 핸들러 호출X
	printf("ret=%u\n", ret);
	while(1) ;
	return 0;
}
