#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;

    unordered_map <string, int> attributes;
    for (int i = 0; i < clothes.size(); i++)
        attributes[clothes[i][1]]++;
    for (auto it = attributes.begin(); it != attributes.end(); it++)
        answer *= (it->second + 1);
    answer--;

    return answer;
}

int main()
{
    // vector<vector<string>> clothes = { {"yellowhat", "headgear"}, {"bluehat", "headgear"}, {"sunglasses", "eyewear"}, {"redpants", "pants"}, { "slacks", "pants" }, {"blueshirts", "shirts"} };
    vector<vector<string>> clothes(30, vector<string>(2));
    for (unsigned int i = 0; i < clothes.size(); i++)
    {
        for (unsigned int j = 0; j < clothes[i].size(); j++)
        {
            clothes[i][j] = i * 10 + j;
        }
    }
    int answer = solution(clothes);

    cout << answer;
}