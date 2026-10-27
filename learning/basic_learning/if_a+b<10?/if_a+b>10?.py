import sys
intput=sys.stdin.readline
import numpy as np
def func(w1,w2,b,x1,x2):
    return (w1*x1+w2*x2+b)>0.0
rng=np.random.default_rng()
w1,w2,b=rng.integers(-1,1),rng.integers(-1,1),rng.integers(-1,1)
lr=0.05
vec=[]
for _ in range(100000):
    a1,a2=rng.integers(0,15),rng.integers(0,15)
    vec.append([a1,a2,(a1+a2>10)])
print("="*30)
print("start training: ")
pos,total_error=0,0
cnt=0
for a1,a2,tag in vec:
    error=tag-int(func(w1,w2,b,a1,a2))
    total_error+=error
    w1+=lr*error*a1
    w2+=lr*error*a2
    b+=lr*error
    cnt+=1
    if not cnt%1000:
       print(f"epoch: {cnt}")
       print(f"total error: {total_error}")
       print(f"w1: {w1} w2: {w2} b: {b}")
       total_error=0
print("stop training")
print("result: ")
print(f"w1: {w1} w2: {w2} b: {b}")
print("="*30)
print("start testing")
for _ in range(10):
    x1,x2=rng.integers(0,15),rng.integers(0,15)
    print(f"x1: {x1} x2: {x2}")
    print(f"Answer: {'YES' if func(w1,w2,b,x1,x2) else 'NO'}")
