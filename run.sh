#!/bin/bash
test_num=$1
python create_test_num.py $test_num > test.txt
sort -R test.txt > test_r.txt

for (( i=0; i<10; i++))
{
    ./array $test_num
}
echo ""
for (( i=0; i<10; i++))
{
    ./sort_array $test_num
}
echo ""
#./list $test_num

