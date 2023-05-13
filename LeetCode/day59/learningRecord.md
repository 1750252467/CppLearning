<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [下一个更大元素 II](#%E4%B8%8B%E4%B8%80%E4%B8%AA%E6%9B%B4%E5%A4%A7%E5%85%83%E7%B4%A0-ii)
  - [题解](#%E9%A2%98%E8%A7%A3)
- [接雨水](#%E6%8E%A5%E9%9B%A8%E6%B0%B4)
  - [题解](#%E9%A2%98%E8%A7%A3-1)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# [下一个更大元素 II](https://leetcode.cn/problems/next-greater-element-ii/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (66.68%) |  806  |    0     |      -      |      -       |   0   |

<details open="" style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E5%A0%86" title="https://leetcode.com/tag/%E5%A0%86" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">堆</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">数组</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" title="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">单调栈</code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给定一个循环数组 `nums` （ `nums[nums.length - 1]` 的下一个元素是 `nums[0]` ），返回 *`nums` 中每个元素的 **下一个更大元素*** 。

数字 `x` 的 **下一个更大的元素** 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 `-1` 。

 

**示例 1:**

```
输入: nums = [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数； 
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
```

**示例 2:**

```
输入: nums = [1,2,3,4,3]
输出: [2,3,4,-1,4]
```

 

**提示:**

- `1 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`

------

[Discussion](https://leetcode.cn/problems/next-greater-element-ii/comments/) | [Solution](https://leetcode.cn/problems/next-greater-element-ii/solution/)

## 题解

```C++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        // 拼接一个新的nums
        vector<int> nums1(nums.begin(), nums.end());
        nums.insert(nums.end(), nums1.begin(), nums1.end());
        // 用新的nums大小来初始化result
        vector<int> result(nums.size(), -1);
        if (nums.size() == 0) return result;

        // 开始单调栈
        stack<int> st;
        st.push(0);
        for (int i = 1; i < nums.size(); i++) { 
            if (nums[i] < nums[st.top()]) st.push(i); 
            else if (nums[i] == nums[st.top()]) st.push(i);
            else { 
                while (!st.empty() && nums[i] > nums[st.top()]) {
                    result[st.top()] = nums[i];
                    st.pop();
                }
                st.push(i);
            }
        }
        // 最后再把结果集即result数组resize到原数组大小
        result.resize(nums.size() / 2);
        return result;
    }
};
```

参考文章：[代码随想录 (programmercarl.com)](https://programmercarl.com/0503.下一个更大元素II.html)

# [接雨水](https://leetcode.cn/problems/trapping-rain-water/description/)

|  Category  |  Difficulty   | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-----------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Hard (62.60%) | 4326  |    0     |      -      |      -       |   0   |

<details open="" style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E5%A0%86" title="https://leetcode.com/tag/%E5%A0%86" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">堆</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">数组</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E5%8F%8C%E6%8C%87%E9%92%88" title="https://leetcode.com/tag/%E5%8F%8C%E6%8C%87%E9%92%88" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">双指针</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" title="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">动态规划</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" title="https://leetcode.com/tag/%E5%8D%95%E8%B0%83%E6%A0%88" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">单调栈</code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

 

**示例 1：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rainwatertrap.png)

```
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
```

**示例 2：**

```
输入：height = [4,2,0,3,2,5]
输出：9
```

 

**提示：**

- `n == height.length`
- `1 <= n <= 2 * 104`
- `0 <= height[i] <= 105`

------

[Discussion](https://leetcode.cn/problems/trapping-rain-water/comments/) | [Solution](https://leetcode.cn/problems/trapping-rain-water/solution/)

## 题解

```C++
// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        st.push(0);
        int sum = 0;
        for (int i = 1; i < height.size(); i++) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int mid = st.top();
                st.pop();
                if (!st.empty()) {
                    int h = min(height[st.top()], height[i]) - height[mid];
                    int w = i - st.top() - 1;
                    sum += h * w;
                }
            }
            st.push(i);
        }
        return sum;
    }
};
```

