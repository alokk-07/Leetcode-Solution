1class Solution:
2    def findMissingElements(self, nums: List[int]) -> List[int]:
3        s = set(nums)
4        ans = []
5
6        for i in range(min(nums), max(nums) + 1):
7            if i not in s:
8                ans.append(i)
9
10        return ans
11        