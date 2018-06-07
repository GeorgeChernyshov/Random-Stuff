#pragma once
#include <fstream>
#include <string>
#include <vector>

class HashTable
{
public:
    HashTable(std::ifstream& ifs);
    ~HashTable();
    void add(std::string word, int pos);
    void remove(std::string word);
    std::pair<int, int> find(std::string word);
private:
    void resize();
    int capacity_ = 13;
    int size_ = 0;
    int opcounter = 0;
    std::vector<std::pair<std::string, std::vector<int>>> *dict_;
};

int GetHash(std::string str, int capacity);
