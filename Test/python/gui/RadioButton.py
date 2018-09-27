from tkinter import *
root = Tk()

Radiobutton(root, text='python').pack()

v = IntVar()
v.set(1)
for i in range(3):
  Radiobutton(root, variable=v, text='tkinter', value=i).pack()

vLang = IntVar()
vOS = IntVar()
vLang.set(1)
vOS.set(2)
for i in [vLang, vOS] :
  for j in range(3):
    Radiobutton(root,
                variable=i,
		value=j,
		text='range' + str(j)
		).pack()
#不同组，个按钮互不影响

#4个按钮value=1，选中一个，其他三个也被选中
for i in range(3):
  Radiobutton(root,
              variable=v,
	      value=1,
	      text='testA' + str(i)
	      ).pack()

for i in range(3):
  Radiobutton(root,
              variable=v,
              value=i,
	      text='testB' + str(i)
	      ).pack()

root.mainloop()
