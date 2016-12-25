#include "BoardTest.h"
#include "Test.h"
#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

void BoardTest::test_canMoveTrue() {
    Board b;
    bool can = true;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (!b.canMove(i, j)) {
                can = false;
                break;
            }
        }
    }
    DO_CHECK(can);
}

void BoardTest::test_canMoveFalse(){
    Board b;
    bool cant = true;
    for (int i = -10; i < 0; i++) {
        for (int j = -10; j < 0; j++) {
            if (b.canMove(i, j)) {
                cant = false;
                break;
            }
        }
    }
    
    for (int i = 0; i < 10; i++) {
        for (int j = 10; j < 20; j++) {
            if (b.canMove(i, j)) {
                cant = false;
                break;
            }
        }
    }
    
    DO_CHECK(cant);
}

void BoardTest::test_canMoveTaken(){
    Board b;
    bool cant = true;
    b.move(0, 0, 1);
    if(b.canMove(0, 0) == true){
        cant = false;
    }
    
    DO_CHECK(cant);
}
        
void BoardTest::test_move1(){
    Board b;
    b.move(0, 0, 1);  
    DO_CHECK(b.tiles_[0][0] == 1);
}

void BoardTest::test_move2(){
    Board b;
    b.move(0, 0, 0);  
    DO_CHECK(b.tiles_[0][0] == 0);
}

void BoardTest::test_move3(){
    Board b;
    b.move(1, 0, 1);
    b.move(0, 1, 0);  
    DO_CHECK(b.tiles_[0][0] == -1);
}
        
void BoardTest::test_isWinPlay(){
    Board b;
    bool p = true;
    if(b.isWin() != play){
        p = false;
    }
    b.move(0, 0, 0);
    b.move(1, 1, 1);
    if(b.isWin() != play){
        p = false;
    }
    DO_CHECK(p);
}

void BoardTest::test_isWinVert(){
    Board b;
    b.move(0, 0, 0);
    b.move(1, 0, 1);
    b.move(0, 1, 0);
    b.move(1, 1, 1);
    b.move(0, 2, 0);
    b.move(1, 2, 1);
    b.move(0, 3, 0);
    b.move(1, 3, 1);
    b.move(0, 4, 0);
    DO_CHECK(b.isWin() == 0);
}

void BoardTest::test_isWinHor(){
    Board b;
    b.move(0, 0, 0);
    b.move(0, 1, 1);
    b.move(1, 0, 0);
    b.move(1, 1, 1);
    b.move(2, 0, 0);
    b.move(2, 1, 1);
    b.move(3, 0, 0);
    b.move(3, 1, 1);
    b.move(4, 0, 1);
    DO_CHECK(b.isWin() == 1);    
}

void BoardTest::test_isWinSlash1(){
    Board b;
    b.move(0, 0, 0);
    b.move(0, 1, 1);
    b.move(1, 1, 0);
    b.move(1, 1, 1);
    b.move(2, 2, 0);
    b.move(2, 1, 1);
    b.move(3, 3, 0);
    b.move(3, 1, 1);
    b.move(4, 4, 0);
    DO_CHECK(b.isWin() == 0);  
}

void BoardTest::test_isWinSlash2(){
    Board b;
    b.move(5, 0, 1);
    b.move(0, 1, 0);
    b.move(6, 1, 1);
    b.move(1, 1, 0);
    b.move(7, 2, 1);
    b.move(2, 1, 0);
    b.move(8, 3, 1);
    b.move(3, 1, 0);
    b.move(9, 4, 1);
    DO_CHECK(b.isWin() == 1);  
}

void BoardTest::test_isWinSlash3(){
    Board b;
    b.move(0, 5, 1);
    b.move(0, 1, 0);
    b.move(1, 6, 1);
    b.move(1, 1, 0);
    b.move(2, 7, 1);
    b.move(2, 1, 0);
    b.move(3, 8, 1);
    b.move(3, 1, 0);
    b.move(4, 9, 1);
    DO_CHECK(b.isWin() == 1);  
}

void BoardTest::test_isWinBackSlash1(){
    Board b;
    b.move(9, 0, 0);
    b.move(0, 1, 1);
    b.move(8, 1, 0);
    b.move(1, 1, 1);
    b.move(7, 2, 0);
    b.move(2, 1, 1);
    b.move(6, 3, 0);
    b.move(3, 1, 1);
    b.move(5, 4, 0);
    DO_CHECK(b.isWin() == 0); 
}

void BoardTest::test_isWinBackSlash2(){
    Board b;
    b.move(4, 0, 0);
    b.move(0, 1, 1);
    b.move(3, 1, 0);
    b.move(1, 1, 1);
    b.move(2, 2, 0);
    b.move(2, 1, 1);
    b.move(1, 3, 0);
    b.move(3, 1, 1);
    b.move(0, 4, 0);
    DO_CHECK(b.isWin() == 0); 
}

void BoardTest::test_isWinBackSlash3(){
    Board b;
    b.move(4, 0, 0);
    b.move(9, 5, 1);
    b.move(3, 1, 0);
    b.move(8, 6, 1);
    b.move(2, 2, 0);
    b.move(7, 7, 1);
    b.move(1, 3, 0);
    b.move(6, 8, 1);
    b.move(5, 9, 1);
    DO_CHECK(b.isWin() == 1); 
}
        
void BoardTest::runAllTests(){
    test_canMoveTrue();
    test_canMoveFalse();
    test_canMoveTaken();        
    test_move1();
    test_move2();
    test_move3();        
    test_isWinPlay();
    test_isWinVert();
    test_isWinHor();
    test_isWinBackSlash1();
    test_isWinBackSlash2();
    test_isWinBackSlash3();
    test_isWinSlash1();
    test_isWinSlash2();
    test_isWinSlash3();
}
