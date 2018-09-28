from tkinter import *
master = Tk()
master.geometry('800x600')

def hello():
  print("hello menu")

def open(event):
  print('open file')

menu_bar = Menu(master)
menu_file = Menu(menu_bar, tearoff = True)


for item in ['Python', 'PHP', 'CPP', 'C', 'Java', 'JavaScript'] :
  menu_bar.add_command(label = item, command = hello)
  

menu_bar.add_cascade(label = 'file', menu = menu_file)
menu_file.add_command(label='open', command=hello, accelerator='Ctrl+O')
menu_file.add_command(label='save')
menu_file.add_separator()
menu_file.add_command(label='exit', command=master.quit)

master['menu'] = menu_bar #master.config(menu=menu_bar)

#master.bind_all('<Control-o>', lambda event: print('hot key Crtl + o'))
master.bind_all('<Control-o>', open)

master.mainloop()
