#!/bin/bash

make fast
if [ ! -e output ]
then
	mkdir output
fi

./a.out public_data.txt <Stdin/1.in >output/1.out
./a.out public_data.txt <Stdin/2.in >output/2.out
./a.out public_data.txt <Stdin/3.in >output/3.out
./a.out public_data.txt <Stdin/4.in >output/4.out

diff outputStd/1.out output/1.out
diff outputStd/2.out output/2.out
diff outputStd/3.out output/3.out
diff outputStd/4.out output/4.out