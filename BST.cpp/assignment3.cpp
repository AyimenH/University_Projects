#include "BST.h"

int main(){
    bool end = true;
    int Case;
    BST BSTree;
    
    while (end != false){
        cout << "Please select an operation to test:\n" << endl;
        cout << "1. Insert a node" << endl
        << "2. Search for a value" << endl
        << "3. Find the predecessor for an existing value" << endl
        << "4. Find the successor for an existing value" << endl
        << "5. Find the height of tree" << endl
        << "6. Find the total number of nodes in tree" << endl
        << "7. Delete a node" << endl
        << "8. Traverse inorder and display" << endl
        << "9. Traverse preorder and display" << endl
        << "10. Traverse postorder and display" << endl
        << "11. Check if a tree is balanced" << endl
        << "12. Destroy tree" << endl
        << "0. Quit" << endl;
        
        cout << "Choice: ";
        cin >> Case;
        
        switch(Case)
        {
            case 1:
                cout << "Enter a value to insert: ";
                cin >> Case;
                if(BSTree.searchNode(Case) == -1)
                {
                    BSTree.insertNode(Case);
                }
                else
                {
                    cout << "Already Exists" << endl;
                }
                break;
            case 2:
                cout << "Enter a value to search for: ";
                cin >> Case;
                cout << BSTree.searchNode(Case) << endl;
                break;
            case 3:
                cout << "Enter a value to find its predecessor: ";
                cin >> Case;
                if(BSTree.pred(Case) == 0)
                {
                    cout << "The predecessor does not exist" << endl;
                }
                else
                {
                    cout << BSTree.pred(Case) << endl;
                }
                break;
            case 4:
                cout << "Enter a value to find its successor: ";
                cin >> Case;
                if(BSTree.succ(Case) == 0)
                {
                    cout << "The successor does not exist" << endl;
                }
                else
                {
                    cout << BSTree.succ(Case) << endl;
                }
                break;
            case 5:
                cout << "The height of your Binary Search Tree is " << BSTree.getHeight() << endl;
                break;
            case 6:
                cout << "The total amount of nodes is " << BSTree.totalNodes() << endl;
                break;
            case 7:
                cout << "Enter a leaf value to remove: ";
                cin >> Case;
                BSTree.del(Case);
                break;
            case 8:
                BSTree.inorderDisplay();
                break;
            case 9:
                BSTree.preorderDisplay();
                break;
            case 10:
                BSTree.postorderDisplay();
                break;
            case 11:
                cout << BSTree.isBalanced() << endl;
                break;
            case 12:
                cout << "Deleting the tree" << endl;
                BSTree.desTree();
                break;
            case 0:
                cout << "Exiting program" << endl;
                end = false;
                break;
            default:
                cout << "Invalid Input, Try again: ";
                cin >> Case;
                cout << endl;
                break;
        }
    }
}
