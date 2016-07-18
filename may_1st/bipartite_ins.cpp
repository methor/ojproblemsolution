#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
std::vector<int> &split(stringstream &ss, char delim, std::vector<int> &elems) {
    std::string item;
    while (std::getline(ss, item, delim)) {
        istringstream iss(item);
        int value;
        iss >> value;
        elems.push_back(value);
    }
    return elems;
}


std::vector<int> split(stringstream &s, char delim) {
    std::vector<int> elems;
    split(s, delim, elems);
    return elems;
}

class Point {
    public:
        int id;
        vector<int> edges;
        int side;
        Point(int id)
        {
            this->id = id;
            side = 0;
        }
};

int main(void)
{
    string s;
    vector<Point> graph;
    while (getline(cin, s))
    {
        stringstream ss(s);
        string item;
        getline(ss, item, ' ');
        istringstream iss(item);
        int value;
        iss >> value;
        Point point(value);

        vector<int> vs = split(ss, ' ');
        point.edges = vs;
        graph.push_back(point);
    }

    queue<Point> pqueue;
    graph[0].side = 1;
    pqueue.push(graph[0]);

    do {
        int size = pqueue.size();
        for (int i = 0; i < size; i++)
        {
            Point p = pqueue.front();
            pqueue.pop();
            for (vector<int>::iterator it = p.edges.begin(); it != p.edges.end(); ++it)
            {
                if (graph[*it].side == 0)
                {
                    graph[*it].side = (p.side == 1 ? 2 : 1);
                    pqueue.push(graph[*it]);
                }
            }
        }
    } while (!pqueue.empty());

    int side = graph[0].side;
    for (unsigned i = 0; i < graph.size(); i++)
    {
        if (graph[i].side == side)
            cout << graph[i].id << endl;
    }

    return 0;
}


    



