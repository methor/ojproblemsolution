#include <map>
#include <iostream>
#include <queue>

using namespace std;
class Edge
{
public:
    int u,v,cost;
    Edge(int u,int v,int cost):u(u),v(v),cost(cost){}
    bool operator < (const Edge &e)const{return cost>e.cost;}
};

class Node {
    public:
        Node *parent;
        int rank;
        Node(int key): parent(this), rank(0), key(key) {}
        int& getKey() { return key;}

    private:
        int key;
};        


class UnionSet {
    public:
        void make_set(Node* vertex);
        void union_set(Node* v1, Node* v2);
        Node* find_set(Node* vertex);
        Node* find_by_key(const int key);

    private:
        void link(Node *v1, Node* v2);
        map<int, Node*> vertex_indexlist;

};

Node* UnionSet::find_by_key(const int key)
{
    return vertex_indexlist[key];
}

void UnionSet::make_set(Node* vertex)
{
    vertex_indexlist.insert(pair<int, Node*>(vertex->getKey(), vertex));
}

void UnionSet::union_set(Node* v1, Node* v2)
{
    link(find_set(v1), find_set(v2));
}

Node* UnionSet::find_set(Node* vertex)
{
    if (vertex->parent != vertex)
        vertex->parent = find_set(vertex->parent);

    return vertex->parent;
}

void UnionSet::link(Node* v1, Node* v2)
{
    if (v1->rank > v2->rank)
        v2->parent = v1;
    else
    {
        v1->parent = v2;
        if (v1->rank == v2->rank)
            v2->rank++;
    }
}

int main()
{
    int n, weight = 0;;
    UnionSet unionSet;
    priority_queue<Edge, vector<Edge> > queue;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Node *node = new Node(i);
        unionSet.make_set(node);
        
    }
    int i,j,w;
    while (cin >> i >> j >> w)
    {
        queue.push(Edge(i,j,w));
    }

    int edges = 0;
    while (edges < n - 1)
    {
        const Edge e = queue.top();
        queue.pop();
        //cout << e.u << " " << e.v << " " << e.cost << endl;
        Node* v1 = unionSet.find_set(unionSet.find_by_key(e.u));
        Node* v2 = unionSet.find_set(unionSet.find_by_key(e.v));
        if (v1 != v2)
        {
            unionSet.union_set(v1, v2);
            weight += e.cost;
            edges++;
        //cout << e.cost << endl;
        }
    }

    cout << weight;
    return 0;
}
        




