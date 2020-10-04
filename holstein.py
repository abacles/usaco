'''
ID: abacles1
LANG: PYTHON3
TASK: holstein
'''

import itertools

def enough(req,have):
    for v in range(len(req)):
        if have[v] < req[v]:
            return False
    return True

fin = open('holstein.in','r')
vtypes = int(fin.readline())
vreq = [int(x) for x in fin.readline().split()]
scptypes = int(fin.readline())
scoops = []
for i in range(scptypes):
    scoops.append([int(x) for x in fin.readline().split()])
fin.close()

success = False
feedcount = scptypes
feed = list(range(scptypes))
for count in range(1,scptypes):
    allcomb = list(itertools.combinations(range(scptypes),count))
    for combination in allcomb:
        ftotal = [sum([scoops[scp][i] for scp in combination]) for i in range(vtypes)]
        if enough(vreq,ftotal):
            success = True
            feed = combination[:]
            feedcount = count
            break
    if success:
        break

fout = open('holstein.out','w')
fout.write(str(feedcount))
for i in feed:
    fout.write(' '+str(i+1))
fout.write('\n')
