#include "/home/ls/Compressor/include/OutputStreamParser.h"
#include <iostream>

void OutputStreamParser::Huffmanize(std::istream& is, HuffCoder& coder){
    int total = 0;
    for(int i = 0; i < 256; i++)
    {
        int t = coder.GetQuantity(i);
        total += t;
        for(int j = 3; j >= 0; j--){
            int x = (unsigned char)((t >> (8*j)) & 0xff);
            unsigned char ch = (unsigned char)x;
            os_.write(reinterpret_cast<char*>(&ch), 1);
        }
    }
    unsigned char intemp = 0, outtemp = 0;
    int a = 0, b = 0;
    double coef = 1/(double)total;
    int newtotal = 0;
    while(total--)
    {
        is.read(reinterpret_cast<char*>(&intemp), 1);
        std::string str = coder.GetCode(intemp);
        b = 0;
        while(str.length() - b > 0)
        {
            if(8 - a > str.length() - b)
            {
                for(int i = 8 - a; i > 8 - a - str.length() + b; i--){
                    outtemp |= (str[b - i + 8 - a] == '0' ? 0 : (1 << (i - 1)));
                }
                a = (a + str.length() - b);
                b = str.length();
            }
            else {
                for(int i = 8 - a; i > 0; i--){
                    outtemp |= (str[b - i + 8 - a] == '0' ? 0 : (1 << (i - 1)));
                }
                b += (8 - a);
                os_.write(reinterpret_cast<char*>(&outtemp), 1);
                newtotal++;
                outtemp = 0;
                a = 0;
            }
        }
    }
    os_.write(reinterpret_cast<char*>(&outtemp), 1);
    newtotal++;
    coef *= newtotal;
    std::cout << "Compression coefficient: " << coef << std::endl;
}

void OutputStreamParser::Dehuffmanize(std::istream& is, HuffCoder& coder)
{
    for(int i = 0; i < 256; i++)
    {
        total_ += coder.GetQuantity(i);
    }
    std::string code;
    unsigned char intemp = 0, outtemp = 0;
    while(!(is.eof()))
    {
        is.read(reinterpret_cast<char*>(&intemp), 1);
        for(int i = 7; i >= 0; --i)
        {
            if(!(intemp & (1 << i)))
            {
                code += '0';
            }
            else
            {
                code += '1';
            }
            for(int j = 0; j < 256; j++)
            {
                if(coder.GetQuantity(j) > 0)
                {
                    if(coder.GetCode(j) == code)
                    {
                        outtemp = (unsigned char)(j);
                        if(total_-- > 0) os_.write(reinterpret_cast<char*>(&outtemp), 1);
                        code.resize(0);
                        //std::cout << coder.GetCode(j) << " " << (int)outtemp << " ";
                        j = 500;
                    }
                }
            }
        }
    }
}

void OutputStreamParser::RLE(std::istream& is)
{
    char* temp = &buffer_;
    int counter = 1;
    is.read(temp, 1);
    int total = 0, newtotal = 0;
    while(!is.eof())
    {
        char next;
        char* nexttemp = &next;
        is.read(nexttemp, 1);
        total++;
        if(next == buffer_)
        {
            counter++;
        } else
        {
            for(int j = 3; j >= 0; j--){
                int x = (unsigned char)((counter >> (8*j)) & 0xff);
                unsigned char ch = (unsigned char)x;
                os_.write(reinterpret_cast<char*>(&ch), 1);
            }
            os_.write(temp, 1);
            newtotal += 5;
            counter = 1;
            buffer_ = next;
        }
    }
    counter--;
    for(int j = 3; j >= 0; j--){
        int x = (unsigned char)((counter >> (8*j)) & 0xff);
        unsigned char ch = (unsigned char)x;
        os_.write(reinterpret_cast<char*>(&ch), 1);
    }
    os_.write(temp, 1);
    counter = 1;
    newtotal += 5;
    double coef = 1/(double)total;
    coef *= newtotal;
    std::cout << "Compression coefficient: " << coef << std::endl;
}

void OutputStreamParser::UnRLE(std::istream& is)
{
    int t = 0;
    char* temp = &buffer_;
    while(!is.eof())
    {
        for(int j = 3; j >= 0; j--)
        {
            is.read(temp, 1);
            int x = (int)buffer_;
            if(x < 0) x += 256;
            t |= (x << 8*j);
        }
        is.read(temp, 1);
        std::cout << t << " ";
        if(!is.eof()) for(int i = 0; i < t; i++) os_.write(temp, 1);
        t = 0;
    }
}
