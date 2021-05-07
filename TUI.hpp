#include <iostream>
#include <string>
#include <vector>
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"
using namespace std;


class ViewChar
{
public:
    friend class View;
    friend class MasterView;
private:

    ViewChar(int, int, char);
    char Char;
    int Xpos;
    int Ypos;
};


class View
{
public:
    View();
    void add_Horizon(string, int, int);
    void add_Vertical(string, int, int);
    friend class MasterView;

private:
    vector<ViewChar *> Chars;
};
class MasterView
{
public:
    MasterView(int, int);
    void Render();
    void Display();
    void addView(View *);

protected:
    char Buffer[20][40];
    vector<View *> Views;
    int MAXx;
    int MAXy;
};