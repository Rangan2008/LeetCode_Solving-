class Solution {
public:
    struct Node {
        long long cnt;
        long long wav;
    };

    string s;
    Node dp[20][2][11][11];
    bool vis[20][2][11][11];

    Node dfs(int pos, bool started, int prev1, int prev2, bool tight) {
        if (pos == (int)s.size()) {
            return {1, 0};
        }

        if (!tight && vis[pos][started][prev1][prev2])
            return dp[pos][started][prev1][prev2];

        int lim = tight ? (s[pos] - '0') : 9;

        Node res = {0, 0};

        for (int d = 0; d <= lim; d++) {
            bool ntight = tight && (d == lim);

            if (!started) {
                if (d == 0) {
                    Node nxt = dfs(pos + 1, false, 10, 10, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                } else {
                    Node nxt = dfs(pos + 1, true, d, 10, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                }
            } else {
                int add = 0;

                if (prev2 != 10) {
                    bool peak = (prev1 > prev2 && prev1 > d);
                    bool valley = (prev1 < prev2 && prev1 < d);
                    add = peak || valley;
                }

                int nprev2 = (prev2 == 10 ? prev1 : prev1);
                int nprev1 = d;

                Node nxt = dfs(pos + 1, true, nprev1, nprev2, ntight);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav + nxt.cnt * add;
            }
        }

        if (!tight) {
            vis[pos][started][prev1][prev2] = true;
            dp[pos][started][prev1][prev2] = res;
        }

        return res;
    }

    long long solve(long long x) {
        if (x < 0) return 0;

        s = to_string(x);
        memset(vis, 0, sizeof(vis));

        Node ans = dfs(0, false, 10, 10, true);
        return ans.wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
