from tkinter import *

root = Tk()
root.title("hello world")
root.geometry('300x200')
root.resizable(width=False, height=True) #宽不可变，高可变，默认为True

frm = Frame(root, bg='blue')
frm_L = Frame(frm)
frm_R = Frame(frm)

Label(frm, text='校训', font=('Arial',20)).pack()

Label(frm_L, text='厚德', font=('Arial', 15)).pack(side=TOP)
Label(frm_L, text='博学', font=('Arial', 15)).pack(side=TOP)

Label(frm_R, text='敬业', font=('Arial', 15)).pack(side=TOP)
Label(frm_R, text='乐群', font=('Arial', 15)).pack(side=TOP)

frm.pack()
frm_L.pack(side=LEFT)
frm_R.pack(side=RIGHT)
root.mainloop()
