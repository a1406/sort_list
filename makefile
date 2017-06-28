all: array sort_array list list2

array: array.c comm.c
	gcc -g -o array array.c comm.c

sort_array: sort_array.c sortarray.c comm.c
	gcc -g -o sort_array sort_array.c sortarray.c comm.c

list: list.c comm.c
	gcc -g -o list list.c comm.c

list2: list2.c comm.c
	gcc -g -o list2 list2.c comm.c
