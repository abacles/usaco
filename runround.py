'''
ID: abacles1
LANG: PYTHON3
TASK: runround
'''

fin = open('runround.in','r')
num = fin.readline().strip()
fin.close()

while True:
    num = str(int(num)+1)
    digs = [0,0,0,0,0,0,0,0,0]
    rr = True
    l = len(num)
    for d in num:
        if d == '0' or digs[ord(d)-ord('1')] > 0:
            rr = False
            break
        digs[ord(d)-ord('1')] += 1
    if not rr:
        continue
    di = 0
    touched = [False]*l
    for i in range(l):
        if touched[di]:
            rr = False
            break
        touched[di] = True
        di = (di+ord(num[di])-ord('1')+1)%l
    if rr and di == 0:
        fout = open('runround.out','w')
        fout.write(num + '\n')
        fout.close()
        print(num)
        break
