def main():
    inf = open('file.txt','r')
    outf = open('newfile.txt','w')

    for line in inf:
        print(line, file=outf, end='')

    print('Completed writel to newfile')

    
main()
