#include <stdio.h>

/* 
 * # merge src1 src2 ... dst
 *
 * 이 구현은, 합병은 되나, 분리가 불가능한 상태이다.
 *
 * 그래서, 파일을 병합할 때, 필수 파일의 정보를 같이 파일에 써야 함.
 */
int main(int argc, char *argv[])
{
	FILE *src, *dst;
	int ret;
	char buffer[1024];
	int i;
	
	if (argc < 4) {
		printf("Usage: merge <src1> <src2> ... <dest>\n");
		return -1;
	}

	dst = fopen(argv[argc-1], "w");

	for (i=0; i<argc-2; i++) {
		src = fopen(argv[i+1], "r");
		while (ret = fread(buffer, 1, sizeof buffer, src)) {
			fwrite(buffer, 1, ret, dst);		
		}

		fclose(src);
	}

	fclose(dst);
	return 0;
}
