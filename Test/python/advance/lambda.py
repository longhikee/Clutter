def calc(x):
  return x*2

print(calc(3))


########################


t = lambda x: x*2
print(t(3))


result = lambda x,y: (x+y, x-y)

print(result(15,3))
print(result(15,3)[1])
