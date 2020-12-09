import math
time_1=input()
time_2=input()
hour_1=[]
hour_2=[]
hour_1=time_1.split(':')
hour_2=time_2.split(':')
min_1=int(hour_1[0])*60+int(hour_1[1])
min_2=int(hour_2[0])*60+int(hour_2[1])
if((math.fabs(min_1 - min_2))<=15):
	print('Встреча состоится')
else:
	print("Встреча не состоится")