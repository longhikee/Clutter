import sys

print("script name is: ",sys.argv[0])

try:
    print("script first argument passed is ", sys.argv[1])

except:
    print("there is no more arguments passed in")

