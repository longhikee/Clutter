from tkinter import *
root = Tk()

t1 = Toplevel()
Label(t1, text='hello label').pack()
t1.title('hello Toplevel')
t1.geometry('400x300')

mbYes,mbYesNo,mbYesNoCancel,mbYesNoAbort = 0,1,2,4
def MessageBox():
  mbType = mbYesNo
  textShow = 'Yes'
  if mbType == mbYes:
    textShow = 'Yes'
  elif mbType == mbYesNo:
    textShow = 'YesNo'
  elif mbType == mbYesNoCancel:
    textShow = 'YesNoCancel'
  elif mbType == mbYesNoAbort:
    textShow == 'YesNoAbort'
  t = Toplevel(height=200, width=400)
  Label(t, text=textShow).pack()

Button(root, text='click me', command=MessageBox).pack()

root.mainloop()
