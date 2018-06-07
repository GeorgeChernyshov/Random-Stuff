#pragma once
#include <queue>
#include <string>

struct TreeNode{
    int left_;
    int right_;
    bool is_leaf_;
    unsigned char symbol_;
};


class HuffCoder
{
public:
    HuffCoder(int* quantities);
    void BuildCodes();
    void dfs(int i, std::string str);
    std::string GetCode(int i);
    int GetQuantity(int i);
private:
    std::priority_queue<std::pair<int, int> > queue_;
    TreeNode* tree_;
    std::string codes_[256];
    int counter_;
    int quantities_[256];
};
