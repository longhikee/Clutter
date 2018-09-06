def append_item(a=1, b=[]):
  b.append(a)
  print(b)

append_item(a=1)
append_item(a=2)
append_item(a=5,b=[])
append_item(a=6,b=[8,9])
append_item(a=7)


def init_item(c=1, d=None):
    if d is None:
        d=[]
    d.append(c)
    print(d)

init_item(c=1)
init_item(c=3)
init_item(c=5,d=[1,2])
