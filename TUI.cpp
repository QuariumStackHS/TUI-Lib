#include "TUI.hpp"
#include <sstream>
int Debug = 0;
View::ViewChar::ViewChar(int X, int Y, char C)
{
    this->Char = C;
    this->Xpos = X;
    this->Ypos = Y;
}
View::View()
{
}
void View::render()
{
}
string View::SaveAll()
{
    return "";
}
View::ViewChar::ViewChar(int X, int Y, char C, View *Master)
{
    this->Char = C;
    this->Xpos = X;
    this->Ypos = Y;
    this->_MasterView = Master;
}
void View::add_Vertical(string str, int y, int x)
{
    int iY = y;
    int IX = 0;
    int iscalc = 0;
    for (int iX = x; iX < x + strlen(str.c_str()); iX++)
    {
        bool is = 0;
        for (int i = 0; i < this->Chars.size(); i++)
        {
            if ((this->Chars[i]->Ypos == iX) && (this->Chars[i]->Xpos == iY))
            {
                this->Chars[i]->Char = str[iX - x];
                this->Chars[i]->_MasterView = this;
                is = 1;
            }
        }
        if (is == 0)
        {

            ViewChar *C = new View::ViewChar(iY, iX, str[iX - x], this);
            this->Chars.push_back(C);
        }
    }
}
void View::add_Horizon(string str, int y, int x)
{
    int iY = y;
    int IX = 0;
    int iscalc = 0;
    for (int iX = x; iX < x + strlen(str.c_str()); iX++)
    {
        if ((int)str[iX - x] == (int)'\n')
        {
            iscalc = iX - x + 1;
            iY++;
        }
        else
        {
            bool is = 0;
            for (int i = 0; i < this->Chars.size(); i++)
            {
                if ((this->Chars[i]->Xpos == iX) && (this->Chars[i]->Ypos == iY))
                {
                    this->Chars[i]->Char = str[iX - x];
                    this->Chars[i]->_MasterView = this;
                    is = 1;
                }
            }
            if (is == 0)
            {
                ViewChar *C = new View::ViewChar(iX - iscalc, iY, str[iX - x], this);
                this->Chars.push_back(C);
            }
        }
    }
}

void MasterView::Display()
{
    for (int i = 0; i < MAXx; i++)
    {
        if (Debug)
        {
            cout << i << "|";
        }
        cout << this->Buffer[i] << "\n\r";
    }
}

void MasterView::Render()
{

    for (int i = 0; i < this->Views.size(); i++)
    {
        if (this->Views[i]->Visible)
        {
            this->Views[i]->render();
            for (int j = 0; j < this->Views[i]->Chars.size(); j++)
            {
                for (int k = 0; k < this->Views[i]->Chars[j]->Xpos; k++)
                {
                    if (this->Buffer[this->Views[i]->Chars[j]->Ypos][k] == '\0')
                        this->Buffer[this->Views[i]->Chars[j]->Ypos][k] = ' ';
                }
                this->Buffer[this->Views[i]->Chars[j]->Ypos][this->Views[i]->Chars[j]->Xpos] = this->Views[i]->Chars[j]->Char;
                if (Debug)
                    cout << this->Views[i]->Chars[j]->Char << "|[" << this->Views[i]->Chars[j]->Xpos << "][" << this->Views[i]->Chars[j]->Ypos << "]" << endl;
            }
        }
    }
}
void MasterView::RemoveView(View *SD)
{
    for (int i = 0; i < this->Views.size(); i++)
    {
        if (this->Views[i] == SD)
        {
            for (int j = 0; j < this->Views[i]->Chars.size(); j++)
            {
                this->Buffer[this->Views[i]->Chars[j]->Ypos][this->Views[i]->Chars[j]->Xpos] = ' ';
            }
            this->Views.erase(this->Views.begin() + i);
        }
    }
}
void MasterView::RemoveView(EditorView *SD)
{
    for (int i = 0; i < this->DATAC.size(); i++)
    {
        if (this->DATAC[i] == SD)
        {
            for (int j = 0; j < this->DATAC[i]->Chars.size(); j++)
            {
                this->Buffer[this->DATAC[i]->Chars[j]->Ypos][this->DATAC[i]->Chars[j]->Xpos] = ' ';
            }
            this->DATAC.erase(this->DATAC.begin() + i);
        }
    }
}
void View::clear()
{
    this->Chars.erase(this->Chars.begin(), this->Chars.end());
}
MasterView::MasterView(int maxX, int maxY)
{
    //this->IN=;
    this->MAXx = maxX;
    this->MAXy = maxY;
}
void MasterView::Save(string Filename)
{
    vector<string> Did;
    ofstream myfile;
    myfile.open(Filename.c_str(), ios_base::out);
    stringstream ss;
    ss << "";
    //cout<<"Begin"<<endl;
    for (int i = 0; i < this->DATAC.size(); i++)
    {
        string current = this->DATAC[i]->SaveAll();
        bool good = 1;
        for (int j = 0; j < Did.size(); j++)
        {
            if (strcmp(Did[j].c_str(), current.c_str()) == 0)
            {
                good = 0;
            }
            else
            {
                Did.push_back(current);
            }
        }
        if (good == 1)
            ss << current;
    }
    myfile << ss.str();
    myfile.close();
}
void MasterView::addView(View *IN)
{

    this->Views.push_back(IN);
}
void MasterView::clear()
{
    for (int i = 0; i < MaxY - 1; i++)
    {
        for (int j = 0; j < MaxX - 1; j++)
        {
            this->Buffer[j][i] = ' ';
        }
    }
}

