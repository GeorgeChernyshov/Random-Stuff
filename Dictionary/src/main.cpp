#include <iostream>
#include "../include/HashTable.h"
#include "../include/RedBlackTree.h"
#include "../include/BTree.h"

using namespace std;

int main()
{
    cout << "Input filename" << endl;
    string filename = "/home/ls/Dictionary/Sawyer";
    //cin >> filename;
    ifstream ifs;
    ifs.open(filename.c_str());
    if(!ifs.good()){
        cout << "Invalid path or filename" << endl;
        return 0;
    }
    HashTable hashTable(ifs);
    hashTable.add("hello", 999);
    cout << "hello: " << hashTable.find("hello").first << endl;
    ifs.clear();
    ifs.seekg(0);
    hashTable.remove("hello");
    string word;
    while(!ifs.eof()) {
        ifs >> word;
        hashTable.remove(word);
    }
    ifs.clear();
    ifs.seekg(0);
    RedBlackTree rbTree(ifs);
    rbTree.add("hello", 999);
    rbTree.add("help", 42);
    cout << "hello: " << rbTree.find("hello") << endl;
    cout << "help: " << rbTree.find("help") << endl;
    rbTree.erase("hello");
    cout << "hello: " << rbTree.find("hello") << endl;
    cout << "help: " << rbTree.find("help") << endl;
    ifs.clear();
    ifs.seekg(0);
    while(!ifs.eof()) {
        ifs >> word;
        if(word == "with") {
            int a = 2;
        }
        rbTree.erase(word);
    }
    ifs.clear();
    ifs.seekg(0);
    return 0;
}
