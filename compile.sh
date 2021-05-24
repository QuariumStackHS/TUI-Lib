g++ TUI.cpp -std=c++17 -c -o TUI.o
g++ main.cpp -std=c++17 -c -o main.o
g++ main.o TUI.o -o LIB/Prog