'''
ID: abacles1
LANG: PYTHON3
TASK: lamps
'''

def push_all(l):
    for i in range(len(l)):
        l[i] = not l[i]
def push_odd(l):
    for i in range(0,len(l),2):
        l[i] = not l[i]
def push_even(l):
    for i in range(1,len(l),2):
        l[i] = not l[i]
def push_tri(l):
    for i in range(0,len(l),3):
        l[i] = not l[i]

fin = open('lamps.in','r')
lcount = int(fin.readline().strip())
pcount = int(fin.readline().strip())
onlamps = [int(_) for _ in fin.readline().split()[:-1]]
offlamps = [int(_) for _ in fin.readline().split()[:-1]]
fin.close()

poss = set()

var = [True,False]

for a in var:
    for o in var:
        for e in var:
            for t in var:
                lamps = [True]*lcount
                if a:
                    push_all(lamps)
                if o:
                    push_odd(lamps)
                if e:
                    push_even(lamps)
                if t:
                    push_tri(lamps)
                pushed = int(a) + int(o) + int(e) + int(t)
                lamps = tuple(lamps)
                if not lamps in poss and pushed <= pcount and pushed%2 == pcount%2:
                    poss.add(lamps)

final = []
for p in poss:
    status = True
    for l in onlamps:
        if not p[l-1]:
            status = False
            break
    if not status:
        continue
    for l in offlamps:
        if p[l-1]:
            status = False
            break
    if not status:
        continue
    final.append([str(int(_)) for _ in p])

final.sort()
fout = open('lamps.out','w')
for config in final:
    fout.write(''.join(config) + '\n')
if len(final) == 0:
    fout.write('IMPOSSIBLE\n')
fout.close()
