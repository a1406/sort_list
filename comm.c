#include "comm.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>

static uint64_t *read_file_num(int num, char *file_name)
{
	FILE *fp = fopen(file_name, "r");
	assert(fp);
	uint64_t *ret = (uint64_t *)malloc(sizeof(uint64_t) * num);
	assert(ret);
	char buf[256];
	for (int i = 0; i < num; ++i)
	{
		fgets(buf, 256, fp);
		ret[i] = strtoul(buf, NULL, 10);
//		printf("read buf = %lu\n", ret[i]);
	}

	fclose(fp);
	
	return ret;
}

uint64_t *read_rand_num(int num)
{
	return read_file_num(num, "./test_r.txt");
}

uint64_t *read_test_num(int num)
{
	return read_file_num(num, "./test.txt");
}

static struct timeval tv_start;
void time_begin()
{
	int ret = gettimeofday(&tv_start, NULL);
	assert(ret == 0);
}
int time_diff()
{
	struct timeval tv_end;
	int ret = gettimeofday(&tv_end, NULL);
	assert(ret == 0);
	return (tv_end.tv_sec - tv_start.tv_sec) * 1000000 + tv_end.tv_usec - tv_start.tv_usec;
}
