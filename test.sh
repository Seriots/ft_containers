#!/bin/bash
make
valgrind ./ft_containers 2> test/log_ft
valgrind ./std_containers 2> test/log_std
#./ft_containers > /dev/pts/6 && ./std_containers > /dev/pts/4


if [ -n "$1" ]; then
	python3 compare_in.py test/ft_test test/std_test > test/compare
else
	python3 compare.py test/ft_test test/std_test
fi
