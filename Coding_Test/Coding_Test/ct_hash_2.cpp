#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void shell_sort(vector<T>& v) {
    int i, j, size;
    size = v.size();
    T temp;

    int gap = size / 2;
    while (gap > 0) {
        for (i = gap; i < size; i++) {
            temp = v.at(i);
            j = i;
            while (j >= gap && v.at(j - gap) > temp) {
                v.at(j) = v.at(j - gap);
                j -= gap;
            }
            v.at(j) = temp;
        }
        gap /= 2;
    }
}

bool solution(vector<string> phone_book) {
    bool answer = true;

    sort(phone_book.begin(), phone_book.end());

    for (vector<string>::iterator it = phone_book.begin(); it != (phone_book.end() - 1); it++)
    {
        if ((*it) == (*(it + 1)).substr(0, (*it).length()))
        {
            answer = false;
            break;
        }
    }

    return answer;
}

int main()
{
    vector<string> p;
    p.push_back("12");
    p.push_back("154");
    p.push_back("1788");
    p.push_back("236");
    p.push_back("5661");
    p.push_back("451");
    p.push_back("1234");

    shell_sort(p);

    for_each(p.begin(), p.end(), [](const string& s) {cout << s << endl; });
}