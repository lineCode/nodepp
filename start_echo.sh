#!/bin/bash

for i in $(seq 1 8)
do
	./echo/echo $i &
	echo "start " $i
done
