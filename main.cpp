#include "TUI.hpp"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
int main()
{
    
    MasterView *MF = new MasterView(20, 40);
    View *I = new View();
    //I->add_Horizon("--------------------------", 0, 0);
    //I->add_Horizon("IP\t|\tDomaine\t|\tPort\t|\tName\0", 0, 0);
    //I->add_Horizon(" Home\t|\t80\t|\tThis", 1, 0);
    //I->add_Vertical("Reltt Runtime", 0, 0);
    View *IJ = new View();
    //IJ->add_Vertical("this is a View", 5, 5);
    IJ->add_Horizon("Ctrl+S Save | ESC Exit |", 18, 0);
    IJ->add_Vertical("Reltt Editor",0,2);
    MF->addView(I);
    MF->addView(IJ);
    
    //char i;
    string LargeBuffer;
    string buffer;
    char ch;
    system("stty raw");
    int x,y=0;
    x=2;
    y=2;
    while(1)
    {   
            //seting the terminal in raw mode

        
        MF->Render();
        system("clear");
        MF->Display();
        
        //sleep(1);
                    ch=getchar();
                    string V="Last char:"+to_string(ch);
                    IJ->add_Vertical(V,10,3);
            if((int)ch==(int)27){          //terminate or come out of raw mode on "~" pressed
            system("stty cooked");
            //while(1);//you may still run the code 
            exit(0); //or terminate
            }
            else if((int)ch==(int)19){
                char*Filename;
                cout<<"Enter Filename to save:";
                cin>>Filename;

            }
            else if((int)ch==(int)127){
                if(LargeBuffer.length()>=1){
                LargeBuffer.pop_back();
                }
                if(buffer.length()>=1)
                buffer.pop_back();
            }

            else if (ch=='\n')
            {y++;
            x=2;
            LargeBuffer+=buffer+"\n";
            buffer.clear();
            }
            
            buffer.push_back(ch);
        I->add_Horizon(buffer, y, x);

    }
}