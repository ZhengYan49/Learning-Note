
/* 
data-time 2020-04-21 14:14:53


题目描述:

1248. 统计「优美子数组」

给你一个整数数组 nums 和一个整数 k。

如果某个 连续 子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。

请返回这个数组中「优美子数组」的数目。

 

示例 1：

输入：nums = [1,1,2,1,1], k = 3
输出：2
解释：包含 3 个奇数的子数组是 [1,1,2,1] 和 [1,2,1,1] 。
示例 2：

输入：nums = [2,4,6], k = 1
输出：0
解释：数列中不包含任何奇数，所以不存在优美子数组。
示例 3：

输入：nums = [2,2,2,1,2,2,1,2,2,2], k = 2
输出：16
 

提示：

1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-number-of-nice-subarrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
/**
主要思路:
 使用左右指针和滑动窗口
使用count统计其中奇数的数量
左指针不停向右移动，直到遇到尾部
如果为奇数就--；
count<k 移动右指针；
count>k 移动左指针；
count==k; 同时移动左指针和右指针；并添加计数
注意；左右指针永远指向奇数
 */

#include <cmath>
#include <cctype>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <cstdint>

using namespace std;


class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        if(nums.size()<k){
            return 0;
        }
          int left = 0, right = 0, oddCnt = 0, res = 0;
        while (right < nums.size()) {
            // 右指针先走，每遇到一个奇数则 oddCnt++。
            if ((nums[right++] & 1) == 1) {
                oddCnt++;
            }

            //  若当前滑动窗口 [left, right) 中有 k 个奇数了，进入此分支统计当前滑动窗口中的优美子数组个数。
            if (oddCnt == k) {
                // 先将滑动窗口的右边界向右拓展，直到遇到下一个奇数（或出界）
                // rightEvenCnt 即为第 k 个奇数右边的偶数的个数
                int tmp = right;
                while (right < nums.size() && (nums[right] & 1) == 0) {
                    right++;
                }
                int rightEvenCnt = right - tmp;
                // leftEvenCnt 即为第 1 个奇数左边的偶数的个数
                int leftEvenCnt = 0;
                while ((nums[left] & 1) == 0) {
                    leftEvenCnt++;
                    left++;
                }
                // 第 1 个奇数左边的 leftEvenCnt 个偶数都可以作为优美子数组的起点
                // (因为第1个奇数左边可以1个偶数都不取，所以起点的选择有 leftEvenCnt + 1 种）
                // 第 k 个奇数右边的 rightEvenCnt 个偶数都可以作为优美子数组的终点
                // (因为第k个奇数右边可以1个偶数都不取，所以终点的选择有 rightEvenCnt + 1 种）
                // 所以该滑动窗口中，优美子数组左右起点的选择组合数为 (leftEvenCnt + 1) * (rightEvenCnt + 1)
                res += (leftEvenCnt + 1) * (rightEvenCnt + 1);

                // 此时 left 指向的是第 1 个奇数，因为该区间已经统计完了，因此 left 右移一位，oddCnt--
                left++;
                oddCnt--;
            }

        }

        return res;
    }
};

//关闭流输出
static auto static_lambda = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    return 0;
}();

int main(int argc,char* argv[]){
    Solution a;
    vector<int> temp={0,2,1,-6,6,-7,9,1,2,0,1};
    a.numberOfSubarrays(temp,5);
    return 0;
}
/*
优质解析1:记录奇数前面偶数的个数，没有就填0；
然后将i前面的偶数个数和i+k后面的偶数个数相乘

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
    vector<int> even;
    int len = 0;
    int even_cnt=0;
    int first_odd=-1;
    int last_odd=0;

    //   //神奇的思路   记录每个奇数前面的偶数个数，没有就填0  //两次遍历 O（2N）
    for(int i=0;i<nums.size();i++)
    {
        if(nums[i]%2==1)
        {
            even.push_back(even_cnt);
            even_cnt=0;
        }
        else{
            even_cnt++;
        }
    }
    even.push_back(even_cnt);
    int res = 0;
    if(even.size()>=k)
    {
        for(int i = k;i<even.size();i++)
        {
            res+=(even[i]+1)*(even[i-k]+1);//统计k个奇数之间的偶数的个数
        }
        return res;
    }
    else return 0;
    }

};
//官方题解：
https://leetcode-cn.com/problems/count-number-of-nice-subarrays/solution/tong-ji-you-mei-zi-shu-zu-by-leetcode-solution/
//优质解析1:
https://leetcode-cn.com/problems/count-number-of-nice-subarrays/solution/count-number-of-nice-subarrays-by-ikaruga/
*/