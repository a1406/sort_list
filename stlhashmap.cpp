#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "comm.h"
#include <hash_map>

using namespace std;
using namespace __gnu_cxx;
//using namespace stdext;

//static uint64_t buf[MAX_TEST_NUM];
struct dict_data
{
	uint64_t index;
	uint64_t data;
};

static struct dict_data dict_data[MAX_TEST_NUM];

void find_entry(hash_map<uint64_t, struct dict_data *> *root, uint64_t entry)
{
	hash_map<uint64_t, struct dict_data *>::iterator ite = root->find(entry);
	assert(ite != root->end());
	assert((ite)->second->data == entry);
}

void delete_entry(hash_map<uint64_t, struct dict_data *> *root, uint64_t entry)
{
	root->erase(entry);
}

void find(hash_map<uint64_t, struct dict_data *> *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(root, data[i]);
	}
}

void delete_(hash_map<uint64_t, struct dict_data *> *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(root, data[i]);
	}
}

void insert(hash_map<uint64_t, struct dict_data *> *root, uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		(*root)[data[i]] = &dict_data[i];
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

	for (int i = 0; i < num; ++i)
	{
		dict_data[i].index = i;
		dict_data[i].data = data[i];
	}
	hash_map<uint64_t, struct dict_data *> root;

	time_begin();
	insert(&root, data, num);
	find(&root, data_r, num);
	delete_(&root, data_r, num);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}
