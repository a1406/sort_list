all: array sort_array list list2 radix rb hash pool

clean:
	rm -f array sort_array list list2 radix rb hash pool

CFLAGS=-g -O2 -Wno-unused-result

array: array.c comm.c
	gcc ${CFLAGS} -o array array.c comm.c

sort_array: sort_array.c sortarray.c comm.c
	gcc ${CFLAGS} -o sort_array sort_array.c sortarray.c comm.c

list: list.c comm.c
	gcc ${CFLAGS} -o list list.c comm.c

list2: list2.c comm.c
	gcc ${CFLAGS} -o list2 list2.c comm.c

radix: radix.c comm.c radix-tree.c
	gcc ${CFLAGS} -o radix radix.c comm.c radix-tree.c

rb: rb.c comm.c rbtree.c
	gcc ${CFLAGS} -o rb rb.c comm.c rbtree.c

hash: hash.c comm.c dict.c
	gcc ${CFLAGS} -o hash hash.c comm.c dict.c

pool: pool.c comm.c mem_pool.c
	gcc ${CFLAGS} -o pool pool.c comm.c mem_pool.c

