class Solution {
public:
    struct Node {
        long long ways;
        long long sum;
    };

    string s;
    Node dp[20][2][3][11][11];
    bool vis[20][2][3][11][11];

    Node dfs(int pos, int started, int len,
             int prev2, int prev1, bool tight) {

        if (pos == (int)s.size())
            return {1, 0};

        if (!tight && vis[pos][started][len][prev2][prev1])
            return dp[pos][started][len][prev2][prev1];

        int limit = tight ? s[pos] - '0' : 9;

        Node res = {0, 0};

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            if (!started && d == 0) {
                Node nxt = dfs(pos + 1, 0, 0, 10, 10, ntight);

                res.ways += nxt.ways;
                res.sum += nxt.sum;
            } else {
                if (!started) {
                    Node nxt = dfs(pos + 1, 1, 1, 10, d, ntight);

                    res.ways += nxt.ways;
                    res.sum += nxt.sum;
                }
                else if (len == 1) {
                    Node nxt = dfs(pos + 1, 1, 2, prev1, d, ntight);

                    res.ways += nxt.ways;
                    res.sum += nxt.sum;
                }
                else {
                    int add =
                        ((prev1 > prev2 && prev1 > d) ||
                         (prev1 < prev2 && prev1 < d));

                    Node nxt = dfs(pos + 1, 1, 2, prev1, d, ntight);

                    res.ways += nxt.ways;
                    res.sum += nxt.sum + 1LL * add * nxt.ways;
                }
            }
        }

        if (!tight) {
            vis[pos][started][len][prev2][prev1] = true;
            dp[pos][started][len][prev2][prev1] = res;
        }

        return res;
    }

    long long solve(long long n) {
        if (n < 0) return 0;

        s = to_string(n);
        memset(vis, 0, sizeof(vis));

        return dfs(0, 0, 0, 10, 10, true).sum;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
