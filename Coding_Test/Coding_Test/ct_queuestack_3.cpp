#include <iostream>
#include <string>
#include <vector>

using namespace std;

int sum_of_vector(vector<int> v)
{
    int sum = 0;

    for (auto it = v.begin(); it != v.end(); it++)
    {
        sum += *it;
    }

    return sum;
}

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;

    vector<int> bridge;

    while (!truck_weights.empty())
    {
        int front_weight = truck_weights.front();

        if (bridge.size() < bridge_length)
        {
            if (sum_of_vector(bridge) + front_weight <= weight)
            {
                bridge.push_back(front_weight);
                truck_weights.erase(truck_weights.begin());
            }
            else
                bridge.push_back(0);

            answer++;
        }
        else
        {
            bridge.erase(bridge.begin());
        }
    }

    answer += bridge_length;
    return answer;
}

int main()
{
    vector<int> truck_weights{5, 2, 7, 3, 9, 2, 3};

    int sol = solution(3, 10, truck_weights);
    cout << sol;
}