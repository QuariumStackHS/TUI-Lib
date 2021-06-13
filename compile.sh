g++ TUI.cpp -std=c++17 -c -o TUI.o -Iinclude -w
g++ main.cpp -std=c++17 -c -o main.o -Iinclude -w
g++ SHA1.cpp -std=c++17 -c -o SHA1.o -Iinclude -w
g++ CLAB.cpp -std=c++17 -c -o Clab.o -Iinclude -w
g++ main.o TUI.o -o Build/cgp SHA1.o Clab.o

g++ CGPInstaller.cpp -std=c++17 -c -o ins.o -Iinclude -w

g++ ins.o TUI.o -o CGPINSTALL