#ifndef BST_h
#define BST_h

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class BST {
private:
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
    };

    TreeNode* root;
    TreeNode* insert(TreeNode* t, int x);
    
    void inorder(TreeNode* t);
    void preorder(TreeNode* t);
    void postorder(TreeNode* t);
    
    vector<int> orderVector(TreeNode* t);
    int predecessor(int x);
    int successor(int x);
    
    int search(TreeNode* t, int x);
    int height(TreeNode* t);
    
    TreeNode* delNode(TreeNode* root, int x);
    TreeNode* des(TreeNode* root);
    
 public:
    
    BST();
    
    void insertNode(int x);
    
    void inorderDisplay();
    void preorderDisplay();
    void postorderDisplay();
    
    int pred(int x);
    int succ(int x);
    
    int searchNode(int x);
    int getHeight();
    int isBalanced();
    int totalNodes();
    
    TreeNode* del(int x);
    TreeNode* desTree();
    
};



#endif
