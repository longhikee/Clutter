counter = 0
try:
  fh = open('file.txt')
except IOError as e:
  print('could not open this file', e)
  counter += 1
finally:
  print('all work was done')
  print('there was %d errors in the process' % counter)
