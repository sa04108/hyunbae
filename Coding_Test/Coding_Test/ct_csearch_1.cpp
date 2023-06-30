#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    int a1, a2, a3;
    int n[3] = { 0, 0, 0 };
    int maxn = 0;

    for (int i = 0; i < answers.size(); i++)
    {
        // 수포자 1의 답
        a1 = i % 5 + 1;

        // 수포자 2의 답
        if (i % 2 == 0)
            a2 = 2;
        else
        {
            if (i % 8 == 1 || i % 8 == 3)
                a2 = i % 8;
            else if (i % 8 == 5)
                a2 = i % 8 - 1;
            else
                a2 = i % 8 - 2;
        }

        // 수포자 3의 답
        switch (i % 10)
        {
        case 0:
        case 1:
            a3 = 3;
            break;

        case 2:
        case 3:
            a3 = 1;
            break;

        case 4:
        case 5:
            a3 = 2;
            break;

        case 6:
        case 7:
            a3 = 4;
            break;

        case 8:
        case 9:
            a3 = 5;
            break;

        default:
            a3 = 0;
            break;
        }

        if (answers[i] == a1)
            n[0]++;
        if (answers[i] == a2)
            n[1]++;
        if (answers[i] == a3)
            n[2]++;
    }

    for (int i = 0; i < 3; i++)
    {
        if (maxn < n[i])
            maxn = n[i];
    }

    for (int i = 0; i < 3; i++)
    {
        if (maxn == n[i])
            answer.push_back(i + 1);
    }

    return answer;
}

int main()
{

}