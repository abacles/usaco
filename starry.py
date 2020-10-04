'''
ID: abacles1
LANG: PYTHON3
TASK: starry
'''

def explore(i, j):
    skymap[i][j] = '2'
    xcluster.append(j), ycluster.append(i)
    for dx in [-1, 0, 1]:
        for dy in [-1, 0, 1]:
            if (0 <= i+dy < height and 0 <= j+dx < width
                and skymap[i+dy][j+dx] == '1'):
                explore(i+dy, j+dx)

def mark(i, j):
    global nextlabel
    xcluster.clear(), ycluster.clear()
    explore(i, j)
    xmin, xmax = min(xcluster), max(xcluster)
    ymin, ymax = min(ycluster), max(ycluster)
    cluster = []
    for i in range(ymin, ymax+1):
        for j in range(xmin, xmax+1):
            cluster.append(skymap[i][j] == '2')
    label = constellations.get((max(xmax-xmin+1, ymax-ymin+1),) + tuple(cluster), None)
    if not label:
        label = nextlabel
        nextlabel = chr(ord(nextlabel) + 1)
        for x in [range(xmax-xmin+1), range(xmax-xmin, -1, -1)]:
            for y in [range(ymax-ymin+1), range(ymax-ymin, -1, -1)]:
                orientation = []
                for i in y:
                    for j in x:
                        orientation.append(skymap[ymin+i][xmin+j] == '2')
                constellations[(max(xmax-xmin+1, ymax-ymin+1),) + tuple(orientation)] = label
                orientation = []
                for j in x:
                    for i in y:
                        orientation.append(skymap[ymin+i][xmin+j] == '2')
                constellations[(max(xmax-xmin+1, ymax-ymin+1),) + tuple(orientation)] = label
    for i in range(len(xcluster)):
        skymap[ycluster[i]][xcluster[i]] = label

skymap = []
with open('starry.in') as fin:
    width, height = int(fin.readline()), int(fin.readline())
    for i in range(height):
        skymap.append(list(fin.readline().strip()))


constellations = {}
xcluster, ycluster = [], []
nextlabel = 'a'

for i in range(height):
    for j in range(width):
        if skymap[i][j] == '1':
            mark(i, j)

with open('starry.out', 'w') as fout:
    for i in range(height):
        fout.write(''.join(skymap[i]) + '\n')
