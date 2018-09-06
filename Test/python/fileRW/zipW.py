import zipfile

fh = zipfile.ZipFile('mydata.zip', 'w')

fh.write('file.txt')
fh.write('newfile.txt')

