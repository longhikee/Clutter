def main():
  try:
    for line in readfile('exception.py'): print(line.strip())
  except IOError as e:
    print('cannot read file: ',e)
  except ValueError as e:
    print('wrong format exception: ', e)

def readfile(filename):
  if filename.endswith('.txt'):
    fh = open(filename)
    return fh.readlines()
  else:
    raise ValueError('Filename must end with .txt')
  
def test():
  try:
    print("Let's")
    raise NameError("thre")
  except NameError:
    print("An ex")
    raise
  else:
    print("he again")
  finally:
    print("final")

#main()
test()
