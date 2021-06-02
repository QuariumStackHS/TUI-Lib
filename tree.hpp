#include <TUI.hpp>
class DepTree{
    private:
        vector<DepTree*>Childs;
    public:
        string ProgName;
        string ConfigFile;
        DepTree(string prog,string CFG);
        int AddChild(DepTree*);

};