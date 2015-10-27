from matplotlib import pyplot as plt
import numpy as np
from sys import exit


x = np.genfromtxt("x.csv",delimiter=';')
y = np.genfromtxt("y.csv",delimiter=';')
sxx = np.genfromtxt("sxx.csv",delimiter=';')
syy = np.genfromtxt("syy.csv",delimiter=';')
sxy = np.genfromtxt("sxy_abs_sq.csv",delimiter=';')
coh = np.genfromtxt("coh.csv",delimiter=';')
coh2 = np.genfromtxt("coh2.csv",delimiter=';')
fr  = np.genfromtxt("f.csv",delimiter=";")

SN = 256

r=4
w = [1.]*SN
hann = [0.0]*SN
for i in range(SN):
	hann[i] = 0.5*(1-np.cos(2*np.pi*i/SN))

c,f = plt.cohere(x,y,NFFT=SN,Fs=1,window=hann)



plt.subplot(r,2,8)
plt.plot(f,c)
plt.title("coh scipy ")

plt.subplot(r,2,1)
plt.plot(x)
plt.title("x")

plt.subplot(r,2,2)
plt.plot(y)
plt.title("y")

plt.subplot(r,2,3)
plt.plot(sxx)
plt.title("Sxx")

plt.subplot(r,2,4)
plt.plot(syy)
plt.title("Syy")

plt.subplot(r,2,5)
plt.plot(sxy)
plt.title("Sxy")

plt.subplot(r,2,6)
plt.plot(fr,coh)
plt.title("coh")

plt.subplot(r,2,7)
plt.plot(fr,coh2)
plt.title("coh2")


plt.tight_layout()
plt.show()

