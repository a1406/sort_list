#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "comm.h"

struct buf_entry
{
	struct buf_entry *next;
	uint64_t data;
};

static struct buf_entry *head;
static struct buf_entry *all_entry[MAX_TEST_NUM];

void find_entry(uint64_t entry)
{
	struct buf_entry *t = head;
	while (t)
	{
		if (t->data == entry)
			return;
		t = t->next;
	}
	assert(0);
}

void delete_entry(uint64_t entry)
{
	struct buf_entry *pre = NULL;
	struct buf_entry *t = head;
	while (t)
	{
		if (t->data == entry)
		{
			if (pre)
			{
				pre->next = t->next;
			}
			else
			{
				head = t->next;
			}
			return;
		}
		pre = t;
		t = t->next;		
	}
	assert(0);
}

void find(uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		find_entry(data[i]);
	}
}

void delete(uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		delete_entry(data[i]);
	}
}

void insert(uint64_t *data, int num)
{
	for (int i = 0; i < num; ++i)
	{
		all_entry[i]->data = data[i];
		all_entry[i]->next = head;
		head = all_entry[i];
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
		malloc(100);
		all_entry[i] = (struct buf_entry *)malloc(sizeof(struct buf_entry));
		malloc(500);		
	}

	time_begin();
	insert(data, num);
	find(data_r, num);
	delete(data_r, num);
	int diff = time_diff();
	printf("[%d] ", diff);
    return 0;
}

