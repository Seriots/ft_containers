import sys
import re

with open(sys.argv[1], 'r') as f1, open(sys.argv[2], 'r') as f2:
	ft_file = f1.readlines()
	std_file = f2.readlines()

for i in range(len(ft_file)):
	if ft_file[i][0:-1].find('ft_') != -1:
		print(f'{ft_file[i][0:-1]: <30} | {std_file[i][0:-1]: <30}', end='\n')
	elif re.search(r'<.*>', ft_file[i][0:-1]):
		print(f'{ft_file[i][0:-1]: <30} | {std_file[i][0:-1]: <30}', end='\n')
	elif ft_file[i][0:-1].find('Time: ') != -1:
		print(f'{ft_file[i][0:-1]: <30} | {std_file[i][0:-1]: <30}', end='\n\n')
	else:
		print(f'{ft_file[i][0:-1]: <30} | {std_file[i][0:-1]: <30} --> ', end='')
		if ft_file[i] == std_file[i]:
			print('OK')
		else:
			print('KO')