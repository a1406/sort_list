#!/bin/bash
test_num=$1
python create_test_num.py $test_num > test.txt
sort -R test.txt > test_r.txt

echo "不排序数组"
for (( i=0; i<10; i++))
{
    ./array $test_num
}
echo "排序数组"
for (( i=0; i<10; i++))
{
    ./sort_array $test_num
}
echo "链表1"
for (( i=0; i<10; i++))
{
    ./list $test_num
}
echo "链表2"
for (( i=0; i<10; i++))
{
    ./list2 $test_num
}
echo ""

