#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int strToHashcode(string& str)
{
    int sum = 0;
    int len = str.size();

    for (int i = 0; i < len; i++)
    {
        sum += ((int)str[i] - 97);
    }

    return sum;
}

int doubleHashing(int hashcode, int len, int stepBy)
{
    // 7 is coprime number
    int step = 7 - hashcode % 7;
    return ((hashcode % len) + (stepBy * step)) % len;
}

int findIndex(string* hashtable, string& content, int tableLength)
{
    int index = 0;
    int len = tableLength;
    // default hashcode determines by sum of each letter's ascii code
    int hashcode = strToHashcode(content);

    // hashtable collision
    int stepBy = 0;
    do
    {
        index = doubleHashing(hashcode, len, stepBy);

        stepBy++;
    } while (!hashtable[index].empty());

    return index;
}

string solution(vector<string> participant, vector<string> completion) {
    //int index = 0;
    //int len = 1000;
    //string* pHashtable = new string[len];
    //string* cHashtable = new string[len];

    //for (unsigned int i = 0; i < participant.size(); i++)
    //{
    //    index = findIndex(pHashtable, participant.at(i), len);
    //    pHashtable[index] = participant.at(i);
    //}

    //for (unsigned int i = 0; i < completion.size(); i++)
    //{
    //    index = findIndex(cHashtable, completion.at(i), len);
    //    cHashtable[index] = completion.at(i);
    //}

    //index = -1;

    //for (int i = 0; i < len; i++)
    //{
    //    if (pHashtable[i] != cHashtable[i]) {
    //        index = i;
    //        break;
    //    }
    //}

    //delete[] pHashtable;
    //delete[] cHashtable;

    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());

    string answer = *(participant.end() - 1);

    for (int i = 0; i < completion.size(); i++)
    {
        if (participant.at(i) != completion.at(i))
        {
            answer = participant.at(i);
            break;
        }
    }

    return answer;
}

int main()
{
    vector<string> p;
    p.push_back("mislav");
    p.push_back("stanko");
    p.push_back("mislav");
    p.push_back("ana");

    vector<string> c;
    c.push_back("stanko");
    c.push_back("ana");
    c.push_back("mislav");

    string s = solution(p, c);
    cout << s;

    return 0;
}