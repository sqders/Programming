print('Введите x0,Vo и t')
a=9.8
x0,V0,t=map(int,input().split())
print(-V0*t+1/2*a*t*t)