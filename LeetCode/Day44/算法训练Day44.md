<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [零钱兑换 II](#%E9%9B%B6%E9%92%B1%E5%85%91%E6%8D%A2-ii)
  - [题解](#%E9%A2%98%E8%A7%A3)
- [组合总和 Ⅳ](#%E7%BB%84%E5%90%88%E6%80%BB%E5%92%8C-%E2%85%A3)
  - [题解](#%E9%A2%98%E8%A7%A3-1)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# [零钱兑换 II](https://leetcode.cn/problems/coin-change-ii/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (70.35%) | 1066  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" title="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details open="" style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给你一个整数数组 `coins` 表示不同面额的硬币，另给一个整数 `amount` 表示总金额。

请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 `0` 。

假设每一种面额的硬币有无限个。 

题目数据保证结果符合 32 位带符号整数。

 



**示例 1：**

```
输入：amount = 5, coins = [1, 2, 5]
输出：4
解释：有四种方式可以凑成总金额：
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
```

**示例 2：**

```
输入：amount = 3, coins = [2]
输出：0
解释：只用面额 2 的硬币不能凑成总金额 3 。
```

**示例 3：**

```
输入：amount = 10, coins = [10] 
输出：1
```

 

**提示：**

- `1 <= coins.length <= 300`
- `1 <= coins[i] <= 5000`
- `coins` 中的所有值 **互不相同**
- `0 <= amount <= 5000`

------

[Discussion](https://leetcode.cn/problems/coin-change-ii/comments/) | [Solution](https://leetcode.cn/problems/coin-change-ii/solution/)

## 题解

```C++
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < coins.size(); i++) { // 遍历物品
            for (int j = coins[i]; j <= amount; j++) { // 遍历背包
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount];
    }
};
```

# [组合总和 Ⅳ](https://leetcode.cn/problems/combination-sum-iv/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (52.90%) |  798  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" title="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给你一个由 **不同** 整数组成的数组 `nums` ，和一个目标整数 `target` 。请你从 `nums` 中找出并返回总和为 `target` 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。

 

**示例 1：**

```
输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。
```

**示例 2：**

```
输入：nums = [9], target = 3
输出：0
```

 

**提示：**

- `1 <= nums.length <= 200`
- `1 <= nums[i] <= 1000`
- `nums` 中的所有元素 **互不相同**
- `1 <= target <= 1000`

 

**进阶：**如果给定的数组中含有负数会发生什么？问题会产生何种变化？如果允许负数出现，需要向题目中添加哪些限制条件？

------

[Discussion](https://leetcode.cn/problems/combination-sum-iv/comments/) | [Solution](https://leetcode.cn/problems/combination-sum-iv/solution/)

## 题解

```C++
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 0; i <= target; i++) { // 遍历背包
            for (int j = 0; j < nums.size(); j++) { // 遍历物品
                if (i - nums[j] >= 0 && dp[i] < INT_MAX - dp[i - nums[j]]) {
                    dp[i] += dp[i - nums[j]];
                }
            }
        }
        return dp[target];
    }
};
```

