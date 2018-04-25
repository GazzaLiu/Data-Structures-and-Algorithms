#!/bin/bash

make fast
if [ ! -e output ]
then
	mkdir output
fi

./a.out public_data.txt <Stdin/1.in >output/1.out

diff outputStd/1.out output/1.out