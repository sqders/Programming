l=int(input())
word=list(input())
h=0
c_word=word.copy()
alpha=[]
l_c_word=len(c_word)
l_w=len(word)
for i in range(l):
	alpha.append("0")
for i in range(l_w**l):
	sis=i
	for j in range(l):
		re=alpha[0]
		n=sis%l_w
		alpha+=str(n)
		alpha.remove(re)
		sis=sis//l_w
	for j in range(l):
		g=(ord(alpha[j])-48)
		alpha[j]=word[int(g)]
		
	for j in range(l):
		while(l_c_word!=0 and h<l_c_word):
			if(str(alpha[j])==str(c_word[h])):
				re=c_word[h]
				c_word.remove(re)
			l_c_word=len(c_word)
			h+=1
		h=0
	if(len(c_word)!=0):
		h=0
		l_c_word=len(c_word)
		c_word=word.copy()
		alpha.clear()
		for j in range(l):
			alpha.append("0")
		continue
	for j in range(l):
		print(alpha[j],end='')
	print(' ',end='')
	alpha.clear()
	c_word=word.copy()
	h=0
	l_c_word=len(c_word)
	for j in range(l):
		alpha.append("0")
