from tkinter import *
master = Tk()

c = Canvas(master, width=200, height=100)

#c.create_line(0, 100, 200, 0, fill='red', dash=(4, 4))
c.create_line(50, 25, 150, 75, fill='blue')
c.create_line(30,60,150,160, fill='black')

t = Canvas(master, width=200, height=200, bg='yellow')
t.create_rectangle(10,20,30,40)

c.pack()
t.pack()
mainloop()
