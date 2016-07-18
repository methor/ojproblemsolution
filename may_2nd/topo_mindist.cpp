#include <vector>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;
enum Color { WHITE, GRAY, BLACK};

class Edge {
    public:
        int point;
        int len;
        Edge(int point, int len): point(point), len(len) {}
};
class Point {
    public:
        int id;
        vector<Edge> edges;
        Color color;
        int min_len;
        
        Point() {}
        Point(int id)
        {
            this->id = id;
            color = WHITE;
            min_len = -1;
        }
};
void _dfs(int index, vector<Point> &graph, unsigned &t, vector<Point*> &vec, int &num)
{
    Point &point = graph[index];
    ++t;
    point.color = GRAY;
    for (unsigned i = 0; i < point.edges.size(); i++)
    {
        if (graph[point.edges[i].point].color == WHITE)
        {
            _dfs(point.edges[i].point, graph, t, vec, num);
        }
    }
    ++t;
    point.color = BLACK;
    vec[num] = &point; num--;
}


vector<Point*>& dfs(vector<Point> &graph)
{
    vector<Point*> *rv = new vector<Point*>();
    rv->resize(graph.size(), NULL);
    for (unsigned i = 0; i < graph.size(); i++)
        graph[i].color = WHITE;
    unsigned t = 0;
    int num = graph.size() - 1;
    for (unsigned i = 0; i < graph.size(); i++)
    {
        if (graph[i].color == WHITE)
            _dfs(i, graph, t, *rv, num);
    }

    return *rv;
}

int main(void)
{
    int n;
    cin >> n;
    vector<Point> graph;
    int len, s, t;
    for (int i = 0; i < n; i++)
        graph.push_back(Point(i));
    while (cin >> s >> t >> len)
    {
        graph[s].edges.push_back(Edge(t,len));
    }
    graph[0].min_len = 0;

    vector<Point*> topolist = dfs(graph);
    
    vector<Point *>::iterator iter = topolist.begin();
    while (iter != topolist.end())
    {
        Point *pt = *iter;
        vector<Edge> &edges = pt->edges;
        for (unsigned i = 0; i < edges.size(); i++)
        {
            Point &p = graph[edges[i].point];
            if (p.min_len == -1 || pt->min_len + edges[i].len > p.min_len)
                p.min_len = pt->min_len + edges[i].len;
        }
        ++iter;
    }
    for (unsigned i = 1; i < graph.size(); i++)
        cout << graph[i].min_len << " ";
    return 0;
}
        




