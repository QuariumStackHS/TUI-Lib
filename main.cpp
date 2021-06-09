#include <TUI.hpp>
#include <Keys.h>

#include <stdio.h>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <termios.h>
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
        size_t pos = txt.find(ch);
        size_t initialPos = 0;
        strs.clear();

        // Decompose statement
        while (pos != std::string::npos)
        {
                strs.push_back(txt.substr(initialPos, pos - initialPos));
                initialPos = pos + 1;

                pos = txt.find(ch, initialPos);
        }

        // Add the last one
        strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

        return strs.size();
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

int compile(MSTS *OBJ, MSTS *SRC, MSTS *INCl, string cppV)
{
        vector<string> OBJs;
        vector<string> SRCs;
        vector<string> IN;
        split(INCl->_Value, IN, ' ');
        split(OBJ->_Value, OBJs, ' ');
        split(SRC->_Value, SRCs, ' ');
        //for(int i=0;OBJ)
        string includestring;
        int ret = 0;
        for (int i = 0; i < IN.size(); i++)
        {
                if (!((strcmp(IN[i].c_str(), " ") == 0) || (strcmp(IN[i].c_str(), "") == 0)))
                {
                        includestring += " -I" + IN[i];
                }
        }
        for (int i = 0; i < OBJs.size(); i++)
        {
                if (!((strcmp(OBJs[i].c_str(), " ") == 0) || (strcmp(OBJs[i].c_str(), "") == 0)))
                {
                        stringstream ss;
                        ss << "g++ -w -std=" << cppV << " -c -o " << OBJs[i] << " " << SRCs[i] << includestring;
                        ret += system(ss.str().c_str());
                        //cout << ss.str() << endl;

                        cout << ss.str() << endl;
                }
                else
                {
                        //cout<<"invalid"<<endl;
                }
        }
        return ret;
}
string Get_Data(string Dependancy, string Key)
{
        //Alias ='Value'\n

        string line;
        ifstream myfile(Dependancy);
        if (myfile.is_open())
        {

                while (getline(myfile, line))
                {
                        if (strcmp(line.c_str(), ""))
                        {
                                //cout << line << endl;

                                //char i;
                                //cin>>i;
                                string Alias = "";
                                string Value = "";

                                for (int i = 0; i < line.size(); i++)
                                {
                                        int Stage = 0;
                                        if (Stage == 0)
                                        {
                                                if ((line[i] == '='))
                                                {
                                                        //cout << "Stage 1 enclenched" << endl;
                                                        for (int k = i; k < line.size(); k++)
                                                        {
                                                                if ((line[k] == '\'') && (Stage == 0))
                                                                {
                                                                        Stage++;
                                                                }
                                                                if (Stage == 1)
                                                                {
                                                                        if (line[k] != '\'')
                                                                        {
                                                                                Value.push_back(line[k]);
                                                                        }

                                                                        else
                                                                        {
                                                                                i = line.size() + 1;
                                                                        }
                                                                }
                                                        }
                                                }
                                                else
                                                {
                                                        if (line[i] != ' ')
                                                                Alias.push_back(line[i]);
                                                }
                                        }
                                }
                                //cout << Value << " : " << Alias << Alias.size() << endl;
                                if (strcmp(Alias.c_str(), "") == 0)
                                {
                                }
                                else
                                {
                                        if (strcmp(Alias.c_str(), Key.c_str()) == 0)
                                        {
                                                return Value;
                                        }
                                }
                        }
                }
                //char fd;
                //cin>>fd;
                myfile.close();
        }

        else
                cout << "Unable to Load Dependancy\"" << Dependancy << "\"" << endl;
        return "";
}

