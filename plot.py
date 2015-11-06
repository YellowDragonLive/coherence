from matplotlib import pyplot as plt
import numpy as np
from sys import exit


x = np.genfromtxt("x.csv",delimiter=';')
y = np.genfromtxt("y.csv",delimiter=';')
coh = np.genfromtxt("coh.csv",delimiter=';')
fr  = np.genfromtxt("f.csv",delimiter=";")

SN = 256

w = [1.]*SN
hann = [0.0]*SN
for i in range(SN):
#	hann[i] = 0.5*(1-np.cos(2*np.pi*i/SN))
	hann[i] = 1.0
c,f = plt.cohere(x,y,NFFT=SN,Fs=1,window=hann)


plt.subplot(2,2,1)
plt.plot(x)
plt.title("x")

plt.subplot(2,2,2)
plt.plot(y)
plt.title("y")

plt.subplot(2,2,3)
plt.plot(fr,coh)
plt.title("coh")

plt.subplot(2,2,4)
plt.plot(f,c)
plt.plot(fr,coh)
plt.title("coh scipy ")

plt.tight_layout()
plt.show()

