from tkinter import *
master = Tk()
master.geometry('800x600')

def hello():
  print("hello menu")

menu_bar = Menu(master)
menu_file = Menu(menu_bar, tearoff = 1)


for item in ['Python', 'PHP', 'CPP', 'C', 'Java', 'JavaScript'] :
  menu_bar.add_command(label = item, command = hello)
  
menu_bar.add_cascade(label = 'Language', menu = menu_file)

master['menu'] = menu_bar

master.mainloop()
