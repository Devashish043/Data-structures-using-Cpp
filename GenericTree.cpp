#include <iostream>
#include <vector>
#include <memory>
#include <climits>
using namespace std;

int intPow(int base, int exp)
{
  int result = 1;
  while (exp--)
    result *= base;
  return result;
}

class GenericTreeInfo
{
public:
  int Level;
  int MaxNoOfNodes;
  int CurrentNoOfNodes;

  GenericTreeInfo()
  {
    Level = -1;
    MaxNoOfNodes = INT_MIN;
    CurrentNoOfNodes = INT_MIN;
  }

  void UpdateValues(int x)
  {
    if (Level == -1)
    {
      Level = 0;
      CurrentNoOfNodes = 0;
      MaxNoOfNodes = 1;
    }
    else if (MaxNoOfNodes == CurrentNoOfNodes)
    {
      Level++;
      CurrentNoOfNodes = 0;
      MaxNoOfNodes = intPow(x, Level);
    }
  }
};

template <typename T>
class GenericTree
{
private:
  T val;
  vector<shared_ptr<GenericTree<T>>> children;

public:
  shared_ptr<GenericTree<T>> InsertNode(shared_ptr<GenericTree<T>> &);
  shared_ptr<GenericTree<T>> FindNode(shared_ptr<GenericTree<T>> &, T);
  void PreOrderTraversal(shared_ptr<GenericTree<T>> &);
};

template <typename T>
class CompleteGenericTree
{
private:
  T val;
  vector<shared_ptr<CompleteGenericTree<T>>> children;
  int currsize;

public:
  static int MaxNoOfChildren;

  CompleteGenericTree()
  {
    currsize = 0;
    children.reserve(MaxNoOfChildren);
  }

  shared_ptr<CompleteGenericTree<T>> InsertNode(shared_ptr<CompleteGenericTree<T>> &, int, GenericTreeInfo &);
  bool FindNode(shared_ptr<CompleteGenericTree<T>> &, T);
  void preOrderTraversal(shared_ptr<CompleteGenericTree<T>> &);
  void InitializeStaticData(int x)
  {
    MaxNoOfChildren = x;
  }
};

template <typename T>
int CompleteGenericTree<T>::MaxNoOfChildren = 0;

// Helper function for safe index input
int getValidIndex(int size, const string &prompt)
{
  int index;
  while (true)
  {
    cout << prompt;
    cin >> index;
    if (index < 0 || index >= size)
      cout << "Invalid Index!!! Re-enter:\n";
    else
      return index;
  }
}

// ------------------- Generic Tree ----------------------
template <typename T>
shared_ptr<GenericTree<T>> GenericTree<T>::InsertNode(shared_ptr<GenericTree<T>> &root)
{
  T value;
  cout << "Enter the value you want to insert: ";
  cin >> value;

  if (!root)
  {
    root = make_shared<GenericTree<T>>();
    root->val = value;
  }
  else
  {
    shared_ptr<GenericTree<T>> ptr = make_shared<GenericTree<T>>();
    ptr->val = value;
    root->children.push_back(ptr);
    return ptr;
  }
  return root;
}

template <typename T>
shared_ptr<GenericTree<T>> GenericTree<T>::FindNode(shared_ptr<GenericTree<T>> &root, T value)
{
  if (!root)
    return nullptr;
  if (root->val == value)
    return root;

  for (auto &child : root->children)
  {
    shared_ptr<GenericTree<T>> result = FindNode(child, value);
    if (result)
      return result;
  }
  return nullptr;
}

template <typename T>
void GenericTree<T>::PreOrderTraversal(shared_ptr<GenericTree<T>> &root)
{
  if (!root)
    return;
  cout << root->val << " -> ";
  for (auto &child : root->children)
    PreOrderTraversal(child);
}

