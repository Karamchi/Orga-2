import fileinput
import sys

opts=["-O0", "-O1", "-O2", "-O3"]

for o in opts:
	f = open("../src/Makefile",'r')
	filedata = f.read()
	f.close()

	newdata = filedata.replace(o,sys.argv[1])

	f = open("../src/Makefile",'w')
	f.write(newdata)
	f.close()
