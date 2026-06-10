class Solution {
    using ll = long long;

    struct SparseTable {
        vector<vector<int>> stMax, stMin;
        vector<int> lg;

        SparseTable(vector<int>& nums) {
            int n = nums.size();

            lg.resize(n + 1);
            for (int i = 2; i <= n; i++)
                lg[i] = lg[i / 2] + 1;

            int K = lg[n] + 1;

            stMax.assign(K, vector<int>(n));
            stMin.assign(K, vector<int>(n));

            for (int i = 0; i < n; i++) {
                stMax[0][i] = nums[i];
                stMin[0][i] = nums[i];
            }

            for (int k = 1; k < K; k++) {
                for (int i = 0; i + (1 << k) <= n; i++) {
                    stMax[k][i] =
                        max(stMax[k - 1][i],
                            stMax[k - 1][i + (1 << (k - 1))]);

                    stMin[k][i] =
                        min(stMin[k - 1][i],
                            stMin[k - 1][i + (1 << (k - 1))]);
                }
            }
        }

        int getMax(int l, int r) {
            int k = lg[r - l + 1];
            return max(stMax[k][l],
                       stMax[k][r - (1 << k) + 1]);
        }

        int getMin(int l, int r) {
            int k = lg[r - l + 1];
            return min(stMin[k][l],
                       stMin[k][r - (1 << k) + 1]);
        }
    };

    struct Node {
        ll val;
        int l, r;

        bool operator<(const Node& other) const {
            return val < other.val;
        }
    };

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();

        SparseTable sp(nums);

        auto rangeValue = [&](int l, int r) -> ll {
            return (ll)sp.getMax(l, r) - sp.getMin(l, r);
        };

        priority_queue<Node> pq;

        for (int l = 0; l < n; l++) {
            pq.push({rangeValue(l, n - 1), l, n - 1});
        }

        ll ans = 0;

        while (k--) {
            auto cur = pq.top();
            pq.pop();

            ans += cur.val;

            int l = cur.l;
            int r = cur.r;

            if (l < r) {
                pq.push({rangeValue(l, r - 1), l, r - 1});
            }
        }

        return ans;
    }
};
