from flask import Flask,request
import openpyxl
import datetime
app = Flask(__name__)
count=0
ticha=[]
@app.route('/', methods=['POST', 'GET'])
def index():
	if request.method == 'POST':
		user_id=request.json['user_id']
		check=request.json['check']
		for a in range(len(check)):
			ticha.append(check[a])
			ticha[len(ticha)-1]["user_id"]=user_id
			ticha[len(ticha)-1]["datetime"]= datetime.datetime.now()
		lenght=str(len(ticha))
		print(ticha)
		if(len(ticha)!=1000):
			obook=openpyxl.open("data.xlsx",read_only=True)
			osheet=obook.active
			print(osheet.max_column)
			rows=osheet.max_row
			cols=osheet.max_column
			obook.close()
			book=openpyxl.Workbook()
			sheet=book.active
			if(cols==3):
				sheet.cell(row=1,column=1).value = 'N'
				sheet.cell(row=1,column=2).value = "User ID"
				sheet.cell(row=1,column=3).value = "Datetime"
				sheet.cell(row=1,column=4).value = "Item"
				sheet.cell(row=1,column=5).value = "Price"
						
			start=rows-2
			for i in range (start,len(ticha)):
				sheet.cell(row=i+2,column=1).value = i+1
				sheet.cell(row=i+2,column=2).value = ticha[i]["user_id"]
				sheet.cell(row=i+2,column=3).value = ticha[i]["datetime"]
				sheet.cell(row=i+2,column=4).value = ticha[i]["item"]
				sheet.cell(row=i+2,column=5).value = ticha[i]["price"]
						
			book.save("data.xlsx")
			book.close()
		return "OK"
	if request.method == 'GET':
		return "Это GET запрос"
 
if __name__ == "__main__":
	app.run()