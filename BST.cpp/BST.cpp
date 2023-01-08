#include "BST.h"

BST::TreeNode *BST::insert(TreeNode *t, int x)
{
  if (root == nullptr)
  {
    t = new TreeNode;
    root = t;

    t->val = x;
    t->left = nullptr;
    t->right = nullptr;
    return root;
  }

  else if (t == nullptr)
  {
    t = new TreeNode;

    t->val = x;
    t->left = nullptr;
    t->right = nullptr;
    return t;
  }

  else if (x < t->val)
  {
    t->left = insert(t->left, x);
  }

  else
  {
    t->right = insert(t->right, x);
  }
  return t;
}

void BST::inorder(TreeNode* t)
{
  if (t != nullptr)
  {
    inorder(t->left);
    cout << t->val << endl;
    inorder(t->right);
  }
}

void BST::preorder(TreeNode* t)
{
  if (t != nullptr)
  {
    cout << t->val << endl;
    preorder(t->left);
    preorder(t->right);
  }
}

void BST::postorder(TreeNode* t)
{
  if (t != nullptr)
  {
    postorder(t->left);
    postorder(t->right);
    cout << t->val << endl;
  }
}

BST::BST()
{
  root = nullptr;
}

void BST::insertNode(int x)
{
    root = insert(root, x);
}

void BST::inorderDisplay()
{
    inorder(root);
}
void BST::preorderDisplay()
{
    preorder(root);
}
void BST::postorderDisplay()
{
    postorder(root);
}

// Predecessor & Successor Functionallity

vector<int> BST::orderVector(TreeNode* t)
{
    stack<TreeNode*> Temporary;
    TreeNode* Current = t;
    vector<int> Node;
    
    while(true)
    {
        if(Current != nullptr)
        {
            Temporary.push(Current);
            Current = Current->left;
        }
        else{
            if(Temporary.empty() == true)
            {
                break;
            }
            Current = Temporary.top();
            Temporary.pop();
            Node.push_back(Current->val);
            Current = Current->right;
        }
    }
    return Node;
}

int BST::predecessor(int x)
{
    vector<int> Node = orderVector(root);
    for (int i = 0; i < Node.size(); i++)
    {
        if(x == Node.at(i))
        {
            return Node[i-1];
        }
    }
    return 0;
}

int BST::pred(int x)
{
    return predecessor(x);
}

int BST::successor(int x)
{
    vector<int> Node = orderVector(root);
    for (int i = 0; i < Node.size(); i++)
    {
        if(x == Node.at(i))
        {
            return Node[i+1];
        }
    }
    return 0;
}

int BST::succ(int x)
{
    return successor(x);
}

 int BST::totalNodes()
{
     vector<int> nodeSize = orderVector(root);
     return nodeSize.size();
}

// Search Functionallity

int currNode;
int BST::search(TreeNode* t, int x)
{
    if (t == nullptr)
    {
        return -1;
    }
    if (t->val == x)
    {
        return 1;
    }
    if (x < t->val)
    {
      currNode = search(t->left, x);
    }
    else
    {
       currNode = search(t->right, x);
    }
    if(currNode == 1)
    {
        return currNode;
    }
    else
    {
        return -1;
    }
}

int BST::searchNode(int x)
{
    return search(root, x);
}

// Height & Balanced Functionallity

int BST::height(TreeNode* t)
{
    if (t == nullptr)
    {
        return -1;
    }
    else
    {
        int leftHeight = height(t->left);
        int rightHeight = height(t->right);
        
        return max(leftHeight, rightHeight) + 1;
    }
}

int BST::getHeight()
{
    return height(root);
}

int BST::isBalanced()
{
    if(root == nullptr)
    {
        return 1;
    }
    
    int leftBalance = height(root->left);
    int rightBalance = height(root->right);
    
    if (abs(leftBalance - rightBalance) <= 1)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// Deletion & Destroy Functionallity

BST::TreeNode* BST::delNode(TreeNode* node, int x)
{
    if (node == nullptr)
    {
        return nullptr;
    }
   if(node->val == x)
    {
        node = nullptr;
        return nullptr;
    }
    
    node->left = delNode(node->left, x);
    node->right = delNode(node->right, x);
    
    return node;
}

BST::TreeNode* BST::del(int x)
{
    return delNode(root, x);
}

BST::TreeNode* BST::des(TreeNode* root)
{
    if(root != nullptr)
    {
        des(root->left);
        des(root->right);
        delete(root);
    }
    return nullptr;
}

BST::TreeNode* BST::desTree()
{
    return des(root);
}
