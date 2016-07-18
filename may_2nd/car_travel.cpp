#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Edge {
    public:
        int id;
        unsigned len;
        Edge(int id, unsigned len): id(id), len(len) {}
};

class Node {
    public:
        Node(int id): id(id), min_tank(-1) {}
        int id;
        int min_tank;
        vector<Edge> edges;
};

class mycomparison
{
    bool reverse;
    public:
    mycomparison(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (Node *& lhs, Node *& rhs) const
    {
        if (reverse == false)
        {
            if (rhs->min_tank == -1)
                return 0;
            if (lhs->min_tank == -1)
                return 1;
            return (lhs->min_tank>rhs->min_tank);
        }
        else
        {
            if (rhs->min_tank == -1)
                return 0;
            if (lhs->min_tank == -1)
                return 1;
            return lhs->min_tank < rhs->min_tank;
        }
    }
};


int main(void)
{
    int n, s, t;
    cin >> n >> s >> t;

    vector<Node*> graph;
    vector<Node *> unknownSet;
    for (int i = 0; i < n; i++)
    {
        graph.push_back(new Node(i));
        if (i != s)
            unknownSet.push_back(graph[i]);
        else
            graph[i]->min_tank = 0;
    }

    int len, si, ti;
    while (cin >> len >> si >> ti)
    {
        graph[si]->edges.push_back(Edge(ti, len));
        graph[ti]->edges.push_back(Edge(si, len));
    }

    Node *latest = graph[s];
    while (unknownSet.size() != 0)
    {
        vector<Edge> &edges = (*latest).edges;
        for (unsigned i = 0; i < edges.size(); i++)
        {
            int min_tank = ((*latest).min_tank < (int)edges[i].len ? 
                    (int)edges[i].len : (*latest).min_tank);
            if (graph[edges[i].id]->min_tank == -1 ||
                    min_tank < graph[edges[i].id]->min_tank)
                graph[edges[i].id]->min_tank = min_tank;
        }
        //make_heap(unknownSet.begin(), unknownSet.end(), mycomparison());
        //pop_heap(unknownSet.begin(), unknownSet.end(), mycomparison());
        //latest = *(unknownSet.end() - 1);
        //unknownSet.pop_back();
        int index = 0;
        for (unsigned i = 0; i < unknownSet.size(); i++)
        {
            if (mycomparison()(unknownSet[i], unknownSet[index]) == 0)
                index = i;
        }
        latest = unknownSet[index];
        unknownSet[index] = *(unknownSet.end() - 1);


        unknownSet.pop_back();
    }

    cout << graph[t]->min_tank;

    return 0;
}




