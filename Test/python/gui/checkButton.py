from tkinter import *

root = Tk()

cbutton1 = Checkbutton(root, text='python')



def callback():
  v.set('check Tkinter')
v = StringVar()
v.set('java')
cbutton2 = Checkbutton(root, text='check java', textvariable=v, command = callback)

w = IntVar()
def callCheckbutton():
  print(w.get())

cbutton3 = Checkbutton(root, variable=w, text='c#', command=callCheckbutton)
#variable default on=1, off=0

s = StringVar()
def callbackbutton():
  print(s.get())

cbutton4 = Checkbutton(root,
                       variable=s,
		       text='c',
		       onvalue='c on',
		       offvalue='c off',
		       command=callbackbutton)

cbutton1.pack()
cbutton2.pack()
cbutton3.pack()
cbutton4.pack()
root.mainloop()
