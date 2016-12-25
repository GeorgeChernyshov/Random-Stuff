#pragma once
#include "Board.h"

class View {
    public:
        View(Board &b, bool show);
        void showBoard();
        void doGameCycle();
    private:
        Board &board_;
        bool show_;
};
