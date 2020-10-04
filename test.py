import itertools

def fact(n):
    if n == 1:
        return 1;
    return n * fact(n-1)

def testhash(state):
    h = 0
    for i in range(7):
        h += (ord(state[i]) - ord('0')) * fact(7-i)
    return h

hashes = {}
r = 0
for pattern in itertools.permutations('12345678',8):
    pattern = ''.join(pattern)
    h = testhash(pattern)
    if h in hashes:
        r += 1
        if r == 1:
            print(h,':',pattern,'vs',hashes[h])
    else:
        hashes[h] = pattern
print(r)
print(testhash('12345768'),testhash('12345687'))
