import sys
import re

with open(sys.argv[1], 'r') as f1, open(sys.argv[2], 'r') as f2:
	ft_file = f1.readlines()
	std_file = f2.readlines()

for i in range(len(ft_file)):
	line_ft = ft_file[i][0:-1]
	line_std = std_file[i][0:-1]
	if len(line_ft) > 50:
		line_ft = line_ft[0:47] + '...'
	if len(line_std) > 50:
		line_std = line_std[0:47] + '...'
	if line_ft.find('ft_') != -1:
		print(f'\033[34m{line_ft: <50} | {line_std: <50}\033[0m', end='\n')
	elif re.search(r'<.*>', line_ft) and ft_file[i][0] == '<':
		print(f'\033[36m{line_ft: <50} | {line_std: <50}\033[0m', end='\n')
	elif line_ft.find('Time: ') != -1:
		print(f'\033[33m{line_ft: <50} | {line_std: <50}\033[0m', end='\n\n')
	else:
		print(f'{line_ft: <50} | {line_std: <50} --> ', end='')
		if ft_file[i] == std_file[i]:
			print('\033[32mOK\033[0m')
		else:
			print('\033[31mKO\033[0m')