

def print_factorization(n: int) -> None:
    g=n
    fin=0
    for i in range (n+1):
        arr.append(0)
    for a in range (2,n+1):
        while((g%a)==0):
          arr[a]+=1  
          g=g/a
    for a in range (2,n+1):
        if(fin<a and arr[a]>0):
            fin=a
    for b in range (n):
        if(fin==b):
            if(arr[b]==1):
                print(b,sep='',end='')
            else:
                print(b,'^',arr[b],sep='',end='')
           
        else:
            if(arr[b]==0):
                continue
            elif(arr[b]==1):
                print(b,'*',sep='',end='')
            else:
                print(b,'^',arr[b],"*",sep='',end='')
    pass
arr=[]
g=0
h=int(input())
print_factorization(h)
