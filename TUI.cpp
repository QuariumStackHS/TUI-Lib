#include "TUI.hpp"
int Debug=0;
View::ViewChar::ViewChar(int X, int Y, char C)
{
    this->Char = C;
    this->Xpos = X;
    this->Ypos = Y;
}
View::View()
{
}
void View::render(){

}
View::ViewChar::ViewChar(int X, int Y, char C,View* Master){
    this->Char = C;
    this->Xpos = X;
    this->Ypos = Y;
    this->_MasterView=Master;
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
                this->Chars[i]->_MasterView=this;
                is = 1;
            }
        }
        if (is == 0)
        {

            ViewChar *C = new View::ViewChar(iY, iX, str[iX - x],this);
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
                    this->Chars[i]->_MasterView=this;
                    is = 1;
                }
            }
            if (is == 0)
            {
                ViewChar *C = new View::ViewChar(iX - iscalc, iY, str[iX - x],this);
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
        cout << this->Buffer[i] <<"\n\r";
    }
}

void MasterView::Render()
{

    for (int i = 0; i < this->Views.size(); i++)
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
void MasterView::RemoveView(View*SD){
    for(int i=0;i<this->Views.size();i++){
        if(this->Views[i]==SD){
            for(int j=0;j<this->Views[i]->Chars.size();j++){
                this->Buffer[this->Views[i]->Chars[j]->Ypos][this->Views[i]->Chars[j]->Xpos]=' ';
            }
            this->Views.erase(this->Views.begin()+i);
        }
    }
}
void View::clear(){
    this->Chars.erase(this->Chars.begin(),this->Chars.end());
}
MasterView::MasterView(int maxX, int maxY)
{
    this->MAXx = maxX;
    this->MAXy = maxY;
}
void MasterView::addView(View *IN)
{

    this->Views.push_back(IN);
}
void MasterView::clear(){
    for (int i=0;i<MaxY-1;i++){
        for (int j=0;j<MaxX-1;j++){
        this->Buffer[j][i]=' ';}
    }
}