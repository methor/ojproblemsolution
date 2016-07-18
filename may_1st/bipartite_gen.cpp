#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#define MID(x) ((x).begin() + ((x).end() - (x).begin()) / 2 + 1)

class Point {
    public:
        int id;
        vector<int> edges;
        Point(int id)
        {
            this->id = id;
        }
};

void difference(vector<int>::iterator first1, vector<int>::iterator first2,vector<int>::iterator last1,vector<int>::iterator last2, vector<int>::iterator result)
{
    for (; first1 != first2; ++first1)
    {
        int contains = 0;
        for (vector<int>::iterator last_tmp = last1; last_tmp != last2; ++last_tmp)
        {
            if (*first1 == *last_tmp)
            {
                contains = 1;
                break;
            }
        }
        if (contains == 0)
        {
            *result = *first1;
            ++result;
        }
    }
}


int main(void)
{


    int n = 1000;
    vector<Point> graph;
    vector<int> pset;
    for (int i = 1; i <= n; i++)
    {
        Point point(i - 1);
        graph.push_back(point);
        pset.push_back(i - 1);
    }
    random_shuffle(pset.begin(), pset.end());
    vector<int> lsubset(pset.begin(), pset.begin() + (pset.end() - 
                pset.begin()) / 2);
    vector<int> rsubset(pset.size() - lsubset.size(), 0);
    try {
    set_difference(pset.begin(), pset.end(), lsubset.begin(), 

            lsubset.end(), rsubset.begin());
    } catch (const char *msg) {
        cerr << msg << "line 41" << endl;
        return -1;
    }
    for (vector<int>::iterator it = lsubset.begin(); it != lsubset.end(); ++it)
    {
        random_shuffle(rsubset.begin(), rsubset.end());
        for (vector<int>::iterator itn = rsubset.begin(); itn != rsubset.end() && itn <= MID(rsubset); ++itn)
        {
            try {
            graph.at(*it).edges.push_back(*itn);
            graph.at(*itn).edges.push_back(*it);
            } catch (...)
            {
                cerr << "line 54" << endl;
                return -1;
            }
        }
    }
        
    for (vector<int>::iterator it = rsubset.begin(); it != rsubset.end(); ++it)
    {
        if (lsubset.size() == graph.at(*it).edges.size())
            continue;

        vector<int> setdiff(lsubset.size() - graph.at(*it).edges.size(), 0);
        //try {
        difference(lsubset.begin(), lsubset.end(), graph.at(*it).edges.begin(), graph.at(*it).edges.end(), setdiff.begin());
        //} catch (const char *msg) {
            //cerr << msg << "line 61" << endl;
            //return -1;
        //}
        
        random_shuffle(setdiff.begin(), setdiff.end());
        for (vector<int>::iterator itn = setdiff.begin(); itn != setdiff.end() && itn <= MID(setdiff); ++itn)
        {
            graph.at(*it).edges.push_back(*itn);
            graph.at(*itn).edges.push_back(*it);
        }
    }
    fstream fs;
    fs.open("bipartite.in", fstream::out);
    for (unsigned i = 0; i < graph.size(); i++)
    {
        fs << graph.at(i).id << " ";
        copy(graph.at(i).edges.begin(), graph.at(i).edges.end(),
                std::ostream_iterator<int>(fs, " "));
        fs << endl;
    }

    fs.close();

    return 0;
}




