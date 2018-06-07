#include "../include/RedBlackTree.h"

RedBlackTreeNode::~RedBlackTreeNode()
{
}

RedBlackTreeNode* RedBlackTreeNode::grandparent()
{
    if(this->parent) {
        return this->parent->parent;
    }
    return nullptr;
}

RedBlackTreeNode* RedBlackTreeNode::uncle()
{
    if(this->grandparent()) {
        if(this->grandparent()->left == this->parent)
            return this->grandparent()->right;
        return this->grandparent()->left;
    }
    return nullptr;
}

RedBlackTreeNode* RedBlackTreeNode::sibling() {
    if(!this->parent) return nullptr;
    if(this->parent->left == this)
        return this->parent->right;
    return this->parent->left;
}

void RedBlackTreeNode::rotate_left()
{
    RedBlackTreeNode* node = this->right;
    if(this->parent) {
        if(this->parent->left == this)
            this->parent->left = node;
        else
            this->parent->right = node;
    }
    node->parent = this->parent;
    this->parent = node;
    this->right = node->left;
    node->left = this;
    if(this->right) this->right->parent = this;
    node->subtree_size++;
    node->subtree_size += this->subtree_size;
}

void RedBlackTreeNode::rotate_right()
{
    RedBlackTreeNode* node = this->left;
    if(this->parent) {
        if(this->parent->left == this)
            this->parent->left = node;
        else
            this->parent->right = node;
    }
    node->parent = this->parent;
    this->parent = node;
    this->left = node->right;
    node->right = this;
    if(this->left) this->left->parent = this;
    this->subtree_size--;
    this->subtree_size -= node->subtree_size;
}

RedBlackTree::RedBlackTree(std::ifstream& ifs)
{
    head_ = new RedBlackTreeNode();
    std::string word;
    int pos = 0;
    while(!ifs.eof()) {
        ifs >> word;
        add(word, ++pos);
    }
}

RedBlackTree::~RedBlackTree()
{
    for(RedBlackTreeNode* node = head_->next; node; node = node->next) {
        delete node;
    }
    for(RedBlackTreeNode* node = head_->prev; node; node = node->prev) {
        delete node;
    }
    delete head_;
}

bool RedBlackTree::add(std::string word, int pos)
{
    return add(word, pos, head_);
}

bool RedBlackTree::add(std::string word, int pos, RedBlackTreeNode* node)
{
    if(head_->color == 0) {
        head_->color = 1;
        head_->word = word;
        head_->positions.push_back(pos);
        height_++;
    }
    else if(word < node->word) {
        if(node->left){
            if(add(word, pos, node->left)) {
                node->subtree_size++;
                return 1;
            }
        } else {
            node->subtree_size++;
            node->left = new RedBlackTreeNode();
            node->left->word = word;
            node->left->positions.push_back(pos);
            node->left->parent = node;
            node->left->prev = node->prev;
            node->prev = node->left;
            node->prev->next = node;
            if(node->prev->prev) {
                node->prev->prev->next = node->prev;
            }
            if(node->color == 0)
                insert_rebalance(node->left);
            return 1;
        }
    }
    else if(word > node->word) {
        if(node->right) {
            if(add(word, pos, node->right)) return 1;
        } else {
            node->right = new RedBlackTreeNode();
            node->right->word = word;
            node->right->positions.push_back(pos);
            node->right->parent = node;
            node->right->next = node->next;
            node->next = node->right;
            node->next->prev = node;
            if(node->next->next) {
                node->next->next->prev = node->next;
            }
            if(node->color == 0)
                insert_rebalance(node->right);
            return 1;
        }
    }
    else if(word == node->word)
        node->positions.push_back(pos);
    return 0;
}

int RedBlackTree::find(std::string word)
{
    return find(word, head_);
}

int RedBlackTree::find(std::string word, RedBlackTreeNode* node)
{
    int ans = 0;
    if(word == node->word) ans += node->subtree_size;
    else if(word < node->word) {
        if(node->left) {
            return find(word, node->left);
        } else {
            return -1;
        }
    }
    else if(word > node->word) {
        if(node->right) {
            ans += (node->subtree_size + 1);
            int a = find(word, node->right);
            if(a == -1) {
                return -1;
            } else {
                ans += a;
            }
        } else {
            return -1;
        }
    }
    return ans;
}

void RedBlackTree::erase(std::string word)
{
    if(find(word) != -1)
        erase(word, head_);
}

void RedBlackTree::erase(std::string word, RedBlackTreeNode* node)
{
    if(word < node->word) {
        node->subtree_size--;
        erase(word, node->left);
    }
    else if(word > node->word) {
        erase(word, node->right);
    }
    else {
        if(node->left && node->right) {
            node->word = node->next->word;
            node->positions = node->next->positions;
            delete_node(node->next);
        } else {
            delete_node(node);
        }
    }
}

void RedBlackTree::delete_node(RedBlackTreeNode* node)
{
    if(!node->right) {
        if(node->color == 1) {
            if(node->left) {
                if(node->left->color == 0) {
                    node->word = node->left->word;
                    node->positions = node->left->positions;
                    delete_node(node->left);
                    return;
                }
            }
            delete_rebalance(node);
        }
        if(node->parent) {
            if(node == node->parent->left)
                node->parent->left = node->left;
            else
                node->parent->right = node->left;
        }
        if(node->next) {
            node->next->prev = node->prev;
            if(node->prev) {
                node->prev->next = node->next;
            }
        } else if(node->prev) {
            node->prev->next = node->next;
        }
        delete node;
    } else {
        node->right->parent = node->parent;
        if(node->parent) {
            if(node == node->parent->left)
                node->parent->left = node->right;
            else
                node->parent->right = node->right;
        }
        if(node->next) {
            node->next->prev = node->prev;
            if(node->prev) {
                node->prev->next = node->next;
            }
        } else if(node->prev) {
            node->prev->next = node->next;
        }
        if (node->color == 1) {
            if(node->right->color == 0) {
                node->right->color = 1;
            } else {
                delete_rebalance(node->right);
            }
        }
        delete node;
    }
}

