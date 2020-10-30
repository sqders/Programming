import math
a=int(input())
b=int(input())
c=int(input())
if a == 0 :
    if b == 0:
        print("Корней нет")
    else:
        print(-c/b)
if b**2-4*a*c<0:
	print("Корней нет")
elif b**2-4*a*c == 0:
	print(-b/(2*a))
else:
    print((-b+ math.sqrt(b**2-4*a*c))/(2*a),(-b- math.sqrt(b**2-4*a*c))/(2*a),sep="\n") 