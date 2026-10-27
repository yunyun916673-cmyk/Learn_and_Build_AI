import sys
import numpy as np
input=sys.stdin.readline
def S(x):
	return 1.0/(1.0+np.exp(-x))
def dS(s):
	return s*(1.0-s)
X=np.array([[0,0],[0,1],[1,0],[1,1]])
Y=np.array([[0],[1],[1],[0]])
rng=np.random.default_rng()
Hw=rng.uniform(-1,1,(2,2))
Hb=rng.uniform(-1,1,(1,2))
Ow=rng.uniform(-1,1,(2,1))
Ob=rng.uniform(-1,1,(1,1))
lr=0.5
print('start training')
for epoch in range(100000):
	Ho=S(np.dot(X,Hw)+Hb)
	Fo=S(np.dot(Ho,Ow)+Ob)
	error=Fo-Y
	if not (epoch%1000):
		print(f"epoch: {epoch}")
		loss=0.5*np.sum(error**2)
	Do=error*dS(Fo)
	Dh=np.dot(Do,Ow.T)*dS(Ho)
	Ow-=lr*np.dot(Ho.T,Do)
	Ob-=lr*np.sum(Do,axis=0,keepdims=True)
	Hw-=lr*np.dot(X.T,Dh)
	Hb-=lr*np.sum(Dh,axis=0,keepdims=True)
print("result: ")
print("default: ",Fo)