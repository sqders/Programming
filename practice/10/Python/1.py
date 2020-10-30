s,l1,r1,l2,r2=map(int,input().split())
if (s<l1+l2 or s>r1+r2):
	print(-1)
else:
	s1=s-r2
	if(s1<l1):
		s1=l1
	s2=s-s1
	if(s2<l2):
		s2=l2
	print(s1,s2)