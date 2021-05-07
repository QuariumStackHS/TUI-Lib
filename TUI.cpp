#include "TUI.hpp"
int Debug=0;
ViewChar::ViewChar(int X, int Y, char C)
{
    this->Char = C;
    this->Xpos = X;
    this->Ypos = Y;
}
View::View()
{
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
                is = 1;
            }
        }
        if (is == 0)
        {
            ViewChar *C = new ViewChar(iY, iX, str[iX - x]);
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
                    is = 1;
                }
            }
            if (is == 0)
            {
                ViewChar *C = new ViewChar(iX - iscalc, iY, str[iX - x]);
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
MasterView::MasterView(int maxX, int maxY)
{
    this->MAXx = maxX;
    this->MAXy = maxY;
}
void MasterView::addView(View *IN)
{

    this->Views.push_back(IN);
}
