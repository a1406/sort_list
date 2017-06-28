all: array sort_array list list2

clean:
	rm -f array sort_array list list2

CFLAGS=-g -O2 -Wno-unused-result

array: array.c comm.c
	gcc ${CFLAGS} -o array array.c comm.c

sort_array: sort_array.c sortarray.c comm.c
	gcc ${CFLAGS} -o sort_array sort_array.c sortarray.c comm.c

list: list.c comm.c
	gcc ${CFLAGS} -o list list.c comm.c

list2: list2.c comm.c
	gcc ${CFLAGS} -o list2 list2.c comm.c
