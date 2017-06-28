#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "comm.h"
#include "radix-tree.h"

//static uint64_t buf[MAX_TEST_NUM];
struct radix_data
{
	uint64_t index;
	uint64_t data;
};

static struct radix_data radix_data[MAX_TEST_NUM];

void find_entry(struct radix_tree_head *root, uint64_t entry)
{
	struct radix_data *data = radix_tree_lookup(root, entry);
	assert(data && data->data == entry);
//	printf("find entry %lu, index = %lu, data %lu\n", entry, data->index, data->data);
}

void delete_entry(struct radix_tree_head *root, uint64_t entry)
{
	struct radix_data *data = radix_tree_delete(root, entry);
	assert(data && data->data == entry);	
//	printf("delete entry %lu, index = %lu, data %lu\n", entry, data->index, data->data);	
}

void find(struct radix_tree_head *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(root, data[i]);
	}
}

void delete(struct radix_tree_head *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(root, data[i]);
	}
}

void insert(struct radix_tree_head *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
//		buf[i] = data[i];
		int ret = radix_tree_insert(root, data[i], &radix_data[i]);
		assert(ret == 0);
	}
}

int main(int argc, char *argv[])
{
	int num = atoi(argv[1]);
    uint64_t *data = read_test_num(num);
	assert(data);
	uint64_t *data_r = read_rand_num(num);
	assert(data_r);

//	radix_tree_init();
//	RADIX_TREE(root);

	struct radix_tree_head root;
	radix_tree_initial(&root);
	for (int i = 0; i < num; ++i)
	{
		radix_data[i].index = i;
		radix_data[i].data = data[i];
	}

	time_begin();
	insert(&root, data, num);
	find(&root, data_r, num);
	delete(&root, data_r, num);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}
