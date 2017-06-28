#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "comm.h"
#include "sortarray.h"

static uint64_t buf[MAX_TEST_NUM];

void insert(uint64_t *data, int num)
{
	int n = 0;
	for (int i = 0; i < num; ++i)
	{
		int ret = array_insert(&data[i], &buf[0], &n, sizeof(uint64_t), 1, comp_uint64);
		assert(ret >= 0);
	}
}
void delete(uint64_t *data, int num)
{
}
void find(uint64_t *data, int num)
{
}

int main(int argc, char *argv[])
{
	int num = atoi(argv[1]);
    uint64_t *data = read_test_num(num);
	assert(data);
	uint64_t *data_r = read_rand_num(num);
	assert(data_r);

	time_begin();
	insert(data, num);
	find(data_r, num);
	delete(data_r, num);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}
