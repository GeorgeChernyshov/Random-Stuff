#include "/home/ls/Compressor/include/func.h"
#include <iostream>

void huffman(std::istream& ifs, std::ostream& ofs)
{
    if(ifs.peek() == std::ifstream::traits_type::eof()){
        char ch = 0;
        char* k = &ch;
        for(int i = 0; i < 1024; i++) ofs.write(k, 1);
        return;
    }
    InputStreamParser reader(ifs);
    reader.CountQuantities();
    int quantities[256];
    for(int i = 0; i < 256; i++)
    {
        reader.GetQuantity(quantities[i], i);
    }
    HuffCoder coder(quantities);
    coder.BuildCodes();
    OutputStreamParser writer(ofs);
    writer.Huffmanize(ifs, coder);
}

void rle(std::istream& ifs, std::ostream& ofs)
{
    OutputStreamParser writer(ofs);
    writer.RLE(ifs);
}

void unhuffman(std::istream& ifs, std::ostream& ofs)
{
    InputStreamParser reader(ifs);
    reader.ParseQuantities();
    int quantities[256];
    bool zero = 1;
    for(int i = 0; i < 256; i++)
    {
        reader.GetQuantity(quantities[i], i);
        if(quantities[i] != 0) zero = 0;
    }
    if(zero){
        return;
    }
    HuffCoder coder(quantities);
    coder.BuildCodes();
    OutputStreamParser writer(ofs);
    writer.Dehuffmanize(ifs, coder);
}

void unrle(std::istream& ifs, std::ostream& ofs)
{
    OutputStreamParser writer(ofs);
    writer.UnRLE(ifs);
}
