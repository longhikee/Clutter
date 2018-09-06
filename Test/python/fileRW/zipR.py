import zipfile
fread = zipfile.ZipFile('mydata.zip','r')
names = fread.namelist()
for name in names:
    print('processing %s' %name)

    fread2 = fread.open(name)
    contents=fread2.read()
    print(contents)
