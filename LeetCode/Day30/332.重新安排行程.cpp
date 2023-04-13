/*
 * @lc app=leetcode.cn id=332 lang=cpp
 * @lcpr version=21906
 *
 * [332] 重新安排行程
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
#include <map>
// @lc code=start
class Solution {
private:
    unordered_map<string,map<string,int>> targets;
    bool backtracking(int ticketNum, vector<string>& result) {
        if(result.size() == ticketNum + 1) {
            return true;
        }
        for(pair<const string,int>& target : targets[result[result.size()-1]]) {
            if(target.second > 0) {
                result.push_back(target.first);
                target.second--;
                if(backtracking(ticketNum,result)) return true;
                result.pop_back();
                target.second++;
             }
        }
        return false;
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        targets.clear();
        vector<string> result;
        for(const vector<string>& vec : tickets) {
            targets[vec[0]][vec[1]]++;
        }
        result.push_back("JFK");
        backtracking(tickets.size(),result);
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]\n
// @lcpr case=end

// @lcpr case=start
// [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]\n
// @lcpr case=end

 */

