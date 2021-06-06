#include "TUI.hpp"

int main(){
    MasterView*I=new MasterView(MaxX,MaxY);
    View*V=new View();
    V->add_Horizon("Dep tree:",1,1);
    V->Visible=1;
    I->addView(V);
    DepTree*i=new DepTree(3,3);
    DepTree*TUI=new DepTree(5,6);
    DepTree*Systeme=new DepTree(5,6);
    DepTree*Reltt=new DepTree(5,6);
    DepTree*MAC=new DepTree(5,6);
    MAC->name="hard..";
    i->AddChild(Systeme);
    Reltt->name="Reltt";
    i->AddChild(Reltt);
    Reltt->AddChild(TUI);
    Systeme->name="OSX";
    Systeme->AddChild(MAC);

    TUI->name="tui";
    i->name="main";
    
    TUI->AddChild(Systeme);
    i->AddChild(TUI);
    i->Visible=1;
    i->render();
    I->addView(i);
    I->Render();
    I->Display();
}