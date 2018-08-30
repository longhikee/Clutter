import operator
getseconditem = operator.itemgetter(1)
list = ['a','b','c','d']
print(getseconditem(list))


print(operator.itemgetter(1,2,5)('abcdefg'))