void RedBlackTree::insert_rebalance(RedBlackTreeNode* node)
{
    if(node == head_) {
        if(node->color == 0) {
            head_->color = 1;
            height_++;
        }
        return;
    }
    if(node->parent->color == 0) {
        if(node->uncle()) {
            if(node->uncle()->color == 0) {
                node->parent->color = 1;
                node->uncle()->color = 1;
                node->grandparent()->color = 0;
                insert_rebalance(node->grandparent());
                return;
            }
        }
        if(node->parent == node->grandparent()->left) {
            if(node == node->parent->right) {
                node->parent->rotate_left();
                insert_rebalance(node->left);
            } else {
                node->parent->color = 1;
                node->grandparent()->color = 0;
                node->grandparent()->rotate_right();
                if(node->grandparent())
                    insert_rebalance(node->grandparent());
            }
        } else {
            if(node == node->parent->left) {
                node->parent->rotate_right();
                insert_rebalance(node->right);
            } else {
                node->parent->color = 1;
                node->grandparent()->color = 0;
                node->grandparent()->rotate_left();
                if(node->grandparent())
                    insert_rebalance(node->grandparent());
            }
        }
    }
    while(head_->parent)
        head_ = head_->parent;
}

void RedBlackTree::delete_rebalance(RedBlackTreeNode* node) {
    if(node == head_) {
        height_--;
        return;
    }
    if(node->sibling()) {
        if(node->sibling()->color == 0) {
            node->sibling()->color = 1;
            node->parent->color = 0;
            if(node == node->parent->left)
                node->parent->rotate_left();
            else
                node->parent->rotate_right();
            delete_rebalance(node);
            return;
        } else {
            if(node->sibling()->left && node->sibling()->right) {
                if(node->sibling()->left->color == 1 && node->sibling()->right->color == 1) {
                    if(node->parent->color == 0) {
                        node->parent->color = 1;
                        node->sibling()->color = 0;
                        return;
                    } else {
                        node->sibling()->color = 0;
                        if(node->parent->color == 1) {
                            delete_rebalance(node->parent);
                            return;
                        }
                        node->parent->color = 1;
                        return;
                    }
                }
                else if(node == node->parent->left) {
                    if(node->sibling()->right->color == 0) {
                        node->sibling()->right->color = 1;
                        node->sibling()->color = node->parent->color;
                        node->parent->color = 1;
                        node->parent->rotate_left();
                    } else {
                        node->sibling()->color = 0;
                        node->sibling()->left->color = 1;
                        node->sibling()->rotate_right();
                        delete_rebalance(node);
                    }
                } else {
                    if(node->sibling()->left->color == 0) {
                        node->sibling()->left->color = 1;
                        node->sibling()->color = node->parent->color;
                        node->parent->color = 1;
                        node->parent->rotate_right();
                    } else {
                        node->sibling()->color = 0;
                        node->sibling()->right->color = 1;
                        node->sibling()->rotate_left();
                        delete_rebalance(node);
                    }
                }
            } else if(node->sibling()->left) {
                if(node->sibling()->left->color == 1) {
                    if(node->parent->color == 0) {
                        node->parent->color = 1;
                        node->sibling()->color = 0;
                        return;
                    } else {
                        node->sibling()->color = 0;
                        if(node->parent->color == 1) {
                            delete_rebalance(node->parent);
                            return;
                        }
                        node->parent->color = 1;
                        return;
                    }
                } else if(node == node->parent->left) {
                    node->sibling()->color = 0;
                    node->sibling()->left->color = 1;
                    node->sibling()->rotate_right();
                    delete_rebalance(node);
                } else {
                    node->sibling()->left->color = 1;
                    node->sibling()->color = node->parent->color;
                    node->parent->color = 1;
                    node->parent->rotate_right();
                }
            } else if(node->sibling()->right) {
                if(node->sibling()->right->color == 1) {
                    if(node->parent->color == 0) {
                        node->parent->color = 1;
                        node->sibling()->color = 0;
                        return;
                    } else {
                        node->sibling()->color = 0;
                        if(node->parent->color == 1) {
                            delete_rebalance(node->parent);
                            return;
                        }
                        node->parent->color = 1;
                        return;
                    }
                }
                else if(node == node->parent->right) {
                    node->sibling()->color = 0;
                    node->sibling()->right->color = 1;
                    node->sibling()->rotate_left();
                    delete_rebalance(node);
                } else {
                    node->sibling()->right->color = 1;
                    node->sibling()->color = node->parent->color;
                    node->parent->color = 1;
                    node->parent->rotate_left();
                }
            } else {
                if(node->parent->color == 0) {
                    node->parent->color = 1;
                    node->sibling()->color = 0;
                    return;
                } else {
                    node->sibling()->color = 0;
                    if(node->parent->color == 1) {
                        delete_rebalance(node->parent);
                        return;
                    }
                    node->parent->color = 1;
                    return;
                }
            }
        }
    }
    while(head_->parent)
        head_ = head_->parent;
}

void RedBlackTree::print()
{
    print(head_);
    std::cout << std::endl;
}

void RedBlackTree::print(RedBlackTreeNode* node)
{
    std::cout << node->word << ", " << node->color;
    std::cout << "(";
    if(node->left)
        print(node->left);
    std::cout << ")";
    std::cout << "(";
    if(node->right)
        print(node->right);
    std::cout << ")";
}
