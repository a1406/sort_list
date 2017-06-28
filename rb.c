#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rbtree.h"
#include "comm.h"

static uint64_t buf[MAX_TEST_NUM];

struct test_node
{
	uint64_t index;
	uint64_t key;
	struct rb_node rb;	
};

static struct rb_root root = RB_ROOT;

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
