from tkinter import *
from PIL import Image, ImageTk
from random import shuffle

root = Tk()

tileset = Image.open("Images\\cell-bgr.png")
cell = ImageTk.PhotoImage(tileset.crop((1, 0, 67, 66)))
light_cell = ImageTk.PhotoImage(tileset.crop((1, 69, 67, 135)))
ball = Image.open("Images\\ball-blue.png").convert('RGBA')
def clck(event):
	bgr = Image.open("page-bgr.png").convert('RGBA')
	ball = Image.open("ball-blue.png").convert('RGBA')
	pic_size_same_as_bgr = Image.new("RGBA", bgr.size)
	pic_size_same_as_bgr.paste(ball, (70,0)) 
	ball_over_bgr = Image.alpha_composite(bgr, pic_size_same_as_bgr)
	img = ImageTk.PhotoImage(ball_over_bgr)
	event.widget.config(image=img)
	 
root = Tk()
 
for row in range(2):
    for col in range(2):
        lbl = Label(root, text=', '.join([str(row), str(col)]))
        lbl.row = row
        lbl.col = col
        lbl.is_pig_here = randint(0, 1)
        lbl.config(image=cell)
        lbl.bind("<Button-1>", clck)
        lbl.grid(row=row, column=col, padx=1, pady=1, sticky = 'nesw')      
root.mainloop()