int link(MSTS *OBJ, MSTS *LIBS, MSTS *Deps, string buildname, int buildT, string thisprog)
{
        vector<string> Dependancys;
        string Dependancys_libs;
        split(Deps->_Value, Dependancys, ' ');
        for (int i = 0; i < Dependancys.size(); i++)
        {
                if (strcmp(Dependancys[i].c_str(), "") != 0)
                {
                        string exename = Get_Data(Dependancys[i], "Config.Exe");
                        int buildtype;

                        try
                        {
                                buildtype = stoi(Get_Data(Dependancys[i], "Build.Type"));

                                string compileDepcommand = thisprog + " " + Dependancys[i] + " build";
                                switch (buildtype)
                                {
                                case 0:
                                        cout << "Dependancy \"" << Dependancys[i] << "\" as a builtype of 0" << endl;
                                        break;
                                case 1:

                                        system(compileDepcommand.c_str());
                                        Dependancys_libs += (" " + exename);
                                        break;
                                case 2:
                                        system(compileDepcommand.c_str());
                                        Dependancys_libs += (" " + exename);
                                        break;
                                default:
                                        break;
                                }
                        }
                        catch (const std::exception &e)
                        {
                        }
                }
        }
        stringstream ss;
        ss << "g++ " << OBJ->_Value << LIBS->_Value << "-o " << buildname << Dependancys_libs;
        switch (buildT)
        {
        case 0:
                /* code */
                break;
        case 1:
                ss << " -shared";
                break;
        case 2:
                ss << " -static";
                /* code */
                break;
        default:
                break;
        }
        //ss<<" &>> Logs.GP";
        cout << ss.str() << endl;
        system(ss.str().c_str());
}

