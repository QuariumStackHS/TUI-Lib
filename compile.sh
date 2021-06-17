g++ src/TUI.cpp -std=c++17 -c -o .cgp/TUI.o -Iinclude -w
g++ src/main.cpp -std=c++17 -c -o .cgp/main.o -Iinclude -w
g++ src/SHA1.cpp -std=c++17 -c -o .cgp/SHA1.o -Iinclude -w
g++ .cgp/main.o .cgp/TUI.o -o Build/cgp .cgp/SHA1.o 

g++ src/CGPInstaller.cpp -std=c++17 -c -o .cgp/ins.o -Iinclude -w

g++ .cgp/ins.o .cgp/TUI.o -o .cgp/install-cgp