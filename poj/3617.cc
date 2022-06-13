#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<char> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int left = 0, right = n - 1;
    int sum = 0;
    while (left <= right) {
        bool isLeft = false;
        for (int i = left, j = right; i <= j; i++, j--) {
            if (v[i] < v[j]) {
                isLeft = true;
                break ;
            }
            if (v[j] < v[i]) {
                break ;
            }
        }

        sum++;
        if (isLeft) {
            cout << v[left++];
        } else {
            cout << v[right--];
        }
        if (sum % 80 == 0) {
            cout << "\n";
        }
    }

    return 0;
}