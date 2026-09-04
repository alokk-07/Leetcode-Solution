1class Solution {
2    public int firstStableIndex(int[] nums, int k) {
3
4        int n = nums.length;
5
6        // suffixMin[i] = minimum value from i to n-1
7        int[] suffixMin = new int[n];
8
9        suffixMin[n - 1] = nums[n - 1];
10
11        for (int i = n - 2; i >= 0; i--) {
12            suffixMin[i] = Math.min(nums[i], suffixMin[i + 1]);
13        }
14
15        // Find prefix maximum and check each index
16        int prefixMax = nums[0];
17
18        for (int i = 0; i < n; i++) {
19
20            prefixMax = Math.max(prefixMax, nums[i]);
21
22            int instability = prefixMax - suffixMin[i];
23
24            if (instability <= k) {
25                return i;
26            }
27        }
28
29        return -1;
30    }
31}