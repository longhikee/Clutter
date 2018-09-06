import os
import sys
import datetime


print(sys.platform)
print(os.name)
print(os.getenv("path"))
print(os.getcwd())

now = datetime.datetime.now()
print(now)
print(now.year,now.month,now.date,now.hour)

