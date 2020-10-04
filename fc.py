'''
ID: abacles1
LANG: PYTHON3
TASK: fc
'''

import math

def convex(p1, p2, p3):
    v1, v2 = (p2[0]-p1[0], p2[1]-p1[1]), (p3[0]-p2[0], p3[1]-p2[1])
    theta1, theta2 = math.atan2(v1[1], v1[0]), math.atan2(v2[1], v2[0])
    return ((theta2 > theta1 and theta2 < theta1 + math.pi) or
            (theta2 + 2*math.pi < theta1 + math.pi))

with open('fc.in') as fin:
    nspots = int(fin.readline())
    spots = [fin.readline().split() for _ in range(nspots)]
    spots = [(float(_[0]), float(_[1])) for _ in spots]

midx = midy = 0
for i in range(nspots):
    midx += spots[i][0] / nspots
    midy += spots[i][1] / nspots

spots.sort(key = lambda p: math.atan2(p[1]-midy, p[0]-midx))

fence = [spots[0], spots[1]]
for i in range(2, nspots):
    while len(fence) > 1 and not convex(fence[-2], fence[-1], spots[i]):
        fence.pop()
    fence.append(spots[i])

start, bad = 0, True
while bad:
    bad = False
    if not convex(fence[-2], fence[-1], fence[start]):
        fence.pop()
        bad = True
    if not convex(fence[-1], fence[start], fence[start+1]):
        start += 1
        bad = True

perim = math.hypot(fence[start][0]-fence[-1][0], fence[start][1]-fence[-1][1])
for i in range(len(fence)-start-1):
    perim += math.hypot(fence[start+i+1][0]-fence[start+i][0], fence[start+i+1][1]-fence[start+i][1])
with open('fc.out', 'w') as fout:
    print('%.2f' % perim, file = fout)

    
