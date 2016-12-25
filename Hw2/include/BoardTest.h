#pragma once
#define DO_CHECK(EXPR) BoardTest::check(EXPR, __FUNCTION__, __FILE__, __LINE__);
#include "Test.h"

class BoardTest: public Test{
    public:
        void test_canMoveTrue();
        void test_canMoveFalse();
        void test_canMoveTaken();
        
        void test_move1();
        void test_move2();
        void test_move3();
        
        void test_isWinPlay();
        void test_isWinVert();
        void test_isWinHor();
        void test_isWinBackSlash1();
        void test_isWinBackSlash2();
        void test_isWinBackSlash3();
        void test_isWinSlash1();
        void test_isWinSlash2();
        void test_isWinSlash3();
        
        void runAllTests();
};
