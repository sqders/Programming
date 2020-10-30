
a=[]
c=[]
sum=0
red=0
black=0
for i in range (37):
	a.append(i)
for i in range (37):
	c.append(0)
while(1) :
	y=int(input())
	if(y==-1):
		quit()
	a.append(37)
	for i in range(len(a)-1):
		if (a[i]==y):
			a.remove(y)
	a.remove(37)
	c[y]+=1
	sum+=1
	for i in range(sum,0,-1):
		for j in range (37):
			if(c[j]==i):
				print(j ,end=' ')
	print("\n")
	for i in range(len(a)):
		print(a[i],end=' ')
	print("\n")
	if(y==1 or y==3 or y==5 or y==9 or y==12 or y==14 or y==16 or y==18 or y==19 or y==21 or y==23 or y==25 or y==27 or y==30 or y==32 or y==34 or y==36 ):
			red+=1
	elif(y!=0):
			black+=1
	print(red,black)
	print('\n')