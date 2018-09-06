from tkinter import *
master = Tk()

#l = Label(master, text="Hello!", fg='red', bg='blue')
#l = Label(master, text="font", font=("Helvetica",16))

l = Label(master, text='longtext123456\n123', anchor=W, justify=RIGHT)

v = StringVar()
Label(master, textvariable=v).pack()
v.set("New Text!")

l.pack()
mainloop()
