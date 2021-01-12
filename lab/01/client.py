from tkinter import *
import requests
from requests.exceptions import InvalidSchema

def new_wet(event):
	try:
		weather = requests.get('http://localhost:3000/raw', headers={'Content-type': 'text/json; charset=UTF-8'}).json()
	except InvalidSchema:
		print('Can\'t connect to server. Exit')
		exit()
	temp = str(weather['temp']).split('.')[0]
	pogoda["text"]=weather['pogoda']
	temperature["text"]=(temp + '°C')
	print("New weather printed \n")
	pass

try:
	weather = requests.get('http://localhost:3000/raw', headers={'Content-type': 'text/json; charset=UTF-8'}).json()
except InvalidSchema:
	print('Can\'t connect to server. Exit')
	exit()
root = Tk()

temp = str(weather['temp']).split('.')[0]
top = Frame(root, background="#ff4f00")
top.pack(side=TOP, fill=X)
middle = Frame(root, background="white")
middle.pack(side=TOP, fill=BOTH)
bottom = Frame(root, background="#ff4f00")
bottom.pack(side=BOTTOM, fill=X)
Label(top, 
	text="Симферополь", 
	bg="#ff4f00", 
	fg="#333333",
	font=('sans-serif', 10, 'bold')).pack(fill=X)
pogoda=Label(top, 
	text=weather['pogoda'], 
	bg="#ff4f00", 
	fg="#333333",
	font=('sans-serif', 8))
temperature=Label(middle, 
	text=(temp + '°C'), 
	padx=50, 
	pady=50,
	fg="#333333",
	font=('sans-serif', 50, 'bold'))
Label(bottom, bg="#ff4f00").pack(fill=X)
pogoda.pack(fill=X)
temperature.pack(fill=X)
root.bind("<Button-3>",new_wet)

root.mainloop()