// ---------------- Complete Generic Tree --------------------
template <typename T>
shared_ptr<CompleteGenericTree<T>> CompleteGenericTree<T>::InsertNode(shared_ptr<CompleteGenericTree<T>> &root, int currlevel, GenericTreeInfo &A)
{
  if (currlevel >= A.Level)
    return nullptr;

  if (currlevel + 1 == A.Level)
  {
    T value;
    if (!root)
    {
      root = make_shared<CompleteGenericTree<T>>();
      cout << "Enter the value you want to insert: ";
      cin >> value;
      root->val = value;
      A.CurrentNoOfNodes++;
    }
    else
    {
      if (root->currsize >= MaxNoOfChildren)
        return nullptr;
      cout << "Enter the value you want to insert: ";
      cin >> value;
      auto ptr = make_shared<CompleteGenericTree<T>>();
      ptr->val = value;
      root->children.push_back(ptr);
      root->currsize++;
      A.CurrentNoOfNodes++;
      return ptr;
    }
  }
  else
  {
    for (auto &child : root->children)
    {
      auto result = InsertNode(child, currlevel + 1, A);
      if (result)
        return result;
    }
  }
  return nullptr;
}

template <typename T>
bool CompleteGenericTree<T>::FindNode(shared_ptr<CompleteGenericTree<T>> &root, T value)
{
  if (!root)
    return false;
  if (root->val == value)
    return true;

  for (auto &child : root->children)
    if (FindNode(child, value))
      return true;

  return false;
}

template <typename T>
void CompleteGenericTree<T>::preOrderTraversal(shared_ptr<CompleteGenericTree<T>> &root)
{
  if (!root)
    return;
  cout << root->val << " -> ";
  for (auto &child : root->children)
    preOrderTraversal(child);
}

