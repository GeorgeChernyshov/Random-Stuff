#include "Test.h"
#include <cstdio>

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum){
    totalNum++;
    if(!expr){
        failedNum++;
        printf("test failed: %s in %s:%ud\n", func, filename, lineNum);
    }
}

void Test::showFinalResult(){
    if(failedNum == 0){
        printf("All tests passed\n");
    }else{
        printf("Failed %d of %d tests\n", failedNum, totalNum);
    }
}
