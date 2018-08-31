::g++ common\Trace.cc -shared -Icommon  -fPIC -o libTrace.dll
::g++ Main.cc Crypt.cc -lTrace -LD:\workspace\Test\cryption -Icommon -O2

g++ Crypt.cc -c -I%common% -o bin\Crypt.o -O2
g++ Main.cc -c -I%common% -o bin\Main.o -O2
g++ bin\crypt.o bin\Main.o %common%\Trace.o -I%common% -o crypt.exe -O2
