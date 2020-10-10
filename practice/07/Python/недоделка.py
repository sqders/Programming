import math
if (input()==1):
	a= input()
	b=input()
	c=input()
	if(a+b-c>0):
		p=(a+b+c)/2
		print(math.sqrt(p*(p-a)*(p-b)*(p-c)))
	else print("Такого треугольника не существует")
elif(input()==2)