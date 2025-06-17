#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
template <typename T>
class UndirectedGraph
{
private:
    T val;
    vector<UndirectedGraph<T>> Link;
    long long cost;
     vector<UndirectedGraph<T>> NumberofVertices;
public:
   
    UndirectedGraph<T>() : cost(0) {}
    UndirectedGraph<T>(T value)
    {
        val = value;
    }
    UndirectedGraph<T>(T value, long long Cost)
    {
        val = value;
        cost = Cost;
    }
    UndirectedGraph<T>(const UndirectedGraph<T> &obj)
    {
        val = obj.val;
        cost = obj.cost;
        for (int i = 0; i < obj.Link.size(); i++)
        {
            Link.push_back(obj.Link[i]);
        }
    }
    void Print()
    {
        for (int i = 0; i < NumberofVertices.size(); i++)
        {
            cout << NumberofVertices[i].val << "-->";
        }
        cout << endl;
    }
    inline void create()
    {
        NumberofVertices.push_back(UndirectedGraph<T>());
        return;
    }
    const void write(int idx, T value)
    {
        NumberofVertices.at(idx).val = value;
    }
    void Linking(int idx1, int idx2, long long weight = 1)
    {
        if (idx1 >= NumberofVertices.size() || idx2 >= NumberofVertices.size() || idx1 < 0 || idx2 < 0)
        {
            cout << "ERROR!!!\n";
        }
        else
        {
            UndirectedGraph<T> &vertex1 = NumberofVertices[idx1];
            UndirectedGraph<T> &vertex2 = NumberofVertices[idx2];
            for (int i = 0; i < vertex1.Link.size(); i++)
            {
                if (vertex1.Link[i].val == vertex2.val)
                    return;
            }
            vertex1.Link.push_back(vertex2);
            vertex1.Link[vertex1.Link.size() - 1].cost = weight;
            vertex2.Link.push_back(vertex1);
            vertex2.Link[vertex2.Link.size() - 1].cost = weight;
        }
        return;
    }
    bool IsLinked(int idx1, int idx2)
    {
        bool flag = false;
        UndirectedGraph<T> V1 = NumberofVertices[idx1];
        UndirectedGraph<T> V2 = NumberofVertices[idx2];
        for (int i = 0; i < V1.Link.size(); i++)
        {
            if (V1.Link[i].val == V2.val)
            {
                flag = true;
                break;
            }
        }
        return flag;
    }
    void Delete(int idx)
    {
        for (int i = 0; i < NumberofVertices.size(); i++)
        {
            if (i == idx)
                continue;
            for (int j = 0; j < NumberofVertices[i].Link.size();)
            {
                if (NumberofVertices[i].Link[j].val == NumberofVertices[idx].val)
                {
                    NumberofVertices[i].Link.erase(NumberofVertices[i].Link.begin() + j);
                }
                else
                    j++;
            }
        }
        NumberofVertices.erase(NumberofVertices.begin() + idx);
        return;
    }
    UndirectedGraph<T> getvertex(int idx)
    {
        if (idx >= NumberofVertices.size() || idx < 0)
        {
            cout << "Invalid!!!\n";
            return UndirectedGraph<T>();
        }
        else
            return NumberofVertices[idx];
    }
    UndirectedGraph<T> Get(T value)
    {
        for (int i = 0; i < NumberofVertices.size(); i++)
        {
            if (NumberofVertices[i].val == value)
                return NumberofVertices[i];
        }
        cout << "Doesn't exist!!!\n";
        return UndirectedGraph<T>();
    }
    void disconnect(int idx1, int idx2)
    {
        if (idx1 >= NumberofVertices.size() || idx2 >= NumberofVertices.size() || idx1 < 0 || idx2 < 0)
        {
            cout << "ERROR!!!\n";
        }
        for (int i = 0; i < NumberofVertices[idx1].Link.size(); i++)
        {
            if (NumberofVertices[idx1].Link[i].val == NumberofVertices[idx2].val)
            {
                NumberofVertices[idx1].Link.erase(NumberofVertices[idx1].Link.begin() + i);
                break;
            }
        }
        for (int i = 0; i < NumberofVertices[idx2].Link.size(); i++)
        {
            if (NumberofVertices[idx2].Link[i].val == NumberofVertices[idx1].val)
            {
                NumberofVertices[idx2].Link.erase(NumberofVertices[idx2].Link.begin() + i);
                break;
            }
        }
        return;
    }
    bool compare(const UndirectedGraph<T> &a, const UndirectedGraph<T> &b)
    {
        return a.cost > b.cost;
    }
    struct Compare
    {
        bool operator()(const UndirectedGraph<T> &a, const UndirectedGraph<T> &b) const
        {
            return a.cost > b.cost; // Min-heap: lower cost has higher priority
        }
    };
    int getidx(T value)
    {
        for (int i = 0; i < NumberofVertices.size(); i++)
        {
            if (value == NumberofVertices[i].val)
                return i;
        }
        return -1;
    }
    long long Dijkstra(int source, int dest)
    {
        if (source >= NumberofVertices.size() || dest >= NumberofVertices.size() || source < 0 || dest < 0)
        {
            cout << "Invalid!!!\n";
            return -1;
        }
        else
        {
            vector<long long> distance(NumberofVertices.size(), LLONG_MAX);
            distance[source] = 0;
            priority_queue<UndirectedGraph<T>, vector<UndirectedGraph<T>>, Compare> Q;
            Q.push(NumberofVertices[source]);
            while (!Q.empty())
            {
                UndirectedGraph<T> x = Q.top();
                Q.pop();
                for (int i = 0; i < x.Link.size(); i++)
                {
                    UndirectedGraph<T> y = Get(x.Link[i].val);
                    y.cost = x.cost + x.Link[i].cost;
                    int idx = getidx(y.val);
                    if (y.cost < distance[idx])
                    {
                        distance[idx] = y.cost;
                        Q.push(y);
                    }
                }
            }
            return (distance[dest] == LLONG_MAX) ? -1 : distance[dest];
        }
    }
    vector<long long> Dijkstra(int source)
    {
        if (source >= NumberofVertices.size() || source < 0)
        {
            cout << "Invalid!!!\n";
            return {};
        }
        else
        {
            vector<long long> distance(NumberofVertices.size(), LLONG_MAX);
            distance[source] = 0;
            priority_queue<UndirectedGraph<T>, vector<UndirectedGraph<T>>, Compare> Q;
            Q.push(NumberofVertices[source]);
            while (!Q.empty())
            {
                UndirectedGraph<T> x = Q.top();
                Q.pop();
                for (int i = 0; i < x.Link.size(); i++)
                {
                    UndirectedGraph<T> y = Get(x.Link[i].val);
                    y.cost = x.cost + x.Link[i].cost;
                    int idx = getidx(y.val);
                    if (y.cost < distance[idx])
                    {
                        distance[idx] = y.cost;
                        Q.push(y);
                    }
                }
            }
            return distance;
        }
    }
    long long getWeight(int idx1, int idx2)
    {
        UndirectedGraph<T> v = NumberofVertices[idx1];
        for (int i = 0; i < v.Link.size(); i++)
        {
            if (v.Link[i].val == NumberofVertices[idx2].val)
                return v.Link[i].cost;
        }
        cout << "ERROR!!!\n";
        return LLONG_MIN;
    }
    long long Ballman_Ford(int source, int dest)
    {
        if (source >= NumberofVertices.size() || dest >= NumberofVertices.size() || source < 0 || dest < 0)
        {
            cout << "Error!!!\n";
            return LLONG_MAX;
        }
        else
        {
            vector<long long> Distance(NumberofVertices.size(), LLONG_MAX);
            Distance[source] = 0;
            for (int i = 0; i < NumberofVertices.size(); i++)
            {
                bool flag = false;
                for (int j = 0; j < NumberofVertices.size(); j++)
                {
                    if(Distance[j]==LLONG_MAX) continue;
                    for (int k = 0; k < NumberofVertices[j].Link.size(); k++)
                    {
                         int idx=getidx(NumberofVertices[j].Link[k].val);
                         long long weight=Distance[j]+NumberofVertices[j].Link[k].cost;
                         if(weight<Distance[idx]){
                            flag=true;
                            Distance[idx]=weight;
                         }
                    }
                }
                if(flag==false) return Distance[dest];
                if(i==NumberofVertices.size()-1&&flag==true){
                    cout<<"Error!!!\nNegative cycle exists!!!\n";
                    return LLONG_MAX;
                }
            }
            return Distance[dest];
        }
    }
    vector<long long> Ballman_Ford(int source){
       if (source >= NumberofVertices.size() || source < 0)
        {
            cout << "Error!!!\n";
            return vector<long long>(NumberofVertices.size(),LLONG_MAX);
        }
        else
        {
            vector<long long> Distance(NumberofVertices.size(), LLONG_MAX);
            Distance[source] = 0;
            for (int i = 0; i < NumberofVertices.size(); i++)
            {
                bool flag = false;
                for (int j = 0; j < NumberofVertices.size(); j++)
                {
                    if(Distance[j]==LLONG_MAX) continue;
                    for (int k = 0; k < NumberofVertices[j].Link.size(); k++)
                    {
                         int idx=getidx(NumberofVertices[j].Link[k].val);
                         long long weight=Distance[j]+NumberofVertices[j].Link[k].cost;
                         if(weight<Distance[idx]){
                            flag=true;
                            Distance[idx]=weight;
                         }
                    }
                }
                if(flag==false) return Distance;
                if(i==NumberofVertices.size()-1&&flag==true){
                    cout<<"Error!!!\nNegative cycle exists!!!\n";
                    return vector<long long>(NumberofVertices.size(),LLONG_MAX);
                }
            }
            return Distance;
        } 
    }
    
};
template<typename T>
class DirectedGraph_Attributes{
    protected:
    T val;
    long double cost;
    vector<DirectedGraph_Attributes<T>> Linkage;
};
template<typename T>
class DirectedGraph:public DirectedGraph_Attributes<T>{
    private:
    vector<DirectedGraph_Attributes<T>>* Numberofvertices;
    public:
    DirectedGraph<T>(){
        Numberofvertices=nullptr;
    }
    ~DirectedGraph<T>(){
        delete Numberofvertices;
    }
    inline void Create(){
        if(!Numberofvertices) Numberofvertices=new vector<DirectedGraph<T>>();
        Numberofvertices->push_back(DirectedGraph<T>());
        return;
    }
    void Write(const int idx,const T value){
        if(idx>=Numberofvertices->size()||idx<0){
            cout<<"Invalid!!!\n";
        }
        else{
            Numberofvertices[idx]->val=value;
        }
        return;
    }
    bool Exist(T value){
        for(int i=0;i<Numberofvertices->size();i++){
            if(Numberofvertices[i]->val==value) return true;
        }
        return false;
    }
    DirectedGraph<T> Get(T value){
        for(int i=0;i<Numberofvertices.size();i++){
            if(Numberofvertices[i]->val==value) return Numberofvertices[i];
        }
        cout<<"Error!!!\n";
        return DirectedGraph<T>();
    }
    int getidx(T value){
        for(int i=0;i<Numberofvertices.size();i++){
            if(Numberofvertices[i].val==value) return i;
        }
        cout<<"Error!!!\n";
        return LLONG_MIN;
    }
    void Linking(int src_vertex,int dest_vertex,long double cost){
        if(src_vertex>=Numberofvertices->size()||dest_vertex>=Numberofvertices->size()||src_vertex<0||dest_vertex<0){
            cout<<"Error!!!\n";
        }
        else{
            for(int i=0;i<Numberofvertices[src_vertex].Linkage.size();i++){
                if(Numberofvertices[src_vertex].Linkage[i].val==Numberofvertices[dest_vertex].val) return;
            }
            Numberofvertices[src_vertex].Linkage.push_back(Numberofvertices[dest_vertex]);
        }
        return;
    }
    
};
int main(){}