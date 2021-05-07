# TUI-Lib
TUI-Lib by QuariumStackHS
Doc:
  0:Install Lib
 
  1: Views
    A "View" in Tui-Lib contain a vector of char and each char have a X, Y & C(the Letter it must print at X, Y)
    there is 2 methods:
      void add_Horizon(string, int Y, int X);
      void add_Vertical(string, int Y, int X);
  2: MasterView
    the MasterView is the terminal controler
    there is 3 methods:
      void Render();//make the next frame and put it in the Buffer
      void Display();//print the Buffer in terminal
      void addView(View *);//Register a pointer to a View;
    
