from tkinter import *
root = Tk()
Button(root,text='A').pack(side=LEFT,expand=YES,fill=Y)
Button(root,text='B').pack(side=TOP,expand=YES,fill=BOTH)
Button(root,text='C').pack(side=RIGHT,expand=YES,fill=NONE)
Button(root,text='D').pack(side=LEFT,expand=NO,fill=Y)
Button(root,text='E').pack(side=TOP,ipadx=10,expand=YES,fill=BOTH)
Button(root,text='F').pack(side=BOTTOM,pady=10,expand=YES)
Button(root,text='G').pack(anchor=SE)
root.mainloop()

'''
　　side:按扭停靠在窗口的哪个位置

　　　　left: 左

　　　　top: 上

　　　　right: 右

　　　　botton: 下

　　fill:填充

　　　　x:水平方向填充

　　　　y:竖直方向填充

　　　　both:水平和竖直方向填充

　　　　none:不填充

　　expand:

　　　　yes:扩展整个空白区

　　　　no:不扩展

　　anchor:

　　　　N:北  下

　　　　E:东  右

　　　　S:南 下

　　　　W:西 左

　　　　CENTER:中间

　　padx:x方向的外边距

　　pady:y方向的外边距

　　ipadx:x方向的内边距

　　ipady：y方向的内边距
'''
