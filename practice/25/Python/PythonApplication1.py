import random
import math
def sorted(arr):
   for i in range (len(arr)-1):
        if(arr[i]<arr[i+1]):
            continue
        else:
            return True
   return False
def BozoSort(arr,bool=True):
    sort_arr=arr.copy()
    while(sorted(sort_arr)):
        x1,x2=random.randint(1,n)-1,random.randint(1,n)-1
        temp=sort_arr[x1]
        sort_arr[x1] =  sort_arr[x2]
        sort_arr[x2] = temp
    if(bool):
        return sort_arr
    else:
        sort_arr.reverse()
        return sort_arr
n=int(input())
arr=list(input().split())
for a in range (n):
    arr[a]=int(arr[a])
print(BozoSort(arr))
print(BozoSort(arr,False))
g=0
temp=[]
input_matrix=[]
for line in range (int(math.sqrt(n))):
    for collums in range(int(math.sqrt(n))):
        temp.append(arr[g])
        g+=1
    term=temp.copy()
    input_matrix.append(term)
    temp.clear()
del g,a,line,collums

def sorted(matrix):
    sort_matrix=matrix.copy()
    for j in range(len(matrix)):
        for i in range (len(matrix)-1):
            if(sort_matrix[j][i]<sort_matrix[j][i+1]):
                continue
            else:
                return True
        if (j!=len(matrix)-1):
            if(sort_matrix[j][len(matrix)-1]<sort_matrix[j+1][0]):
                continue
            else:
                return True
    return False
def BozoSort(matrix,bool=True):
    sort_matrix=matrix.copy()
    while(sorted(sort_matrix)):
         x1,x2,y1,y2=random.randint(1,math.sqrt(n))-1,random.randint(1,math.sqrt(n))-1,random.randint(1,math.sqrt(n))-1,random.randint(1,math.sqrt(n))-1
         term=sort_matrix[x1][y1]
         sort_matrix[x1][y1]=sort_matrix[x2][y2]
         sort_matrix[x2][y2]=term
    if(bool):
        return sort_matrix
    else:
        sort_matrix.reverse()
        for i in range (len(sort_matrix)):
            sort_matrix[i].reverse()
        return sort_matrix
print(BozoSort(input_matrix))
print(BozoSort(input_matrix,False))
copy_arr=arr.copy()
def BozoSort(a,b,c,bool=True):
    while(a>b or b>c):
        rand=random.randint(0,2)
        if(rand==0):
            temp=a
            a=b
            b=temp
        elif(rand==1):
            temp=a
            a=c
            c=temp
        elif(rand==2):
            temp=b
            b=c
            c=temp
    return [a,b,c]


a,b,c=copy_arr[0],copy_arr[1],copy_arr[2]
print(BozoSort(a,b,c))
