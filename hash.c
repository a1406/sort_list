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
	dictEntry *ret = dictFind(root, &entry);
	assert(ret != 0);
	assert(*(uint64_t *)(ret->key) == entry);
	assert(((struct dict_data *)(ret->val))->data == entry);
//	struct radix_data *data = radix_tree_lookup(root, entry);
//	assert(data && data->data == entry);
//	printf("find entry %lu, index = %lu, data %lu\n", entry, data->index, data->data);
}

void delete_entry(dict *root, uint64_t entry)
{
	int ret = dictDelete(root, &entry);
	assert(ret == DICT_OK);
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
		int ret = dictAdd(root, &data[i], &dict_data[i]);
		assert(ret == DICT_OK);
//		buf[i] = data[i];
//		int ret = radix_tree_insert(root, data[i], &radix_data[i]);
//		assert(ret == 0);
	}
}

#define GOLDEN_RATIO_64 0x61C8864680B583EBull
static unsigned int my_hash_func(const void *key)
{
	return (*(uint64_t *)key) * GOLDEN_RATIO_64 >> (4);
	
    uint64_t hash = *(uint64_t *)key;

    /*  Sigh, gcc can't optimise this alone like it does for 32 bits. */
    uint64_t n = hash;
    n <<= 18;
    hash -= n;
    n <<= 33;
    hash -= n;
    n <<= 3;
    hash += n;
    n <<= 3;
    hash -= n;
    n <<= 4;
    hash += n;
    n <<= 2;
    hash += n;

    /* High bits are more random, so use them. */
    return hash >> 8;
}
	
//	return dictGenHashFunction(key, 8);	
//}

static int my_hash_compare(void *privdata, const void *key1, const void *key2)
{
	if (*(uint64_t *)key1 == *(uint64_t *)key2)
		return (1);
	return (0);
	/* else if (*(uint64_t *)key1 > *(uint64_t *)key2) */
	/* 	return 1; */
	/* else */
	/* 	return -1; */
}

static dictType my_dict_type = {
    my_hash_func,            /* hash function */
    NULL,                      /* key dup */
    NULL,                      /* val dup */
    my_hash_compare,      /* key compare */
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
