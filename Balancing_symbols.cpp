#include<iostream>
#include<string>
using namespace std;
class GrowingStack{
    private:
    int size;
    int capacity;
    int* arr;
    int top;
    public:
    GrowingStack(){
        size=0;
        capacity=0;
        arr=NULL;
        top=-1;
    }
    GrowingStack( const GrowingStack& copy){
        size=copy.size;
        top=copy.top;
        capacity=copy.capacity;
        arr=new int[capacity];
        for(int i=0;i<size;i++){
            arr[i]=copy.arr[i];
        }
    }
    GrowingStack& operator=(const GrowingStack& obj){
        if(this==&obj){
            cout<<"Assignment operation failed!!!\n";
            cout<<"This pointer is unable to point current object";
            return *this;
        }
        size=obj.size;
        top=obj.top;
        capacity=obj.capacity;
        arr=new int[capacity];
        for(int i=0;i<size;i++){
            arr[i]=obj.arr[i];
        }
        return *this;
    }
    ~GrowingStack(){
        delete[] arr;
    }
    void push(GrowingStack&);
    void pop(GrowingStack&);
    void inflate(GrowingStack&);
    int isempty(GrowingStack&);
    int getmaxsize(GrowingStack&);
    int currentsize(GrowingStack&);
    void CreatingStackusingCopyConstructor(GrowingStack&);
    void CreatingStackusingassignmentOperator(GrowingStack&);
    friend void alternate_merge_stack(GrowingStack&,GrowingStack&,int);
    void initialize(GrowingStack&);
    int balancing_of_symbols();
};
int GrowingStack::balancing_of_symbols(){
    string symbol;
    int count=0;
    cout<<"please provide the stream of input symbols in terminal:";
    cin.ignore();
    getline(cin,symbol);
    int len=symbol.length();
    char str[symbol.length()/2];
    int check=symbol.length()-1;
    if(symbol[check]=='(' ||symbol[check]=='[' ||symbol[check]=='{') return 0;
    int i=-1;
    do{
        if(symbol[check]==' '){
            check--;
        }
        else if(symbol[check]==')'||symbol[check]=='}'||symbol[check]==']'){
            i++;
            if(i>=len/2) return 0;
            else{
                str[i]=symbol[check];
                check--;
            }
        }
        else{
            if(symbol[check]=='('){
                if(str[i]==')'){
                    check--;
                    i--;
                }
                else return 0;
            }
            else if(symbol[check]=='['){
                if(str[i]==']'){
                    check--;
                    i--;
                }
                else return 0;
            }
            else{
                if(str[i]=='}'){
                    check--;
                    i--;
                }
                else return 0;
            }
        }
    }
    while(check!=-1 || i!=-1);
    if(check!=-1 ||i!=-1) return 0;
    return 1;
}
void GrowingStack::initialize(GrowingStack& x){
    cout<<"Enter the size of stack:";
    cin>>x.capacity;
    x.size=0;
    x.arr=new int[x.capacity];
    cout<<"Stack created!!!\n";
    return;
}
void GrowingStack::inflate(GrowingStack& x){
    if(x.size==x.capacity){
        cout<<"STACK IS FULL INCREASING SIZE BY DOUBLE:\n";
        x.capacity*=2;
        int* array;
        array=new int[x.capacity];
        for(int i=0;i<x.size;i++){
            array[i]=x.arr[i];
        }
        delete[] x.arr;
        x.arr=array;
        array=nullptr;
        delete array;
    }
    return;
}

void GrowingStack::push(GrowingStack &x){
    x.top++;
    inflate(x);
    int val;
    cout<<"Enter the element whose value yoou want to push:";
    cin>>val;
    x.arr[x.top]=val;
    x.size++;
    return;
}
inline int GrowingStack::isempty(GrowingStack& x){
    if(x.size==0) return 1;
    else return 0; 
}
void GrowingStack::pop(GrowingStack& x){
    int i=isempty(x);
    if(i){
        cout<<"Stack is empty!!!\n";
        return;
    }
    cout<<"Popped value is:"<<x.arr[x.top]<<endl;
    x.top--;
    x.size--;
    return;   
}
inline int GrowingStack::getmaxsize(GrowingStack& x){
    return x.capacity;
}
inline int GrowingStack::currentsize(GrowingStack& x){
    return x.size;
}
void GrowingStack::CreatingStackusingassignmentOperator(GrowingStack& stack){
    if(stack.size==0){
        cout<<"Stack is empty!!!\n";
        return;
    }
    GrowingStack newstack;
    newstack=stack;
    cout<<"Elements of existing stack:";
    for(int i=0;i<stack.size;i++){
        cout<<stack.arr[i]<<" ";
    }
    cout<<endl;
    cout<<"Elements of copied stack is:";
    for(int i=0;i<newstack.size;i++){
        cout<<newstack.arr[i]<<" ";
    }
    cout<<endl;
    return;
 }
