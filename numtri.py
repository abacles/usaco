'''
ID: abacles1
LANG: PYTHON3
TASK: numtri
'''

fin = open('numtri.in','r')
tri = []
rowcount = int(fin.readline())
for i in range(rowcount):
    tri.append([int(x) for x in fin.readline().split()])
fin.close()

tridist = list(tri)
for r in range(1,rowcount):
    for c in range(len(tri[r])):
        prev = []
        if c > 0:
            prev.append(tridist[r-1][c-1])
        if c < len(tri[r-1]):
            prev.append(tridist[r-1][c])
        tridist[r][c] = max(prev) + tri[r][c]

print(max(tridist[-1]))
fout = open('numtri.out','w')
fout.write(str(max(tridist[-1])) + '\n')
fout.close()
