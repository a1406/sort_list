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

void find_entry(struct radix_tree_root *root, uint64_t entry)
{
	/* for (int i = 0; i < num; ++i) */
	/* { */
	/* 	if (buf[i] == entry) */
	/* 		return; */
	/* } */
	struct radix_data *data = radix_tree_lookup(root, entry);
	printf("entry %lu, index = %lu, data %lu\n", entry, data->index, data->data);
//	assert(0);
}

void delete_entry(struct radix_tree_root *root, uint64_t entry)
{
/* 	for (int i = 0; i < num; ++i) */
/* 	{ */
/* 		if (buf[i] == entry) */
/* 		{ */
/* 			buf[i] = buf[num - 1]; */
/* //			memmove(&buf[i], &buf[i+1], num - i - 1); */
/* 			return; */
/* 		} */
/* 	} */
//	assert(0);
}

void find(struct radix_tree_root *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(root, data[i]);
	}
}

void delete(struct radix_tree_root *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(root, data[i]);
	}
}

void insert(struct radix_tree_root *root, uint64_t *data, int num)
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

	radix_tree_init();
	RADIX_TREE(root);

	for (int i = 0; i < num; ++i)
	{
		radix_data[i].index = i;
		radix_data[i].data = data[i];
	}

//	uint64_t n = 100;
	radix_tree_insert(&root, 1, 0x300);
	void *t = radix_tree_lookup(&root, 1);	
	radix_tree_insert(&root, 1, 0x100);
	t = radix_tree_lookup(&root, 1);	
	radix_tree_insert(&root, 1, 0x200);
	t = radix_tree_lookup(&root, 1);		

	time_begin();
	insert(&root, data, num);
	find(&root, data_r, num);
	delete(&root, data_r, num);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}
