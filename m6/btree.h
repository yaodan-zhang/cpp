/* This program improves a binary tree implementation in https://www.cprogramming.com/tutorial/lesson18.html
 The main modification is to change all raw pointer usage into an light weight RAII version, unique_ptr.*/
#ifndef BTREE_H
#define BTREE_H
#include<iostream>
#include<memory>
using namespace std;
namespace mybtree{
class node
{
public:
node(int key) : key_value(key), left(nullptr), right(nullptr) {}
// A copy constructor is needed for returning a deeply copied subtree in search()
node(node const &other);
int key_value;
unique_ptr<node> left;
unique_ptr<node> right;
};

node::node(node const &other) {
    this->key_value = other.key_value;
    this->left = other.left? make_unique<node>(*other.left) : nullptr;
    this->right = other.right? make_unique<node>(*other.right) : nullptr;
}

class btree
{
    public:
		btree() { 
			root = nullptr;
		}
        btree(int key) {
            root = make_unique<node>(key);
        }
        btree(unique_ptr<node> root): root(move(root)) {}
		void insert(int key) {
			if (root) // if root holds an object
				insert(key, *root);
			else
			{
				root = make_unique<node>(key);
			}
		}
		btree search(int key) const {
            if (root) {
			    return search(key, *root);
            }
            return btree();
		}
        friend ostream& operator <<(ostream& os, btree const &bst);

    private:
		void insert(int key, node &leaf) {
			if (key < leaf.key_value)
			{
				if (leaf.left)
					insert(key, *leaf.left);
				else
				{
					leaf.left = make_unique<node>(key);
				}
			}
			else if (key >= leaf.key_value)
			{
				if (leaf.right)
					insert(key, *leaf.right);
				else
				{
					leaf.right = make_unique<node>(key);
				}
			}
		}
		btree search(int key, node const &leaf) const{
			if (key == leaf.key_value) {
				return btree(make_unique<node>(leaf));
            } else if (key < leaf.key_value) {
                if (leaf.left) {
				    return search(key, *leaf.left);
                } else {
                    return btree();
                }
            } else if (key > leaf.key_value) {
                if (leaf.right) {
					return search(key, *leaf.right);
                } else {
                    return btree();
                }
			} else{
                return btree();
            }
		}
        unique_ptr<node> root;
};


// Print the node and its subtree.
//https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
void print_node(ostream& os, string const &prefix, node const &node, bool isLeft) {
    os << prefix;

    os << (isLeft ? "├──" : "└──" );

    // print the value of the node
    os << node.key_value << endl;

    // enter the next tree level - left and right branch
    if (node.left) {
        print_node(os, prefix + (isLeft ? "│   " : "    "), *(node.left), true);
    }
    if (node.right) {
        print_node(os, prefix + (isLeft ? "│   " : "    "), *(node.right), false);
    }
}

// Print the tree.
ostream& operator <<(ostream& os, btree const &bst) {
    if (bst.root) {
        print_node(os, "", *(bst.root), false);
    }
    return os;
}
}
#endif