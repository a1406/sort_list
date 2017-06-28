#ifndef COMM_H
#define COMM_H

#include <stdint.h>

#define MAX_TEST_NUM (100000)

uint64_t *read_test_num(int num);
uint64_t *read_rand_num(int num);

void time_begin();
int time_diff();

#endif /* COMM_H */
