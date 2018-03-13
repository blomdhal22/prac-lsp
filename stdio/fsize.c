// ./a.out aaa
// 6

/* 
 * file size 알아오는 방법
 * 
 * 1. read하고 read되는 바이트를 누적하여 계산
 * 2. inode 속의 파일 size 읽어오기(stat)
 * 3. fseek를 이용해서 offset을 파일 끝으로 옮기는 방식
 */
#include <stdio.h>

// fp 관리가 안된다.
// fp를 강제로 0으로 만들기 때문에.
/*
int get_fsize(FILE *fp)
{
	int fsize, fpos;

	fpos = fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	// 원복이 필요하다
	fseek(fp, fpos, SEEK_SET);
	return fsize;
}
*/

int get_fsize(FILE *fp)
{
	int fsize, fpos;
	fpos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, fpos, SEEK_SET);
	return fsize;
}

int main(int argc, char *argv[])
{
	FILE *fp;
	int fsize;
	char buff[1024];
	int ret;

	fp = fopen(argv[1], "r");
	fgets(buff, sizeof buff, fp);
	fputs(buff, stdout);

	fsize = get_fsize(fp);
	fgets(buff, sizeof buff, fp);
	fputs(buff, stdout);
	fclose(fp);

	printf("%s size=%d\n",  argv[1], fsize);
	return 0;
}
