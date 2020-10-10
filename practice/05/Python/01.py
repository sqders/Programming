print('Введите x0,Vo и t')
a=9.8
x0,V0,t=map(int,input().split())
print(-V0*t+a*t*t/2)