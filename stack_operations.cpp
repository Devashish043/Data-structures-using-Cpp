#include <iostream>
#include <string>
using namespace std;
class stack
{
private:
    int size;
    int capacity;
    char *arr;
    int top;

public:
    stack() : top(-1), size(0), capacity(0)
    {
        arr = nullptr;
    }
    stack(const string S){
        int len=S.length();
        capacity=size=len;
        top=size-1;
        arr=new char[capacity];
        for(int i=0;i<size;i++){
            arr[i]=S[i];
        }
    }
    stack(const stack &obj)
    {
        top = obj.top;
        size = obj.size;
        capacity = obj.capacity;
        arr = new char[capacity];
        for (int i = 0; i < size; i++)
        {
            arr[i] = obj.arr[i];
        }
    }
    ~stack(){
        delete[] arr;
    }
    int initialize(stack &, int);
    int balanced_symbol(stack &);
    void inflate(stack &);
    stack infix_to_postfix(stack &);
    int palindrome(stack &);
    friend void PrintStack(stack&); 
    void push(stack &, char);
    char pop(stack &);
};
void PrintStack(stack& S){
    for(int i=0;i<S.size;i++){
        cout<<S.arr[i];
    }
    cout<<endl;
    return;
}
int stack::initialize(stack &S, int x = 2)
{
    S.capacity = x;
    S.size = 0;
    S.top = -1;
    if (x < 1)
        return 0;
    else if (x == 1)
        S.arr = new char;
    else
        S.arr = new char[S.capacity];
    return 1;
}
void stack::inflate(stack &S)
{
    if (S.size == S.capacity)
    {
        S.capacity *= 2;
        char *array = new char[S.capacity];
        for (int i = 0; i < S.size; i++)
        {
            array[i] = S.arr[i];
        }
        delete[] S.arr;
        S.arr = array;
    }
    return;
}
void stack::push(stack &S, char c)
{
    inflate(S);
    S.top++;
    S.arr[S.top] = c;
    S.size++;
    return;
}
char stack::pop(stack& S){
    if(S.top==-1){
        cout<<"Stack is empty!!!\npop operation failed!!!";
        return -1;
    }
    else{
        char x=S.arr[S.top];
        S.top--;
        return x;
    }
}
int stack::palindrome(stack &S)
{
    if (S.size % 2 == 0)
    {
        stack Palindrome;
        Palindrome.initialize(Palindrome, S.size / 2);
        for (int i = S.top, j = 0; i >= S.size / 2; i--, j++)
        {
            Palindrome.arr[j] = S.arr[i];
            Palindrome.top = j;
        }
        S.top = S.size / 2 - 1;
        while (S.top != -1 && Palindrome.top != -1)
        {
            if (S.arr[S.top] == Palindrome.arr[Palindrome.top])
            {
                S.top--;
                S.size--;
                Palindrome.top--;
                Palindrome.size--;
            }
            else
                return 0;
        }
        if (S.top == -1 && Palindrome.top == -1)
            return 1;
        else
            return 0;
    }
    else
    {
        stack Palindrome;
        Palindrome.initialize(Palindrome, S.size / 2);
        for (S.top, Palindrome.top = 0; S.top > S.size / 2; S.top--, Palindrome.top++)
        {
            Palindrome.arr[Palindrome.top] = S.arr[S.top];
        }
        S.top--;
        Palindrome.top--;
        while (S.top != -1 && Palindrome.top != -1)
        {
            if (S.arr[S.top] == Palindrome.arr[Palindrome.top])
            {
                Palindrome.top--;
                S.top--;
                S.size--;
            }
            else
                return 0;
        }
        if (S.top == -1 && Palindrome.top == -1)
            return 1;
        else
            return 0;
    }
}
stack stack::infix_to_postfix(stack &S)
{
    stack STACK;
    stack Operand;
    Operand.initialize(Operand);
    STACK.initialize(STACK);
    if (S.top == -1)
    {
        cout << "Stack is empty!!!\n";
        return STACK;
    }
    int x = 0;
    while (x <= S.top)
    {
        if (S.arr[x] >= 48 && S.arr[x] <= 57)
        {
            push(STACK, S.arr[x]);
        }
        else if (S.arr[x] == '+' || S.arr[x] == '-' || S.arr[x] == '*' || S.arr[x] == '/')
        {
            push(STACK,' ');
            if (S.arr[x] == '+')
            {
                while (1)
                {
                    if (Operand.top == -1 || Operand.arr[Operand.top] == '(' || Operand.arr[Operand.top] == '{' || Operand.arr[Operand.top] == '[')
                    {
                        push(Operand, S.arr[x]);
                        break;
                    }
                    else
                    {
                        push(STACK,pop(Operand));
                    }
                }
            }
            else if (S.arr[x] == '-')
            {

                while (1)
                {
                    if (Operand.top == -1 || Operand.arr[Operand.top] == '(' || Operand.arr[Operand.top] == '{' || Operand.arr[Operand.top] == '[')
                    {
                        push(Operand, S.arr[x]);
                        break;
                    }
                    else
                    {
                        push(STACK,pop(Operand));
                    }
                }
            }
            else{
                while (1)
                {
                    if (Operand.top == -1 || Operand.arr[Operand.top] == '(' || Operand.arr[Operand.top] == '{' || Operand.arr[Operand.top] == '['||Operand.arr[Operand.top] == '-'||Operand.arr[Operand.top] == '+')
                    {
                        push(Operand, S.arr[x]);
                        break;
                    }
                    else
                    {
                        push(STACK,pop(Operand));
                    }
                }
            }
        }
        else if(S.arr[x]=='('||S.arr[x]=='{'||S.arr[x]=='['){
            push(STACK,' ');
            push(Operand,S.arr[x]);
        }
        else if(S.arr[x]==')'||S.arr[x]=='}'||S.arr[x]==']'){
            if(S.arr[x]==')'){
            while(Operand.arr[Operand.top]!='('){
                    push(STACK,pop(Operand));
                }
                Operand.top--;
            }
            else if(S.arr[x]=='}'){
                while(Operand.arr[Operand.top]!='{'){
                    push(STACK,pop(Operand));
                }
                Operand.top--;
            }
            else{
                while(Operand.arr[Operand.top]!='['){
                    push(STACK,pop(Operand));
                }
                Operand.top--;
            }
        }
        x++;

    }
    if(Operand.top!=-1){
        while(Operand.top>-1){
            push(STACK,pop(Operand));
        }
    }
    return STACK;
}
int stack::balanced_symbol(stack &Stack)
{
    if (Stack.top == -1)
    {
        cout << "Stack is Empty!!!\n";
        return -1;
    }
    else if ((Stack.arr[Stack.top] >= 48 && Stack.arr[Stack.top] <= 57) || Stack.arr[Stack.top] == '}' || Stack.arr[Stack.top] == ')' || Stack.arr[Stack.top] == ']')
    {
        stack S(Stack);
        bool flag = false;
        char Operator;
        stack operand, symbol;
        operand.initialize(operand);
        symbol.initialize(symbol);
        while (S.top != -1)
        {
            if (S.arr[S.top] == '}' || S.arr[S.top] == ']' || S.arr[S.top] == ')')
            {
                symbol.inflate(symbol);
                symbol.top++;
                symbol.arr[symbol.top] = S.arr[S.top];
                S.top--;
                S.size--;
            }
            else if (S.arr[S.top] == '{' || S.arr[S.top] == '(' || S.arr[S.top] == '[')
            {
                if (S.arr[S.top] == '{' && symbol.arr[symbol.top] == '}')
                {
                    if (flag == true)
                        return 0;
                    S.top--;
                    S.size--;
                    symbol.top--;
                    symbol.size--;
                }
                else if (S.arr[S.top] == '[' && symbol.arr[symbol.top] == ']')
                {
                    if (flag == true)
                        return 0;
                    S.top--;
                    S.size--;
                    symbol.top--;
                    symbol.size--;
                }
                else if (S.arr[S.top] == '(' && symbol.arr[symbol.top] == ')')
                {
                    if (flag == true)
                        return 0;
                    S.top--;
                    S.size--;
                    symbol.top--;
                    symbol.size--;
                }
                else
                    return 0;
            }
            else if (S.arr[S.top] == '+' || S.arr[S.top] == '-' || S.arr[S.top] == '/' || S.arr[S.top] == '*')
            {
                if (operand.top == -1)
                    return 0;
                else if (flag == true)
                    return 0;
                else
                {
                    Operator = S.arr[S.top];
                    S.top--;
                    S.size--;
                    flag = true;
                }
            }
            else
            {
                if (flag == false)
                {
                    operand.top++;
                    operand.inflate(operand);
                    operand.arr[operand.top] = S.arr[S.top];
                    operand.size++;
                    S.top--;
                    S.size--;
                }
                else
                {
                    flag = false;
                    operand.top = 0;
                    operand.size = 1;
                    operand.arr[operand.top] = 1;
                    S.size--;
                    S.top--;
                }
            }
        }
        if (flag != false || symbol.top != -1)
            return 0;
        else
            return 1;
    }
    else
        return 0;
}
int main()
{
   string S;
   cout<<"Please enter the required expression:";
   getline(cin,S);
    stack array(S);
    cout<<"Given expression is:";
    PrintStack(array);
    int x=array.balanced_symbol(array);
    if(x==0||x==-1){
        cout<<"There is a error in entered expression!!!\n";
    }
    else{
        stack postfix=array.infix_to_postfix(array);
        cout<<"Given postfix expression is:";
        PrintStack(postfix);
    }
    return 0;
}