ops[0]='-O0'
ops[1]='-O1'
ops[2]='-O2'
ops[3]='-O3'

files[0]="cropflip"
files[1]="mblur"
files[2]="bandas"
files[3]="sierpinski"

rm -f *.time
rm -f tiempos/*
mkdir -p tiempos
mkdir -p Objdump
mkdir -p Objdump/"${files[@]}"

for op in "${ops[@]}"
do
	python ../pyscripts/agregarOptimizaciones.py $op
	make
	for j in {1..10}
	do
		./tp2 cropflip -i c lena.bmp 150 150 250 300		
		./tp2 mblur -i c lena.bmp
		./tp2 bandas -i c lena.bmp
		./tp2 sierpinski -i c lena.bmp
	done
	for f in "${files[@]}"
	do
		mv $f\_c.time tiempos/$f\_c$op.time
		rm Objdump/$f/$f$op.txt
		objdump -Mintel -D $f\_c.o >> Objdump/$f/$f$op.txt
	done
		
done


./tp2 cropflip -i asm lena.bmp 150 150 250 300		
./tp2 mblur -i asm lena.bmp
./tp2 bandas -i asm lena.bmp
./tp2 sierpinski -i asm lena.bmp
for f in "${files[@]}"
do
	mv $f\_asm.time tiempos/$f\_asm.time
done



for f in "${files[@]}" 
do
	python ../pyscripts/graficar.py tiempos/$f\_c-O0.time tiempos/$f\_c-O1.time tiempos/$f\_c-O2.time tiempos/$f\_c-O3.time tiempos/$f\_asm.time
done





python ../pyscripts/agregarOptimizaciones.py -O0
make
