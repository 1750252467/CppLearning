/*
 * @lc app=leetcode.cn id=131 lang=cpp
 * @lcpr version=21902
 *
 * [131] 分割回文串
 */
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// @lc code=start
class Solution {

private:
    vector<vector<string>> result;
    vector<string> path;
    void backtracking(const string& s, int startIndex) {

        if(startIndex >= s.size()) {
            result.push_back(path);
            return;
        }

        for(int i = startIndex; i < s.size();i++) {
            if(isPalindrome(s,startIndex,i)) {

                string str = s.substr(startIndex,i-startIndex+1);
                path.push_back(str);
            }else {
                continue;
            }
            backtracking(s,i+1);
            path.pop_back();
        }
    }

        bool isPalindrome(const string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
public:
    vector<vector<string>> partition(string s) {
        result.clear();
        path.clear();
        backtracking(s,0);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "aab"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n
// @lcpr case=end

 */


