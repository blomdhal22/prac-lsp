#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp;
	int ret;
	char buffer[1024];

	fp = fopen(argv[1], "r");

	while(ret = fread(buffer, 1, sizeof buffer, fp)) {
		fwrite(buffer, 1, ret, stdout);
	}

	fclose(fp);

	return 0;
}
