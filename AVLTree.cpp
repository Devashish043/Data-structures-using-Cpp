#include <iostream>
#include <memory>
#include <vector>
#include <stack>
using namespace std;
class AVLTree
{
private:
    int val;
    shared_ptr<AVLTree> Left;
    shared_ptr<AVLTree> Right;
    int height;

public:
    AVLTree()
    {
        height = 0;
        Left = Right = nullptr;
    }
    shared_ptr<AVLTree> InsertNode(shared_ptr<AVLTree> &, int);
    shared_ptr<AVLTree> LeftLeftRotation(shared_ptr<AVLTree> &);
    shared_ptr<AVLTree> RightRightRotation(shared_ptr<AVLTree> &);
    shared_ptr<AVLTree> RightLeftRotation(shared_ptr<AVLTree> &);
    shared_ptr<AVLTree> LeftRightRotation(shared_ptr<AVLTree> &);
    int heightOfAVLTree(shared_ptr<AVLTree> &);
    shared_ptr<AVLTree> DeleteNode(shared_ptr<AVLTree> &, int);
    void PreOrderTraversal(shared_ptr<AVLTree> &);
    void AVLRangePrint(shared_ptr<AVLTree> &, int, int);
    bool Node_exists(shared_ptr<AVLTree> &, int);
};
bool AVLTree::Node_exists(shared_ptr<AVLTree> &head, int key)
{
    if (!head)
        return false;
    else if (head->val == key)
        return true;
    else
    {
        bool x = Node_exists(head->Left, key);
        if (x)
            return true;
        x = Node_exists(head->Right, key);
        if (x)
            return true;
    }
    return false;
}
int AVLTree::heightOfAVLTree(shared_ptr<AVLTree> &head)
{
    if (!head)
        return -1;
    return 1 + max(heightOfAVLTree(head->Left), heightOfAVLTree(head->Right));
}
shared_ptr<AVLTree> AVLTree::LeftLeftRotation(shared_ptr<AVLTree> &root)
{
    auto ptr1 = root;
    auto ptr2 = root->Left->Right;
    root = root->Left;
    root->Right = ptr1;
    ptr1->Left = ptr2;
    root->Left->height = heightOfAVLTree(root->Left);
    root->Right->height = heightOfAVLTree(root->Right);
    root->height = 1 + max(root->Left->height, root->Right->height);
    return root;
}
shared_ptr<AVLTree> AVLTree::RightRightRotation(shared_ptr<AVLTree> &root)
{
    auto ptr1 = root;
    auto ptr2 = root->Right->Left;
    root = root->Right;
    root->Left = ptr1;
    ptr1->Right = ptr2;
    root->Left->height = heightOfAVLTree(root->Left);
    root->Right->height = heightOfAVLTree(root->Right);
    root->height = 1 + max(root->Left->height, root->Right->height);
    return root;
}
shared_ptr<AVLTree> AVLTree::LeftRightRotation(shared_ptr<AVLTree> &root)
{
    auto ptr1 = root;
    auto ptr2 = root->Left->Right->Left;
    auto ptr3 = root->Left->Right->Right;
    root = root->Left->Right;
    root->Right = ptr1;
    root->Left = ptr1->Left;
    ptr1->Left = ptr3;
    ptr1 = root->Left;
    ptr1->Right = ptr2;
    root->Left->height = heightOfAVLTree(root->Left);
    root->Right->height = heightOfAVLTree(root->Right);
    root->height = 1 + max(root->Left->height, root->Right->height);
    return root;
}
shared_ptr<AVLTree> AVLTree::RightLeftRotation(shared_ptr<AVLTree> &root)
{
    auto ptr1 = root;
    root = root->Right->Left;
    auto leftref = root->Left;
    auto rightref = root->Right;
    root->Left = ptr1;
    root->Right = ptr1->Right;
    ptr1->Right = leftref;
    ptr1 = root->Right;
    ptr1->Left = rightref;
    root->Left->height = heightOfAVLTree(root->Left);
    root->Right->height = heightOfAVLTree(root->Right);
    root->height = 1 + max(root->Left->height, root->Right->height);
    return root;
}
shared_ptr<AVLTree> AVLTree::InsertNode(shared_ptr<AVLTree> &root, int key)
{
    if (!root)
    {
        root = make_shared<AVLTree>();
        root->val = key;
        return root;
    }

    if (key > root->val)
    {
        root->Right = InsertNode(root->Right, key);
    }
    else if (key < root->val)
    {
        root->Left = InsertNode(root->Left, key);
    }
    int LeftSubtreeheight = -1;
    int RightSubtreeheight = -1;
    int BalanceFactor;
    if (root->Left)
        LeftSubtreeheight = root->Left->height;
    if (root->Right)
        RightSubtreeheight = root->Right->height;
    BalanceFactor = LeftSubtreeheight - RightSubtreeheight;
    if (BalanceFactor > 1)
    {
        if (key < root->Left->val)
        {
            root = LeftLeftRotation(root);
        }
        else
        {
            root = LeftRightRotation(root);
        }
    }
    else if (BalanceFactor < -1)
    {
        if (key > root->Right->val)
        {
            root = RightRightRotation(root);
        }
        else
        {
            root = RightLeftRotation(root);
        }
    }
    LeftSubtreeheight = -1;
    RightSubtreeheight = -1;
    if (root->Left)
        LeftSubtreeheight = root->Left->height;
    if (root->Right)
        RightSubtreeheight = root->Right->height;
    root->height = 1 + max(LeftSubtreeheight, RightSubtreeheight);
    return root;
}
shared_ptr<AVLTree> AVLTree::DeleteNode(shared_ptr<AVLTree> &root, int key)
{
    if (!root)
        return nullptr;
    stack<shared_ptr<AVLTree>> S;
    auto ptr = root;
    while (ptr)
    {
        if (ptr->val == key)
            break;
        else if (key > ptr->val)
        {
            S.push(ptr);
            ptr = ptr->Right;
        }
        else
        {
            S.push(ptr);
            ptr = ptr->Left;
        }
    }
    if (!ptr)
        return nullptr;
    if (ptr->Left && ptr->Right)
    {
        S.push(ptr);
        auto ptr1 = ptr->Right;
        while (ptr1->Left)
        {
            S.push(ptr1);
            ptr1 = ptr1->Left;
        }
        ptr->val = ptr1->val;
        if ((!ptr1->Left) && (!ptr1->Right))
        {
            ptr = S.top();
            if (ptr->Left == ptr1)
                ptr->Left = nullptr;
            else
                ptr->Right = nullptr;
            ptr->height = heightOfAVLTree(ptr);
        }
        else if (ptr1->Right)
        {
            ptr = S.top();
            ptr->Left = ptr1->Right;
            ptr->height = heightOfAVLTree(ptr);
        }
    }
    else if (ptr->Left || ptr->Right)
    {
        if (S.empty())
        {
            if (root->Left)
            {
                root = root->Left;
            }
            else
                root = root->Right;
            return root;
        }
        auto ptr1 = S.top();
        if (ptr1->Left == ptr)
        {
            if (ptr->Left)
            {
                ptr1->Left = ptr->Left;
                ptr1->height = heightOfAVLTree(ptr1);
            }

            else
            {
                ptr1->Left = ptr->Right;
                ptr1->height = heightOfAVLTree(ptr1);
            }
        }
        else
        {
            if (ptr->Left)
                ptr1->Right = ptr->Left;
            else
                ptr1->Right = ptr->Right;
            ptr1->height = heightOfAVLTree(ptr1);
        }
    }
    else
    {
        if (!S.empty())
        {
            S.pop();
            auto ptr1 = S.top();
            if (ptr1->Left == ptr)
                ptr1->Left = nullptr;
            else
                ptr1->Right = nullptr;
            ptr1->height = heightOfAVLTree(ptr1);
        }
        else
            root = nullptr;
    }

    while (!S.empty())
    {
        int Balancefactor = -1;
        ptr = S.top();
        S.pop();
        if (ptr->Left)
            Balancefactor = ptr->Left->height;
        if (ptr->Right)
            Balancefactor -= ptr->Right->height;
        if (Balancefactor > 1)
        {
            if (ptr->Left->Left)
                ptr = LeftLeftRotation(ptr);
            else
                ptr = LeftRightRotation(ptr);
        }
        else if (Balancefactor < -1)
        {
            if (ptr->Right->Right)
                ptr = RightRightRotation(ptr);
            else
                ptr = RightLeftRotation(ptr);
        }
    }
    return root;
}
void AVLTree::PreOrderTraversal(shared_ptr<AVLTree> &head)
{
    if (head)
    {
        cout << head->val << "-> ";
        PreOrderTraversal(head->Left);
        PreOrderTraversal(head->Right);
    }
    return;
}
void AVLTree::AVLRangePrint(shared_ptr<AVLTree> &root, int RangeMinval, int RangeMaxval)
{
    if (!root)
        return;
    else if (root->val < RangeMinval)
    {
        if (root->Right)
            AVLRangePrint(root->Right, RangeMinval, RangeMaxval);
    }
    else
    {
        if (root->val > RangeMaxval)
        {
            if (root->Left)
                AVLRangePrint(root->Left, RangeMinval, RangeMaxval);
        }
        else
        {
            cout << root->val << "->";
            if (root->Left)
                AVLRangePrint(root->Left, RangeMinval, RangeMaxval);
            if (root->Right)
                AVLRangePrint(root->Right, RangeMinval, RangeMaxval);
        }
    }
    return;
}
int main()
{
    vector<shared_ptr<AVLTree>> Tree;
    while (1)
    {
        int select;
        cout << "Enter 1->Creating AVLTree\n2->Inserting Node in AVL Tree\n3->Deleting Node in AVLTree\n4->PreOder Traversal\n5->Print Nodes of a given Range\n6->exit:";
        while (1)
        {
            cin >> select;
            if (select < 1 || select > 6)
                cout << "Invalid choice!!!\nplease enter the valid choice:";
            else
                break;
        }
        if (select == 1)
        {
            shared_ptr<AVLTree> ptr;
            Tree.push_back(ptr);
        }

        else if (select == 2)
        {
            int Index;
            cout << "enter the Index of AVLTree at which you want to Insert new Node:\nNote:Indexing will start from zero\nIndex:";
            while (1)
            {
                cin >> Index;
                if (Index < 0 || Index >= Tree.size())
                    cout << "Invalid choice!!!\nplease enter the valid index:";
                else
                    break;
            }
            int Nodeval;
            cout << "Enter the Node value which you want to Insert:";
            cin >> Nodeval;
            auto result = Tree[Index]->InsertNode(Tree[Index], Nodeval);
            if (!result)
                cout << "Insert Operation Failed!!!\n";
            else
            {
                Tree[Index] = result;
                cout << "Node Inserted Successfully\n";
            }
        }
        else if (select == 3)
        {
            int Index;
            cout << "enter the Index of AVLTree at which you want to Perform Delete Operation:\nNote:Indexing will start from zero\nIndex:";
            while (1)
            {
                cin >> Index;
                if (Index < 0 || Index >= Tree.size())
                    cout << "Invalid choice!!!\nplease enter the valid index:";
                else
                    break;
            }
            int Nodeval;
            cout << "Enter the Node value which you want to Delete:";
            cin >> Nodeval;
            auto Node = Tree[Index]->DeleteNode(Tree[Index], Nodeval);
            if (!Node)
                cout << "Delete Operation Failed!!!\n";
            else
            {
                Tree[Index] = Node;
                cout << "Node Deleted Successfully!!!\n";
            }
        }
        else if (select == 4)
        {
            int Index;
            cout << "enter the Index of AVLTree at which you want to Perform Delete Operation:\nNote:Indexing will start from zero\nIndex:";
            while (1)
            {
                cin >> Index;
                if (Index < 0 || Index >= Tree.size())
                    cout << "Invalid choice!!!\nplease enter the valid index:";
                else
                    break;
            }
            Tree[Index]->PreOrderTraversal(Tree[Index]);
            cout << "NULL\n";
        }
        else if (select == 5)
        {
            int Index;
            cout << "enter the Index of AVLTree at which you want to Perform range based print operation\nNote:Indexing will start from zero\nIndex:";
            while (1)
            {
                cin >> Index;
                if (Index < 0 || Index >= Tree.size())
                    cout << "Invalid choice!!!\nplease enter the valid index:";
                else
                    break;
            }
            int RangeMinval, RangeMaxval;
            cout << "Enter Range lower Bound:";
            cin >> RangeMinval;
            cout << "Enter Range upper Bound:";
            cin >> RangeMaxval;
            if (Tree[Index]->Node_exists(Tree[Index], RangeMinval && Tree[Index]->Node_exists(Tree[Index], RangeMaxval)))
            {
                Tree[Index]->AVLRangePrint(Tree[Index], RangeMinval, RangeMaxval);
            }
            else
            {
                cout << "Either/both Upper bound/Lower bound doesn't exists!!!\nOperation Aborted!!!\n";
            }
        }
        else break;
    }
    return 0;
}