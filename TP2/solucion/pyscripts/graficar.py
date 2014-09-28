import numpy as np
import matplotlib.pyplot as plt
import os
from sys import argv
import decimal



datos=[]
for f in argv[1:]:
	datos.append([int(s[:s.find(' ')]) for s in open(f,'r').readlines()])

#files=[[] for arg in argv[1:]]
#plt.figure(num=1, figsize=(12,5))
labels=[a.split('/')[1].split('.')[0] for a in argv[1:]]
#plt.boxplot(datos, labels=labels, meanline=True)
# demonstrate how to toggle the display of different elements:
fig=plt.figure(1)
ax = fig.add_subplot(111)#, figsize=(12,6))
ax.boxplot(datos)
ax.set_xticklabels(labels)
ax.set_title(labels[0].split('_')[0])


'''
	plt.subplot(1, len(datos), i)
	plt.plot(datos[i], marker='o')
#	plt.axhline( np.mean(datos[i]), color='b', linestyle='dashed', linewidth=3)
	plt.title(argv[i+1].split('.')[0])
'''

plt.savefig(argv[1].split('.')[0]+'.png',dpi=100)#argv[1].split('_')[0]+'_time.png',dpi=100)


