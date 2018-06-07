#include "/home/ls/Compressor/include/HuffCoder.h"
#include <iostream>
//I'm using the priority queue for this
HuffCoder::HuffCoder(int* quantities)
{
    counter_ = 0;
    int rev[256];
    for(int i = 0; i < 256; i++)
    {
        if(quantities[i] > 0){
            rev[counter_] = i;
            counter_++;
        }
        quantities_[i] = quantities[i];
    }
    tree_ = new TreeNode[2*counter_ - 1];
    for(int i = counter_ - 1; i < 2*counter_ - 1; i++)
    {
        tree_[i].left_ = -1;
        tree_[i].right_ = -1;
        tree_[i].is_leaf_ = 1;
        tree_[i].symbol_ = rev[i - counter_ + 1];
        std::pair<int, int> p;
        p.first = -quantities[rev[i + 1 - counter_]];
        p.second = i;
        queue_.push(p);
    }
}
//String codes is probably not the best choise
void HuffCoder::BuildCodes()
{
    for(int i = counter_ - 2; i >= 0; i--)
    {
        std::pair<int, int> p1 = queue_.top();
        queue_.pop();
        std::pair<int, int> p2 = queue_.top();
        queue_.pop();
        std::pair<int, int> p;
        p.first = p1.first + p2.first;
        p.second = i;
        tree_[i].left_ = p1.second;
        tree_[i].right_ = p2.second;
        tree_[i].is_leaf_ = 0;
        tree_[i].symbol_ = -1;
        queue_.push(p);
    }
    std::string str;
    dfs(0, str);
    int total = 1024*8;
    for(int i = 0; i < 256; i++){
        if(quantities_[i] > 0)
        std::cout << (char)i << " " << quantities_[i] << " "<< codes_[i] << std::endl;
        total += quantities_[i]*codes_[i].length();
    }
}

std::string HuffCoder::GetCode(int i)
{
    return codes_[i];
}

void HuffCoder::dfs(int i, std::string str)
{
    if(tree_[i].is_leaf_)
    {
        codes_[tree_[i].symbol_] = str;
        return;
    }
    dfs(tree_[i].left_, str + "0");
    dfs(tree_[i].right_, str + "1");
}

int HuffCoder::GetQuantity(int i)
{
    return quantities_[i];
}
