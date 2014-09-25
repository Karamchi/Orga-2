from pylab import *

names = []
values = []

read_file = open('promedio.csv')

for line in read_file:
	name, value = line.strip().split(';')
	names.append(name)
	values.append(float(value))
	
pos = arange(len(names)) + 1000

bar(pos, values, align='center', color= '#b8ff5c')
xticks(pos, names)
show()
