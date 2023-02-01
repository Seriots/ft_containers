
with open("ono", "r") as f:
	lines = f.readlines()

i = 0
line2 = []
for elem in lines:
	if elem[-1] == "\n":
		elem = elem[:-1]
	line2.append((int(elem), i))
	i += 1
#print(line2)
line2.sort()
line3 = []
i = 0
for elem in line2:
	line3.append((int(elem[1]), (i)))
	i+=1
line3.sort()
print(line3)