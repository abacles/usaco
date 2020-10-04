'''
ID: abacles1
LANG: PYTHON3
TASK: humble
'''

import heapq

fin = open('humble.in','r')
pcount,n = [int(_) for _ in fin.readline().split()]
primes = [int(_) for _ in fin.readline().split()]
fin.close()

primes.sort()
humble = []
hsize = 0
prev = []
found = set()

for i in range(pcount):
    heapq.heappush(humble,-primes[i])
    prev.append(primes[i])
    found.add(primes[i])
    hsize += 1

while True:
    if hsize == n and -humble[0] <= prev[0]*primes[0]:
        break
    curr = []
    for p in prev:
        if hsize == n and -humble[0] <= p*primes[0]:
            break
        for m in primes:
            if hsize == n and -humble[0] <= p*m:
                break
            if not p*m in found:
                curr.append(p*m)
                found.add(p*m)
                if hsize < n:
                    heapq.heappush(humble,-p*m)
                    hsize += 1
                else:
                    heapq.heapreplace(humble,-p*m)
    prev = sorted(curr)

fout = open('humble.out','w')
fout.write(str(-humble[0]) + '\n')
fout.close()
