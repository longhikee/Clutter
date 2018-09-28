from tkinter import *
root = Tk()

t = Text(root)
t.insert(1.0, 'hello1\n')
t.insert(END, 'hello2\n')
t.insert(END, 'hello3\n')
t.insert(END, 'hello4\n')
t.insert(END, 'hello5\n')
t.insert(END, 'hello6\n')
t.insert(END, 'hello7\n')
t.insert(END, 'hello8\n')

t.delete(2.0, 5.0)

t.pack()

root.mainloop()
