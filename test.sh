#!/bin/bash
if [ ! -f "ft_containers" ] || [ ! -f "std_containers" ]; then
	sh load.sh
fi

if [ ! -d "test" ]; then
	mkdir test
fi
./ft_containers | ./std_containers
#./ft_containers > /dev/pts/6 && ./std_containers > /dev/pts/4


if [ -n "$1" ]; then
	python3 compare_in.py test/ft_test test/std_test > test/compare
else
	python3 compare.py test/ft_test test/std_test
fi
