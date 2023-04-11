<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [复原 IP 地址](#%E5%A4%8D%E5%8E%9F-ip-%E5%9C%B0%E5%9D%80)
  - [题解](#%E9%A2%98%E8%A7%A3)
- [子集](#%E5%AD%90%E9%9B%86)
  - [题解](#%E9%A2%98%E8%A7%A3-1)
- [子集 II](#%E5%AD%90%E9%9B%86-ii)
  - [题解](#%E9%A2%98%E8%A7%A3-2)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# [复原 IP 地址](https://leetcode.cn/problems/restore-ip-addresses/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (57.89%) | 1197  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E5%AD%97%E7%AC%A6%E4%B8%B2" title="https://leetcode.com/tag/%E5%AD%97%E7%AC%A6%E4%B8%B2" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" title="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

**有效 IP 地址** 正好由四个整数（每个整数位于 `0` 到 `255` 之间组成，且不能含有前导 `0`），整数之间用 `'.'` 分隔。

- 例如：`"0.1.2.201"` 和` "192.168.1.1"` 是 **有效** IP 地址，但是 `"0.011.255.245"`、`"192.168.1.312"` 和 `"192.168@1.1"` 是 **无效** IP 地址。

给定一个只包含数字的字符串 `s` ，用以表示一个 IP 地址，返回所有可能的**有效 IP 地址**，这些地址可以通过在 `s` 中插入 `'.'` 来形成。你 **不能** 重新排序或删除 `s` 中的任何数字。你可以按 **任何** 顺序返回答案。

 

**示例 1：**

```
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
```

**示例 2：**

```
输入：s = "0000"
输出：["0.0.0.0"]
```

**示例 3：**

```
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
```

 

**提示：**

- `1 <= s.length <= 20`
- `s` 仅由数字组成

------

[Discussion](https://leetcode.cn/problems/restore-ip-addresses/comments/) | [Solution](https://leetcode.cn/problems/restore-ip-addresses/solution/)

## 题解

```C++
class Solution {
private:
    vector<string> result;

    void backtracking(string& s, int startIndex,int pointNum) {
        if(pointNum == 3) {
            if(isValid(s,startIndex,s.size()-1)) {
                result.push_back(s);
            }
            return;
        }

        for(int i = startIndex; i < s.size();i++) {
            if(isValid(s,startIndex,i)) {
                s.insert(s.begin() + i + 1, '.');
                pointNum++;
                backtracking(s,i+2,pointNum);
                pointNum--;
                s.erase(s.begin() + i + 1);
            }else break;
        }
    }

    bool isValid(const string& s, int start, int end) {
        if(start > end) {
            return false;

        }
        if(s[start] == '0' && start != end) {
            return false;
        } 
        int num = 0;
        for(int i = start; i <= end; i++) {
            if(s[i] > '9' || s[i] < '0') {
                return false;
            }

            num = num * 10 + (s[i] - '0');
            if(num > 255) {
                return false;
            }
        }
        return true;

     }
public:
    vector<string> restoreIpAddresses(string s) {
        result.clear();
        if(s.size() < 4 || s.size() > 12) return result;
        backtracking(s,0,0);
        return result;
    }
};
```

# [子集](https://leetcode.cn/problems/subsets/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (81.07%) | 2001  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E4%BD%8D%E6%93%8D%E4%BD%9C" title="https://leetcode.com/tag/%E4%BD%8D%E6%93%8D%E4%BD%9C" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" title="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。你可以按 **任意顺序** 返回解集。

 

**示例 1：**

```
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

**示例 2：**

```
输入：nums = [0]
输出：[[],[0]]
```

 

**提示：**

- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`
- `nums` 中的所有元素 **互不相同**

------

[Discussion](https://leetcode.cn/problems/subsets/comments/) | [Solution](https://leetcode.cn/problems/subsets/solution/)

## 题解

```C++
// @lc code=start
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        if(startIndex >= nums.size()) {
            return;
        }
        for(int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums,i+1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums,0);
        return result;
    }
};
```

# [子集 II](https://leetcode.cn/problems/subsets-ii/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (63.67%) | 1067  |    0     |      -      |      -       |   0   |

<details open="" style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E4%BD%8D%E6%93%8D%E4%BD%9C" title="https://leetcode.com/tag/%E4%BD%8D%E6%93%8D%E4%BD%9C" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">位操作</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">数组</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" title="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">回溯</code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给你一个整数数组 `nums` ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。返回的解集中，子集可以按 **任意顺序** 排列。

 

**示例 1：**

```
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
```

**示例 2：**

```
输入：nums = [0]
输出：[[],[0]]
```

 

**提示：**

- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`

------

[Discussion](https://leetcode.cn/problems/subsets-ii/comments/) | [Solution](https://leetcode.cn/problems/subsets-ii/solution/)

## 题解

```C++
// @lc code=start
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums,int startIndex, vector<bool>& used) {
        result.push_back(path);
        for(int i = startIndex; i < nums.size(); ++i) {

            if(i > 0 && nums[i] == nums[i-1] && used[i-1] == false) {
                continue;
            }

            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums,i + 1,used);
            used[i] = false;
            path.pop_back();
        }

    }
 public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(),false);
        sort(nums.begin(),nums.end());
        backtracking(nums,0,used);
        return result;
    }
};
```

