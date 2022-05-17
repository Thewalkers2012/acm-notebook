# Leetcode 953 - [验证外星语词典](https://leetcode.cn/problems/verifying-an-alien-dictionary/)

## 解法: 枚举
直接对字符串数组进行遍历，然后对与当前元素与前一个元素进行比对，注意两者相等的时候，valid 此时还是 false，因此还要对其进行判断长短才行。

## cpp 代码
```cpp
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        vector<int> index(26);
        for (int i = 0; i < order.size(); i++) {
            index[order[i] - 'a'] = i;
        }
        for (int i = 1; i < words.size(); i++) {
            bool valid = false;
            for (int j = 0; j < words[i - 1].size() && j < words[i].size(); j++) {
                int prev = index[words[i - 1][j] - 'a'];
                int curr = index[words[i][j] - 'a'];
                if (prev < curr) {
                    valid = true;
                    break;
                } else if (prev > curr) {
                    return false;
                }
            }
            if (!valid) {
                /* 比较两个字符串的长度 */
                if (words[i - 1].size() > words[i].size()) {
                    return false;
                }
            }
        }
        return true;
    }
};

```