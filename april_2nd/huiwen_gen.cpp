#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

#define HUIWEN_LEAST(x) (10 * (x) * (x))
#define HUIWEN_LEAST_WORD(x) (HUIWEN_LEAST(x) * (1 + (x)))
#define WORD_LEAST(x) ((int)pow((double)(x), (double)(x)))

static const char charset[] = "abcdefghijklmn"
"opqrstuvwxyz";

char* gen_rand(int len)
{
    char *s = new char[len + 1];
    for (int k = 0; k < len; k++)
        s[k] = charset[rand() % (sizeof(charset) - 1)];

    s[len] = 0;

    return s;
}


int main()
{
    fstream fs;
    fs.open("test.in", std::fstream::out);

    vector<string> str_list;
    int count = 0;

    for (int i = 2; i <= 6; i++)
    {
        for (int j = 0; j < WORD_LEAST(i); j++)
        {
            char *str = gen_rand(i);
            str_list.push_back(*new string(str));
        }
        for (int j = 0; j < HUIWEN_LEAST(i); j++)
        {
            char *str = gen_rand(i);
            str_list.push_back(*new string(str));

            for (int k = 0; k < i; k++)
            {
                string dupstr(str);
                random_shuffle(dupstr.begin(), dupstr.end());
                str_list.push_back(dupstr);
            }
        }
    }

    random_shuffle(str_list.begin(), str_list.end());

    str_list.push_back(*new string("zzzzzzz"));
    str_list.push_back(*new string("zzzzzzz"));

    count = str_list.size();
    fs << count << endl;

    std::copy(str_list.begin(), str_list.end(), std::ostream_iterator<string>(fs, " "));

    fs.close();

    return 0;
}
                


