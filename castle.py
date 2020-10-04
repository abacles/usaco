'''
ID: abacles1
LANG: PYTHON3
TASK: castle
'''

def reachable(walls):
    dirmap = {1:'l',2:'u',4:'r',8:'d'}
    reach = []
    empty = 15 - walls
    for i in (8,4,2,1):
        if empty >= i:
            empty -= i
            reach += dirmap[i]
    return reach

def visit(ri,ci):
    visited[ri][ci] = True
    room[ri][ci] = roomcount
    for direction in reachable(castle[ri][ci]):
        if direction == 'r' and not visited[ri][ci+1]:
            visit(ri,ci+1)
        elif direction == 'd' and not visited[ri+1][ci]:
            visit(ri+1,ci)
        elif direction == 'l' and not visited[ri][ci-1]:
            visit(ri,ci-1)
        elif direction =='u' and not visited[ri-1][ci]:
            visit(ri-1,ci)
            
def room_size(roommap,rnum):
    if rnum in roomsizes:
        return roomsizes[rnum]
    size = 0
    for row in roommap:
        for cell in row:
            if cell == rnum:
                size += 1
    roomsizes[rnum] = size
    return size

def biggest_room(roommap,rcount):
    return max([(x,room_size(roommap,x)) for x in range(rcount)],key = lambda item:item[1])

def rm_wall(roommap):
    bestsize = 0
    for c in range(cc):
        for r in reversed(range(rc)):
            if r > 0 and roommap[r-1][c] != roommap[r][c] and \
               room_size(roommap,roommap[r-1][c])+room_size(roommap,roommap[r][c]) > bestsize:
                bestsize = room_size(roommap,roommap[r-1][c]) + \
                           room_size(roommap,roommap[r][c])
                bestloc = (r+1,c+1,'N')
            if r < rc-1 and roommap[r+1][c] != roommap[r][c] and \
               room_size(roommap,roommap[r+1][c])+room_size(roommap,roommap[r][c]) > bestsize:
                bestsize = room_size(roommap,roommap[r+1][c]) + \
                           room_size(roommap,roommap[r][c])
                bestloc = (r+1,c+1,'S')
            if c > 0 and roommap[r][c-1] != roommap[r][c] and \
               room_size(roommap,roommap[r][c-1])+room_size(roommap,roommap[r][c]) > bestsize:
                bestsize = room_size(roommap,roommap[r][c-1]) + \
                           room_size(roommap,roommap[r][c])
                bestloc = (r+1,c+1,'W')
            if c < cc-1 and roommap[r][c+1] != roommap[r][c] and \
               room_size(roommap,roommap[r][c+1])+room_size(roommap,roommap[r][c]) > bestsize:
                bestsize = room_size(roommap,roommap[r][c+1]) + \
                           room_size(roommap,roommap[r][c])
                bestloc = (r+1,c+1,'E')
    return (bestloc,bestsize)

castle = []

fin = open('castle.in','r')
cc,rc = map(int,fin.readline().split())
for i in range(rc):
    castle.append([int(x) for x in fin.readline().split()])
fin.close()

visited = [[False for i in range(cc)] for j in range(rc)]
room = [[-1 for i in range(cc)] for j in range(rc)]
roomcount = 0
roomsizes = {}

r = 0
for row in castle:
    c = 0
    for cell in row:
        if not visited[r][c]:
            visit(r,c)
            roomcount += 1
        c += 1
    r += 1

bigroom = biggest_room(room,roomcount)
badwall = rm_wall(room)

fout = open('castle.out','w')
fout.write(str(roomcount) + '\n')
fout.write(str(bigroom[1]) + '\n')
fout.write(str(badwall[1]) + '\n')
fout.write(' '.join([str(x) for x in badwall[0]]) + '\n')
fout.close()
