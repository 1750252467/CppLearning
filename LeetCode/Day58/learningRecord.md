<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [每日温度](#%E6%AF%8F%E6%97%A5%E6%B8%A9%E5%BA%A6)
  - [题解](#%E9%A2%98%E8%A7%A3)
- [下一个更大元素 I](#%E4%B8%8B%E4%B8%80%E4%B8%AA%E6%9B%B4%E5%A4%A7%E5%85%83%E7%B4%A0-i)
  - [题解](#%E9%A2%98%E8%A7%A3-1)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# [每日温度](https://leetcode.cn/problems/daily-temperatures/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (69.02%) | 1485  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E5%A0%86" title="https://leetcode.com/tag/%E5%A0%86" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" title="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给定一个整数数组 `temperatures` ，表示每天的温度，返回一个数组 `answer` ，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。

 

**示例 1:**

```
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
```

**示例 2:**

```
输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
```

**示例 3:**

```
输入: temperatures = [30,60,90]
输出: [1,1,0]
```

 

**提示：**

- `1 <= temperatures.length <= 105`
- `30 <= temperatures[i] <= 100`

------

[Discussion](https://leetcode.cn/problems/daily-temperatures/comments/) | [Solution](https://leetcode.cn/problems/daily-temperatures/solution/)

## 题解

```C++
// @lc code=start
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
       stack<int> st;
       vector<int> result(temperatures.size(),0);
       st.push(0);
       for(int i = 0; i < temperatures.size(); i++){
        if(temperatures[i] < temperatures[st.top()]) {
            st.push(i);
        }else if(temperatures[i] == temperatures[st.top()]) {
            st.push(i);
        }else {
            while(!st.empty() && temperatures[i] > temperatures[st.top()]) {
                result[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
       }
       return result;
    }
};
```





# [下一个更大元素 I](https://leetcode.cn/problems/next-greater-element-i/description/)

|  Category  |  Difficulty   | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-----------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Easy (71.77%) | 1014  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E5%A0%86" title="https://leetcode.com/tag/%E5%A0%86" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%93%88%E5%B8%8C%E8%A1%A8" title="https://leetcode.com/tag/%E5%93%88%E5%B8%8C%E8%A1%A8" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" title="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

`nums1` 中数字 `x` 的 **下一个更大元素** 是指 `x` 在 `nums2` 中对应位置 **右侧** 的 **第一个** 比 `x` 大的元素。

给你两个 **没有重复元素** 的数组 `nums1` 和 `nums2` ，下标从 **0** 开始计数，其中`nums1` 是 `nums2` 的子集。

对于每个 `0 <= i < nums1.length` ，找出满足 `nums1[i] == nums2[j]` 的下标 `j` ，并且在 `nums2` 确定 `nums2[j]` 的 **下一个更大元素** 。如果不存在下一个更大元素，那么本次查询的答案是 `-1` 。

返回一个长度为 `nums1.length` 的数组 `ans` 作为答案，满足 `ans[i]` 是如上所述的 **下一个更大元素** 。

 

**示例 1：**

```
输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
输出：[-1,3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
- 1 ，用加粗斜体标识，nums2 = [1,3,4,2]。下一个更大元素是 3 。
- 2 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
```

**示例 2：**

```
输入：nums1 = [2,4], nums2 = [1,2,3,4].
输出：[3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 2 ，用加粗斜体标识，nums2 = [1,2,3,4]。下一个更大元素是 3 。
- 4 ，用加粗斜体标识，nums2 = [1,2,3,4]。不存在下一个更大元素，所以答案是 -1 。
```

 

**提示：**

- `1 <= nums1.length <= nums2.length <= 1000`
- `0 <= nums1[i], nums2[i] <= 104`
- `nums1`和`nums2`中所有整数 **互不相同**
- `nums1` 中的所有整数同样出现在 `nums2` 中

 

**进阶：**你可以设计一个时间复杂度为 `O(nums1.length + nums2.length)` 的解决方案吗？

------

[Discussion](https://leetcode.cn/problems/next-greater-element-i/comments/) | [Solution](https://leetcode.cn/problems/next-greater-element-i/solution/)

## 题解

```C++
// @lc code=start
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
       stack<int> st;
       vector<int> result(temperatures.size(),0);
       st.push(0);
       for(int i = 0; i < temperatures.size(); i++){
        if(temperatures[i] < temperatures[st.top()]) {
            st.push(i);
        }else if(temperatures[i] == temperatures[st.top()]) {
            st.push(i);
        }else {
            while(!st.empty() && temperatures[i] > temperatures[st.top()]) {
                result[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
       }
       return result;
    }
};
```

