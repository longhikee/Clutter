from tkinter import *
master = Tk()

def callback():
  print("click!")

#b = Button(master, text='click', command=callback)
#b = Button(master, text='disable', state=DISABLED)
#b = Button(master, text='size', state=DISABLED, padx=59, pady=99)
b = Button(master, text='size', state=DISABLED, bg='yellow', fg='red', font=("Helvetica", 16))

'''
f = Frame(master, height=320, width=320)
f.pack()
b = Button(f, text='button')
b.pack(fill=BOTH, expand=1)
'''

#b = Button(master, text='longtext1234567890987654321234567890987654321', anchor=W, justify=LEFT, padx=2)

#b.config(relief=SUNKEN)

#b = Button(master, text=('click','me'), command=callback, padx =40, pady=60, background='#ffff00', relief=GROOVE, underline=2)

#b = Button(master, text='click', command=callback, width=10, height=12, anchor=SE)

b.pack()
mainloop()

'''
 1 #coding=gbk
 2 
 3 activebackground, activeforeground:当按钮被激活时所使用的颜色
 4 anchor:控制按钮上内容的位置。使用N, NE, E, SE, S, SW, W, NW, or CENTER这些值之一。默认值是CENTER。
 5 background (bg), foreground (fg):按钮的颜色。默认值与特定平台相关。
 6 bitmap:显示在窗口部件中的位图。如果image选项被指定了，则这个选项被忽略。下面的位图在所有平台上都有 效：error, gray75, gray50, gray25, gray12, hourglass, info, questhead, question, 和 warning.
 7 
 8 borderwidth (bd):按钮边框的宽度。默认值与特定平台相关。但通常是1或2象素。
 9 command:当按钮被按下时所调用的一个函数或方法。所回调的可以是一个函数、方法或别的可调用的Python对象。
10 cursor:当鼠标移动到按钮上时所显示的光标。
11 default:如果设置了，则按钮为默认按钮。
12 disabledforeground:当按钮无效时的颜色。
13 image:在部件中显示的图象。如果指定，则text和bitmap选项将被忽略。
14 justify:定义多行文本如何对齐。可取值有：LEFT, RIGHT, 或 CENTER。
15 padx, pady:指定文本或图象与按钮边框的间距。
16 state:按钮的状态：NORMAL, ACTIVE 或 DISABLED。默认值为NORMAL。
17 relief:边框的装饰。通常按钮按下时是凹陷的，否则凸起。另外的可能取值有GROOVE, RIDGE, 和 FLAT。
18 text:显示在按钮中的文本。文本可以是多行。如果bitmaps或image选项被使用，则text选项被忽略
19 textvariable:
20 underline:在文本标签中哪个字符加下划线。默认值为-1，意思是没有字符加下划线
21 width, height:按钮的尺寸。如果按钮显示文本，尺寸使用文本的单位。如果按钮显示图象，尺寸以象素为单位（或屏幕的单位）。如果尺寸没指定，它将根据按钮的内容来计算。


'''
