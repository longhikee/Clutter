print(sorted([2,3,4,7,1,6]))
print(sorted(['a','g','c','h','z','i']))

items=['bread','eggs','milk','cheese']
print("sorted(items)~~~~")
print(sorted(items))
items.sort()
print("item.sort()~~~~")
print(items)
items.sort(key=lambda x: x,reverse=True)
print("item.sort() in reverse~~~")
print(items)


books = [('book1','a',10),('book2','b',8),('book3','c',6)]
#the third element sorted
sorted(books,key=lambda books:books[2])
print(books)
print(sorted(books,key=lambda books:books[2]))
