import numpy as np
import matplotlib.pyplot as plt
import os
from sys import argv
import decimal



datos=[]
for f in argv[1:]:
	datos.append(s[:s.find(' ') for s in open(f,'r').readlines())

#files=[[] for arg in argv[1:]]
plt.figure(1, figsize=(12,5))
for i in range(len(datos)):
	plt.subplot(1, len(datos), i)
	plt.plot(datos[i], marker='o')
	plt.axhline( mean(datos[i]), color='b', linestyle='dashed', linewidth=3)
	plt.title(argv[i+1].split('.')[0])

plt.savefig(argv[1].split('_')[0]+'_time.png',dpi=100)


