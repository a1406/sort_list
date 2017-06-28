#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "comm.h"

static uint64_t buf[MAX_TEST_NUM];

void find_entry(uint64_t entry, int num)
{
	for (int i = 0; i < num; ++i)
	{
		if (buf[i] == entry)
			return;
	}
	assert(0);
}

void delete_entry(uint64_t entry, int num)
{
	for (int i = 0; i < num; ++i)
	{
		if (buf[i] == entry)
		{
			buf[i] = buf[num - 1];
//			memmove(&buf[i], &buf[i+1], num - i - 1);
			return;
		}
	}
	assert(0);
}

void find(uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(data[i], num);
	}
}

void delete(uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(data[i], num);
	}
}

void insert(uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		buf[i] = data[i];
	}
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
