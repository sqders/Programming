lis=[ "hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen"]
alpha=[]
value=0
prob=1
for i in range(26):
	alpha.append(0)
for i in range(len(lis)):
	for j in range(len(lis[i])):
		for w in range(97,122):
			if(ord(lis[i][j])==w):
				alpha[w-97]+=1
for i in range(26):
	value+=alpha[i]
stop=input("Введите стоп слово:")
for i in range (len(stop)):	
	for w in range(97,122):
		if(ord(stop[i])==w):
			prob*=(alpha[w-97]/value)
print(prob)
