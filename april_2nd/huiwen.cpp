#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <list>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

using namespace std;

std::fstream fin;
std::fstream fout;



class Word {
    public:
        string post_perm;
        string prev_perm;
};

bool compare(Word a, Word b)
{
    string sa = a.post_perm;
    string sb = b.post_perm;    
    if (sa.size() < sb.size())
        return true;
    else if (sa.size() > sb.size())
        return false;
    else
    {
        if (sa.compare(sb) <= 0)
            return true;
        else 
            return false;
    }
}

bool comp_by_prev(Word a, Word b)
{
    if (a.prev_perm.compare(b.prev_perm) <= 0)
        return true;
    else
        return false;
}

int main()
{
#if LOCAL
fin.open("test.in", std::fstream::in);
fout.open("test.out", std::fstream::out);
cin.rdbuf(fin.rdbuf());
cout.rdbuf(fout.rdbuf());
#endif

    int n;
    Word *wordbuf;
    cin >> n;
    wordbuf = new Word[n];
    for (int i = 0; i < n; i++)
    {
        cin >> wordbuf[i].prev_perm;
        wordbuf[i].post_perm = wordbuf[i].prev_perm;

        sort(wordbuf[i].post_perm.begin(), wordbuf[i].post_perm.end(),
                less<char>());
    }
    fstream sout;
    sout.open("sort.out", std::fstream::out);
    

    sort(wordbuf, wordbuf+n, compare);


    vector<Word> huiwen_list;
    int begin = 0, end = 0;

    for (int i = 1; i < n; i++)
    {
        if (wordbuf[i].post_perm.compare(wordbuf[i-1].post_perm) == 0)
            end++;
        else         {
            if (end - begin > 0)
            {

                sort(wordbuf+begin, wordbuf+end+1,comp_by_prev);
                for (int i = begin; i < end + 1; i++)
                {
                    sout << wordbuf[i].prev_perm << " ";
                }
                sout << endl;
                huiwen_list.push_back(wordbuf[begin]);
            }
            // reset begin & end
            begin = end + 1;
            end = begin;
        }
    }
    if (begin != n - 1) // last huiwen left out
    {
        sort(wordbuf+begin, wordbuf+end+1, comp_by_prev);
                for (int i = begin; i < end + 1; i++)
                {
                    sout << wordbuf[i].prev_perm << " ";
                }
                sout << endl;
        huiwen_list.push_back(wordbuf[begin]);
    }


    cout << huiwen_list.size() << endl;
    sort(huiwen_list.begin(), huiwen_list.end(), comp_by_prev);
    for (unsigned i = 0; i < huiwen_list.size(); i++)
    {
        cout << huiwen_list.at(i).prev_perm;
        if (i != huiwen_list.size() - 1)
            cout << endl;

        
        
    }

    //sout.close();

    return 0;
}







