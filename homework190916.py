#!/usr/bin/python3
import numpy as np
def resize(p):
    while(p<n):
        p = p*2
    return p

def read(n,arr,p):
    ak = arr[:n, :n]
    for i in range(0,n):
        str1 = input()
        ak[i] = str1.split()
    return arr

def create(n,arr,p):
    arr = np.empty((p,p))
    read(n,arr,p)
    return arr

def strassen(a,b,p,c):
    a11 = a[:p//2, :p//2]
    a12 = a[:p//2, p//2:p]
    a21 = a[p//2:p, :p//2]
    a22 = a[p//2:p, p//2:p]
    b11 = b[:p//2, :p//2]
    b12 = b[:p//2, p//2:p]
    b21 = b[p//2:p, :p//2]
    b22 = b[p//2:p, p//2:p]
    if p > 4:
        p1 = np.empty((p//2,p//2), dtype = a.dtype)
        p2 = np.empty((p//2,p//2), dtype = a.dtype)
        p3 = np.empty((p//2,p//2), dtype = a.dtype)
        p4 = np.empty((p//2,p//2), dtype = a.dtype)
        p5 = np.empty((p//2,p//2), dtype = a.dtype)
        p6 = np.empty((p//2,p//2), dtype = a.dtype)
        p7 = np.empty((p//2,p//2), dtype = a.dtype)
        p1 = strassen((a11+a22),(b11+b22), p//2, p1)
        p2 = strassen((a21+a22), b11, p//2, p2)
        p3 = strassen(a11,(b12-b22), p//2, p3)
        p4 = strassen(a22,(b21-b11), p//2, p4)
        p5 = strassen((a11+a12),b22, p//2, p5)
        p6 = strassen((a21-a11),(b11+b12), p//2, p6)
        p7 = strassen((a12-a22),(b21+b22), p//2, p7)
    else:
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
    return c
    

def ansout(c,n):
    for i in range(0,n):
        for j in range(0,n):
            print(int(c[i][j]), end = " "),
        print( )

n = input()
n = int(n)
a = []
b = []
p = 1
p = resize(p)
a = create(n,a,p)
b = create(n,b,p)
c = np.empty((p,p), dtype = a.dtype)
с = strassen(a,b,p,c)
c.dtype = a.dtype
ansout(c,n)
