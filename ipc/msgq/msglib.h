#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>

typedef struct msg_q
{
	long to_mtype;
	long fm_mtype;
	char mtext[100];
} MSG_t;

int CreateMQ(long key);
int OpenMQ(long key);
long SendMQ(int qid, long mtype, MSG_t msg);
long RecvMQ(int qid, long mtype, MSG_t *msg);
int GetFreeSizeMQ(int qid, long *freesize);
int RemoveMQ(int qid);
