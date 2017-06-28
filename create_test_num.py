import random
import sys
import string

#print len(sys.argv)
#print sys.argv

nums = set()
maxnum = 200000000000

n = string.atoi(sys.argv[1])
for i in range(n):
    n = random.randint(1,maxnum)
    while n in nums:
        n = random.randint(1,maxnum)
    nums.add(n)
    print n

