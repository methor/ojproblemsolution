#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(void)
{
    fstream fs;
    fs.open("test.in", fstream::out);

    int n = 10000, s = 100, t = 500;
    fs << n << " " << s << " " << t << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (rand() < RAND_MAX * 0.01)
                fs << (rand() % 99) + 2 << " " << i << " " << j << endl;
        }
    }

    fs.close();

    return 0;
}


