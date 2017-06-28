#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "comm.h"
#include "dict.h"

//static uint64_t buf[MAX_TEST_NUM];
struct dict_data
{
	uint64_t index;
	uint64_t data;
};

static struct dict_data dict_data[MAX_TEST_NUM];

void find_entry(dict *root, uint64_t entry)
{
//	struct radix_data *data = radix_tree_lookup(root, entry);
//	assert(data && data->data == entry);
//	printf("find entry %lu, index = %lu, data %lu\n", entry, data->index, data->data);
}

void delete_entry(dict *root, uint64_t entry)
{
//	struct radix_data *data = radix_tree_delete(root, entry);
//	assert(data && data->data == entry);	
//	printf("delete entry %lu, index = %lu, data %lu\n", entry, data->index, data->data);	
}

void find(dict *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(root, data[i]);
	}
}

void delete(dict *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(root, data[i]);
	}
}

void insert(dict *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
//		buf[i] = data[i];
//		int ret = radix_tree_insert(root, data[i], &radix_data[i]);
//		assert(ret == 0);
	}
}

static unsigned int my_hash_func(const void *key)
{
	return dictGenHashFunction(key, 8);	
}

static dictType my_dict_type = {
    my_hash_func,            /* hash function */
    NULL,                      /* key dup */
    NULL,                      /* val dup */
    NULL,      /* key compare */
    NULL, /* key destructor */
    NULL                       /* val destructor */
};


int main(int argc, char *argv[])
{
	int num = atoi(argv[1]);
    uint64_t *data = read_test_num(num);
	assert(data);
	uint64_t *data_r = read_rand_num(num);
	assert(data_r);

	dict *d = dictCreate(&my_dict_type,NULL);	

	for (int i = 0; i < num; ++i)
	{
		dict_data[i].index = i;
		dict_data[i].data = data[i];
	}

	time_begin();
	insert(d, data, num);
	find(d, data_r, num);
	delete(d, data_r, num);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}
