#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int pub = 0;
    int day = (100 - (*progresses.begin())) / (*speeds.begin());
    if ((100 - (*progresses.begin())) % (*speeds.begin()) != 0)
        day++;

    vector<int>::iterator it = progresses.begin();
    while (!progresses.empty())
    {
        (*it) += day * (*speeds.begin());

        if (*it >= 100)
        {
            // pop-front in queue
            it = progresses.erase(progresses.begin());
            speeds.erase(speeds.begin());
            pub++;
        }
        else
        {
            answer.push_back(pub);
            pub = 0;
            day += (100 - (*progresses.begin())) / (*speeds.begin());
            if ((100 - (*progresses.begin())) % (*speeds.begin()) != 0)
                day++;
        }
    }
    answer.push_back(pub);

    return answer;
}

int main()
{
    vector<int> p;
    p.push_back(95);
    p.push_back(90);
    p.push_back(99);
    p.push_back(99);
    p.push_back(80);
    p.push_back(99);

    vector<int> s;
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);

    vector<int> r = solution(p, s);

    for_each(r.begin(), r.end(), [](const int& i) {cout << i << endl; });

    return 0;
}