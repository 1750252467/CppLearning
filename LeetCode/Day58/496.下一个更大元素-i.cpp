/*
 * @lc app=leetcode.cn id=496 lang=cpp
 * @lcpr version=21907
 *
 * [496] 下一个更大元素 I
 */

// @lc code=start
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> result(nums1.size(), -1);
        if (nums1.size() == 0) return result;

        unordered_map<int, int> umap; // key:下标元素，value：下标
        for (int i = 0; i < nums1.size(); i++) {
            umap[nums1[i]] = i;
        }
        st.push(0);
        for (int i = 1; i < nums2.size(); i++) {
            if (nums2[i] < nums2[st.top()]) {           // 情况一
                st.push(i);
            } else if (nums2[i] == nums2[st.top()]) {   // 情况二
                st.push(i);
            } else {                                    // 情况三
                while (!st.empty() && nums2[i] > nums2[st.top()]) {
                    if (umap.count(nums2[st.top()]) > 0) { // 看map里是否存在这个元素
                        int index = umap[nums2[st.top()]]; // 根据map找到nums2[st.top()] 在 nums1中的下标
                        result[index] = nums2[i];
                    }
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,1,2]\n[1,3,4,2].\n
// @lcpr case=end

// @lcpr case=start
// [2,4]\n[1,2,3,4].\n
// @lcpr case=end

 */

