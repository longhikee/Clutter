from tkinter import *
root = Tk()
Entry(root, text='in variable').pack()

txt = StringVar()
txt.set('input your text here')

e = Entry(root, textvariable=txt)

e.pack()
e['state'] = 'readonly'
#e['state'] = 'normal'

for mask in ['*','#','$']:
    e = StringVar()
    entry = Entry(root,textvariable = e)
    e.set('password')
    entry.pack()
    entry['show'] = mask

root.mainloop()
