def main():
    f = open('file.txt')

    #read file
    for line in f:
        print(line, end='')
        print(line.split())
    
main()
