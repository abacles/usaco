'''
ID: abacles1
LANG: PYTHON3
TASK: preface
'''

fin = open('preface.in','r')
n = int(fin.readline())
fin.close()

marks = {1:'I',5:'V',10:'X',50:'L',100:'C',500:'D',1000:'M'}
values = {v:k for k,v in marks.items()}


numeral = ['','I','II','III','IV','V','VI','VII','VIII','IX']
count = {m:0 for m in values.keys()}

for num in range(1,n+1):
    if num > 9:
        roman = ''.join([marks[values[c]*10] for c in numeral[num//10]])
        roman += numeral[num%10]
        numeral.append(roman)
    else:
        roman = numeral[num]
    for c in roman:
        count[c] += 1

fout = open('preface.out','w')
for m in 'IVXLCDM':
    if count[m] > 0:
        fout.write(m + ' ' + str(count[m]) + '\n')
fout.close()