string MSTS::Save()
{
    return Alias + " = '" + _Value + "'\n";
}
MSTS::MSTS(string Key, string Value, string alias)
{
    this->_Key = Key;
    this->Alias = alias;
    this->_Value = Value;
}
string EditorView::SaveAll()
{
    string Chunk = "";
    for (int i = 0; i < this->Values.size(); i++)
    {
        if(strcmp(this->Values[i]->Alias.c_str(),"")==0){

        }
        else
        Chunk += this->Values[i]->Save();
    }
    //cout<<Chunk<<endl;
    //char i;
    //cin>>i;
    return Chunk;
}
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
void MasterView::addView(EditorView *IN)
{
    bool exist = 0;
    for (int i = 0; i < DATAC.size(); i++)
    {
        if (DATAC[i] == IN)
        {
            exist = 1;
        }
    }
    if (exist == 0)
        DATAC.push_back(IN);
    Views.push_back(IN);
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
void MasterView::Load(string Filename)
{
    //Alias ='Value'\n

    string line;
    ifstream myfile(Filename);
    if (myfile.is_open())
    {

        while (getline(myfile, line))
        {
            if(strcmp(line.c_str(),"")){
            cout<<line<<endl;

            //char i;
            //cin>>i;
            string Alias = "";
            string Value = "";
            
            for (int i = 0; i < line.size(); i++)
            {int Stage=0;
                if (Stage == 0)
                {
                    if (line[i] == '=')
                    {
                        cout<<"Stage 1 enclenched"<<endl;
                        for(int k=i;k<line.size();k++){
                           if((line[k]=='\'')&&(Stage==0)){
                               Stage++;
                           }
                           if (Stage==1){
                               if(line[k]!='\''){
                                   Value.push_back(line[k]);
                               }
                               
                               else{i=line.size()+1;}
                           }
                        }
                        
                    }
                    else{
                        if(line[i]!=' ')
                        Alias.push_back(line[i]);
                    }
                }
            }
            cout << Value << " : " << Alias<<Alias.size() << endl;
            //char k;
            //cin>>k;
            for (int i = 0; i < this->DATAC.size(); i++)
            {
                for (int j = 0; j < this->DATAC[i]->Values.size(); j++)
                {
                    cout<<this->DATAC[i]->Values[j]->Alias<<this->DATAC[i]->Values[j]->Alias.size()<<endl;
                    if (strcmp(this->DATAC[i]->Values[j]->Alias.c_str(), Alias.c_str()) == 0)
                    {
                        this->DATAC[i]->Values[j]->_Value = Value;
                    }
                }
            }
            }
        }
        //char fd;
        //cin>>fd;
        myfile.close();
    }

    else
        cout << "Unable to Load file\""<<Filename<<"\""<<endl;
}
dropdownlist::dropdownlist(int X,int Y){
this->x=X;
}
    void dropdownlist::add_MSTS(MSTS *, int){

    }
string dropdownlist::SaveAll(){
return this->Alias+" = '"+to_string(this->current_index)+"'";
}