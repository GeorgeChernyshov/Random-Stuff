#pragma once
#include "/home/ls/Compressor/include/InputStreamParser.h"
#include "/home/ls/Compressor/include/OutputStreamParser.h"
#include "/home/ls/Compressor/include/HuffCoder.h"

void huffman(std::istream& ifs, std::ostream& ofs);
void rle(std::istream& ifs, std::ostream& ofs);

void unhuffman(std::istream& ifs, std::ostream& ofs);
void unrle(std::istream& ifs, std::ostream& ofs);
