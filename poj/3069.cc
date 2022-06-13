#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int r, n;
    while (cin >> r >> n, r != -1 || n != -1) {
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        sort(v.begin(), v.end());

        int ans = 0, left = 0;
        while (left < n) {
            int pos = v[left];
            while (left < n && v[left + 1] - pos <= r) {
                left++;
            }
            pos = v[left];
            while (left < n && v[left + 1] - pos <= r) {
                left++;
            }
            ans++;
            left++;
        }

        cout << ans << "\n";
    }

    return 0;
}
