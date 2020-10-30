n=int(input())
def f(a):
	if (a==1):
		return a
	else :
		return f(a-1)*a
print(f(n))