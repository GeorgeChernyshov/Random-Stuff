#pragma once
#include <fstream>
#include <string.h>
#include <stdio.h>

class InputStreamParser
{
public:
    InputStreamParser(std::istream& is);
    void CountQuantities();
    void ParseQuantities();
    void GetQuantity(int& q, int i);
private:
    int quantities_[256];
    std::istream& is_;
    char buffer_;
};
