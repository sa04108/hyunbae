#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

struct compare
{
    bool operator()(vector<int>& former, vector<int>& later)
    {
        if (former.back() == later.back())
            return former.front() > later.front();
        return former.back() > later.back();
    }
};

int solution(vector<vector<int>> jobs) {
    int size = jobs.size();
    int answer = 0;
    int endTime = 0;
    priority_queue<vector<int>, vector<vector<int>>, compare> waitingJobs;

    // sort jobs vector by its request time. if same request time, then sort by its processing time
    sort(jobs.begin(), jobs.end());

    for (int i = 0; i < size; i++)
    {
        if (!jobs.empty()) {
            if (waitingJobs.empty() && jobs.front()[0] > endTime)
                endTime = jobs.front()[0];

            while (jobs.front()[0] <= endTime)
            {
                waitingJobs.push(jobs.front());
                jobs.erase(jobs.begin());
                if (jobs.empty()) break;
            }
        }

        answer += waitingJobs.top()[1] + (endTime - waitingJobs.top()[0]);
        endTime += waitingJobs.top()[1];
        waitingJobs.pop();
    }

    answer /= size;
    return answer;
}

int main()
{
    vector<vector<int>> v(10, vector<int>(2));

    v[0][0] = 24; v[0][1] = 10;
    v[1][0] = 28; v[1][1] = 39;
    v[2][0] = 43; v[2][1] = 20;
    v[3][0] = 37; v[3][1] = 5;
    v[4][0] = 47; v[4][1] = 22;
    v[5][0] = 20; v[5][1] = 47;
    v[6][0] = 15; v[6][1] = 34;
    v[7][0] = 15; v[7][1] = 2;
    v[8][0] = 35; v[8][1] = 43;
    v[9][0] = 26; v[9][1] = 1;

    int avg = solution(v);
    cout << avg;
}