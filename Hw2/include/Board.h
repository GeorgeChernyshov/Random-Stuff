#pragma once

enum state { play, x_wins, o_wins, draw };

class Board{
    public:
        Board();
        void move(int x, int y, char sign);
        bool canMove(int x, int y);
        state isWin();
    private:
        char tiles_[10][10];
};
