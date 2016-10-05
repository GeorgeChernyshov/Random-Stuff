#!/usr/bin/python3
import numpy as np

n = input()
n = int(n)
p = 1
while p < n:
    p = p*2
a = []
a = np.zeros((p,p))
ak = a[:n, :n]
for i in range(0,n):
    str = input()
    ak[i] = str.split()
b = np.zeros((p,p))
bk = b[:n, :n]
for i in range(0,n):
    str = input()
    bk[i] = str.split()
a11 = a[:p//2, :p//2]
a12 = a[:p//2, p//2:p]
a21 = a[p//2:p, :p//2]
a22 = a[p//2:p, p//2:p]
b11 = b[:p//2, :p//2]
b12 = b[:p//2, p//2:p]
b21 = b[p//2:p, :p//2]
b22 = b[p//2:p, p//2:p]
c = np.zeros((p,p))
p1 = np.dot((a11+a22),(b11+b22))
p2 = np.dot((a21+a22), b11)
p3 = np.dot(a11,(b12-b22))
p4 = np.dot(a22,(b21-b11))
p5 = np.dot((a11+a12),b22)
p6 = np.dot((a21-a11),(b11+b12))
p7 = np.dot((a12-a22),(b21+b22))
c[:p//2, :p//2] = p1+p4-p5+p7
c[:p//2, p//2:p] = p3+p5
c[p//2:p, :p//2] = p2+p4
c[p//2:p, p//2:p] = p1-p2+p3+p6
for i in range(0,n):
    for j in range(0,n):
        print(int(c[i][j]), end = " "),
    print( )
