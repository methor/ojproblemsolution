#include <iostream>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
enum Color { WHITE, GRAY, BLACK};

class Point {
    public:
        int id;
        vector<int> edges;
        Color color;
        unsigned stime;
        unsigned ftime;
        int pred;
        Point(int id)
        {
            this->id = id;
            color = WHITE;
            pred = -1;
            stime = 0;
            ftime = 0;
        }
};

bool contains(vector<int> container, int value)
{
    for (unsigned i = 0; i < container.size(); i++)
    {
        if (container[i] == value)
            return true;
    }
    return false;
}


void _dfs(int index, vector<Point> &graph, unsigned &t)
{
    Point &point = graph[index];
    ++t;
    point.stime = t;
    point.color = GRAY;
    for (unsigned i = 0; i < point.edges.size(); i++)
    {
        if (graph[point.edges[i]].color == WHITE)
        {
            graph[point.edges[i]].pred = index;
            _dfs(point.edges[i], graph, t);
        }
    }
    ++t;
    point.color = BLACK;
    point.ftime = t;
}

void dfs(vector<Point> &graph)
{
    for (unsigned i = 0; i < graph.size(); i++)
        graph[i].color = WHITE;
    unsigned t = 0;
    for (unsigned i = 0; i < graph.size(); i++)
    {
        if (graph[i].color == WHITE)
            _dfs(i, graph, t);
    }
}

vector<Point> &construct()
{
    vector<Point> *pgraph = new vector<Point>();
    vector<Point> &graph = *pgraph;
    int i = 0;
    string s;
    while (std::getline(cin, s))
    {
        Point point(i);
        vector<int> edges;
        stringstream ss(s);
        string item;
        while (std::getline(ss, item, ' '))
        {
            istringstream iss(item);
            int item_int;
            iss >> item_int;
            edges.push_back(item_int);
        }
        point.edges = edges;
        graph.push_back(point);

        i++;
    }
    return graph;

}

vector<Point> &construct_input_edges()
{

    vector<Point> *pgraph = new vector<Point>();
    vector<Point> &graph = *pgraph;
    int n, s, t;
    cin >> n >> s >> t;
    for (int i = 0; i < n; i++)
        graph.push_back(*new Point(i));
    int si, ti, len;
    while (cin >> len >> si >> ti)
    {
        graph[si].edges.push_back(ti);
        graph[ti].edges.push_back(si);
    }
    return graph;
}



vector<Point> &construct_reverse(vector<Point> graph)
{
    vector<Point> *prgraph = new vector<Point>();
    vector<Point> &rgraph = *prgraph;
    for (unsigned i = 0; i < graph.size(); i++)
    {
        Point point(i);
        point.stime = graph[i].stime;
        point.ftime = graph[i].ftime;
        rgraph.push_back(point);
    }
    for (unsigned i = 0; i < graph.size(); i++)
    {
        for (unsigned j = 0; j < graph[i].edges.size(); j++)
        {
            int neighbor = graph[i].edges[j];
            rgraph[neighbor].edges.push_back(i);
            //
        }
    }

    return rgraph;
}

class CPoint {
    public:
        int cid;
        vector<int> inner_points; // index on original graph, i.e. graph[p.inner_points[j]]
        vector<int> cedges; // index on cgraph, i.e. cgraph[p.cedges[j]]
        unsigned min_ftime;
        unsigned max_ftime;
        Color color;
        int cpred;
        CPoint(int cid)
        {
            this->cid = cid;
            color = WHITE;
            cpred = -1;
            min_ftime = 0;
            max_ftime = 0;
        }
};

int max_f_white(vector<Point> &graph)
{
    int index = -1;
    unsigned t = 0;
    for (unsigned i = 0; i < graph.size(); i++)
    {
        if (graph[i].color == WHITE && graph[i].ftime > t)
        {
            t = graph[i].ftime;
            index = i;
        }
    }
    return index;
}

int find_cindex_by_ftime(unsigned ftime, vector<CPoint> &cgraph)
{
    for (unsigned i = 0; i < cgraph.size() - 1; i++)
    {
        if (ftime >= cgraph[i].min_ftime && ftime <= cgraph[i].max_ftime)
            return i;
    }
    return -1;
}

