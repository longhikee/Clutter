o = range(25)
for i in o: print(i,end=' ')
print()

o = range(5,25,2)
for i in o: print(i,end=' ')
print()

class inclusive_range:
  def __init__(self,*args):
      numargs = len(args)
      if numargs < 1: raise TypeError('requre at least 1 param')
      elif numargs == 1:
        self.stop = args[0]
        self.step = 1
        self.start = 0
        
      elif numargs == 2:
        (self.start, self.stop) = args
        self.step = 1
        
      elif numargs == 3:
        (self.start, self.stop, self.step) = args
        
      else: raise TypeError('expected no more than 3 param')

  def __iter__(self):
    i = self.start
    while i <= self.stop:
      yield i
      i += self.step

obj = inclusive_range(1,10,1)
for i in obj: print(i,end=' ')
