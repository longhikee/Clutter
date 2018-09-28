from tkinter import *
 
result = []
def get_text(event):
    result.append(event.char)
    text.delete('0.0', END)
    text.insert(END, ''.join(result))
    canv.create_text(20, 20, text=text.get("0.0", END), anchor=W, width=300)
     
 
root = Tk()
root.title("Tk 画布捕获键盘")
Label(root, text="请输入...").pack(side=TOP, fill=X)
canv = Canvas(root, width=400, height=300)
canv.pack(side=TOP, expand=YES, fill=BOTH)
text = Text(canv)
canv.focus_set()
canv.bind("<Key>", get_text)
root.mainloop()
