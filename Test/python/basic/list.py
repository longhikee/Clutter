words = "the quick brown fox jumps over the lazy dog"
print(words)

list = "the quick brown fox jumps over the lazy dog".split()
print(list)
print(list[0])


info = [[c.upper(), c.lower(), len(c)] for c in list]
for data in info:
  print(data)
