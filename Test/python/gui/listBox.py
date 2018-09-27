from tkinter import *
root = Tk()
lb = Listbox(root)
for item in ['python', 'java', 'c']:
  lb.insert(END, item)

lbm = Listbox(root, selectmode=MULTIPLE)
for item in ['one', 'two', 'three', 'four', 'five', 'six']:
  lbm.insert(END, item)

lbm.delete(0,1)
lbm.selection_set(0,2)
lbm.selection_clear(1)

'''return item'''
print(lbm.get(0,3))
'''return index value: true/false'''
print(lbm.selection_includes(3))
print(lbm.selection_includes(0))


lbind = Listbox(root)
def printList(event):
  print (lbind.get(lbind.curselection()))

lbind.bind('<Double-Button-1>', printList)
for i in range(10):
  lbind.insert(END, str(i*100))

lb.pack()
lbm.pack()
lbind.pack()
root.mainloop()