void _xdfs(int index, vector<Point> &graph, vector<CPoint> &cgraph)
{
    Point &point = graph[index];
    point.color = GRAY;
    int cindex = cgraph.size() - 1;;
    cgraph[cindex].inner_points.push_back(index);
    // update min_ftime of cpoint indexed by cindex on cgraph
    if (graph[index].ftime < cgraph[cindex].min_ftime)
    {
        cgraph[cindex].min_ftime = graph[index].ftime;
    }
    for (unsigned i = 0; i < point.edges.size(); i++)
    {
        if (graph[point.edges[i]].ftime > cgraph[cindex].max_ftime)
        {
            int cneighbor_index = find_cindex_by_ftime(graph[point.edges[i]].ftime, cgraph);
            if (cneighbor_index == -1)
            {
                cout << "error" << endl;
                exit(-1);
            }
            // at this time graph is reversed graph, so we add edges in cgraph 
            // in REVERSED order.
           if (!contains(cgraph[cneighbor_index].cedges, cindex)) 
               cgraph[cneighbor_index].cedges.push_back(cindex);
        }
        if (graph[point.edges[i]].color == WHITE)
        {
            graph[point.edges[i]].pred = index;
            _xdfs(point.edges[i], graph, cgraph);
        }
    }
    point.color = BLACK;
}

vector<CPoint> &xdfs(vector<Point> &graph)
{
    vector<CPoint> *pcgraph = new vector<CPoint>();
    vector<CPoint> &cgraph = *pcgraph;
    int i = 0;
    int index = max_f_white(graph);
    while (index != -1)
    {
        CPoint cpoint(i);
        cpoint.max_ftime = graph[index].ftime;
        cpoint.min_ftime = cpoint.max_ftime;
        cgraph.push_back(cpoint);
        _xdfs(index, graph, cgraph);
        index = max_f_white(graph);
        i++;
    }
    return cgraph;
}

void _cdfs(int index, vector<CPoint> &cgraph, unsigned &inf)
{
    CPoint &cpoint = cgraph[index];
    inf += cpoint.inner_points.size();

    cpoint.color = GRAY;
    for (unsigned i = 0; i < cpoint.cedges.size(); i++)
    {
        if (cgraph[cpoint.cedges[i]].color == WHITE)
        {
            _cdfs(cpoint.cedges[i], cgraph, inf);
        }
    }
    cpoint.color = BLACK;
}

unsigned cdfs(int index, vector<CPoint> &cgraph)
{
    for (unsigned i = 0; i < cgraph.size(); i++)
        cgraph[i].color = WHITE;
    unsigned inf = 0;
    _cdfs(index, cgraph, inf);
    return inf;
}


int main(void)
{
    vector<Point> graph = construct_input_edges();
    //
    dfs(graph);
    vector<Point> rgraph = construct_reverse(graph);
    vector<CPoint> cgraph = xdfs(rgraph);

    cout << cgraph.size() << endl;

    //vector<Point> graph = construct();
    ////
    //dfs(graph);
    //vector<Point> rgraph = construct_reverse(graph);
    //vector<CPoint> cgraph = xdfs(rgraph);

    //vector<int> index_maxinf;
    //vector<unsigned> cinf;
    //unsigned max = 0;
    //for (unsigned i = 0; i < cgraph.size(); i++)
    //{
        //unsigned inf = cdfs(i, cgraph);
        //cinf.push_back(inf);
        //if (inf >= max)
            //max = inf;
    //}
    //for (unsigned i = 0; i < cinf.size(); i++)
    //{
        //if (cinf[i] == max)
        //{
            //for (unsigned j = 0; j < cgraph[i].inner_points.size(); j++)
                //index_maxinf.push_back(cgraph[i].inner_points[j]);
        //}
    //}
    //std::sort(index_maxinf.begin(), index_maxinf.end());
    //cout << max - 1 << endl;
    //for (unsigned i = 0; i < index_maxinf.size(); i++)
    //{
        //cout << index_maxinf[i] << " ";
        ////if (i != index_maxinf.size() - 1)
            ////cout << " ";
    //}

    return 0;
}





