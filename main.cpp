#include "TUI.hpp"
#include "Keys.h"

#include <stdio.h>

#include <time.h>
#include <unistd.h>
#include <termios.h>

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
int main(int argc, char **argv)
{
        string circlechar = "/|\\-\\-";
        int XXindex = 0;
        //char**FakeArgs={"Begin:","<>","TT","TTTTT"};
        //Reltt_INT *Reltt=new Reltt_INT(argc,argv);
        MasterView *MF = new MasterView(MaxX, MaxY);
        string Fname = "Base";
        if (argc >= 2)
        {
                Fname = argv[1];
        }

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
        Ch.push_back("Source");
        Ch.push_back("Build");
        Legend->add_Horizon("| W : ↑ | A : ← | S : ↓ | D : → | Enter : Edit | \\ : Back ", 25, 5);
        vign *IKD = new vign(Ch, 6, 5);

        EditorView *Config = new EditorView(7, 5);
        MSTS *Projectname = new MSTS("|Project name", "None", "Config.Project");
        MSTS *Exename = new MSTS("|Executable Name", "None", "Config.Exe");
        Config->add_MSTS(Projectname, 0); // ("|Project name:"+projectname,7,5);
        Config->add_MSTS(Exename, 1);     // ("|Project EXE :"+EXEname,8,5);
        EditorView *gpp = new EditorView(7, 5);

        dropdownlist *buildtype = new dropdownlist(10, 5);

        MSTS *CppVersion = new MSTS("|C++ Version", "c++17", "G++.C++");
        MSTS *Target = new MSTS("|Target (executable/shared/static)", "shared", "G++.Target");
        EditorView *source = new EditorView(7, 5);
        MSTS *sourceFiles = new MSTS("|", "main.cpp", "source.files");
        MSTS *sourceTarget = new MSTS("|Add Src file", "_", "");
        source->add_MSTS(sourceTarget, 0);
        gpp->add_MSTS(CppVersion, 0);
        IKD->render();
        //IJ->add_Vertical("this is a View", 5, 5);
        //IJ->add_Horizon("Ctrl+C Compile | ESC Exit |", 18, 0);
        //IJ->add_Vertical("Reltt Editor",0,2);

        EditorView *addsrc = new EditorView(8, 5);
        MSTS *pathFiles = new MSTS("|Path to Source file", "_", "");
        MSTS *ObjName = new MSTS("|Obj-Name", "_", "");
        MSTS *Save = new MSTS("|", "Save", "");
        addsrc->add_MSTS(pathFiles, 0);
        addsrc->add_MSTS(ObjName, 1);
        addsrc->add_MSTS(Save, 2);
        addsrc->Visible = 0;
        buildtype->Visible = 0;
        MSTS *MSTS_Excutable = new MSTS("", "Executable", "");
        MSTS *MSTS_Shared = new MSTS("", "Shared", "");
        MSTS *MSTS_Static = new MSTS("", "Static", "");
        buildtype->Key = "|Build Type     ";
        buildtype->Alias = "Build.Type";
        buildtype->add_MSTS(MSTS_Excutable, 0);
        buildtype->add_MSTS(MSTS_Shared, 1);
        buildtype->add_MSTS(MSTS_Static, 2);
        View *Roue = new View();
        int Rouex = 5;
        int Rouey = 5;
        //MF->addView()
        MF->addView(addsrc);
        MF->addView(source);
        MF->addView(I);
        MF->addView(IJ);
        MF->addView(IKD);
        MF->addView(Legend);
        MF->addView(Config);
        MF->addView(gpp);
        MF->addView(buildtype);
        MF->Load(Fname);
        Config->Visible = 0;

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
        MF->addView(Roue);
        while (1)
        {
                MF->clear();
                string sdf = "";
                sdf += circlechar[XXindex];
                Roue->add_Horizon(sdf, Rouex, Rouey);
                if (circlechar.size() - 1 == XXindex)
                {
                        XXindex = 0;
                }
                else
                {
                        XXindex++;
                }
                //seting the terminal in raw mode
                //Config
                if (IKD->current_index == 0)
                {
                        buildtype->clear();
                        buildtype->Visible = 0;
                        //MF->addView()
                        //Projectname->_Value=to_string(Config->current_index);
                        if (Lock)
                        {
                                Config->Values[Config->current_index]->_Value = buffer;
                        }
                        gpp->clear();
                        gpp->Visible = 0;
                        Config->Visible = 1;

                        Config->render();
                }
                //G++
                if (IKD->current_index == 1)
                {
                        addsrc->clear();
                        addsrc->Visible = 0;
                        Config->clear();
                        Config->Visible = 0;
                        source->clear();
                        source->Visible = 0;
                        buildtype->Visible = 1;

                        if (Lock)
                        {
                                if (gpp->current_index == 0)
                                {
                                        gpp->Values[gpp->current_index]->_Value = buffer;
                                }
                        }
                        gpp->Visible = 1;
                        if(gpp->current_index!=-1){
                                buildtype->isOn=0;
                        }
                        buildtype->clear();
                        buildtype->render();
                        gpp->render();
                }
                //Source
                if (IKD->current_index == 2)
                {
                        buildtype->clear();
                        buildtype->Visible = 0;
                        gpp->clear();
                        gpp->Visible = 0;
                        if (Lock)
                        {
                                if (source->current_index == -1)
                                {
                                        addsrc->Values[addsrc->current_index]->_Value = buffer;
                                        addsrc->render();
                                }
                                else
                                {
                                        source->Values[source->current_index]->_Value = buffer;
                                }
                        }
                        addsrc->render();
                        source->Visible = 1;

                        source->render();
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
                IJ->add_Horizon(V, 23, 5);
                //for(int hd=0;hd<errors->Chars.size();)
                //errors->Chars[hd]->Char=' ';
                if ((int)ch == (int)27)
                { //terminate or come out of raw mode on "~" pressed
                        system("stty cooked");
                        //while(1);//you may still run the code
                        exit(0); //or terminate
                }
                else if ((int)ch == (int)92)
                {
                        if (IKD->current_index == 2)
                        {
                                addsrc->Visible = 0;
                                source->current_index = 0;
                        }
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
                        if (buildtype->ischoosing == 1){
                                buildtype->ischoosing = 0;
                                buildtype->render();
                                Lock = -1;
                                gpp->current_index =1;
                        }
                        if ((source->current_index == 0) && (IKD->current_index == 2))
                        {
                                addsrc->Visible = 1;
                                addsrc->render();
                                source->current_index = -1;
                        }
                        else if (buildtype->Visible == 1 && gpp->current_index == -1)
                        {
                                buildtype->ischoosing = 1;

                        }
                        else if (buildtype->Visible == 0 && gpp->current_index == -1){
                                buildtype->ischoosing = 0;

                        }
                        else
                        {
                                if (Lock == 1)
                                        Lock = 0;
                                else if(Lock==0)
                                        Lock = 1;
                                buffer = "";
                        }
                        if (Lock==-1){
                                Lock=0;
                        }
                }
                else if ((int)ch == (int)19)
                {
                        MF->Save(Fname);
                }
                else if (((int)ch == (int)Down) && (Lock == 0))
                {
                        if (IKD->current_index == 0)
                        {
                                if (!(Config->current_index >= Config->Values.size() - 1))
                                        Config->current_index++;
                        }
                        else if (IKD->current_index == 1)
                        {
                                if (gpp->current_index == 0)
                                {
                                        gpp->current_index = -1;
                                        buildtype->isOn=1;
                                        buildtype->render();
                                }
                                else if (buildtype->ischoosing == 1)
                                {
                                                                                if ((buildtype->current_index > 0))
                                        {
                                                buildtype->current_index--;
                                                buildtype->render();
                                        }

                                }
                                else if (!(gpp->current_index >= gpp->Values.size() - 1))
                                        gpp->current_index++;
                        }
                        else if (IKD->current_index == 2)
                        {
                                if ((addsrc->Visible == 1))
                                {
                                        if (!(addsrc->current_index >= addsrc->Values.size() - 1))
                                                addsrc->current_index++;
                                }
                                else if (!(source->current_index >= source->Values.size() - 1))
                                        source->current_index++;
                        }
                }
                else if (((int)ch == (int)UP) && (Lock == 0))
                {
                        if (IKD->current_index == 0)
                        {
                                if ((Config->current_index > 0))
                                        Config->current_index--;
                        }
                        if (IKD->current_index == 1)
                        {
                                if ((gpp->current_index > 0))
                                        gpp->current_index--;
                                else if (buildtype->ischoosing == 1)
                                {
                                        if (!(buildtype->current_index >= buildtype->EA.size() - 1))
                                        {
                                                buildtype->current_index++;
                                                buildtype->render();
                                        }
                                }
                                else if(!(gpp->current_index>=0)){
                                        gpp->current_index++;
                                }
                        }
                        if (IKD->current_index == 2)
                        {
                                if (addsrc->Visible == 1)
                                {
                                        if ((addsrc->current_index > 0))
                                                addsrc->current_index--;
                                }
                                else if ((source->current_index > 0))
                                        source->current_index--;
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