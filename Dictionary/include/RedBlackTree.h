#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

struct RedBlackTreeNode{
    RedBlackTreeNode(int color = 0, int subtree_size = 0) : color(color), subtree_size(subtree_size) {}
    ~RedBlackTreeNode();
    int color;
    int subtree_size = 0;
    std::string word;
    std::vector<int> positions;
    RedBlackTreeNode* left = nullptr;
    RedBlackTreeNode* right = nullptr;
    RedBlackTreeNode* parent = nullptr;
    RedBlackTreeNode* next = nullptr;
    RedBlackTreeNode* prev = nullptr;

    RedBlackTreeNode* grandparent();
    RedBlackTreeNode* uncle();
    RedBlackTreeNode* sibling();

    void rotate_left();
    void rotate_right();
};

class RedBlackTree{
public:
    RedBlackTree(std::ifstream& ifs);
    ~RedBlackTree();
    bool add(std::string word, int pos);
    void remove(std::string word);
    int find(std::string word);
    void erase(std::string word);
    void print();
private:
    bool add(std::string word, int pos, RedBlackTreeNode* node);
    int find(std::string word, RedBlackTreeNode* node);
    void erase(std::string word, RedBlackTreeNode* node);
    void insert_rebalance(RedBlackTreeNode* node);
    void delete_rebalance(RedBlackTreeNode* node);
    void delete_node(RedBlackTreeNode* node);
    void print(RedBlackTreeNode* node);
    RedBlackTreeNode* head_;
    int opcounter = 0;
    int height_ = 1;
};
