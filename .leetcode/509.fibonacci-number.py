#
# @lc app=leetcode id=509 lang=python3
#
# [509] Fibonacci Number
#

# @lc code=start
class Solution:
    def fib(self, n: int) -> int:
        obj = Solution
        if(n == 0):
            return 0
        if(n == 1):
            return 1
        return obj.fib(n-2) + obj.fib(n-1)
# @lc code=end

