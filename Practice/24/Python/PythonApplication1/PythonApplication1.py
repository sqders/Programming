import json
id=0
maxid=0
with open('in.json', "r") as inpu:
    data=json.load(inpu)
for a in range (len(data)):
    id=data[a]["userId"]
    if(id>maxid):
        maxid=id
mas=[]
for i in range (maxid+1):
    mas.append(0)
    print(i)
for a in range (len(data)):
   if(data[a]["completed"]):
        mas[data[a]["userId"]]+=1
print(mas)
dick=[]
for i in range(maxid+1):
    if(mas[i]>0):
        dick.append({"userId":i,"task_completed":mas[i]})
print(dick)
with open('out.json','w') as f:
    json.dump(dick,f,indent=2)
