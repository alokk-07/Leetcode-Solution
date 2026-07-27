1class Solution:
2    def maxProduct(self, nums: List[int]) -> int: 
3        first = second = 0
4
5        for num in nums:
6            if num > first:
7               second = first
8               first = num 
9            elif num > second:
10                second = num 
11
12        return (first - 1) * (second - 1)
13
14        