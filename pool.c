#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "comm.h"
#include "mem_pool.h"

//static uint64_t buf[MAX_TEST_NUM];
struct dict_data
{
	uint64_t index;
	uint64_t data;
};

void find_entry(struct mass_pool *root, uint64_t entry)
{

}

void delete_entry(struct mass_pool *root, uint64_t entry)
{
}

void find(struct mass_pool *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(root, data[i]);
	}
}

void delete(struct mass_pool *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(root, data[i]);
	}
}

void insert(struct mass_pool *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
//		buf[i] = data[i];
	}
}

int main(int argc, char *argv[])
{
	int num = atoi(argv[1]);
    uint64_t *data = read_test_num(num);
	assert(data);
	uint64_t *data_r = read_rand_num(num);
	assert(data_r);

	struct mass_pool root;
	init_mass_pool(0, sizeof(struct dict_data), num, 0, &root);

	time_begin();
	insert(&root, data, num);
	find(&root, data_r, num);
	delete(&root, data_r, num);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}
