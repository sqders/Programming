a=int(input())
b=int(input())
d=a
def f(h,v):
	if (v==1):
		return h
	else :
		h = f(h,v-1)*d
		return h
c=f(a,b)
print(c)