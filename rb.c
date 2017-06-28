#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rbtree.h"
#include "comm.h"

//static uint64_t buf[MAX_TEST_NUM];

struct test_node
{
	uint64_t index;
	uint64_t key;
	struct rb_node rb;	
};
static struct test_node test_node[MAX_TEST_NUM];

static void rb_insert__(struct test_node *node, struct rb_root *root)
{
	struct rb_node **new = &root->rb_node, *parent = NULL;
	uint64_t key = node->key;

	while (*new) {
		parent = *new;
		if (key < rb_entry(parent, struct test_node, rb)->key)
			new = &parent->rb_left;
		else
			new = &parent->rb_right;
	}

	rb_link_node(&node->rb, parent, new);
	rb_insert_color(&node->rb, root);
}
static inline void rb_erase__(struct test_node *node, struct rb_root *root)
{
	rb_erase(&node->rb, root);
}

static inline struct test_node *rb_find__(uint64_t key, struct rb_root *root)
{
	struct rb_node **new = &root->rb_node, *parent = NULL;	
	while (*new) {	
		parent = *new;
		struct test_node *entry = rb_entry(parent, struct test_node, rb);
		uint64_t entry_key = entry->key;
		if (key == entry_key)
			return entry;
		if (key < entry->key)
			new = &parent->rb_left;
		else
			new = &parent->rb_right;
	}
	return NULL;
}

void find_entry(uint64_t entry, struct rb_root *root)
{
	struct test_node *data = rb_find__(entry, root);
	assert(data && data->key == entry);
}

void delete_entry(uint64_t entry, struct rb_root *root)
{
	struct test_node *data = rb_find__(entry, root);
	rb_erase__(data, root);
}

void find(uint64_t *data, int num, struct rb_root *root)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(data[i], root);
	}
}

void delete(uint64_t *data, int num, struct rb_root *root)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(data[i], root);
	}
}

void insert(uint64_t *data, int num, struct rb_root *root)
{
	for (int i = 0; i < num; ++i)
	{
		rb_insert__(&test_node[i], root);
	}
}

int main(int argc, char *argv[])
{
	int num = atoi(argv[1]);
    uint64_t *data = read_test_num(num);
	assert(data);
	uint64_t *data_r = read_rand_num(num);
	assert(data_r);

	struct rb_root root = RB_ROOT;
	for (int i = 0; i < num; ++i)
	{
		test_node[i].index = i;
		test_node[i].key = data[i];
	}

	time_begin();
	insert(data, num, &root);
	find(data_r, num, &root);
	delete(data_r, num, &root);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}
