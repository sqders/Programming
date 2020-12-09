import random
print("Здарова!Вы играете в игру УГАДАЙ ЧИСЛО")

x=-1
n=1
while(n==1):
	a=int(random.random()*100)
	for i in range(6):
		if (i==5):
			print("Вы проиграли. Было загадано: ",'{',a,'}',sep='')
			break
		if (x==a):
			print("Поздравляю! Вы угадали")
			break
		if(x>a):
			print("Загаданное число меньше")
		if(x<a and x!=-1):
			print("Загаданное число больше")
		x=int(input())
		
	print("Хотите начать сначала? (1 - ДА )")
	n=int(input())