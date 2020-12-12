n=int(input())
args='1 2'
some=[]
args=input().split()
for a in range(len(args)):
    args[a]=int(args[a])
def top5():
    some.append(args[i])
    some.sort()
    if (len(some)>5):
        some_5=[some[4],some[3],some[2],some[1],some[0]]
        return some_5
    else:
        some.reverse()
        return some
for i in range (0,n):
    print(top5())
