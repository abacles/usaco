'''
ID: abacles1
LANG: PYTHON3
TASK: msquare
'''

from collections import deque

def A(cstate):
    nstate = [' '] * 8
    for i in range(8):
        nstate[i] = cstate[7-i]
    return ''.join(nstate)
def B(cstate):
    nstate = [' '] * 8
    for i in range(4):
        nstate[(i+1)%4] = cstate[i]
        nstate[(i+3)%4+4] = cstate[i+4]
    return ''.join(nstate)
def C(cstate):
    transf = [0,2,5,3,4,6,1,7]
    nstate = [' '] * 8
    for i in range(8):
        nstate[transf[i]] = cstate[i]
    return ''.join(nstate)
transformations = [A,B,C]

def bfs(find):
    curr = '12345678'
    q = deque([curr])
    prev = {curr:'0'}
    if curr == find:
        return prev
    while len(q) > 0:
        curr = q.pop()
        for i in range(3):
            nxt = transformations[i](curr)
            if not nxt in prev:
                q.appendleft(nxt)
                prev[nxt] = chr(ord('A') + i)
                if nxt == find:
                    return prev
    return None

fin = open('msquare.in','r')
goal = fin.readline().strip().replace(' ','')
fin.close()

prevlist = bfs(goal)
path = []
while prevlist[goal] != '0':
    path.append(prevlist[goal])
    for i in range(3):
        goal = transformations[ord(path[-1])-ord('A')](goal)
path = list(reversed(path))
fout = open('msquare.out','w')
fout.write(str(len(path)) + '\n')
for i in range(len(path)):
    fout.write(path[i])
    if i % 60 == 59:
        fout.write('\n')
fout.write('\n')
fout.close()

