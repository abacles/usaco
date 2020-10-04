'''
ID: abacles1
LANG: PYTHON3
TASK: prefix
'''

from collections import deque

fin = open('prefix.in','r')
l = fin.readline().strip()
patt = []
plen = [False]*11
while l != '.':
    rin = l.split()
    for p in rin:
        patt.append(p)
        plen[len(p)] = True
    l = fin.readline().strip()
l = fin.readline().strip()
seq = ''
while l != '':
    seq += l
    l = fin.readline().strip()
fin.close()

h = []
patt.sort()
for p in patt:
    
slen = len(seq)
reachable = [False]*(slen+1)

q = deque([0])
reachable[0] = True
best = 0
while len(q) > 0:
    s = q.pop()
    for l in range(10,0,-1):
        if plen[l]:
            if s+l <= slen and seq[s:s+l] in patt and not reachable[s+l]:
                reachable[s+l] = True
                if s+l > best:
                    q.append(s+l)
                    best = s+l
                else:
                    q.appendleft(s+l)
                if s+l == slen:
                    q = []
                    break
            
fout = open('prefix.out','w')
fout.write(str(best) + '\n')
print(best)
fout.close()
