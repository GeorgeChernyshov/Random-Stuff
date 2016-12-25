#pragma once

enum state { play, x_wins, o_wins, draw };

class Board{
    public:
        Board();
        void move(int x, int y, char sign);
        bool canMove(int x, int y);
        state isWin();

        char tiles_[10][10];
};
