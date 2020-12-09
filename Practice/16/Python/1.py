n=int(input())
a=[-1]
x=list(str(input()).split())
for i in range(n):
	if(x[i][0]=="a" and x[i][4:]=="55661"):
		a.remove(-1)
		a.append(x[i])
for i in range(len(a)):
	print(a[i])