DepTree *buildTree(string RGPFILE)
{
        vector<string> Dependancys;
        DepTree *MasterNode = new DepTree(5, 5);
        // cout<<Deps->_Value<<endl;
        //cout<<RGPFILE<<endl;
        vector<string> Fullpath;
        split(Get_Data(RGPFILE, "Config.Exe"), Fullpath, '/');
        MasterNode->name = Fullpath[Fullpath.size() - 1];
        vector<string> Dependancys_of_this;
        split(Get_Data(RGPFILE, "source.Deps"), Dependancys, ' ');
        for (int i = 0; i < Dependancys.size(); i++)
        {
                //cout<<Dependancys[i]<<endl;
                if (strcmp(Dependancys[i].c_str(), "") != 0)
                {

                        string exename = Get_Data(Dependancys[i], "Config.Exe");
                        //cout<<"c"<<exename<<endl;
                        //deps->name=exename;
                        //split(Get_Data(Dependancys[i], "source.Deps"), Dependancys_of_this, ' ');
                        DepTree *k = buildTree(Dependancys[i]);
                        MasterNode->AddChild(k);
                }
        }
        MasterNode->Visible = 1;

        return MasterNode;
}
int main(int argc, char **argv)
{
        string circlechar = "/|\\-";
        int XXindex = 0;
        //char**FakeArgs={"Begin:","<>","TT","TTTTT"};
        //Reltt_INT *Reltt=new Reltt_INT(argc,argv);
        MasterView *MF = new MasterView(MaxX, MaxY);
        string Fname = "Base.rgp";
        string command = "";
        if (argc == 2)
        {
                Fname = argv[1];
        }
        else if (argc == 3)
        {
                Fname = argv[1];
                command = argv[2];
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
        Ch.push_back("Deps");
        Ch.push_back("Git");
        Legend->add_Horizon("| W : ↑ | A : ← | S : ↓ | D : → | Enter : Edit | \\ : Back ", 25, 5);
        vign *IKD = new vign(Ch, 2, 1);

        EditorView *Config = new EditorView(3, 1);
        MSTS *Projectname = new MSTS("|Project name", "None", "Config.Project");
        MSTS *Exename = new MSTS("|Executable Name", "None", "Config.Exe");
        MSTS *AddLib = new MSTS("|Add Lib", "_", "");
        MSTS *AddDependancy = new MSTS("|Add Dependancy", "_", "");
        MSTS *AddInclude = new MSTS("|Add Include", "_", "");
        Config->add_MSTS(Projectname, 0); // ("|Project name:"+projectname,7,5);
        Config->add_MSTS(Exename, 1);     // ("|Project EXE :"+EXEname,8,5);
        Config->add_MSTS(AddLib, 2);
        Config->add_MSTS(AddDependancy, 3);
        Config->add_MSTS(AddInclude, 4);
        EditorView *gpp = new EditorView(3, 1);

        dropdownlist *buildtype = new dropdownlist(6, 1);
        dropdownlist *CompileBuild = new dropdownlist(6, 1);

        MSTS *CppVersion = new MSTS("|C++ Version", "c++17", "G++.C++");
        MSTS *Target = new MSTS("|Target (executable/shared/static)", "shared", "G++.Target");
        EditorView *source = new EditorView(6, 1);
        EditorView *Git = new EditorView(6, 1);
        MSTS *sourceFiles = new MSTS("|", "main.cpp", "source.files");
        MSTS *sourceTarget = new MSTS("|Add Src file", "_", "");
        source->add_MSTS(sourceTarget, 0);
        gpp->add_MSTS(CppVersion, 0);
        IKD->render();
        //IJ->add_Vertical("this is a View", 5, 5);
        //IJ->add_Horizon("Ctrl+C Compile | ESC Exit |", 18, 0);
        //IJ->add_Vertical("Reltt Editor",0,2);

        EditorView *addsrc = new EditorView(3, 1);

        EditorView *addobj = new EditorView(9, 1);
        EditorView *addDep = new EditorView(9, 1);
        EditorView *addinc = new EditorView(9, 1);

        MSTS *pathFiles = new MSTS("|Path to Source file", "_", "");
        MSTS *ObjName = new MSTS("|Obj-Name", "_", "");
        MSTS *Save = new MSTS("|", "Save", "");
        addsrc->add_MSTS(pathFiles, 0);
        addsrc->add_MSTS(ObjName, 1);
        addsrc->add_MSTS(Save, 2);
        MSTS *Objpath = new MSTS("|Path to Object(*.o/*.lib/*.so/*.dll/*.a)", "_", "");
        MSTS *SaveBtn = new MSTS("|", "Save Object", "");
        addobj->add_MSTS(Objpath, 0);
        addobj->add_MSTS(SaveBtn, 1);
        MSTS *DepPath = new MSTS("|Path to .rgp", "_", "");
        MSTS *DSaveBtn = new MSTS("|", "Save", "");
        addDep->add_MSTS(DepPath, 0);
        addDep->add_MSTS(DSaveBtn, 1);

        MSTS *INCPath = new MSTS("|Path to include", "_", "");
        MSTS *ISaveBtn = new MSTS("|", "Save", "");
        addinc->add_MSTS(INCPath, 0);
        addinc->add_MSTS(ISaveBtn, 1);

        addsrc->Visible = 0;
        buildtype->Visible = 0;
        CompileBuild->Visible = 0;
        MSTS *MSTS_Excutable = new MSTS("", "Executable", "");
        MSTS *MSTS_Shared = new MSTS("", "Shared", "");
        MSTS *MSTS_Static = new MSTS("", "Static", "");
        MSTS *MSTS_sourcefiles = new MSTS("|files", "", "source.cppfiles");
        MSTS *MSTS_objfiles = new MSTS("|objs", "", "source.cppobj");
        MSTS *MSTS_objLib = new MSTS("|Libs", "", "source.Libs");
        MSTS *MSTS_Dependancy = new MSTS("|Dependancys", "", "source.Deps");
        MSTS *MSTS_Includes = new MSTS("|includes", "", "source.includes");

        MSTS *MSTS_Git_Commit = new MSTS("|Commit", "_", "");
        EditorView *Git_Commit = new EditorView(9, 1);
        MSTS *MSTS_Git_Push = new MSTS("|Push", "_", "");
        EditorView *Git_Push = new EditorView(9, 1);
        MSTS *MSTS_Git_Fetch = new MSTS("|Fetch", "_", "");
        source->add_MSTS(MSTS_sourcefiles, 1);
        source->add_MSTS(MSTS_objfiles, 2);
        source->add_MSTS(MSTS_objLib, 3);
        source->add_MSTS(MSTS_Dependancy, 4);
        source->add_MSTS(MSTS_Includes, 5);

        MSTS *CommitMSG = new MSTS("Commit MSG", "_", "");
        MSTS *CommitButton = new MSTS("~", "Commit!", "");
        Git_Commit->add_MSTS(CommitMSG, 0);
        Git_Commit->add_MSTS(CommitButton, 1);

        Git->add_MSTS(MSTS_Git_Commit, 0);
        Git->add_MSTS(MSTS_Git_Push, 1);
        Git->add_MSTS(MSTS_Git_Fetch, 2);

        buildtype->Key = "|Build Type     ";
        buildtype->Alias = "Build.Type";
        buildtype->add_MSTS(MSTS_Excutable, 0);
        buildtype->add_MSTS(MSTS_Shared, 1);
        buildtype->add_MSTS(MSTS_Static, 2);
        View *Roue = new View();
        int Rouex = 1;
        int Rouey = 1;

        MSTS *BuildButton = new MSTS("", "Build", "");
        MSTS *CompileButton = new MSTS("", "Compile", "");
        MSTS *LinkButton = new MSTS("", "Link", "");
        CompileBuild->add_MSTS(BuildButton, 0);
        CompileBuild->add_MSTS(CompileButton, 1);
        CompileBuild->add_MSTS(LinkButton, 2);
        //MF->addView()
        addobj->Visible = 0;
        addinc->Visible = 0;
        addDep->Visible = 0;
        Git_Commit->Visible=0;
        DepTree *Project = buildTree(argv[1]);
        MF->addView(Git_Commit);
        MF->addView(Git);
        MF->addView(addDep);
        MF->addView(addobj);
        MF->addView(CompileBuild);
        MF->addView(addinc);
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

        int x, y = 0;
        x = 2;
        y = 2;
        string projectname;
        string EXEname;
        string sourcebuffer;
        string objbuffer;
        //when on zero you can navigate in menus
        int Lock = 0;
        MF->addView(Roue);
        //sourcebuffer;
        //objbuffer;

        if (strcmp(command.c_str(), "build") == 0)
        {
                compile(MSTS_objfiles, MSTS_sourcefiles, MSTS_Includes, gpp->Values[0]->_Value);
                link(MSTS_objfiles, MSTS_objLib, MSTS_Dependancy, Config->Values[1]->_Value, buildtype->current_index, argv[0]);
        }
        else
        {
                system("stty raw");
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
                                if ((Lock) && (((Config->current_index != 2) && (Config->current_index != 3) && (Config->current_index != 4)) && Config->current_index >= 0))
                                {
                                        Config->Values[Config->current_index]->_Value = buffer;
                                }
                                else if ((Config->current_index == 2) && (Lock))
                                {
                                        addobj->Visible = 1;

                                        Config->current_index = -1;
                                        Lock = 0;
                                }
                                else if ((Config->current_index == 3) && (Lock))
                                {
                                        addDep->Visible = 1;
                                        //addDep->render();

                                        Config->current_index = -2;
                                        Lock = 0;
                                }
                                else if ((Config->current_index == 4) && (Lock))
                                {
                                        addinc->Visible = 1;
                                        //addDep->render();

                                        Config->current_index = -3;
                                        Lock = 0;
                                }
                                else if (Config->current_index == -1)
                                {
                                        if (Lock)
                                        {
                                                if (addobj->current_index == 0)
                                                        addobj->Values[addobj->current_index]->_Value = buffer;
                                                else
                                                {
                                                        MSTS_objLib->_Value += addobj->Values[0]->_Value + ' ';
                                                        Lock = 0;
                                                }
                                        }
                                }
                                else if (Config->current_index == -2)
                                {
                                        if (Lock)
                                        {
                                                if (addDep->current_index == 0)
                                                        addDep->Values[addDep->current_index]->_Value = buffer;
                                                else
                                                {
                                                        MSTS_Dependancy->_Value += addDep->Values[0]->_Value + ' ';
                                                        Lock = 0;
                                                }
                                        }
                                }
                                else if (Config->current_index == -3)
                                {
                                        if (Lock)
                                        {
                                                if (addinc->current_index == 0)
                                                        addinc->Values[addinc->current_index]->_Value = buffer;
                                                else
                                                {
                                                        MSTS_Includes->_Value += addinc->Values[0]->_Value + ' ';
                                                        Lock = 0;
                                                }
                                        }
                                }
                                if ((Config->current_index == -1) && (addobj->Visible == 0))
                                {
                                        Config->current_index = 2;
                                }
                                if ((Config->current_index == -2) && (addDep->Visible == 0))
                                {
                                        Config->current_index = 3;
                                }
                                if ((Config->current_index == -3) && (addinc->Visible == 0))
                                {
                                        Config->current_index = 4;
                                }
                                gpp->clear();
                                gpp->Visible = 0;
                                Config->Visible = 1;
                                addinc->render();
                                addDep->render();
                                addobj->render();
                                Config->render();
                        }
                        //G++
                        if (IKD->current_index == 1)
                        {
                                addDep->clear();
                                addDep->Visible = 0;
                                addobj->clear();
                                addobj->Visible = 0;
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
                                if (gpp->current_index != -1)
                                {
                                        buildtype->isOn = 0;
                                }
                                buildtype->clear();
                                buildtype->render();
                                gpp->render();
                        }
                        //Source
                        if (IKD->current_index == 2)
                        {
                                CompileBuild->Visible = 0;
                                CompileBuild->clear();
                                buildtype->clear();
                                buildtype->Visible = 0;
                                gpp->clear();
                                gpp->Visible = 0;
                                if (Lock)
                                {
                                        if (source->current_index == -1)
                                        {
                                                if (ch != 13)
                                                        addsrc->Values[addsrc->current_index]->_Value = buffer;

                                                //addsrc->Values[addsrc->current_index]->_Value += buffer;
                                                addsrc->render();
                                        }
                                        else
                                        {
                                                source->Values[source->current_index]->_Value = buffer;
                                        }
                                }
                                if (addsrc->current_index == 2)
                                {
                                        if (ch == 13)
                                        {
                                                MSTS_sourcefiles->_Value += addsrc->Values[0]->_Value + " ";
                                                MSTS_objfiles->_Value += addsrc->Values[1]->_Value + " ";
                                                addsrc->current_index = 0;
                                        }
                                        //cout<<objbuffer<<sourcebuffer<<endl;
                                }
                                addsrc->render();
                                source->Visible = 1;

                                source->render();
                        }
                        //build
                        else if ((IKD->current_index == 3))
                        {
                                Project->Visible = 0;
                                Project->clear();
                                addsrc->Visible = 0;
                                addsrc->clear();
                                source->Visible = 0;
                                source->clear();
                                CompileBuild->clear();
                                CompileBuild->Visible = 1;
                                CompileBuild->ischoosing = 1;
                                if (ch == 13)
                                {
                                        int i = CompileBuild->current_index;
                                        switch (i)
                                        {
                                        case 0:
                                                //build
                                                compile(MSTS_objfiles, MSTS_sourcefiles, MSTS_Includes, gpp->Values[0]->_Value);
                                                link(MSTS_objfiles, MSTS_objLib, MSTS_Dependancy, Config->Values[1]->_Value, buildtype->current_index, argv[0]);
                                                /* code */
                                                break;
                                        case 1:
                                                //compile
                                                compile(MSTS_objfiles, MSTS_sourcefiles, MSTS_Includes, gpp->Values[0]->_Value);
                                                break;
                                        case 2:
                                                link(MSTS_objfiles, MSTS_objLib, MSTS_Dependancy, Config->Values[1]->_Value, buildtype->current_index, argv[0]);
                                                //link
                                                break;
                                        default:
                                                break;
                                        }
                                        Lock = 0;
                                }
                                CompileBuild->render();
                        }
                        else if (IKD->current_index == 4)
                        {
                                CompileBuild->Visible = 0;
                                CompileBuild->clear();

                                Project->Visible = 1;
                                Project->render();
                                Git->Visible = 0;
                                Git->clear();

                                MF->addView(Project);
                        }
                        else if (IKD->current_index == 5)
                        {
                                Project->Visible = 0;
                                Git->Visible = 1;
                                Git->render();
                                if (Git_Commit->Visible == 1 && Lock == 1)
                                {
                                        if (Git_Commit->current_index == 1)
                                        {
                                                string cmd = "git commit -a -m \"";
                                                cmd += Git_Commit->Values[0]->_Value + "\"";
                                                buffer = "";
                                                system(cmd.c_str());
                                                                                           Lock=0;
                                                Git_Commit->Visible=0;
                                                Git->current_index=0;
                                        }
                                        else
                                        {
                                                Git_Commit->Values[0]->_Value = buffer;
     
                                        }
                                        Git_Commit->render();
                                }
                                Git_Commit->render();
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
                                if (IKD->current_index == 0)
                                {

                                        if (Config->current_index == -1)
                                                Config->current_index = 2;
                                        else if (Config->current_index == -2)
                                                Config->current_index = 3;
                                        else if (Config->current_index == -3)
                                                Config->current_index = 4;

                                        addinc->Visible = 0;
                                        addobj->Visible = 0;
                                        addDep->Visible = 0;
                                }
                                else if (IKD->current_index == 2)
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

                                if (Git->Visible == 1 && Git->current_index >= 0)
                                {
                                        switch (Git->current_index)
                                        {
                                        case 0:
                                                Git->current_index = -1;
                                                Git_Commit->Visible = 1;

                                                break;
                                        case 1:

                                                break;
                                        case 2:

                                                break;

                                        default:
                                                break;
                                        }
                                }
                                if (buildtype->ischoosing == 1)
                                {
                                        buildtype->ischoosing = 0;
                                        buildtype->render();
                                        Lock = -1;
                                        gpp->current_index = 1;
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
                                else if (buildtype->Visible == 0 && gpp->current_index == -1)
                                {
                                        buildtype->ischoosing = 0;
                                }
                                else if ((addsrc->current_index == 2) && (addsrc->Visible == 1))
                                {
                                        //pathFiles->_Value+' ';
                                        //ObjName->_Value+' ';
                                }
                                else if (addsrc->current_index == 0 && Lock == 0)
                                {
                                        Lock = 1;
                                }
                                else if (IKD->current_index == 3)
                                {
                                }
                                else
                                {
                                        if (Lock == 1)
                                                Lock = 0;
                                        else if (Lock == 0)
                                                Lock = 1;
                                        buffer = "";
                                }
                                if (Lock == -1)
                                {
                                        Lock = 0;
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
                                        if (Config->current_index == -1)
                                        {
                                                if (!(addobj->current_index >= addobj->Values.size() - 1))
                                                        addobj->current_index++;
                                        }
                                        else if (Config->current_index == -2)
                                        {
                                                if (!(addDep->current_index >= addDep->Values.size() - 1))
                                                        addDep->current_index++;
                                        }
                                        else if (Config->current_index == -3)
                                        {
                                                if (!(addinc->current_index >= addinc->Values.size() - 1))
                                                        addinc->current_index++;
                                        }
                                        else if (!(Config->current_index >= Config->Values.size() - 1))
                                                Config->current_index++;
                                }
                                else if (IKD->current_index == 1)
                                {
                                        if (gpp->current_index == 0)
                                        {
                                                gpp->current_index = -1;
                                                buildtype->isOn = 1;
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
                                else if (IKD->current_index == 3)
                                {
                                        if (CompileBuild->ischoosing == 1)
                                        {
                                                if ((CompileBuild->current_index > 0))
                                                {
                                                        CompileBuild->current_index--;
                                                        CompileBuild->render();
                                                }
                                        }
                                }
                                else if (IKD->current_index == 5)
                                {
                                        if (Git_Commit->Visible)
                                        {
                                                if (Git_Commit->current_index < Git_Commit->Values.size())
                                                        Git_Commit->current_index++;
                                        }
                                        if (Git->Visible == 1)
                                        {
                                                if ((Git->current_index < Git->Values.size() - 1))
                                                {
                                                        Git->current_index++;

                                                        Git->render();
                                                }
                                        }
                                }
                        }
                        else if (((int)ch == (int)UP) && (Lock == 0))
                        {
                                if (IKD->current_index == 0)
                                {
                                        if (Config->current_index == -1)
                                        {
                                                if ((addobj->current_index > 0))
                                                        addobj->current_index--;
                                        }
                                        else if (Config->current_index == -2)
                                        {
                                                if ((addDep->current_index > 0))
                                                        addDep->current_index--;
                                        }
                                        else if (Config->current_index == -3)
                                        {
                                                if ((addinc->current_index > 0))
                                                        addinc->current_index--;
                                        }
                                        else if ((Config->current_index > 0))
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
                                        else if (!(gpp->current_index >= 0))
                                        {
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
                                else if (IKD->current_index == 3)
                                {
                                        if (CompileBuild->ischoosing == 1)
                                        {
                                                if (!(CompileBuild->current_index >= CompileBuild->EA.size() - 1))
                                                {
                                                        CompileBuild->current_index++;
                                                        CompileBuild->render();
                                                }
                                        }
                                }
                                else if (IKD->current_index == 5)
                                {
                                        if (Git_Commit->Visible)
                                        {
                                                if (Git_Commit->current_index > 0)
                                                {
                                                        Git_Commit->current_index--;
                                                }
                                        }
                                        if (Git->Visible = 1)
                                        {
                                                if (Git->current_index > 0)
                                                        Git->current_index--;
                                        }
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
}