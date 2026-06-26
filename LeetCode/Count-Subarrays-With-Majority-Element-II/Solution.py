1class Solution:
2    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
3        from typing import List
4
5class BIT:
6    def __init__(self, n):
7        self.n = n
8        self.tree = [0] * (n + 1)
9
10    def update(self, idx, val):
11        while idx <= self.n:
12            self.tree[idx] += val
13            idx += idx & -idx
14
15    def query(self, idx):
16        res = 0
17        while idx > 0:
18            res += self.tree[idx]
19            idx -= idx & -idx
20        return res
21
22
23class Solution:
24    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
25
26        # If target never appears
27        if target not in nums:
28            return 0
29
30        # Convert to +1 / -1
31        arr = [1 if x == target else -1 for x in nums]
32
33        # Prefix sums
34        prefix = [0]
35        s = 0
36        for x in arr:
37            s += x
38            prefix.append(s)
39
40        # Coordinate compression
41        vals = sorted(set(prefix))
42        rank = {v: i + 1 for i, v in enumerate(vals)}
43
44        bit = BIT(len(vals))
45        ans = 0
46
47        # Count previous prefix sums < current prefix
48        for p in prefix:
49            idx = rank[p]
50            ans += bit.query(idx - 1)
51            bit.update(idx, 1)
52
53        return ans