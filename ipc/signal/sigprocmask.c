#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	sigset_t set;
	sigset_t oldset;

	sigemptyset(&set);	// clean up
	sigaddset(&set, SIGINT);
	// @how: SIG_BLOCK(add), SIG_UNBLOCK(cancel), SIG_SETMASK(overwrite) 
	sigprocmask(SIG_BLOCK, &set, &oldset);	// signal의 임계 영역 시작			
    sleep(3);		// 3초 동안에는 SIGINT 반응하지 않는다.
	sigprocmask(SIG_SETMASK, &oldset, 0);     // signal의 임계 영역 종료
	
	// signal 보류가 종료되고, 보류되었던 SIGINT가 발생하면서, 프로그램이 종료된다.
	while(1) ;
}
