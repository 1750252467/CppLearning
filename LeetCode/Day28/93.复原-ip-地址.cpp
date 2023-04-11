/*
 * @lc app=leetcode.cn id=93 lang=cpp
 * @lcpr version=21902
 *
 * [93] 复原 IP 地址
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
// @lc code=end



/*
// @lcpr case=start
// "25525511135"\n
// @lcpr case=end

// @lcpr case=start
// "0000"\n
// @lcpr case=end

// @lcpr case=start
// "101023"\n
// @lcpr case=end

 */


