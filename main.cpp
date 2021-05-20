#include "TUI.hpp"
#include "Keys.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
class MSTS
{
public:
        MSTS(string Key, string Value);
        string _Key;
        string _Value;
};
MSTS::MSTS(string Key, string Value)
{
        this->_Key = Key;
        this->_Value = Value;
}
class vign : public View
{
public:
        vign(vector<string>, int, int);
        void render();
        int bigestComb = 0;
        vector<string> Comb;
        int current_index = 0;
        int x;
        int y;
};
class EditorView : public View
{
public:
        vector<MSTS *> Values;
        int current_index = 0;
        int x;
        int y;
        EditorView(int, int);
        void render();
        void add_MSTS(MSTS *, int);
};
void EditorView::render()
{
        this->clear();
        for (int i = 0; i < Values.size(); i++)
        {
                string Data = "";
                if (this->current_index == i)
                {
                        Data = Values[i]->_Key + " : " + YELLOW + Values[i]->_Value + RESET;
                }
                else
                {
                        Data = Values[i]->_Key + " : " + Values[i]->_Value;
                }

                this->add_Horizon(Data, this->x + i, this->y);
        }
}
void EditorView::add_MSTS(MSTS *data, int index)
{
        Values.insert(Values.begin() + index, data);
}
EditorView::EditorView(int XX, int YY)
{
        this->x = XX;
        this->y = YY;
}

vign::vign(vector<string> comb, int xX, int yY)
{
        for (int i = 0; i < comb.size(); i++)
        {
                int nyt = comb[i].size();
                if (nyt > this->bigestComb)
                {
                        this->bigestComb = nyt;
                }
                this->Comb.push_back(comb[i]);
        }
        this->x = xX;
        this->y = yY;
}
void vign::render()
{
        string vignette = "";

        for (int i = 0; i < this->Comb.size(); i++)
        {
                if (i == this->current_index)
                {
                        vignette.append(((string) "|").append(BOLDBLUE) + this->Comb[i] + RESET);
                }
                else
                {
                        vignette.append(((string) "|") + this->Comb[i]);
                }
        }
        vignette.append("|");
        this->add_Horizon(vignette, this->x, this->y);
}
char getch()
{
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
                perror("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror("tcsetattr ~ICANON");
        return (buf);
}
/*
        Reltt.exe
<-|config|Objects|Linking|->





*/
int main()
{

        MasterView *MF = new MasterView(MaxX, MaxY);
        View *I = new View();
        //I->add_Horizon("--------------------------", 0, 0);
        //I->add_Horizon("IP\t|\tDomaine\t|\tPort\t|\tName\0", 0, 0);
        //I->add_Horizon(" Home\t|\t80\t|\tThis", 1, 0);
        //I->add_Vertical("Reltt Runtime", 0, 0);
        View *IJ = new View();
        View *errors = new View();
        View *Legend = new View();
        vector<string> Ch;
        Ch.push_back("Config");
        Ch.push_back("G++");
        Ch.push_back("Objects");
        Ch.push_back("Linking");
        Legend->add_Horizon("| W : ↑ | A : ← | S : ↓ | D : → | Enter : Edit |", 25, 5);
        vign *IKD = new vign(Ch, 6, 5);

        EditorView *Config = new EditorView(7, 5);
        MSTS *Projectname = new MSTS("Project name", "None");
        MSTS *Exename = new MSTS("Executable Name", "None");
        Config->add_MSTS(Projectname, 0); // ("|Project name:"+projectname,7,5);
        Config->add_MSTS(Exename, 1);     // ("|Project EXE :"+EXEname,8,5);
        View *gpp = new View();

        IKD->render();
        //IJ->add_Vertical("this is a View", 5, 5);
        //IJ->add_Horizon("Ctrl+C Compile | ESC Exit |", 18, 0);
        //IJ->add_Vertical("Reltt Editor",0,2);

        MF->addView(I);
        MF->addView(IJ);
        MF->addView(IKD);
        MF->addView(Legend);

        //char i;
        string LargeBuffer;
        string buffer;
        char ch;
        system("stty raw");
        int x, y = 0;
        x = 2;
        y = 2;
        string projectname;
        string EXEname;
        //when on zero you can navigate in menus
        int Lock = 0;
        while (1)
        {
                MF->clear();
                //seting the terminal in raw mode

                if (IKD->current_index == 0)
                {
                        //MF->addView()
                        //Projectname->_Value=to_string(Config->current_index);
                        if (Lock)
                        {
                                Config->Values[Config->current_index]->_Value = buffer;
                        }
                        MF->RemoveView(gpp);
                        MF->addView(Config);

                        Config->render();
                }
                if (IKD->current_index == 1)
                {
                        Config->clear();
                        MF->RemoveView(Config);
                        MF->addView(gpp);
                        gpp->add_Horizon("|G++ C++ ISO :", 7, 5);
                }

                MF->Render();
                MF->addView(IJ);
                MF->clear();
                MF->Render();
                system("clear");
                MF->Display();

                //sleep(1);
                ch = getchar();
                string V = "Last char:" + to_string(ch);

                IJ->clear();
                IJ->add_Horizon(V, 39, 5);
                //for(int hd=0;hd<errors->Chars.size();)
                //errors->Chars[hd]->Char=' ';
                if ((int)ch == (int)27)
                { //terminate or come out of raw mode on "~" pressed
                        system("stty cooked");
                        //while(1);//you may still run the code
                        exit(0); //or terminate
                }
                else if (((int)ch == (int)Left) && (Lock == 0))
                {
                        if (IKD->current_index == 0)
                        {
                                errors->add_Horizon("<-Max index", 15, 6);
                        }
                        else
                        {
                                IKD->current_index--;
                                IKD->render();
                        }
                }
                else if ((int)ch == (int)13)
                {
                        if (Lock == 1)
                                Lock = 0;
                        else
                                Lock = 1;
                        buffer = "";
                }
                else if (((int)ch == (int)Down) && (Lock == 0))
                {
                        if (IKD->current_index == 0)
                        {
                                if (!(Config->current_index >= Config->Values.size() - 1))
                                        Config->current_index++;
                        }
                }
                else if (((int)ch == (int)UP) && (Lock == 0))
                {
                        if (IKD->current_index == 0)
                        {
                                if ((Config->current_index > 0))
                                        Config->current_index--;
                        }
                }
                else if (((int)ch == (int)100) && (Lock == 0))
                {
                        if (IKD->current_index == Ch.size() - 1)
                        {
                                errors->add_Horizon("Max index->", 15, 6);
                        }
                        else
                        {
                                IKD->current_index++;
                                IKD->render();
                        }
                }
                else if ((int)ch == (int)127)
                {
                        if (LargeBuffer.length() >= 1)
                        {
                                LargeBuffer.pop_back();
                        }
                        if (buffer.length() >= 1)
                                buffer.pop_back();
                }
                else
                {
                        buffer.push_back(ch);
                }

                MF->RemoveView(IJ);
                I->add_Horizon(buffer, y, x);
        }
}