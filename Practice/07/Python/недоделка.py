import math
o=int(input())
if (o==1):
	print("Введите длины:")
	a= int(input())
	b= int(input())
	c= int(input())
if(o==2):
	x1,y1=map(int,input().split())
	x2,y2=map(int,input().split())
	x3,y3=map(int,input().split())
	a=math.sqrt((x1-x2)**2+(y1-y2)**2)
	b=math.sqrt((x2-x3)**2+(y2-y3)**2)
	c=math.sqrt((x3-x1)**2+(y3-y1)**2)
if(a+b-c>0):
	p=(a+b+c)/2
	print("S =",math.sqrt(p*(p-a)*(p-b)*(p-c)))
else:
	print("Такого треугольника не существует")