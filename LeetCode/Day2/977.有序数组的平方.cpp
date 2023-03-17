/*
 * @lc app=leetcode.cn id=977 lang=cpp
 * @lcpr version=21801
 *
 * [977] 有序数组的平方
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
/*class Solution {
public:
//快速排序
int partition(vector<int>& nums, int left, int right) {
	// 选取基准值
	int pivot = nums[left];
	int i = left, j = right;
	while (i < j) {
		// 移动 j
		while (i < j && nums[j] >= pivot) {   // 1 2 3 4 5 6 7 8 9
			j--;
		}
		// i == j || arr[j] < pivot
		nums[i] = nums[j];

		// 移动 i
		while (i < j && nums[i] <= pivot) {
			i++;
		}
		// i == j || arr[i] > pivot
		nums[j] = nums[i];
	}
	// i == j
	nums[i] = pivot;
	return i;
}

void quick_sort1(vector<int>& nums, int left, int right) {
	// 边界条件
	if (left >= right) return;
	// 递归公式
	int idx = partition(nums, left, right);
	quick_sort1(nums, left, idx - 1);
	quick_sort1(nums, idx + 1, right);
}
void quick_sort(vector<int>& nums) {
	quick_sort1(nums, 0, nums.size()-1);
}
    vector<int> sortedSquares(vector<int>& nums) {

        for(int i = 0; i < nums.size();++i){
            nums[i] *=nums[i]; 
        }
		quick_sort(nums);
		
		return nums;
    }
};

*/

//双指针
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
		int size = nums.size()-1;
		vector<int> result(nums.size(), 0);
		int left = 0 , right = size; 
		while(left <= right) {
			if(nums[left]*nums[left] > nums[right]* nums[right]) {
				result[size--] = nums[left] * nums[left];
				left++;
			}else{
				result[size--] = nums[right] * nums[right];
				right--;
			}
		}
		return result;
    }
};



// @lc code=end

// @lcpr-div-debug-arg-start
// funName=
// paramTypes= []
// returnType=
// @lcpr-div-debug-arg-end


/*
// @lcpr case=start
// [-4,-1,0,3,10]\n
// @lcpr case=end

// @lcpr case=start
// [-7,-3,2,3,11]\n
// @lcpr case=end

 */


