#include <iostream>
#include "/home/ls/Compressor/include/func.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        cout << "No input arguments\n";
        return 0;
    }
    if(argc < 4)
    {
        cout << "Not enough input arguments\n";
    }
    if(argc == 4)
    {
        ifstream ifs;
        ifs.open(argv[2], ios::binary);
        if(!(ifs.good()))
        {
            cout << "File " << argv[2] << " doesn't exist\n";
        }
        else
        {
            if(!(strcmp(argv[1], "huffman")))
            {
                ofstream ofs;
                ofs.open(argv[3], ios::binary);
                huffman(ifs, ofs);
            }
            else if(!(strcmp(argv[1], "rle")))
            {
                ofstream ofs;
                ofs.open(argv[3], ios::binary);
                rle(ifs, ofs);
            }
            else if(!(strcmp(argv[1], "compress")))
            {
                ofstream ofs;
                ofs.open("./temp", ios::binary);
                huffman(ifs, ofs);
                ofs.close();
                ifstream ifs2;
                ofstream ofs2;
                ifs2.open("./temp", ios::binary);
                ofs2.open(argv[3], ios::binary);
                rle(ifs2, ofs2);
                remove("./temp");
            }
            else if(!(strcmp(argv[1], "unhuffman")))
            {
                ofstream ofs;
                ofs.open(argv[3], ios::binary);
                unhuffman(ifs, ofs);
            }
            else if(!(strcmp(argv[1], "unrle")))
            {
                ofstream ofs;
                ofs.open(argv[3], ios::binary);
                unrle(ifs, ofs);
            }
            else if(!(strcmp(argv[1], "decompress")))
            {
                ofstream ofs;
                ofs.open("./temp", ios::binary);
                unrle(ifs, ofs);
                ofs.close();
                ifstream ifs2;
                ofstream ofs2;
                ifs2.open("./temp", ios::binary);
                ofs2.open(argv[3], ios::binary);
                unhuffman(ifs2, ofs2);
                remove("./temp");
            }
            else cout << "Wrong input\n";
        }
    }
    return 0;
}
