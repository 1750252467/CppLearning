<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [最后一块石头的重量 II](#%E6%9C%80%E5%90%8E%E4%B8%80%E5%9D%97%E7%9F%B3%E5%A4%B4%E7%9A%84%E9%87%8D%E9%87%8F-ii)
  - [题解](#%E9%A2%98%E8%A7%A3)
- [目标和](#%E7%9B%AE%E6%A0%87%E5%92%8C)
  - [题解](#%E9%A2%98%E8%A7%A3-1)
- [一和零](#%E4%B8%80%E5%92%8C%E9%9B%B6)
  - [题解](#%E9%A2%98%E8%A7%A3-2)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# [最后一块石头的重量 II](https://leetcode.cn/problems/last-stone-weight-ii/description/)

|  Category  |   Difficulty    | Likes | Dislikes |    ContestSlug     | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :----------------: | :----------: | :---: |
| algorithms | Medium (69.05%) |  667  |    0     | weekly-contest-137 |      Q4      | 2092  |

<details open="" style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">数组</code></a><span>&nbsp;</span>|<span>&nbsp;</span><a href="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" title="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;">动态规划</code></a></p></details>

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

有一堆石头，用整数数组 `stones` 表示。其中 `stones[i]` 表示第 `i` 块石头的重量。

每一回合，从中选出**任意两块石头**，然后将它们一起粉碎。假设石头的重量分别为 `x` 和 `y`，且 `x <= y`。那么粉碎的可能结果如下：

- 如果 `x == y`，那么两块石头都会被完全粉碎；
- 如果 `x != y`，那么重量为 `x` 的石头将会完全粉碎，而重量为 `y` 的石头新重量为 `y-x`。

最后，**最多只会剩下一块** 石头。返回此石头 **最小的可能重量** 。如果没有石头剩下，就返回 `0`。

 

**示例 1：**

```
输入：stones = [2,7,4,1,8,1]
输出：1
解释：
组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
```

**示例 2：**

```
输入：stones = [31,26,33,21,40]
输出：5
```

 

**提示：**

- `1 <= stones.length <= 30`
- `1 <= stones[i] <= 100`

------

[Discussion](https://leetcode.cn/problems/last-stone-weight-ii/comments/) | [Solution](https://leetcode.cn/problems/last-stone-weight-ii/solution/)

## 题解

1.确定dp数组以及下标的含义

**dp[j]表示容量（这里说容量更形象，其实就是重量）为j的背包，最多可以背最大重量为dp[j]**。

可以回忆一下01背包中，dp[j]的含义，容量为j的背包，最多可以装的价值为 dp[j]。

相对于 01背包，本题中，石头的重量是 stones[i]，石头的价值也是 stones[i] ，可以 “最多可以装的价值为 dp[j]” == “最多可以背的重量为dp[j]”

2.确定递推公式

01背包的递推公式为：dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);

本题则是：**dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);**

一些同学可能看到这dp[j - stones[i]] + stones[i]中 又有- stones[i] 又有+stones[i]，看着有点晕乎。

大家可以再去看 dp[j]的含义。

3.dp数组如何初始化

既然 dp[j]中的j表示容量，那么最大容量（重量）是多少呢，就是所有石头的重量和。

因为提示中给出1 <= stones.length <= 30，1 <= stones[i] <= 1000，所以最大重量就是30 * 1000 。

而我们要求的target其实只是最大重量的一半，所以dp数组开到15000大小就可以了。

当然也可以把石头遍历一遍，计算出石头总重量 然后除2，得到dp数组的大小。

我这里就直接用15000了。

接下来就是如何初始化dp[j]呢，因为重量都不会是负数，所以dp[j]都初始化为0就可以了，这样在递归公式dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);中dp[j]才不会初始值所覆盖。

代码为：

```text
vector<int> dp(15001, 0);
```

4.确定遍历顺序

如果使用一维dp数组，物品遍历的for循环放在外层，遍历背包的for循环放在内层，且内层for循环倒序遍历！

```C++
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        vector<int> dp(15001, 0);
        int sum = 0;
        for (int i = 0; i < stones.size(); i++) sum += stones[i];
        int target = sum / 2;
        for (int i = 0; i < stones.size(); i++) { // 遍历物品
            for (int j = target; j >= stones[i]; j--) { // 遍历背包
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - dp[target] - dp[target];
    }
};

```

参考文章：[代码随想录 (programmercarl.com)](https://programmercarl.com/1049.最后一块石头的重量II.html#思路)

# [目标和](https://leetcode.cn/problems/target-sum/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (48.74%) | 1611  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" title="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" title="https://leetcode.com/tag/%E5%9B%9E%E6%BA%AF" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details open="" style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给你一个整数数组 `nums` 和一个整数 `target` 。

向数组中的每个整数前添加 `'+'` 或 `'-'` ，然后串联起所有整数，可以构造一个 **表达式** ：

- 例如，`nums = [2, 1]` ，可以在 `2` 之前添加 `'+'` ，在 `1` 之前添加 `'-'` ，然后串联起来得到表达式 `"+2-1"` 。

返回可以通过上述方法构造的、运算结果等于 `target` 的不同 **表达式** 的数目。

 

**示例 1：**

```
输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
```

**示例 2：**

```
输入：nums = [1], target = 1
输出：1
```

 

**提示：**

- `1 <= nums.length <= 20`
- `0 <= nums[i] <= 1000`
- `0 <= sum(nums[i]) <= 1000`
- `-1000 <= target <= 1000`

------

[Discussion](https://leetcode.cn/problems/target-sum/comments/) | [Solution](https://leetcode.cn/problems/target-sum/solution/)

## 题解

```C++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) sum += nums[i];
        if (abs(S) > sum) return 0; // 此时没有方案
        if ((S + sum) % 2 == 1) return 0; // 此时没有方案
        int bagSize = (S + sum) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bagSize];
    }
};
```

参考文章：[代码随想录 (programmercarl.com)](https://programmercarl.com/0494.目标和.html#动态规划)

# [一和零](https://leetcode.cn/problems/ones-and-zeroes/description/)

|  Category  |   Difficulty    | Likes | Dislikes | ContestSlug | ProblemIndex | Score |
| :--------: | :-------------: | :---: | :------: | :---------: | :----------: | :---: |
| algorithms | Medium (64.91%) |  943  |    0     |      -      |      -       |   0   |

<details style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Tags</strong></summary><p><a href="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" title="https://leetcode.com/tag/%E6%95%B0%E7%BB%84" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%AD%97%E7%AC%A6%E4%B8%B2" title="https://leetcode.com/tag/%E5%AD%97%E7%AC%A6%E4%B8%B2" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a><a href="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" title="https://leetcode.com/tag/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92" style="color: var(--vscode-textLink-foreground);"><code style="color: var(--vscode-textLink-foreground); white-space: pre-wrap;"></code></a></p></details>

<details open="" style="color: rgb(0, 0, 0); font-family: -apple-system, BlinkMacSystemFont, &quot;Segoe WPC&quot;, &quot;Segoe UI&quot;, system-ui, Ubuntu, &quot;Droid Sans&quot;, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"><summary><strong>Companies</strong></summary></details>

给你一个二进制字符串数组 `strs` 和两个整数 `m` 和 `n` 。

请你找出并返回 `strs` 的最大子集的长度，该子集中 **最多** 有 `m` 个 `0` 和 `n` 个 `1` 。

如果 `x` 的所有元素也是 `y` 的元素，集合 `x` 是集合 `y` 的 **子集** 。

 

**示例 1：**

```
输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
输出：4
解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4 。
其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"} 不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。
```

**示例 2：**

```
输入：strs = ["10", "0", "1"], m = 1, n = 1
输出：2
解释：最大的子集是 {"0", "1"} ，所以答案是 2 。
```

 

**提示：**

- `1 <= strs.length <= 600`
- `1 <= strs[i].length <= 100`
- `strs[i]` 仅由 `'0'` 和 `'1'` 组成
- `1 <= m, n <= 100`

------

[Discussion](https://leetcode.cn/problems/ones-and-zeroes/comments/) | [Solution](https://leetcode.cn/problems/ones-and-zeroes/solution/)

## 题解

```C++
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0)); // 默认初始化0
        for (string str : strs) { // 遍历物品
            int oneNum = 0, zeroNum = 0;
            for (char c : str) {
                if (c == '0') zeroNum++;
                else oneNum++;
            }
            for (int i = m; i >= zeroNum; i--) { // 遍历背包容量且从后向前遍历！
                for (int j = n; j >= oneNum; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
```

参考文章：[代码随想录 (programmercarl.com)](https://programmercarl.com/0474.一和零.html#思路)