#include "../include/HashTable.h"

HashTable::HashTable(std::ifstream& ifs)
{
    dict_ = new std::vector<std::pair<std::string, std::vector<int>>>[capacity_];
    std::string word;
    int pos = 0;
    while(!ifs.eof()) {
        ifs >> word;
        add(word, ++pos);
    }
}

HashTable::~HashTable()
{
    delete[] dict_;
}
//Collisions are resolved using lists
void HashTable::add(std::string word, int pos)
{
    std::pair<int, int> p = find(word);
    if(p.first != -1) {
        dict_[p.first][p.second].second.push_back(pos);
        return;
    }
    int index = GetHash(word, capacity_);
    std::pair<std::string, std::vector<int>> p1(word, std::vector<int>(1, pos));
    dict_[index].push_back(p1);
    size_++;
    if(2*size_ > capacity_)
        resize();
}

void HashTable::remove(std::string word)
{
    std::pair<int, int> p = find(word);
    if(p.first != -1) {
        auto it = dict_[p.first].begin();
        it += p.second;
        dict_[p.first].erase(it);
    }
}

std::pair<int, int> HashTable::find(std::string word)
{
    int index = GetHash(word, capacity_);
    for(int i = 0; i < dict_[index].size(); ++i){
        if(dict_[index][i].first == word) {
            return std::pair<int, int>(index, i);
        }
    }
    return std::pair<int, int>(-1, -1);
}
//2x+3 - quite good number sequence
void HashTable::resize()
{
    int new_capacity = (2*capacity_) + 3;
    std::vector<std::pair<std::string, std::vector<int>>> * new_dict =
        new std::vector<std::pair<std::string, std::vector<int>>>[new_capacity];
    std::string word;
    for(int i = 0; i < capacity_; ++i) {
        for(int j = 0; j < dict_[i].size(); ++j) {
            word = dict_[i][j].first;
            int index = GetHash(word, new_capacity);
            std::pair<std::string, std::vector<int>> p = dict_[i][j];
            new_dict[index].push_back(p);
        }
    }
    delete[] dict_;
    dict_ = new_dict;
    capacity_ = new_capacity;
}
//Polynomial Hashes
int GetHash(std::string str, int capacity)
{
    int hash_ = 0;
    for(int i = 0; i < str.size(); ++i) {
        hash_ *= 541;
        hash_ += (20*capacity + int(str[i]));
        hash_ = hash_ % capacity;
    }
    return hash_;
}
