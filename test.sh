#!/bin/bash
if [ ! -f "ft_containers" ] || [ ! -f "std_containers" ]; then
	sh load.sh
fi

if [ ! -d "test" ]; then
	mkdir test
fi
./ft_containers > test/ft_test | ./std_containers > test/std_test

if [ -n "$1" ]; then
	python3 compare_in.py test/ft_test test/std_test > test/compare
else
	python3 compare.py test/ft_test test/std_test
fi
