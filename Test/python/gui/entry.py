from tkinter import *
root = Tk()
Entry(root, text='input your text here').pack()

txt = StringVar()
txt.set('input your text here')

e = Entry(root, textvariable=txt)

e.pack()
e['state'] = 'readonly'

for mask in ['*','#','$']:
    e = StringVar()
    entry = Entry(root,textvariable = e)
    e.set('password')
    entry.pack()
    entry['show'] = mask

root.mainloop()
