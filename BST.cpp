#include <iostream>
#include <queue>
#include <limits.h>
#include <vector>
// #include<stack>
using namespace std;
class Tree
{
private:
    int val;
    Tree *left;
    Tree *right;

public:
    Tree()
    {
        val = -1;
        left = right = nullptr;
    }
    Tree(const Tree *obj)
    {
    }
    void insertNewNode(Tree *&, int);
    bool Node_exists(Tree *&, int);
    void deleteNode(Tree *&, int);
    void inorder(Tree *&);
    void preorder(Tree *&);
    void postorder(Tree *&);
    void deleteTree(Tree *&);
    int find_max_elem(Tree *&);
    int find_max_elem_iterative(Tree *&);
    void Level_Order_Traversal_Using_Recursion(Tree *&, int, int);
    // void Level_Order_Traversal_using_Queue(Tree *&);
    int height_BST(Tree *&);
    void DpthOfNode(Tree *&, int, int);
    int NumOfLeafNodes(Tree *&);
    int NumOfFullNodes(Tree *&);
    int NumOfHalfNodes(Tree *&);
    int DiameterOfBST(Tree *&, int);
    int MaxSumLevel(Tree *&);
    void SumOfeachLevel(Tree *&, int, int, int &);
    void RootToLeafPaths(Tree *&, vector<int> &);
    void MirrorTree(Tree *);
    Tree *ConstructIdenticalTree(Tree *&);
    Tree *LCA(Tree *&, int, int);
    void print(Tree *&head)
    {
        cout << head->val << endl;
    }
    void zigzag(Tree *&, int, int);
    void VerticalTraversal(Tree *&, int, int);
    int VerticalTraversalSubProgram(Tree *&, bool);
};
void Tree::insertNewNode(Tree *&head, int value)
{
    if (!head)
    {
        head = new Tree;
        head->val = value;
        head->left = head->right = nullptr;
    }
    else
    {
        int choose = 0;
        if (head->val >= value)
            choose = 1;
        if (choose)
        {
            if (head->left)
                insertNewNode(head->left, value);
            else
            {
                head->left = new Tree;
                Tree *ptr = head->left;
                ptr->val = value;
                ptr->left = ptr->right = nullptr;
            }
        }
        else
        {
            if (head->right)
                insertNewNode(head->right, value);
            else
            {
                head->right = new Tree;
                Tree *ptr = head->right;
                ptr->val = value;
                ptr->left = ptr->right = nullptr;
            }
        }
    }
    return;
}
bool Tree::Node_exists(Tree *&head, int key)
{
    if (!head)
        return false;
    else if (head->val == key)
        return true;
    else
    {
        bool x = Node_exists(head->left, key);
        if (x)
            return true;
        x = Node_exists(head->right, key);
        if (x)
            return true;
    }
    return false;
}
void Tree::deleteNode(Tree *&head, int key)
{
    Tree *aux = head;
    Tree *iterator = nullptr;
    while (aux)
    {
        if (aux->val == key)
            break;
        iterator = aux;
        if (aux->val >= key)
            aux = aux->left;
        else
            aux = aux->right;
    }
    if (!aux)
    {
        cout << "Node doesn't exists!!!\n";
    }
    else
    {
        if (iterator == nullptr)
        {
            if ((!aux->left) && (!aux->right))
            {
                delete aux;
                head = nullptr;
            }
            else if ((aux->left) && (aux->right))
            {
                iterator = aux->right;
                while (iterator->left)
                    iterator = iterator->left;
                iterator->left = aux->left;
                head = aux->right;
                delete aux;
            }
            else
            {
                if (aux->left)
                {
                    head = head->left;
                    delete aux;
                }
                else
                {
                    head = head->right;
                    delete aux;
                }
            }
        }
        else if ((!aux->left) && (!aux->right))
        {
            if (iterator->left == aux)
            {
                delete iterator->left;
                iterator->left = nullptr;
            }
            else
            {
                delete iterator->right;
                iterator->right = nullptr;
            }
            delete aux;
            aux = nullptr;
        }
        else if ((aux->left) && (aux->right))
        {
            Tree *ptr = nullptr;
            if (iterator->right == aux)
            {
                iterator->right = aux->right;
                ptr = iterator->right;
                while (ptr->left)
                {
                    ptr = ptr->left;
                }
                ptr->left = aux->left;
            }
            else
            {
                iterator->left = aux->right;
                ptr = iterator->left;
                while (ptr->left)
                {
                    ptr = ptr->left;
                }
                ptr->left = aux->left;
            }
            delete aux;
        }
        else
        {
            if (iterator->left == aux)
            {
                if (aux->left)
                {
                    iterator->left = aux->left;
                }
                else
                {
                    iterator->left = aux->right;
                }
            }
            else
            {
                if (aux->left)
                {
                    iterator->right = aux->left;
                }
                else
                {
                    iterator->right = aux->right;
                }
            }
            delete aux;
        }
    }
    return;
}
void Tree::preorder(Tree *&head)
{
    if (head)
    {
        cout << head->val << "-> ";
        preorder(head->left);
        preorder(head->right);
    }
    return;
}
void Tree::deleteTree(Tree *&head)
{
    if (!head)
        return;
    else
    {
        deleteTree(head->left);
        deleteTree(head->right);
        delete head;
    }
    return;
}
void Tree::inorder(Tree *&head)
{
    if (head)
    {
        inorder(head->left);
        cout << head->val << "-> ";
        inorder(head->right);
    }
    return;
}
void Tree::postorder(Tree *&head)
{
    if (head)
    {
        postorder(head->left);
        postorder(head->right);
        cout << head->val << "-> ";
    }
    return;
}
int Tree::find_max_elem(Tree *&head)
{
    int x;
    if (!head)
        return -1;
    else
    {
        if (head->right)
        {
            x = head->find_max_elem(head->right);
        }
        else
            return head->val;
    }
    return x;
}
int Tree::find_max_elem_iterative(Tree *&head)
{
    if (!head)
        return -1;
    else
    {
        Tree *ptr = head;
        while (ptr->right)
        {
            ptr = ptr->right;
        }
        return ptr->val;
    }
}
void Tree::Level_Order_Traversal_Using_Recursion(Tree *&head, int currlevel, int level)
{
    if (!head)
    {
        cout << "Tree is Empty!!!\n";
    }
    else if (currlevel > level)
        return;
    else if (currlevel == level)
    {
        cout << head->val << "->";
    }
    else
    {
        if (head->left)
            Level_Order_Traversal_Using_Recursion(head->left, currlevel + 1, level);
        if (head->right)
            Level_Order_Traversal_Using_Recursion(head->right, currlevel + 1, level);
    }
    return;
}
int Tree::NumOfFullNodes(Tree *&head)
{
    if ((!head) || (!head->left) && (!head->right))
        return 0;
    else if ((head->left) && (head->right))
        return 1 + NumOfFullNodes(head->left) + NumOfFullNodes(head->right);
    else
    {
        if (head->left)
            return NumOfFullNodes(head->left);
        if (head->right)
            return NumOfFullNodes(head->right);
    }
}
/*void Tree::Level_Order_Traversal_using_Queue(Tree *&head)
{
    if (!head)
    {
        cout << "Error!!!\nCan't print empty Tree!!!\n";
    }
    else
    {
        queue<Tree *> Queue;
        Tree *ptr = head;
        Queue.push(ptr);
        while (!Queue.empty())
        {
            ptr = Queue.front();
            Queue.pop();
            if (ptr->left)
                Queue.push(ptr->left);
            if (ptr->right)
                Queue.push(ptr->right);
            cout << ptr->val << "->";
        }
    }
    return;
}*/
int Tree::height_BST(Tree *&head)
{
    if (!head)
        return -1;
    return 1 + max(height_BST(head->left), height_BST(head->right));
}
void Tree::DpthOfNode(Tree *&head, int value, int Depth)
{
    if (!head)
    {
        cout << "Node Doesn't exists!!!\n";
    }
    else if (value == head->val)
    {
        cout << "The depth of a Node is:" << Depth << endl;
    }
    else
    {
        if (head->val > value)
            DpthOfNode(head->left, value, Depth + 1);
        else
            DpthOfNode(head->right, value, Depth + 1);
    }
    return;
}
int Tree::DiameterOfBST(Tree *&head, int Diameter)
{
    int LeftsubTree = 1 + height_BST(head->left);
    int Rightsubtree = 1 + height_BST(head->right);
    Diameter = max(Diameter, LeftsubTree + Rightsubtree);
    return Diameter;
}
int Tree::NumOfLeafNodes(Tree *&head)
{
    int x = 0, y = 0;
    if (head->left || head->right)
    {
        if (head->left)
            x = NumOfLeafNodes(head->left);
        if (head->right)
            y = NumOfLeafNodes(head->right);
    }
    else
    {
        return 1;
    }
    return (x + y);
}
int Tree::NumOfHalfNodes(Tree *&head)
{
    if ((!head) || ((!head->left) && (!head->right)))
        return 0;
    else if ((head->left) && (head->right))
        return NumOfHalfNodes(head->left) + NumOfHalfNodes(head->right);
    else
    {
        if (head->left)
            return 1 + NumOfHalfNodes(head->left);
        if (head->right)
            return 1 + NumOfHalfNodes(head->right);
    }
}
void Tree::SumOfeachLevel(Tree *&head, int currlevel, int level, int &sum)
{
    if (!head)
    {
        cout << "Tree is Empty!!!\n";
    }
    else if (currlevel > level)
        return;
    else if (currlevel == level)
    {
        sum += head->val;
    }
    else
    {
        if (head->left)
            SumOfeachLevel(head->left, currlevel + 1, level, sum);
        if (head->right)
            SumOfeachLevel(head->right, currlevel + 1, level, sum);
    }
    return;
}
int Tree::MaxSumLevel(Tree *&head)
{
    int height = height_BST(head);
    int Level = -1;
    int max = INT_MIN;
    for (int i = 0; i <= height; i++)
    {
        int sum = 0;
        SumOfeachLevel(head, 0, i, sum);
        if (max < sum)
        {
            max = sum;
            Level = i;
        }
    }
    return Level;
}
void Tree::RootToLeafPaths(Tree *&head, vector<int> &v)
{
    if (!head)
        return;
    else if ((!head->left) && (!head->right))
    {
        v.push_back(head->val);
        for (int i = 0; i < v.size(); i++)
        {
            cout << v.at(i) << "->";
        }
        cout << "NULL\n";
        v.pop_back();
    }
    else
    {
        v.push_back(head->val);
        if (head->left)
            RootToLeafPaths(head->left, v);
        if (head->right)
            RootToLeafPaths(head->right, v);
        v.pop_back();
    }
    return;
}
void Tree::MirrorTree(Tree *head)
{
    if (!head)
        return;
    else
    {
        Tree *ptr = head->left;
        head->left = head->right;
        head->right = ptr;
        MirrorTree(head->left);
        MirrorTree(head->right);
    }
    return;
}
Tree *Tree::ConstructIdenticalTree(Tree *&head)
{
    if (!head)
        return nullptr;
    Tree *ptr = new Tree;
    ptr->val = head->val;
    ptr->left = ConstructIdenticalTree(head->left);
    ptr->right = ConstructIdenticalTree(head->right);
    return ptr;
}
Tree *Tree::LCA(Tree *&head, int val1, int val2)
{
    if (!head)
        return head;
    else if (head->val == val1 || head->val == val2)
    {
        return head;
    }
    else
    {
        Tree *left = LCA(head->left, val1, val2);
        Tree *right = LCA(head->right, val1, val2);
        if (left && right)
        {
            return head;
        }
        else if (left)
            return left;
        else if (right)
            return right;
    }
}
void Tree::zigzag(Tree *&head, int currlevel, int level)
{
    if (!head)
    {
        cout << "Tree is Empty!!!\n";
    }
    else if (currlevel > level)
        return;
    else if (currlevel == level)
    {
        cout << head->val << "->";
    }
    else
    {
        if (level % 2 == 0)
        {
            if (head->left)
                Level_Order_Traversal_Using_Recursion(head->left, currlevel + 1, level);
            if (head->right)
                Level_Order_Traversal_Using_Recursion(head->right, currlevel + 1, level);
        }
        else
        {
            if (head->right)
                Level_Order_Traversal_Using_Recursion(head->right, currlevel + 1, level);
            if (head->left)
                Level_Order_Traversal_Using_Recursion(head->left, currlevel + 1, level);
        }
    }
    return;
}
void Tree::VerticalTraversal(Tree *&head, int currheight, int targetheight)
{
    if (!head)
        return;
    else if (currheight == targetheight)
    {
        cout << head->val << "->";
    }
    VerticalTraversal(head->left, currheight-1, targetheight);
    VerticalTraversal(head->right, currheight+1, targetheight);
    return;
}
int Tree::VerticalTraversalSubProgram(Tree *&head, bool x)
{
    if (!head)
    {
        if (x)
            return -1;
        else
            return 0;
    }
    else if (x)
    {
        int a = 0;
        Tree *ptr = head;
        while (ptr)
        {
            a++;
            ptr = ptr->right;
        }
        return a;
    }
    else
    {
        int a = 0;
        Tree *ptr = head;
        while (ptr)
        {
            a--;
            ptr = ptr->left;
        }
        return a;
    }
}
int main()
{
    Tree *root = nullptr;
    int select;
    int Nodeval;
    while (1)
    {
        cout << "Enter 1->inserting node\t\t2->deleting Node\t\t3->for searching element\n4->PreOrder Traversal\t\t5->Inorder Traversal\t\t6->postorder Traversal\n7->Delete BST\t\t\t8->Finding maximum BST using recursion\t\t9->Finding maximum element using Iteration\n10->BFS using recursion\t\t11->BFS using Queue\t\t12->height of Tree\t\t13->Depth of Node\n14->Number of Leaf Nodes:\t\t15->Number of Full Nodes\t\t16->Number of Half Nodes\t\t17->Diameter of BST\n18->Level having maximum sum\t\t19->Print root to Leaf path\t\t";
        cout << "20->Mirror Tree\n21->Construct Identical BST\t\t22->Least Common Ancestor of two node\t\t23->ZigZag Traversal\t\t24->vertical Traversal\n25->exit:";
        do
        {
            cin >> select;
            if (select < 1 || select > 25)
            {
                cout << "ERROR!!!\nplease carefully enter the required field:";
            }
        } while (select < 1 || select > 25);
        if (select == 1)
        {
            cout << "Enter the value that you want to insert in Tree:";
            cin >> Nodeval;
            root->insertNewNode(root, Nodeval);
        }
        else if (select == 2)
        {
            cout << "Enter the Node value that you want to Delete:";
            cin >> Nodeval;
            root->deleteNode(root, Nodeval);
        }
        else if (select == 3)
        {
            cout << "Enter the Node value that you want to Search:";
            cin >> Nodeval;
            if (root->Node_exists(root, Nodeval))
            {
                cout << "Node exists\n";
            }
            else
            {
                cout << "Node doesn't exists!!!\n";
            }
        }
        else if (select == 4)
        {
            root->preorder(root);
            cout << "Null\n";
        }
        else if (select == 5)
        {
            root->inorder(root);
            cout << "Null\n";
        }
        else if (select == 6)
        {
            root->postorder(root);
            cout << "Null\n";
        }
        else if (select == 7)
        {
            root->deleteTree(root);
            root = nullptr;
        }
        else if (select == 8)
        {
            int max = root->find_max_elem(root);
            if (max == -1)
            {
                cout << "Tree is Empty!!!\nNo maximum element exists!!!\n";
            }
            else
            {
                cout << "Maximum element of the given tree is:" << max << endl;
            }
        }
        else if (select == 9)
        {
            int max = root->find_max_elem_iterative(root);
            if (max == -1)
            {
                cout << "Tree is Empty!!!\nNo maximum element exists!!!\n";
            }
            else
            {
                cout << "Maximum element of the given tree is:" << max << endl;
            }
        }
        else if (select == 10)
        {
            for (int i = 0; i <= root->height_BST(root); i++)
            {
                root->Level_Order_Traversal_Using_Recursion(root, 0, i);
            }
            cout << "NULL\n";
        }
        else if (select == 11)
        {
            // root->Level_Order_Traversal_using_Queue(root);
        }
        else if (select == 12)
        {
            cout << "Height of BST is:" << root->height_BST(root) << endl;
        }
        else if (select == 13)
        {
            int Node;
            cout << "Enter Node value:";
            cin >> Node;
            root->DpthOfNode(root, Node, 0);
        }
        else if (select == 14)
        {
            if (!root)
            {
                cout << "Tree is Empty!!!\n";
            }
            else
            {
                cout << "Number of Leaf Nodes in BST:" << root->NumOfLeafNodes(root) << endl;
            }
        }
        else if (select == 15)
        {
            cout << "Number of Full Nodes in  BST is:" << root->NumOfFullNodes(root) << endl;
        }
        else if (select == 16)
        {
            cout << "Number of Half Nodes in  BST is:" << root->NumOfHalfNodes(root) << endl;
        }
        else if (select == 17)
        {
            cout << "Diameter of BST is:" << root->DiameterOfBST(root, 0) << endl;
        }
        else if (select == 18)
        {
            int x = root->MaxSumLevel(root);
            if (x == -1)
            {
                cout << "Tree is Empty!!!\nLevel containing maximum sum of Nodes doesn't exists!!!\n";
            }
            else
            {
                cout << "Level containing maximum Sum of Nodes is:" << root->MaxSumLevel(root) << endl;
            }
        }
        else if (select == 19)
        {
            vector<int> v;
            root->RootToLeafPaths(root, v);
        }
        else if (select == 20)
        {
            cout << "Given BST is:";
            root->preorder(root);
            cout << "NULL\n";
            cout << "Mirror Tree is:";
            root->MirrorTree(root);
            root->preorder(root);
            cout << "NULL\n";
        }
        else if (select == 21)
        {
            Tree *ptr = root->ConstructIdenticalTree(root);
            cout << "Given Identical BST IS:";
            root->preorder(ptr);
            cout << "NULL\n";
            ptr->deleteTree(ptr);
        }
        else if (select == 22)
        {
            bool x, y;
            int val1, val2;
            cout << "Enter first node value:";
            cin >> val1;
            cout << "Enter second node value:";
            cin >> val2;
            if (root->Node_exists(root, val1) && root->Node_exists(root, val2))
            {
                Tree *ptr = root->LCA(root, val1, val2);
                cout << "The Lowest COMMON Ancestor of Node of val:" << val1 << " and value:" << val2 << " is:";
                root->print(ptr);
            }
            else
            {
                cout << "either/both of the node doesn't exists!!!\n";
            }
        }
        else if (select == 23)
        {
            for (int i = 0; i <= root->height_BST(root); i++)
            {
                root->zigzag(root, 0, i);
            }
            cout << "NULL\n";
        }
        else if (select == 24)
        {
            int maxleft, maxright;
            maxleft = root->VerticalTraversalSubProgram(root, false);
            maxright = root->VerticalTraversalSubProgram(root, true);
            for (int i = maxleft; i <= maxright; i++)
            {
                root->VerticalTraversal(root, 0, i);
            }
            cout << "NULL\n";
        }
        else
            break;
    }
    if (root)
        root->deleteTree(root);
    return 0;
}