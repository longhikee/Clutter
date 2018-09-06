import sys
old = sys.stdout
sys.stdout = open('tmp.txt','w')
print('test>>>>>>>>>>>>>>>>>>>>>')

sys.stdout = old
print('test<<<<<<<<<<<<<<')
