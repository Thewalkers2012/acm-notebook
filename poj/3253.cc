#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int> > heap;
    for (int i = 0, x; i < n; i++) {
        cin >> x; 
        heap.push(x);
    }

    long long ans = 0;
    while (heap.size() > 1) {
        int a = heap.top();
        heap.pop();
        int b = heap.top();
        heap.pop();
        ans += a + b;
        heap.push(a + b);
    }

    cout << ans << "\n";

    return 0;
}