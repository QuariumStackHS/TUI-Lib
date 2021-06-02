#include "tree.hpp"
DepTree::DepTree(string prog,string CFG){
this->ProgName=prog;
this->ConfigFile=CFG;
}
int DepTree::AddChild(DepTree*D){
    this->Childs.push_back(D);
    return 0;
}