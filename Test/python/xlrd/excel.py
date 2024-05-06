import xlrd


#file="Worksheet.xlsx"
file="中文.xlsx"

print("file name: " + file)

workbook = xlrd.open_workbook(file)

print("sheet name: ")
#print(workbook.sheet_names())
for s in workbook.sheet_names():
    print(s)

table = workbook.sheet_by_index(0)
rows = table.nrows
print("there is " + str(rows) + " rows")
for i in range(0, rows):
    print(table.row_values(i))

cols = table.ncols
print("First colum: ")
col = table.col_slice(0)
print(col)

print("data type: ")
print(table.col_types(0, 0, rows))

workbook.release_resources()
