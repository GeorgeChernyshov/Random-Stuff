#pragma once
#include <fstream>
#include "stdio.h"
#include "/home/ls/Compressor/include/HuffCoder.h"
#include <unordered_map>

class OutputStreamParser
{
public:
    OutputStreamParser(std::ostream& os) : os_(os), buffer_(0), total_(0) {}
    void Huffmanize(std::istream& is, HuffCoder& coder);
    void Dehuffmanize(std::istream& is, HuffCoder& coder);
    void RLE(std::istream& is);
    void UnRLE(std::istream& is);
private:
    std::ostream& os_;
    char buffer_;
    int total_;
};