// ------------------ Main ------------------
int main()
{
  int DataType = 4, MaxNoOfTrees, CurrentNoOfTrees = 0;
  cout << "Enter max number of Tree creation Limit: ";
  cin >> MaxNoOfTrees;

  cout << "Choose data type:\n1 -> int\t2 -> float\t3 -> char\nchoice: ";
  while (DataType < 1 || DataType > 3)
  {
    cin >> DataType;
    if (DataType < 1 || DataType > 3)
      cout << "Invalid Input!!!\nchoice: ";
  }

  if (DataType == 1)
  {
    int TypeOfGenericTree = 2;
    cout << "Enter:\t0 -> Generic Tree\t1 -> Complete Generic Tree\nchoice: ";
    while (TypeOfGenericTree < 0 || TypeOfGenericTree > 1)
    {
      cin >> TypeOfGenericTree;
      if (TypeOfGenericTree < 0 || TypeOfGenericTree > 1)
        cout << "Invalid Input!!!\nchoice: ";
    }

    if (TypeOfGenericTree == 0)
    {
      vector<shared_ptr<GenericTree<int>>> v;
      while (true)
      {
        int choice;
        cout << "\n1->Create Generic Tree\n2->Insert Node\n3->Find Node\n4->PreOrder Traversal\n5->Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
          if (CurrentNoOfTrees >= MaxNoOfTrees)
          {
            cout << "Maximum Tree Limit Reached!\n";
            continue;
          }
          shared_ptr<GenericTree<int>> ptr;
          v.push_back(ptr);
          CurrentNoOfTrees++;
        }
        else if (choice == 2)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to insert node: ");
          if(!v.at(idx)){
            auto ptr=v[idx]->InsertNode(v[idx]);
            continue;
          }
          int Nodeval;
          cout << "Enter node value to insert at: ";
          cin >> Nodeval;
          auto ptr = v[idx]->FindNode(v[idx], Nodeval);
          if (!ptr)
            cout << "Node not found!\n";
          else
            ptr->InsertNode(ptr);
        }
        else if (choice == 3)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to search: ");
          int Nodeval;
          cout << "Enter node value to search: ";
          cin >> Nodeval;
          auto ptr = v[idx]->FindNode(v[idx], Nodeval);
          if (!ptr)
            cout << "Node not found!\n";
          else
            cout << "Node exists.\n";
        }
        else if (choice == 4)
        {
          int idx = getValidIndex(v.size(), "Enter tree index for traversal: ");
          v[idx]->PreOrderTraversal(v[idx]);
          cout << "NULL\n";
        }
        else
          break;
      }
    }
    else
    {
      int x;
      cout << "Enter maximum number of children per node: ";
      cin >> x;

      CompleteGenericTree<int> temp;
      temp.InitializeStaticData(x);

      vector<shared_ptr<CompleteGenericTree<int>>> v;
      vector<GenericTreeInfo> Info;

      while (true)
      {
        int choice;
        cout << "\n1->Create Complete Tree\n2->Insert Node\n3->Find Node\n4->PreOrder Traversal\n5->Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
          if (CurrentNoOfTrees >= MaxNoOfTrees)
          {
            cout << "Max Tree Limit Reached!\n";
            continue;
          }
          shared_ptr<CompleteGenericTree<int>> ptr;
          v.push_back(ptr);
          GenericTreeInfo infoObj;
          Info.push_back(infoObj);
          CurrentNoOfTrees++;
        }
        else if (choice == 2)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to insert node: ");
          Info[idx].UpdateValues(x);
          v[idx]->InsertNode(v[idx], -1, Info[idx]);
          
        }
        else if (choice == 3)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to search: ");
          int Nodeval;
          cout << "Enter node value to search: ";
          cin >> Nodeval;
          if (v[idx]->FindNode(v[idx], Nodeval))
            cout << "Node exists\n";
          else
            cout << "Node not found!\n";
        }
        else if (choice == 4)
        {
          int idx = getValidIndex(v.size(), "Enter tree index for traversal: ");
          v[idx]->preOrderTraversal(v[idx]);
          cout << "NULL\n";
        }
        else
          break;
      }
    }
  }
  else if (DataType == 2)
  { // ---- FLOAT SUPPORT ----
    int TypeOfGenericTree = 2;
    cout << "Enter:\t0 -> Generic Tree\t1 -> Complete Generic Tree\nchoice: ";
    while (TypeOfGenericTree < 0 || TypeOfGenericTree > 1)
    {
      cin >> TypeOfGenericTree;
      if (TypeOfGenericTree < 0 || TypeOfGenericTree > 1)
        cout << "Invalid Input!!!\nchoice: ";
    }

    if (TypeOfGenericTree == 0)
    {
      vector<shared_ptr<GenericTree<float>>> v;
      while (true)
      {
        int choice;
        cout << "\n1->Create Generic Tree\n2->Insert Node\n3->Find Node\n4->PreOrder Traversal\n5->Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
          if (CurrentNoOfTrees >= MaxNoOfTrees)
          {
            cout << "Maximum Tree Limit Reached!\n";
            continue;
          }
          shared_ptr<GenericTree<float>> ptr;
          v.push_back(ptr);
          CurrentNoOfTrees++;
        }
        else if (choice == 2)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to insert node: ");
          if(!v.at(idx)){
            auto ptr=v[idx]->InsertNode(v[idx]);
            continue;
          }
          float Nodeval;
          cout << "Enter node value to insert at: ";
          cin >> Nodeval;
          auto ptr = v[idx]->FindNode(v[idx], Nodeval);
          if (!ptr)
            cout << "Node not found!\n";
          else
            ptr->InsertNode(ptr);
        }
        else if (choice == 3)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to search: ");
          float Nodeval;
          cout << "Enter node value to search: ";
          cin >> Nodeval;
          auto ptr = v[idx]->FindNode(v[idx], Nodeval);
          if (!ptr)
            cout << "Node not found!\n";
          else
            cout << "Node exists.\n";
        }
        else if (choice == 4)
        {
          int idx = getValidIndex(v.size(), "Enter tree index for traversal: ");
          v[idx]->PreOrderTraversal(v[idx]);
          cout << "NULL\n";
        }
        else
          break;
      }
    }
    else
    {
      int x;
      cout << "Enter maximum number of children per node: ";
      cin >> x;

      CompleteGenericTree<float> temp;
      temp.InitializeStaticData(x);

      vector<shared_ptr<CompleteGenericTree<float>>> v;
      vector<GenericTreeInfo> Info;

      while (true)
      {
        int choice;
        cout << "\n1->Create Complete Tree\n2->Insert Node\n3->Find Node\n4->PreOrder Traversal\n5->Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
          if (CurrentNoOfTrees >= MaxNoOfTrees)
          {
            cout << "Max Tree Limit Reached!\n";
            continue;
          }
          shared_ptr<CompleteGenericTree<float>> ptr;
          v.push_back(ptr);
          GenericTreeInfo infoObj;
          Info.push_back(infoObj);
          CurrentNoOfTrees++;
        }
        else if (choice == 2)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to insert node: ");
          Info[idx].UpdateValues(x);
          v[idx]->InsertNode(v[idx], -1, Info[idx]);
          
        }
        else if (choice == 3)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to search: ");
          float Nodeval;
          cout << "Enter node value to search: ";
          cin >> Nodeval;
          if (v[idx]->FindNode(v[idx], Nodeval))
            cout << "Node exists\n";
          else
            cout << "Node not found!\n";
        }
        else if (choice == 4)
        {
          int idx = getValidIndex(v.size(), "Enter tree index for traversal: ");
          v[idx]->preOrderTraversal(v[idx]);
          cout << "NULL\n";
        }
        else
          break;
      }
    }
  }
  else if (DataType == 3)
  { // ---- CHAR SUPPORT ----
    int TypeOfGenericTree = 2;
    cout << "Enter:\t0 -> Generic Tree\t1 -> Complete Generic Tree\nchoice: ";
    while (TypeOfGenericTree < 0 || TypeOfGenericTree > 1)
    {
      cin >> TypeOfGenericTree;
      if (TypeOfGenericTree < 0 || TypeOfGenericTree > 1)
        cout << "Invalid Input!!!\nchoice: ";
    }

    if (TypeOfGenericTree == 0)
    {
      vector<shared_ptr<GenericTree<char>>> v;
      while (true)
      {
        int choice;
        cout << "\n1->Create Generic Tree\n2->Insert Node\n3->Find Node\n4->PreOrder Traversal\n5->Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
          if (CurrentNoOfTrees >= MaxNoOfTrees)
          {
            cout << "Maximum Tree Limit Reached!\n";
            continue;
          }
          shared_ptr<GenericTree<char>> ptr;
          v.push_back(ptr);
          CurrentNoOfTrees++;
        }
        else if (choice == 2)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to insert node: ");
          if(!v[idx]){
            v[idx]->InsertNode(v[idx]);
            continue;
          }
          char Nodeval;
          cout << "Enter node value to insert at: ";
          cin >> Nodeval;
          auto ptr = v[idx]->FindNode(v[idx], Nodeval);
          if (!ptr)
            cout << "Node not found!\n";
          else
            ptr->InsertNode(ptr);
        }
        else if (choice == 3)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to search: ");
          char Nodeval;
          cout << "Enter node value to search: ";
          cin >> Nodeval;
          auto ptr = v[idx]->FindNode(v[idx], Nodeval);
          if (!ptr)
            cout << "Node not found!\n";
          else
            cout << "Node exists.\n";
        }
        else if (choice == 4)
        {
          int idx = getValidIndex(v.size(), "Enter tree index for traversal: ");
          v[idx]->PreOrderTraversal(v[idx]);
          cout << "NULL\n";
        }
        else
          break;
      }
    }
    else
    {
      int x;
      cout << "Enter maximum number of children per node: ";
      cin >> x;

      CompleteGenericTree<char> temp;
      temp.InitializeStaticData(x);

      vector<shared_ptr<CompleteGenericTree<char>>> v;
      vector<GenericTreeInfo> Info;

      while (true)
      {
        int choice;
        cout << "\n1->Create Complete Tree\n2->Insert Node\n3->Find Node\n4->PreOrder Traversal\n5->Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
          if (CurrentNoOfTrees >= MaxNoOfTrees)
          {
            cout << "Max Tree Limit Reached!\n";
            continue;
          }
          shared_ptr<CompleteGenericTree<char>> ptr;
          v.push_back(ptr);
          GenericTreeInfo infoObj;
          Info.push_back(infoObj);
          CurrentNoOfTrees++;
        }
        else if (choice == 2)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to insert node: ");
          Info[idx].UpdateValues(x);
          v[idx]->InsertNode(v[idx], -1, Info[idx]);
          
        }
        else if (choice == 3)
        {
          int idx = getValidIndex(v.size(), "Enter tree index to search: ");
          char Nodeval;
          cout << "Enter node value to search: ";
          cin >> Nodeval;
          if (v[idx]->FindNode(v[idx], Nodeval))
            cout << "Node exists\n";
          else
            cout << "Node not found!\n";
        }
        else if (choice == 4)
        {
          int idx = getValidIndex(v.size(), "Enter tree index for traversal: ");
          v[idx]->preOrderTraversal(v[idx]);
          cout << "NULL\n";
        }
        else
          break;
      }
    }
  }

  return 0;
}
