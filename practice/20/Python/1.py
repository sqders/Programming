denga=int(input())
t=int(input())
v=[]
price=[]
name=[]
litr=[]
sum=0
butilka=0
for i in range(t):
	v.append(0)
	price.append(0)
	name.append("0")
	litr.append(0)
for i in range(t):
	name[i],price[i],v[i]=input().split()
	price[i]=int(price[i])
	v[i]=int(v[i])
	litr[i]=v[i]/price[i]
for i in range(t):
    for j in range(0, t-i-1):
        if litr[j] > litr[j+1]:
            temp1 = litr[j]
            litr[j] = litr[j+1]
            litr[j+1] = temp1
            temp2 = v[j]
            v[j] = v[j+1]
            v[j+1] = temp2
            temp3 = price[j]
            price[j] = price[j+1]
            price[j+1] = temp3
            temp4 = name[j]
            name[j] = name[j+1]
            name[j+1] = temp4
while(sum<=denga):
	term=sum
	sum+=price[t-1]
	butilka+=1
	if(butilka-1==0):
		print(-1)
	else:
		print(name[t-1],butilka-1,'\n',v[t-1]*(butilka-1),'\n',denga-term)
