g++ TUI.cpp -std=c++17 -c -o TUI.o -Iinclude -w
g++ main.cpp -std=c++17 -c -o main.o -Iinclude -w
g++ main.o TUI.o -o Build/cgp