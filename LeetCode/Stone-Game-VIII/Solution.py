1class Solution:
2    def stoneGameVIII(self, stones):
3        n = len(stones)
4
5        # Prefix sums
6        prefix = [0] * n
7        prefix[0] = stones[0]
8
9        for i in range(1, n):
10            prefix[i] = prefix[i - 1] + stones[i]
11
12        # Base case
13        dp = prefix[n - 1]
14
15        # Work backwards
16        for i in range(n - 2, 0, -1):
17            dp = max(dp, prefix[i] - dp)
18
19        return dp