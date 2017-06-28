import random
import sys
import string

#print len(sys.argv)
#print sys.argv
n = string.atoi(sys.argv[1])
for i in range(n):
    print random.randint(1,9999999999)
