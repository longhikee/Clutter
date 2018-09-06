import os
import shutil
from os import path

if path.exists("os.py"):
    src = path.realpath("os.py")
else:
    src="no file with this name"

print(src, end='  ###  \n')

location,filename = path.split(src)
print(location, end='  ####  ')
print(filename)

