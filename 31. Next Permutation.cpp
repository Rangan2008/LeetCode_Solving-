class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();

        int i = n - 2;

        // Find first decreasing element from the right
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // If such element exists
        if (i >= 0) {
            int j = n - 1;

            // Find just larger element from the right
            while (nums[j] <= nums[i]) {
                j--;
            }

            swap(nums[i], nums[j]);
        }

        // Make suffix smallest possible
        reverse(nums.begin() + i + 1, nums.end());
    }
};
