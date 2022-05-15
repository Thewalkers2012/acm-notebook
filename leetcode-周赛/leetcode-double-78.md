# Leetcode 第 78 场双周赛题解

### Problem A - [找到一个数字的 K 美丽值](https://leetcode.cn/problems/find-the-k-beauty-of-a-number/)

#### 解法: 枚举
模拟即可
#### cpp 代码
```cpp
class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string s = to_string(num);
        int ans = 0;
        for (int i = 0; i + k - 1 < s.size(); i++) {
            int x = stoi(s.substr(i, k));
            if (x > 0 && num % x == 0) ans++;
        }
        return ans;
    }
};
```

- `to_string()`: 将数字转换为字符串 
- `stoi()`: 将字符串转换为数字
- 在对 $num$ 除 $x$ 的时候要对 $x$ 进行判断，判断其是不是正数


### Problem B - [分割数组的方案数](https://leetcode.cn/problems/number-of-ways-to-split-array/)
#### 解法: 枚举 & 前缀和
先求下该数组的前缀和，然后在遍历 $i$ 从 0 到 $n - 1$ 判断是前缀大还是后缀大
#### cpp 代码
```cpp
class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int ans = 0, n = nums.size();
        vector<long long> s(n + 1);
        for (int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + nums[i - 1];
        }
        
        for (int i = 1; i < n; i++) {
            if (s[i] >= s[n] - s[i]) {
                ans++;
            }
        }
        
        return ans;
    }
};
```

- 注意前缀和数组要开 $long long$
### Problem C - [毯子覆盖的最多白色砖块数](https://leetcode.cn/problems/maximum-white-tiles-covered-by-a-carpet/)
#### 解法: 贪心 & 滑动窗口
- 贪心结论：毯子的左端点一定和某瓷砖的左端点一致。
- 因此我们枚举毯子的左端点和哪个瓷砖的左端点一致，并通过滑动窗口维护此时毯子右端最多覆盖到哪组瓷砖，取最大值作为答案即可，复杂度 $O(nlog(n))$，由于一开始要排序
#### cpp 代码
```cpp
class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        sort(tiles.begin(), tiles.end());

        int n = tiles.size();
        int left = 0, right = 0, now = 0, ans = 0;
        while (left < n) {
            while (right < n && tiles[right][1] - tiles[left][0] + 1 <= carpetLen) {
                now += tiles[right][1] - tiles[right][0] + 1;
                right++;
            }
            if (right < n) {
                ans = max(ans, now + max(0, tiles[left][0] + carpetLen - tiles[right][0]));
            } else {
                ans = max(ans, now);
            }
            now -= tiles[left][1] - tiles[left][0] + 1;
            left++;
        }
        
        return ans;
    }
};
```

- TODO 考虑让 $right$ 先走试一试

### Problem D - [最大波动的子字符串](https://leetcode.cn/problems/substring-with-largest-variance/)
#### 题解：枚举 & DP
枚举哪个字符是出现最多的（记为 x），哪个字符是出现最少的（记为 y）。把字符串中所有的 $x$ 改为 $1$，字符串中所有的 $y$ 更改为 $-1$，那么最终的结果就是最大子串，并且该子串中包含 $x$ 和 $y$。

- 首先是最大最长子串，$dp[i] = dp[i] - min(dp[j])$ 
- 但是有特殊情况！我们不能把一段全是 x 的子串计入答案，也就是说子串里最少出现一个 y 才行。因此我们维护最近出现的 y 的位置 k，只允许从该位置之前作为子串的开头，即 $0 <= j < k$。
```cpp
class Solution {
public:
    int largestVariance(string s) {
        int ans = 0, n = s.size();

        for (char x = 'a'; x <= 'z'; x++) {
            for (char y = 'a'; y <= 'z'; y++) {
                if (x == y) {
                    continue ;
                }
                vector<int> f(n + 1);
                int t = 0, mn = 1e9;
                for (int i = 1, j = 0; i <= n; i++) {
                    char ch = s[i - 1];
                    if (ch == x) {
                        f[i] = ++t;
                    } else if (ch == y) {
                        f[i] = --t;
                        while (j < i) {
                            mn = min(mn, f[j++]);
                        }
                    } else {
                        f[i] = t;
                    }
                    ans = max(ans, f[i] - mn);
                }
            }
        }

        return ans;
    }
};
```