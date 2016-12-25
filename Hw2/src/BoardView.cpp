#include "BoardView.h"
#include <cstdio>
#include <cstdlib>

View::View(Board &b, bool show_){
    board_ = b;
    this->show_ = show_;
}

void View::showBoard(){
    for(int i = 0; i < 10; i++){    
        for(int j = 0; j < 10; j++){       
            if(board_[j][i] == -1){
                printf(".");
            }
            
            if(board_[j][i] == 0){
                printf("O");
            }
            
            if(board_[j][i] == 1){
                printf("X");
            }
        }
        
        printf("\n");
    }
    
    printf("\n");
}

void View::doGameCycle(){
    int x, y;
    char playerID = 1;
    bool done;
    while(board_.isWin() == play){
        done = false;
        if(show_){
            showBoard();
        }
        
        while(done == false){
            if(playerId == 1){
                printf("X move: ");
            }
            
            if(playerID == 0){
                printf("O move: ");
            }
            
            scanf("%d %d", x, y);
            
            if(board_.canMove(x, y) == 0){
                board_.move(x, y, playerID);
                done = true;
            }else{
                if(x == -1 && y == -1){
                    printf("Good Bye");
                    exit(1);
                }
                printf("Bad Move!");
            }
        }
        
        state status = board_.isWin();
        if(status == x_wins){
            printf("X wins!\n");
        }
        
        if(status == o_wins){
            printf("O wins!\n");
        }
        
        if(status == draw){
            printf("Draw!\n");
        }
        
        PlayerID = 1 - PlayerID;
    }
}
