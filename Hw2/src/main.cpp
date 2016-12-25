#include "Board.h"
#include "BoardView.h"
#include <cstring>
#include <cstdio>

int main(int argc, char **argv){
    bool show = true;
    if(argc > 1){
        if(!strcmp(argv[1], "silent")){
            show = false;
        }
    }
    
    Board b;
    View v(b, show);
    
    v.doGameCycle();
    return 0;
}
