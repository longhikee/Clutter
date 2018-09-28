from tkinter import *

root = Tk()

lb = Label(root, text='label')
e = Entry(root, textvariable='entry')
b = Button(root, text='button')

lb.place(x=10,y=0)
e.place(x=20,y=50)
b.place(x=30,y=100)

root.mainloop()
