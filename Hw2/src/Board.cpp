#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

Board::Board(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            tiles_[i][j] = -1;
        }
    }
}

bool Board::canMove(int x, int y){
    bool b = 0;
    if(x < 0 || x > 9 || y < 0 || y > 9){
        b = 1;
    }
    
    if(tiles_[x][y] != -1){
        b = 1;   
    }
    
    return b;
}

void Board::move(int x, int y, char sign){
    if(canMove(x, y) == 0){
        tiles_[x][y] = sign;
    }
}

state Board::isWin(){
    int row;
    int prev;
    int tile_visited;
    
    for(int i = 0; i < 10; i++){
        row = 1;
        
        prev = tiles_[0][i];
        
        for(int j = 1; j < 10; j++){
            tile_visited = 0;
            if(prev == -1){
                row = 1;
                tile_visited = 1;
            }
            
            if(prev != -1 && tile_visited == 0){
                if(prev == tiles_[j][i]){
                    row++;
                    if(row == 5){
                        if(tiles_[j][i] == 0){
                            return o_wins;
                        }else{
                            return x_wins;
                        }
                    }
                }
            }
            prev = tiles_[j][i];
        }
    }
    
    for(int i = 0; i < 10; i++){
        row = 1;
        
        prev = tiles_[i][0];
        
        for(int j = 1; j < 10; j++){
            tile_visited = 0;
            if(prev == -1){
                row = 1;
                tile_visited = 1;
            }
            
            if(prev != -1 && tile_visited == 0){
                if(prev == tiles_[i][j]){
                    row++;
                    if(row == 5){
                        if(tiles_[i][j] == 0){
                            return o_wins;
                        }else{
                            return x_wins;
                        }
                    }
                }
            }
            prev = tiles_[i][j];
        }
    }
    
    for(int i = 0; i < 6; i++){
        row = 1;
        
        prev = tiles_[0][i];
        
        for(int j = 1; j < 10-i; j++){
            tile_visited = 0;
            if(prev == -1){
                row = 1;
                tile_visited = 1;
            }
            
            if(prev != -1 && tile_visited == 0){
                if(prev == tiles_[j][i + j]){
                    row++;
                    if(row == 5){
                        if(tiles_[j][i + j] == 0){
                            return o_wins;
                        }else{
                            return x_wins;
                        }
                    }
                }
                prev = tiles_[j][i + j];
            }
        }
        
        row = 1;
        
        prev = tiles_[i][0];
        
        for(int j = 1; j < 10-i; j++){
            tile_visited = 0;
            if(prev == -1){
                row = 1;
                tile_visited = 1;
            }
            
            if(prev != -1 && tile_visited == 0){
                if(prev == tiles_[i + j][j]){
                    row++;
                    if(row == 5){
                        if(tiles_[i + j][j] == 0){
                            return o_wins;
                        }else{
                            return x_wins;
                        }
                    }
                }
                prev = tiles_[j][i + j];
            }
        }
    }
    
    for(int i = 9; i > 4; i--){
        row = 1;
        
        prev = tiles_[0][i];
        
        for(int j = 1; j < 10-i; j++){
            tile_visited = 0;
            if(prev == -1){
                row = 1; 
                tile_visited = 1;
            }
            
            if(prev != -1 && tile_visited == 0){
                if(prev == tiles_[j][i - j]){
                    row++;
                    if(row == 5){
                        if(tiles_[j][i - j] == 0){
                            return o_wins;
                        }else{
                            return x_wins;
                        }
                    }
                }
            }
            prev = tiles_[j][i - j];
        }
        
        row = 1;
        
        prev = tiles_[i][0];
        
        for(int j = 1; j < 10-i; j++){
            tile_visited = 0;
            if(prev == -1){
                row = 1;
                tile_visited = 1;
            }
            
            if(prev != -1 && tile_visited == 0){
                if(prev == tiles_[i - j][j]){
                    row++;
                    if(row == 5){
                        if(tiles_[i - j][j] == 0){
                            return o_wins;
                        }else{
                            return x_wins;
                        }
                    }
                }
            }
            prev = tiles_[j][i - j];
        }
    }
    
    bool tie = 0;
    
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(tiles_[i][j] == -1){
                tie = 1;
            }
        }
    }
    
    if(tie == 0){
        return draw;
    }
    
    return play;
}
