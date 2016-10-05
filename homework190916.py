#!/usr/bin/python3
import numpy as np
def resize(p,n):
    while(p<n):
        p = p*2
    return p

def read(n,arr):
    ak = arr[:n, :n]
    for i in range(0,n):
        str1 = input()
        ak[i] = str1.split()
    return arr

def strassen(a,b,p,c):
    if p > 4:
        a11 = a[:p//2, :p//2]
        a12 = a[:p//2, p//2:p]
        a21 = a[p//2:p, :p//2]
        a22 = a[p//2:p, p//2:p]
        b11 = b[:p//2, :p//2]
        b12 = b[:p//2, p//2:p]
        b21 = b[p//2:p, :p//2]
        b22 = b[p//2:p, p//2:p]
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
        c[:p//2, :p//2] = p1+p4-p5+p7
        c[:p//2, p//2:p] = p3+p5
        c[p//2:p, :p//2] = p2+p4
        c[p//2:p, p//2:p] = p1-p2+p3+p6
    else:
        c[:p, :p] = np.dot(a,b)    
    return c
    

def ansout(c,n):
    for i in range(0,n):
        print(" ".join(map(str, c[i][:n])))

n = input()
n = int(n)
p = 1
u = resize(p,n)
a = np.empty((u,u))
b = np.empty((u,u))
read(n,a)
read(n,b)
c = np.empty((u,u), dtype = a.dtype)
с = strassen(a,b,u,c)
ansout(c,n)
