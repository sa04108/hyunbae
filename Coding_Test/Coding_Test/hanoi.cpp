#include <iostream>
using namespace std;

void hanoi(const int &n, const int &start, const int &end, const int &mid) {
	if (n < 1) return;

	hanoi(n - 1, start, mid, end);
	cout << start << ' ' << end << "\n";
	hanoi(n - 1, mid, end, start);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	cout << (1 << n) - 1 << "\n";
	hanoi(n, 1, 3, 2);

	return 0;
}