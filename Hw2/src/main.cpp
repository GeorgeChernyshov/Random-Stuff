#include "Board.h"
#include "BoardView.h"
#include <cstring>
#include <cstdio>

int main(int argc, char **argv){
    bool silent = true;
    if(argc > 1){
        if(!strcmp(argv[1], "silent")){
            silent = false;
        }
    }
    
    Board b;
    View v(b, silent);
    
    v.doGameCycle();
    return 0;
}
