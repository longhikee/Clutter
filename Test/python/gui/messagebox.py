from tkinter import *
import tkinter
import tkinter.messagebox
import tkinter.filedialog

root = Tk()
root.geometry('800x600')
tkinter.messagebox.showinfo('info', 'message')
def doubleConfirm():
  ret = tkinter.messagebox.askokcancel('Confirm', 'Are you sure to execute the operation')
  print(ret)
  if ret :
    print('confirm')

Button(root, text='OK', width=20, height=10, command=doubleConfirm).pack(side=BOTTOM)


f = tkinter.filedialog.askopenfilename()
print(f)

root.mainloop()

'''
messagebox.askquestion    return yes/no

messagebox.askyesno       return True/False

messagebox.askretrycancel return True/False

messagebox.askyesnocancel return True/False/None
'''