void GrowingStack::CreatingStackusingCopyConstructor(GrowingStack& stack){
    if(stack.size==0){
        cout<<"Stack is empty!!!\n";
        return;
    }
    GrowingStack newstack(stack);
    cout<<"Elements of existing stack:";
    for(int i=0;i<stack.size;i++){
        cout<<stack.arr[i]<<" ";
    }
    cout<<endl;
    cout<<"Elements of copied stack is:";
    for(int i=0;i<newstack.size;i++){
        cout<<newstack.arr[i];
    }
    cout<<endl;
    return;
}
void alternate_merge_stack(GrowingStack& stack1,GrowingStack& stack2,int round){
    if(stack1.size==0&&stack2.size==0){
        cout<<"Both stack is empty!!!\n";
        return;
    }
    GrowingStack stack3;
    if(round%2!=0){
        if(stack1.size!=0){
            stack3.capacity=stack1.size;
            stack3.top=-1;
            stack3.size=0;
            cout<<"Elements of stack 1 is:";
            for(int i=0;i<stack1.size;i++){
                cout<<stack1.arr[i]<<" ";
            }
            cout<<endl;
            stack3.arr=new int[stack3.capacity];
            for(int i=0;i<stack3.capacity;i++){
                stack3.top++;
                stack3.arr[stack3.top]=stack1.arr[stack1.top];
                stack1.top--;
                stack1.size--;
                stack3.size++;
            }
            cout<<"Stack1 is empty now!!!\n";
        }
        else{
            stack3.capacity=stack2.size;
            stack3.top=-1;
            stack3.size=0;
            cout<<"Elements of stack 2 is:";
            for(int i=0;i<stack2.size;i++){
                cout<<stack2.arr[i]<<" ";
            }
            cout<<endl;
            
            stack3.arr=new int[stack3.capacity];
            for(int i=0;i<stack3.capacity;i++){
                stack3.top++;
                stack3.arr[stack3.top]=stack2.arr[stack2.top];
                stack2.top--;
                stack2.size--;
                stack3.size++;
            }
            cout<<"Stack2 is empty now!!!\n";
        }
    }
    else{
        if(stack2.size!=0){
            stack3.capacity=stack2.size;
            stack3.top=-1;
            stack3.size=0;
            cout<<"Elements of stack 2 is:";
            for(int i=0;i<stack2.size;i++){
                cout<<stack2.arr[i]<<" ";
            }
            cout<<endl;
            stack3.arr=new int[stack3.capacity];
            for(int i=0;i<stack3.capacity;i++){
                stack3.top++;
                stack3.arr[stack3.top]=stack2.arr[stack2.top];
                stack2.top--;
                stack2.size--;
                stack3.size++;
            }
            cout<<"Elements of stack2 is empty now!!!\n";
        }
        else{
            stack3.capacity=stack1.size;
            stack3.top=-1;
            stack3.size=0;
            cout<<"Elements of stack 1 is:";
            for(int i=0;i<stack1.size;i++){
                cout<<stack1.arr[i]<<" ";
            }
            cout<<endl;
            stack3.arr=new int[stack3.capacity];
            for(int i=0;i<stack3.capacity;i++){
                stack3.top++;
                stack3.arr[stack3.top]=stack1.arr[stack1.top];
                stack2.top--;
                stack2.size--;
                stack3.size++;
            }
            cout<<"Elements of stack1 is empty now!!!\n";
        }
    }
    cout<<"Elements of stack3 is:";
    for(int i=0;i<stack3.size;i++){
        cout<<stack3.arr[i]<<" ";
    }
    cout<<endl;
    return; 
}
int main(){
    GrowingStack stack;
    stack.initialize(stack);
    while(1){
        
        int choice;
        cout<<"Enter 1->push:\n2->pop:\n3->getmax stack size:\n4->current stack size:\n5->To use copy constructor:\n6->To use assignment '=' operator:\n7->check balancing symbols:\n0->terminate:";
        cin>>choice;
        if(choice<0 ||choice>7){
        cout<<"Invalid choice\n";
        continue;
        }
        else if(choice==0) break;
        else if(choice==1){
          stack.push(stack);
        }
        else if(choice==2){
             stack.pop(stack);
            }
        else if(choice==3){
        
            cout<<"Maximum size of stack is:"<<stack.getmaxsize(stack)<<endl;
        }  
        
        else if(choice==4){
            cout<<"Current size of stack is:"<<stack.currentsize(stack)<<endl;
        } 
        else if(choice==5){
         stack.CreatingStackusingCopyConstructor(stack);
        }
        else if(choice==6){
         stack.CreatingStackusingassignmentOperator(stack);
        }
        else{
            int x=stack.balancing_of_symbols();
            if(x==1) cout<<"symbol is balanced\n";
            else cout<<"Symbol is not balanced!!!\n";
        }
    }
    return 0;
}