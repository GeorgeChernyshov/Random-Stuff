#include <iostream>
#include "/home/ls/Compressor/include/InputStreamParser.h"

InputStreamParser::InputStreamParser(std::istream& is) : is_(is)
{
    buffer_ = 0;
    for(int i = 0; i < 256; i++) quantities_[i] = 0;
}

void InputStreamParser::CountQuantities()
{
    char* temp = &buffer_;
    int t = 0;
    while(!(is_.eof())){
        is_.read(temp, 1);
        t = buffer_;
        if(t < 0) t += 256;
        if(!(is_.eof())) quantities_[t]++;
    }
    is_.clear();
    is_.seekg(0, std::ios::beg);
}

void InputStreamParser::GetQuantity(int& q, int i)
{
    q = quantities_[i];
}

void InputStreamParser::ParseQuantities()
{
    unsigned char temp;
    for(int i = 0; i < 256; i++)
    {
        for(int j = 3; j >= 0; j--)
        {
            is_.read(reinterpret_cast<char*>(&temp), 1);
            int t = temp;
            quantities_[i] += (t << 8*j);
        }
    }
}
