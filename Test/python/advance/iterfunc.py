with open('lambda.py') as fh:
  for line in iter(fh.readline,''):
    print(line)

fh2 = open('lambda.py')
for line in fh2:
  print(line.split())